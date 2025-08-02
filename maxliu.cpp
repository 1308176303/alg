#include <cstdio>
#include <cstring>

const int MAXN = 205;

// 用于二分图匹配的边结构体
struct Edge {
    int destination;     // 边的终点
    int next;   // 下一条边的索引（链表结构）
} edge[6005];

// 二分图匹配相关变量
int head[MAXN];    // 邻接表头指针数组
int count11;           // 边的计数器
int match[MAXN];   // 匹配数组：match[v] = u 表示右部点v匹配到左部点u
bool visit[MAXN];    // DFS访问标记数组
int n, m;          // n个顶点，m条边

// 向二分图中添加一条边 u -> v
void addEdge(int u, int v) {
    edge[count11].destination = v;              // 设置边的终点
    edge[count11].next = head[u];      // 链接到之前的边
    head[u] = count11++;               // 更新头指针并递增计数器
}

// 匈牙利算法的DFS部分：为左部点u寻找增广路径
bool dfs(int u) {
    // 遍历从u出发的所有边
    for (int i = head[u]; i != -1; i = edge[i].next) {
        int v = edge[i].destination;        // 获取边的终点v
        
        if (!visit[v]) {             // 如果右部点v未被访问
            visit[v] = true;         // 标记v为已访问
            
            // 如果v未匹配，或者v的当前匹配点可以找到新的匹配
            if (match[v] == -1 || dfs(match[v])) {
                match[v] = u;      // 建立新的匹配关系
                return true;       // 找到增广路径
            }
        }
    }
    return false;                  // 未找到增广路径
}

// 匈牙利算法主函数：求二分图的最大匹配
int getmax() {
    int result = 0;
    
    // 对每个左部点尝试寻找匹配
    for (int i = 1; i <= n; i++) {
        // 重置访问标记数组
        for (int j = 1; j <= n; j++) {
            visit[j] = false;
        }
        
        // 如果找到增广路径，匹配数加1
        if (dfs(i)) {
            result++;
        }
    }
    return result;
}

// 原图的邻接表结构体（实际上在这个版本中未使用）
struct linjiebiao {
    int destination, next;
} origEdge[6005];

// 原图相关变量
int origHead[MAXN], originCount;      // 原图邻接表头指针和边计数器
bool hasRu[MAXN];           // 标记节点是否有入边
int pathStart[MAXN], pathNext[MAXN];  // pathNext[u] = v 表示在路径中u的下一个节点是v
bool inPath[MAXN];                // 标记节点是否已经在某条路径中

// 向原图中添加一条边（虽然定义了但实际未被有效使用）
void addOriginEdge(int u, int v) {
    origEdge[originCount].destination = v;
    origEdge[originCount].next = origHead[u];
    origHead[u] = originCount++;
}

// 输出一条从start开始的路径
void displayResultPath(int start) {
    int path[MAXN], len = 0;
    int current = start;
    
    // 沿着pathNext链表收集路径上的所有节点
    while (current != -1) {
        path[len++] = current;         // 将当前节点加入路径
        current = pathNext[current];       // 移动到下一个节点
    }
    
    // 输出路径：先输出长度，再输出每个节点
    printf("%d", len);
    for (int i = 0; i < len; i++) {
        printf(" %d", path[i]);
    }
    printf("\n");
}

int main() {
    scanf("%d %d", &n, &m);
    
    // 初始化所有数组
    for (int i = 0; i <= n; i++) {
        head[i] = origHead[i] = -1;           // 邻接表头指针初始化为-1
        match[i] = pathNext[i] = -1;          // 匹配和路径数组初始化为-1
        hasRu[i] = inPath[i] = false;   // 布尔数组初始化为false
    }
    count11 = originCount = 0;                        // 边计数器初始化为0
    
    // 读取图的边信息
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(u, v);           // 添加到二分图（左部点u连向右部点v）
        addOriginEdge(u, v);       // 添加到原图（实际未使用）
        hasRu[v] = true;   // 标记v有入边
    }
    
    // 核心算法：最小路径覆盖 = 节点数 - 最大匹配数
    int matching = getmax();          // 求最大匹配
    int pathCount = n - matching;     // 计算最小路径数
    
    printf("%d\n", pathCount);        // 输出最小路径数
    
    // 根据匹配结果构造路径连接关系
    for (int v = 1; v <= n; v++) {
        if (match[v] != -1) {              // 如果右部点v有匹配
            pathNext[match[v]] = v;        // 在路径中，match[v]的下一个节点是v
            inPath[v] = true;              // 标记v已经在路径中
        }
    }
    
    // 找到所有路径的起点并输出完整路径
    for (int i = 1; i <= n; i++) {
        if (!inPath[i]) {                  // 如果节点i不在任何路径的中间或末尾
            displayResultPath(i);          // 说明i是某条路径的起点，输出这条路径
        }
    }
    
    return 0;
}