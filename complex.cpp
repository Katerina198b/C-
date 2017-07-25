class C {    
    public:
        double re, im;
        C () {
            re = 0;
            im = 0;
        }
        C (double r, double m) {
           re = r;
           im = m;
        };
        C (const double &re) {
           this->re = re;
           im = 0;
        };
        C (const C &c) {
           re = c.re;
           im = c.im;
        };
        double abs () {
            return sqrt(re*re + im*im);
        };
        
        C operator+ (C c) {
            return C(c.re + re, c.im + im);
        };
        C operator- (C c) {
            return C(re - c.re, im - c.im);
        };
        C operator* (C c) {
            return C(c.re*re - c.im*im, re*c.im + im*c.re);
        }
        C operator / (C c) {
            return C((c.re*re + c.im*im)/(c.im*c.im + c.re*c.re), (im*c.re - re*c.im)/(c.im*c.im + c.re*c.re));
        }
        int operator== (C c) {
            double eps = 0.00000001;
            return ((::abs(c.re - re) < eps) && (::abs(c.im - im) < eps)); 
        }
        int operator!= (C c) {
            double eps = 0.00000001;
            return ((::abs(c.re - re) > eps) || (::abs(c.im - im) > eps));
        }
        friend std::ostream & operator <<( std::ostream &os, const C &c )
        {
            return os << c.re << " " << c.im;
        }
};

C operator+ (double left, C right) {
    return right + left;
};
C operator- (double left, C c) {
    return C(left - c.re, 0 - c.im);
};
C operator* (double left, C right) {
    return right * left;
};
C operator/ (double re, C c) {
    return C((c.re*re)/(c.re*c.re + c.im*c.im), (-re*c.im)/(c.re*c.re + c.im*c.im));
};
int operator== (double left, C right) {
    return right == left;
};
int operator!= (double left, C right) {
    return right != left;
};
