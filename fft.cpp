#include <iostream>
#include <complex>

using namespace std;

const double PI = acos(-1.0);

void fft(complex<double>* a, int n, bool flag) {
    if (n == 1) return;

    complex<double>* a0 = new complex<double>[n / 2];
    complex<double>* a1 = new complex<double>[n / 2];
    for (int i = 0; i < n / 2; ++i) {
        a0[i] = a[i * 2];
        a1[i] = a[i * 2 + 1];
    }

    fft(a0, n / 2, flag);
    fft(a1, n / 2, flag);

    double ang = 2 * PI / n * (flag ? -1 : 1);
    complex<double> wn(cos(ang), sin(ang)), w(1);

    for (int i = 0; i < n / 2; ++i) {
        complex<double> u = a0[i];
        complex<double> v = w * a1[i];
        a[i] = u + v;
        a[i + n / 2] = u - v;
        w *= wn;
    }

    if (flag) {
        for (int i = 0; i < n; ++i)
            a[i] /= 2;
    }

    delete[] a0;
    delete[] a1;
}
void deal(int* a, int lena, int* b, int lenb, int* res) {
    int n = 1;
    while (n < lena + lenb - 1) 
        n *= 2;

    complex<double>* a1 = new complex<double>[n];
    complex<double>* b1 = new complex<double>[n];

    //把多项式系数作为实部赋给复数
    for (int i = 0; i < n; ++i) {
        if (i < lena)
            a1[i] = complex<double>(a[i], 0);
        else
            a1[i] = complex<double>(0, 0);
    
        if (i < lenb)
            b1[i] = complex<double>(b[i], 0);
        else
            b1[i] = complex<double>(0, 0);
    }

    //fft变换
    fft(a1, n, false);
    fft(b1, n, false);

    for (int i = 0; i < n; ++i)
        a1[i] *= b1[i];

    //反变换
    fft(a1, n, true);

    for (int i = 0; i < lena + lenb - 1; ++i) {
        double val = a1[i].real();
        int intval;
        //四舍五入
        if (val >= 0)
            intval = (int)(val + 0.5);
        else
            intval = (int)(val - 0.5);
        res[i] = intval;
    }

    delete[] a1;
    delete[] b1;
}

int main() {
    int n, m;
    cin >> n >> m;

    int* a = new int[n + 1];
    int* b = new int[m + 1];

    for (int i = 0; i <= n; i++) cin >> a[i];
    for (int i = 0; i <= m; i++) cin >> b[i];

    int finalsize = n + m + 1;
    int* result = new int[finalsize];

    //0到n,一共n+1项
    deal(a, n + 1, b, m + 1, result);

    for (int i = 0; i < finalsize; ++i) {
        cout << result[i] <<  " " ;
    }
    cout << endl;

    delete[] a;
    delete[] b;
    delete[] result;

    return 0;
}