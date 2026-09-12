using point = complex<double>;
struct mec{
    array<point,3> z;
    int sz;
    mec(point &a,point &b,point &c){
        z[0] = a, z[1] = b, z[2] = c, sz = 3;
    }
    mec(point &a,point &b){
        z[0] = a, z[1] = b, sz = 2;
    }
};

/* I < 0 if z inside C,
   I > 0 if z outside C,
   I = 0 if z on the circumference of C */
double indicator(mec const& C, point z) {
    auto visit([&](auto &&C) {
        point a = C.z[0], b = C.z[1];
        point I0 = (b - z) * conj(a - z);
        if  (C.sz == 2) {
            return real(I0);
        } else {
            point c = C.z[2];
            point I2 = (a - c) * conj(b - c);
            point I1 = I0 * I2;
            return imag(I2) < 0 ? -imag(I1) : imag(I1);
        }
    });
    return visit(C);
}

bool inside(mec const& C, point p) {
    return indicator(C, p) <= 0;
}
random_device rd;
mt19937_64 gen(rd());
// o(n)
mec enclosing_circle(vector<point> &p) {
    int n = p.size();
    ranges::shuffle(p, gen);
    auto C = mec{p[0], p[1]};
    for(int i = 0; i < n; i++) {
        if(!inside(C, p[i])) {
            C = mec{p[i], p[0]};
            for(int j = 0; j < i; j++) {
                if(!inside(C, p[j])) {
                    C = mec{p[i], p[j]};
                    for(int k = 0; k < j; k++) {
                        if(!inside(C, p[k])) {
                            C = mec{p[i], p[j], p[k]};
                        }
                    }
                }
            }
        }
    }
    return C;
}
Point x;
x = {1,2};
