struct BigInteger
{
	static const int baselen = 9;
	static const int base = 1000000000;
	int sign; /* 1 if val >= 0, -1 otherwise */
	vector<uint32_t> num; /* each contains 10^9 */

	BigInteger() : sign(1), num(0) {}
	BigInteger(long long n) : sign(n >= 0 ? 1 : -1) {
		unsigned long long unum = n;
		if (sign == -1) unum = 0ull-unum;
		while (unum != 0) {
			num.push_back(unum % base);
			unum /= base;
		}
	}
  BigInteger(const string& str): sign(1){
    int end = 0;
    if(str[0]=='-'){
      sign = -1;
      end = 1;
    }
    int i = str.size()-1;
    if(i==end&&str[i]=='0') return;
    while(i>=end){
      int v = 0;
      int pos = 1;
      while(pos<base && i>=end){
        v += (str[i]-'0') * pos;
        pos *= 10;
        i--;
      }
      num.push_back(v);
    }

  }
	static int absoluteCmp(const vector<uint32_t> &n1, const vector<uint32_t> &n2) {
		if (n1.size() != n2.size()) {
      return n1.size() - n2.size();
		}
		for (auto i = n1.size(); i-- > 0; ) {
			if (n1[i] != n2[i]) return n1[i] - n2[i];
		}
		return 0;
	}
  int compare(const BigInteger &other) const {
    if(sign != other.sign) return sign - other.sign;
    return absoluteCmp(num, other.num) * sign;
  }
	bool operator < (const BigInteger &other) const {
    return compare(other) < 0;
	}
	bool operator <= (const BigInteger &other) const {
		return compare(other) <= 0;
	}
	bool operator > (const BigInteger &other) const {
		return compare(other) > 0;
	}
	bool operator >= (const BigInteger &other) const {
		return compare(other) >= 0;
	}
	bool operator == (const BigInteger &other) const {
		return compare(other) == 0;
	}
	bool operator != (const BigInteger &other) const {
		return compare(other) != 0;
	}
	static void add(BigInteger &dest, const vector<uint32_t> &n1, const vector<uint32_t> &n2) {
		dest.num.reserve(1 + max(n1.size(), n2.size()));
		uint32_t carry = 0;
		for (size_t i = 0; i < n1.size() || i < n2.size(); i++) {
			uint32_t cur = carry;
			if (i < n1.size()) cur += n1[i];
			if (i < n2.size()) cur += n2[i];
			if (cur >= base) {
				cur -= base;
				carry = 1;
			} else {
				carry = 0;
			}
			dest.num.push_back(cur);
		}
		if (carry) dest.num.push_back(carry);
	}
	static void subtract(BigInteger &dest, const vector<uint32_t> &n1, const vector<uint32_t> &n2) {
		const vector<uint32_t> *np1 = &n1, *np2 = &n2;
		dest.num.reserve(max(n1.size(), n2.size()));
		if (absoluteCmp(n1, n2) <= 0) {
			swap(np1, np2);
			dest.sign = -1;
		} else {
			dest.sign = 1;
		}
		int32_t carry = 0;
		for (size_t i = 0; i < np1->size() || i < np2->size(); i++) {
			int32_t cur = carry;
			if (i < np1->size()) cur += (*np1)[i];
			if (i < np2->size()) cur -= (*np2)[i];
			if (cur < 0) {
				cur += base;
				carry = -1;
			} else {
				carry = 0;
			}
			dest.num.push_back(cur);
		}
		while (dest.num.size() && dest.num.back() == 0) dest.num.pop_back();
	}

	static void multiply(BigInteger &dest, const vector<uint32_t> &n1, const vector<uint32_t> &n2) {
    dest.num.assign(n1.size() + n2.size(), 0);
		for (size_t i = 0; i < n1.size(); i++) {
			uint64_t carry = 0;
			for (size_t j = 0; j < n2.size(); j++) {
        carry += (uint64_t)n1[i] * n2[j] + dest.num[i+j];
        dest.num[i+j] = carry % base;
				carry /= base;
			}
			dest.num[i+n2.size()] += carry;
		}
    while (dest.num.size() && dest.num.back() == 0) dest.num.pop_back();
	}

