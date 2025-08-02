#include <iostream>
#include <complex>

using namespace std;

// 定义圆周率常量，用于计算单位根
const double PI = acos(-1.0);

/**
 * 递归实现的快速傅里叶变换（FFT）和逆变换（IFFT）
 * @param a     复数数组，表示多项式系数（实部为系数，虚部为0）
 * @param n     数组长度，必须为2的幂
 * @param flag  false表示FFT，true表示IFFT
 */
void fft(complex<double>* a, int n, bool flag)
{
    if (n == 1)
        return;

    // 分治：将偶数下标和奇数下标的元素分别存入a0和a1
    complex<double>* a0 = new complex<double>[n / 2];
    complex<double>* a1 = new complex<double>[n / 2];
    for (int i = 0; i < n / 2; ++i)
    {
        a0[i] = a[i * 2];       // 偶数下标
        a1[i] = a[i * 2 + 1];   // 奇数下标
    }

    // 递归处理偶数和奇数部分
    fft(a0, n / 2, flag);
    fft(a1, n / 2, flag);

    // 计算单位根，flag为true时取负号用于逆变换
    double ang = 2 * PI / n * (flag ? -1 : 1);
    complex<double> wn(cos(ang), sin(ang)), w(1);

    // 蝶形运算，合并结果
    for (int i = 0; i < n / 2; ++i)
    {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        w *= wn;
    }

    // 逆变换时需要每项除以2
    if (flag)
    {
        for (int i = 0; i < n; ++i)
        {
            a[i] /= 2;
        }
    }

    // 释放临时数组
    delete[] a0;
    delete[] a1;
}

/**
 * 多项式乘法，利用FFT实现
 * @param a     第一个多项式的系数数组
 * @param lena  第一个多项式的项数
 * @param b     第二个多项式的系数数组
 * @param lenb  第二个多项式的项数
 * @param res   存放结果多项式系数的数组
 */
void deal(int* a, int lena, int* b, int lenb, int* res)
{
    // 计算卷积结果的最小2的幂长度
    int n = 1;
    while (n < lena + lenb - 1)
    {
        n *= 2;
    }

    // 分配复数数组，初始化为0
    complex<double>* a1 = new complex<double>[n];
    complex<double>* b1 = new complex<double>[n];

    // 把多项式系数赋值到复数数组的实部，虚部为0
    for (int i = 0; i < n; ++i)
    {
        if (i < lena)
        {
            a1[i] = complex<double>(a[i], 0);
        }
        else
        {
            a1[i] = complex<double>(0, 0);
        }

        if (i < lenb)
        {
            b1[i] = complex<double>(b[i], 0);
        }
        else
        {
            b1[i] = complex<double>(0, 0);
        }
    }

    // 对两个多项式分别做FFT
    fft(a1, n, false);
    fft(b1, n, false);

    // 逐项相乘（频域卷积）
    for (int i = 0; i < n; ++i)
    {
        a1[i] *= b1[i];
    }

    // 逆FFT变换回时域
    fft(a1, n, true);

    // 取实部并四舍五入，得到最终多项式系数
    for (int i = 0; i < lena + lenb - 1; ++i)
    {
        double val = a1[i].real();
        int intval;
        if (val >= 0)
        {
            intval = (int)(val + 0.5);
        }
        else
        {
            intval = (int)(val - 0.5);
        }
        res[i] = intval;
    }

    // 释放内存
    delete[] a1;
    delete[] b1;
}

int main()
{
    int n, m;
    cin >> n >> m;

    int* a = new int[n + 1];
    int* b = new int[m + 1];

    // 输入第一个多项式的系数（从x^0到x^n）
    for (int i = 0; i <= n; ++i)
    {
        cin >> a[i];
    }
    // 输入第二个多项式的系数（从x^0到x^m）
    for (int i = 0; i <= m; ++i)
    {
        cin >> b[i];
    }

    int finalsize = n + m + 1; // 结果多项式的项数
    int* result = new int[finalsize];

    // 计算多项式乘积
    deal(a, n + 1, b, m + 1, result);

    // 输出结果多项式的系数
    for (int i = 0; i < finalsize - 1; ++i)
    {
        cout << result[i] << " ";
    }
    cout << result[finalsize - 1] << endl; // 输出最后一项

    // 释放内存
    delete[] a;
    delete[] b;
    delete[] result;

    return 0;
}