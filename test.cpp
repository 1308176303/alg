#include<iostream>
using namespace std;
int main(){
    int n;
    cin>>n;
    int *A = new int[n+1]; // 假设A已经赋值完毕
    for (int i = 0; i < n; i++)
    {
        cin>>A[i];
    }
    int q ;
    cin>>q;
    int l = -1, r = n, m;
    while (r - l > 1) {
        m = (l + r) / 2;
        if (A[m] >= q) r = m; else l = m;
    }
    if (A[r] == q) cout << r; 
    else cout << -1;
    return 0;
}