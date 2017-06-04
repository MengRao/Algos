#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <Sort.h>

using namespace std;

#define MAXEVENTS 64

static int
make_socket_non_blocking(int sfd)
{
  int flags, s;

  flags = fcntl(sfd, F_GETFL, 0);
  if (flags == -1)
  {
    return -1;
  }

  flags |= O_NONBLOCK;
  s = fcntl(sfd, F_SETFL, flags);
  if (s == -1)
  {
    return -1;
  }

  return 0;
}

static int
create_and_bind(char *port)
{
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int s, sfd;

  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;     
  hints.ai_socktype = SOCK_STREAM; 
  hints.ai_flags = AI_PASSIVE;

  s = getaddrinfo(NULL, port, &hints, &result);
  if (s != 0)
  {
    return -1;
  }

  for (rp = result; rp != NULL; rp = rp->ai_next)
  {
    sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
    if (sfd == -1)
      continue;

    s = bind(sfd, rp->ai_addr, rp->ai_addrlen);
    if (s == 0)
    {
      break;
    }

    close(sfd);
  }

  if (rp == NULL)
  {
    return -1;
  }

  freeaddrinfo(result);

  return sfd;
}

int
main(int argc, char *argv[])
{
  ios::sync_with_stdio(false);

  int sfd, s;
  int efd;
  struct epoll_event event;
  struct epoll_event events[MAXEVENTS];

  if (argc != 2)
  {
    cout << "Usage: " << argv[0] << " <port>" << endl;
    exit(1);
  }

  sfd = create_and_bind(argv[1]);
  if (sfd == -1)
    abort();

  s = make_socket_non_blocking(sfd);
  if (s == -1)
    abort();

  s = listen(sfd, SOMAXCONN);
  if (s == -1)
  {
    abort();
  }

  efd = epoll_create1(0);
  if (efd == -1)
  {
    abort();
  }

  event.data.fd = sfd;
  event.events = EPOLLIN | EPOLLET;
  s = epoll_ctl(efd, EPOLL_CTL_ADD, sfd, &event);
  if (s == -1)
  {
    abort();
  }

  Sort<100> st;

  while (1)
  {
    int n, i;

    n = epoll_wait(efd, events, MAXEVENTS, -1);
    for (i = 0; i < n; i++)
    {
      if ((events[i].events & EPOLLERR) ||
        (events[i].events & EPOLLHUP) ||
        (!(events[i].events & EPOLLIN)))
      {
        close(events[i].data.fd);
        continue;
      }

      else if (sfd == events[i].data.fd)
      {
        while (1)
        {
          struct sockaddr in_addr;
          socklen_t in_len;
          int infd;

          in_len = sizeof in_addr;
          infd = accept(sfd, &in_addr, &in_len);
          if (infd == -1)
          {
            break;
          }

          s = make_socket_non_blocking(infd);
          if (s == -1)
            abort();

          event.data.fd = infd;
          event.events = EPOLLIN | EPOLLET;
          s = epoll_ctl(efd, EPOLL_CTL_ADD, infd, &event);
          if (s == -1)
          {
            abort();
          }
        }
        continue;
      }
      else
      {
        while (1)
        {
          ssize_t count;
          char buf[12];

          count = read(events[i].data.fd, buf, 12);

          if (count == -1 && errno == EAGAIN)
          {
            break;
          }
          else if (count != 12)
          {
            close(events[i].data.fd);
            break;
          }

          if (!st.recv(*(uint*)buf, *(ull*)(buf + 4))) {
            return 0;
          }
        }

      }
    }
  }

  close(sfd);

  return 0;
}