#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int x, y, c, id;
};

bool compareEdges(const Edge &a, const Edge &b) {
    if (a.c != b.c) {
        return a.c < b.c;
    } else {
        return a.id < b.id;
    }
}

class UnionFind {
private:
    vector<int> parent;
    //该点为根的集合的大小(高度)
    vector<int> rank;
public:
    UnionFind(int size) {
        parent.resize(size + 1);
        
        rank.resize(size + 1, 1);
        //初始化所有根节点的父亲为自己
        for (int i = 0; i <= size; ++i) {
            parent[i] = i;
        }
    }

    //找到u的祖先
    int find(int u) {
        //父亲不是自己的节点就是中间节点,需要递归寻找祖先根
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    bool unite(int u, int v) {
        //u的祖先
        int uRoot = find(u);
        //v的祖先
        int vRoot = find(v);
        //如果u和v的祖先相同，说明已经在同一集合中
        if (uRoot == vRoot) {
            return false;
        }
        //小的集合合并到大的里
        if (rank[uRoot] > rank[vRoot]) {
            parent[vRoot] = uRoot;
            rank[uRoot] += rank[vRoot];
        } else {
            parent[uRoot] = vRoot;
            rank[vRoot] += rank[uRoot];
        }
        return true;
    }
};

int main() {
    

    int N, M;
    cin >> N >> M;
    vector<Edge> edges(M);
    for (int i = 0; i < M; ++i) {
        cin >> edges[i].x >> edges[i].y >> edges[i].c;
        //id从1开始
        edges[i].id = i + 1;
    }

    //从小到大升序排,优先边权值,再看id(字典序)
    sort(edges.begin(), edges.end(), compareEdges);

    UnionFind uf(N);
    long long total_weight = 0;
    int total_xor = 0;
    int edge_count = 0;

    for (const auto &edge : edges) {
        if (uf.unite(edge.x, edge.y)) {
            total_weight += edge.c;
            total_xor ^= edge.id;
            edge_count++;
            if (edge_count == N - 1) {
                break;
            }
        }
    }

    if (edge_count != N - 1) {
        cout << -1 << '\n';
    } else {
        cout << total_weight << ' ' << total_xor << '\n';
    }

    return 0;
}