	static void division(BigInteger &dest, const vector<uint32_t> &n1, const vector<uint32_t> &n2) {
		dest.num.clear();
		BigInteger remain(0);
		remain.num = n1;
		for (int k = n1.size()-n2.size(); k >= 0; k--)
		{
			BigInteger sub;
			sub.num.assign(k, 0);
			sub.num.insert(sub.num.end(), n2.begin(), n2.end());
			if (sub > remain) {
				if (dest.num.size()) dest.num.push_back(0);
				continue;
			}
			int low = 0, high = base - 1;
			while (low <= high) {
				int mid = low + high >> 1;
				BigInteger submul = sub * mid;
				if (submul <= remain) low = mid + 1;
				else high = mid - 1;
			}
			remain -= sub * high;
			dest.num.push_back(high);
		}
		reverse(dest.num.begin(), dest.num.end());
	}

	BigInteger operator + (const BigInteger &other) const {
		BigInteger ret;
		if (sign != other.sign) {
			subtract(ret, num, other.num);
			ret.sign *= sign;
		} else {
			add(ret, num, other.num);
			ret.sign = sign;
		}
		if (ret.num.empty()) ret.sign = 1;
		return ret;
	}
	BigInteger operator - (const BigInteger &other) const {
		BigInteger ret;
		if (sign == other.sign) {
			subtract(ret, num, other.num);
			ret.sign *= sign;
		} else {
			add(ret, num, other.num);
			ret.sign = sign;
		}
		if (ret.num.empty()) ret.sign = 1;
		return ret;
	}
	
	BigInteger operator * (const BigInteger &other) const {
		BigInteger ret;
		ret.sign = sign * other.sign;
		multiply(ret, num, other.num);
		if (ret.num.empty()) ret.sign = 1;
		return ret;
	}
	BigInteger operator / (const BigInteger &other) const {
		BigInteger ret;
		ret.sign = sign * other.sign;
		division(ret, num, other.num);
		if (ret.num.empty()) ret.sign = 1;
		return ret;
	}
	BigInteger operator % (const BigInteger &other) const {
		BigInteger val = *this;
		val -= other * (val / other);
		return val;
	}
	BigInteger &operator += (const BigInteger &other) {
		*this = *this + other;
		return *this;
	}
	BigInteger &operator -= (const BigInteger &other) {
		*this = *this - other;
		return *this;
	}
	BigInteger &operator *= (const BigInteger &other) {
		*this = *this * other;
		return *this;
	}
	BigInteger &operator /= (const BigInteger &other) {
		*this = *this / other;
		return *this;
	}
	BigInteger &operator %= (const BigInteger &other) {
		*this = *this % other;
		return *this;
	}
  string to_string() const {
		string res;
		res.reserve(num.size() * baselen + 2);
		if (sign == -1) res.push_back('-');
		int fzero = 1;
		for (auto i = num.size(); i-->0; ) {
			uint32_t v = num[i];
			int pos = base / 10;
			while (pos) {
				int digit = v / pos;
				v %= pos;
				pos /= 10;
				if (digit) fzero = 0;
				if (fzero == 0) res.push_back("0123456789"[digit]);
			}
		}
		if (fzero) res.push_back('0');
		return res;
	}
	long long to_int() const {
		long long res = 0, b = sign;
		for (int i = 0; i < num.size(); i++) {
			res += b * num[i];
			b *= base;
		}
		return res;
	}
  friend ostream& operator<<(ostream& o, const BigInteger& b) {
    return o << b.to_string();
  }
  friend istream& operator>>(istream& i, BigInteger& b) {
    string s; i >> s; b = BigInteger(s); return i;
  }
	
};
typedef BigInteger bint;
