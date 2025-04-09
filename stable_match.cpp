#include <iostream>
using namespace std;

// gs稳定匹配算法
int main() {
    // 初始化
    int n;
    cin >> n;

    // 男性偏好
    int **man = new int*[n+1];
    for (int i = 0; i <= n; i++) {
        man[i] = new int[n+1];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> man[i][j];
        }
    }

    // 女性偏好
    int **woman = new int*[n+1];
    for (int i = 0; i <= n; i++) {
        woman[i] = new int[n+1];
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> woman[i][j];
        }
    }

    // 匹配结果
    int *res = new int[n+1];  // 匹配结果
    bool *w = new bool[n+1];  // 女性是否已经匹配
    for (int i = 1; i <= n; i++) {
        res[i] = -1;  // -1表示还未匹配
        w[i] = false;
    }

    // 匹配过程
    int *procnt = new int[n+1]();  // 男性求婚次数，初始化为0
    bool flag = true;  // 是否还有男性未匹配
    while (flag) {
        int curMan = -1;
        for (int i = 1; i <= n; i++) {
            // 找到一个还没匹配的男人
            if (res[i] == -1) {
                curMan = i;
                break;
            }
        }
        // 都已经匹配就退出循环
        if (curMan == -1) {
            flag = false;
            break;
        }
        int curWo = man[curMan][++procnt[curMan]];  // 当前男人想要求婚的女人
        if (!w[curWo]) {
            w[curWo] = true;
            res[curMan] = curWo;
        } 
        else 
        {
            // 已配对的话就看m和m’
            int curPar = -1;
            for (int i = 1; i <= n; i++) {
                if (res[i] == curWo) {
                    curPar = i;
                    break;
                }
            }

            for (int i = 1; i <= n; i++) {
                //先遇到curPar的话就break
            	if (woman[curWo][i] == curPar) break;
                if (woman[curWo][i] == curMan)
                {
                    res[curMan] = curWo;
                    res[curPar] = -1;
                    break;
                }
                
            }
        }
    }

    // 输出匹配结果
    for (int i = 1; i < n; i++) {
        cout << res[i] << " ";
    }
    cout << res[n] ;

    // 释放内存
    for (int i = 0; i < n; i++) {
        delete[] man[i];
        delete[] woman[i];
    }
    delete[] man;
    delete[] woman;
    delete[] res;
    delete[] w;
    delete[] procnt;

    return 0;
}
