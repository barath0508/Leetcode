class Fancy {
    static const long long MOD = 1000000007;
    vector<long long> base;
    long long mul, add;

    long long modPow(long long a, long long e) {
        long long r = 1;
        a %= MOD;
        while (e > 0) {
            if (e & 1) r = r * a % MOD;
            a = a * a % MOD;
            e >>= 1;
        }
        return r;
    }

public:
    Fancy() {
        mul = 1;
        add = 0;
    }

    void append(int val) {
        long long v = val;
        long long tmp = (v - add) % MOD;
        if (tmp < 0) tmp += MOD;
        long long mul_inv = modPow(mul, MOD - 2);
        long long x = tmp * mul_inv % MOD;
        base.push_back(x);
    }

    void addAll(int inc) {
        add = (add + inc) % MOD;
    }

    void multAll(int m) {
        mul = mul * m % MOD;
        add = add * m % MOD;
    }

    int getIndex(int idx) {
        if (idx < 0 || idx >= (int)base.size()) return -1;
        long long x = base[idx];
        long long res = (x * mul + add) % MOD;
        return (int)res;
    }
};
