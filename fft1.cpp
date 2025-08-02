/**
 * FFT多项式乘法实现
 * 使用递归FFT算法计算两个多项式的卷积
 */
#include <iostream>
#include <complex>
#include <cmath>

using namespace std;
using cp = complex<double>;  // 复数类型别名，简化代码
const double PI = acos(-1.0);  // 精确计算PI值

/**
 * 计算 n 次单位根的第 k 项
 * @param n  单位根的阶数
 * @param k  第k个单位根
 * @return   对应的复数 e^(2πik/n)
 */
cp omega(int n, int k)
{
    double ang = 2 * PI * k / n;  // 计算角度：2π*k/n
    return cp(cos(ang), sin(ang));  // 返回复数: cos(θ) + i·sin(θ)
}

/**
 * 递归实现的快速傅里叶变换和逆变换
 * @param a    复数数组，表示多项式系数
 * @param n    数组长度，必须是2的幂
 * @param inv  变换方向: false表示正变换，true表示逆变换
 */
void fft(cp *a, int n, bool inv)
{
    // 递归基（长度为1时，无需变换）
    if (n == 1)
        return;

    // 分配临时缓冲区
    cp* buf = new cp[n];  // 使用动态分配避免静态数组的递归冲突
    int m = n / 2;  // 分治：一半长度

    // 步骤1: 奇偶拆分 - 按照下标奇偶性将数组分成两半
    for (int i = 0; i < m; ++i)
    {
        buf[i]   = a[2 * i];     // 偶数下标
        buf[i+m] = a[2 * i + 1]; // 奇数下标
    }
    // 复制回原数组，为递归做准备
    for (int i = 0; i < n; ++i)
        a[i] = buf[i];

    // 步骤2: 递归处理两个子问题
    fft(a,     m, inv);  // 处理偶数部分
    fft(a + m, m, inv);  // 处理奇数部分

    // 步骤3: 蝶形合并 - 组合两个子问题的结果
    for (int i = 0; i < m; ++i)
    {
        cp w = omega(n, i);  // 计算当前旋转因子
        if (inv) w = conj(w);  // 逆变换用共轭复数（负角度）
        cp t = w * a[i + m];   // 旋转奇数部分
        buf[i]   = a[i] + t;   // 蝶形运算: 上半部分
        buf[i+m] = a[i] - t;   // 蝶形运算: 下半部分
    }
    // 复制回原数组
    for (int i = 0; i < n; ++i)
        a[i] = buf[i];

    // 释放临时缓冲区
    delete[] buf;
}

int main()
{
    int n, m;  // n和m分别是两个多项式的次数
    cin >> n >> m;
    
    // 计算结果多项式所需长度，并找到不小于该长度的最小2的幂
    int len = n + m + 1;  // 两个多项式乘积的系数个数
    int N = 1;
    while (N < len) N <<= 1;  // 计算大于len的最小2的幂

    // 分配空间并初始化为0
    cp* fA = new cp[N]();  // 第一个多项式的系数
    cp* fB = new cp[N]();  // 第二个多项式的系数

    // 读入A多项式的系数 (从高到低)
    for (int i = 0; i <= n; ++i)
    {
        int coef;
        cin >> coef;
        fA[i] = cp(coef, 0);  // 实部为系数，虚部为0
    }

    // 读入B多项式的系数 (从高到低)
    for (int i = 0; i <= m; ++i)
    {
        int coef;
        cin >> coef;
        fB[i] = cp(coef, 0);  // 实部为系数，虚部为0
    }

    // 对两个多项式进行快速傅里叶变换 (FFT)
    fft(fA, N, false);  // 正变换
    fft(fB, N, false);  // 正变换

    // 点乘运算 (频域相乘等价于时域卷积)
    for (int i = 0; i < N; ++i)
        fA[i] *= fB[i];  // 频域点乘

    // 逆变换 (IFFT) 将结果从频域转回时域
    fft(fA, N, true);  // 逆变换
    
    // 逆变换需要除以N进行归一化
    for (int i = 0; i < N; ++i)
        fA[i] /= N;

    // 输出结果 (按题目要求从高到低输出)
    for (int i = 0; i <= n+m; ++i)
    {
        int coeff = round(fA[i].real());  // 四舍五入取整
        cout << coeff;
        if (i < n+m) cout << " ";  // 除最后一个数外，后面都跟空格
    }
    //cout << endl;

    // 释放动态分配的内存
    delete[] fA;
    delete[] fB;
    return 0;
}