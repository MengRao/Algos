// Palindrome tree. Useful structure to deal with palindromes in strings, constructed in O(N)
//
// This code finds all distinct palindrome substrings and count their number of occurrences in O(N)
//
#include <stdio.h>
#include <string.h>
#include <vector>
using namespace std;
#define mod 1000000007
#define nchars 8

struct Node {
    Node *nexts[nchars];
    Node *suffix;
    long long count;
    int length;
    Node(int length, Node *suffix = NULL) : length(length) {
        this->suffix = suffix ? suffix : this;
        for (int i = 0; i < nchars; i++) nexts[i] = NULL;
        count = 0;
    }
};

Node* nodes[100011];
char _s[100011];
char *s = _s + 1;
int main() {
    scanf("%s", s);
    int n = strlen(s);
    s[-1] = nchars;

    Node *r0 = new Node(0, new Node(-1));
    Node *curr = r0;

    int nodec = 0;
    for (int i = 0; i < n; i++) {
        s[i] -= 'a';
        #define proceed(node) do {\
            while (s[i-node->length-1] != s[i]) node = node->suffix;\
        } while (0)

        proceed(curr);
        if (!curr->nexts[s[i]]) {
            Node *suffix;
            if (~curr->length) {
                suffix = curr->suffix;
                proceed(suffix);
                suffix = suffix->nexts[s[i]];
            } else {
                suffix = r0;
            }
            nodes[nodec++] = curr->nexts[s[i]] = new Node(curr->length + 2, suffix);
        }

        curr = curr->nexts[s[i]];
        curr->count++;
    }

    long long t = 0;
    while (nodec--) {
        Node *node = nodes[nodec];
        node->suffix->count += node->count;
        t += node->count * (node->count - 1);
        t %= mod;
    }
    t = t * (mod+1 >> 1) % mod;
    printf("%lld\n", t);
}