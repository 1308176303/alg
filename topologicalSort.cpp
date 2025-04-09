#include<iostream>
#include<vector>
using namespace std;

int a, b; // 点数，边数
int *result; 
int **matrix; // 邻接矩阵
int *rdegree;
int *visit;
int count = 1;
bool has_cycle = false;
bool *in_stack;

void topo_sort(int n)
{
    if(has_cycle) return; // 如果已经发现有环，直接返回

    if(rdegree[n]==0) // 入度为0
    {
        result[count++]=n;
        visit[n]=1;
        for(int i=1;i<=a;i++)
        {
            if(matrix[n][i]== 1)
            {
                rdegree[i]--;
            }
        }
        return;
    }


    in_stack[n] = true; // 标记节点n在递归栈中
    
    //处理找的到指向该点的所有点，如果入度为0就直接加入结果，否则递归调用这个函数处理那个父节点
    //如果无法完成拓扑排序，则输出Impossible!
    for(int i=1; i<=a; i++)
    {
        if(matrix[i][n] == 1 && visit[i] == 0)
        {
            if(in_stack[i]) // 如果该前驱节点在递归栈中，说明有环
            {
                has_cycle = true;
                return;
            }
            topo_sort(i);
            if(has_cycle) return;
        }
    }   
    in_stack[n] = false;
    if(rdegree[n] == 0 && visit[n] == 0)
    {
        result[count++] = n;
        visit[n] = 1;
        for(int i=1; i<=a; i++)
        {
            if(matrix[n][i] == 1)
            {
                rdegree[i]--;
            }
        }
    }

    
}

int main()
{
    int n; // 组数
    cin >> n;
    for(int i = 1; i <= n; i++)
    {
        cin >> a >> b;
        rdegree = new int[a+1](); // 存每个节点的入度
        result = new int[a+1];
        visit = new int[a+1];
        has_cycle = false; 
        matrix = new int*[a+1];
        in_stack = new bool[a+1]();
        for(int j=1; j<=a; j++) {
            in_stack[j] = false;
        }
        for(int j = 1; j <= a; j++)
        {
            matrix[j] = new int[a+1]();
        }
        for(int j=1;j<=a;j++)
        {
            visit[j]=0;
        }
        
        // 初始化邻接矩阵
        for(int j = 1; j <= a; j++)
            for(int k = 1; k <= a; k++)
                matrix[j][k] = 0;
        
        // 读取边并更新入度
        for(int j = 1; j <= b; j++)
        {
            int x, y;
            cin >> x >> y; // x->y
            matrix[x][y] = 1;
            rdegree[y]++; // y的入度加1
        }
        
        int j =1;
        topo_sort(j); // 无解的时候输出Impossible!
        j++;
        while(j<=a&& !has_cycle)
        {
            if(visit[j])
            {
                j++;
                continue;
            }
            else
            {
                topo_sort(j);
                j++;
            }
        }

        bool all_visited = true;
        for(int j=1; j<=a; j++)
        {
            if(visit[j] == 0)
            {
                all_visited = false;
                break;
            }
        }

        if(has_cycle || !all_visited)
        {
            cout << "Impossible!" << endl;
        }
        else
        {
            for(int j=1; j<count; j++)
            {
                cout << result[j];
                if(j < count-1) cout << " ";
            }
            cout << endl;
        }
        
        // 重置计数器
        count = 1;

        // 释放内存
        delete[] rdegree;
        delete[] result;
        delete[] visit;
        delete[] in_stack;
        for(int j = 1; j <= a; j++) {
            delete[] matrix[j];
        }
        delete[] matrix;
    }
    return 0;
}