using ld = long double;
const ld pi = acos(-1);
using cd = complex<double>;

struct FFT {
    void fft(vector<cd> &a, bool inv) {
        int n = a.size();
        // bit reversal sort
        // 101-->011  بنزود من ورا
        for (int i = 0, j = 0; i < n; ++i) {
            if (i < j)swap(a[i], a[j]);
            ll bit = n >> 1;

            //++j
            for (; j & bit; bit >>= 1)j ^= bit;
            j ^= bit;
        }

        for (int len = 2; len <= n; len <<= 1) {
            ld ang = 2 * pi / len;
            cd w1(cos(ang), sin(ang) * (inv ? -1 : 1));


            for (int i = 0; i < n; i += len) {
                cd w(1, 0);

                for (ll j = 0; j < len / 2; ++j) {
                    auto temp = a[i + j];
                    /*even*/
                    a[i + j] = a[i + j] + w * a[i + j + len / 2];
                    /*odd*/
                    a[i + j + len / 2] = temp - w * a[i + j + len / 2];

                    w *= w1;
                }
            }
        }
        if (inv)
            for (auto &i: a)i /= n;


        // fft(even, inv);
        // fft(odd, inv);
        //
        // ld ang = 2 * pi / n;
        //
        // cd w(1, 0), w1(cos(ang), sin(ang) * (inv ? -1 : 1));
        //
        // for (int i = 0; i < n / 2; i++) {
        //     a[i] = even[i] + w * odd[i];
        //     a[i + n / 2] = even[i] - w * odd[i];
        //     w *= w1;
        //
        //     if (inv) {
        //         // n power of 2 and we iterate over log level <==> a[i]/=n;
        //         a[i] /= 2;
        //         a[i + n / 2] /= 2;
        //     }
        // }
    }

    auto mul(vector<ll> &a, vector<ll> &b) {
        vector<cd> fa(all(a)), fb(all(b));
        ll sz = 1;
        while (a.size() + b.size() > sz)sz <<= 1;

        fa.resize(sz), fb.resize(sz);

        fft(fa, 0), fft(fb, 0);

        for (int i = 0; i < sz; i++) {
            fa[i] *= fb[i];
        }

        fft(fa, 1);
        vector<ll> ret(sz);

        for (int i = 0; i < sz; i++) {
            ret[i] = round(fa[i].real());
        }

        return ret;
    }
};
