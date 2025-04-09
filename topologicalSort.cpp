#include <iostream>
#include <cstring>

const int MAX_N = 5005;
const int MAX_M = 5005;

struct Edge {
    int to;
    Edge* next;
};

Edge edges[MAX_M];
Edge* adj[MAX_N];
int edge_count = 0;

int in_degree[MAX_N];
int heap[MAX_N];
int heap_size = 0;

void init_graph(int N) {
    edge_count = 0;
    for (int i = 1; i <= N; ++i) {
        adj[i] = nullptr;
        in_degree[i] = 0;
    }
}

void add_edge(int x, int y) {
    edges[edge_count].to = y;
    edges[edge_count].next = adj[x];
    adj[x] = &edges[edge_count];
    edge_count++;
    in_degree[y]++;
}

void heap_push(int x) {
    int i = heap_size++;
    heap[i] = x;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent] >= heap[i]) break;
        std::swap(heap[parent], heap[i]);
        i = parent;
    }
}

void heapify(int i) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;
    if (left < heap_size && heap[left] > heap[largest]) {
        largest = left;
    }
    if (right < heap_size && heap[right] > heap[largest]) {
        largest = right;
    }
    if (largest != i) {
        std::swap(heap[i], heap[largest]);
        heapify(largest);
    }
}

int heap_pop() {
    int max_val = heap[0];
    heap[0] = heap[--heap_size];
    heapify(0);
    return max_val;
}

void topological_sort(int N, int* result) {
    heap_size = 0;
    for (int i = 1; i <= N; ++i) {
        if (in_degree[i] == 0) {
            heap_push(i);
        }
    }

    int idx = 0;
    while (heap_size > 0) {
        int u = heap_pop();
        result[idx++] = u;
        for (Edge* e = adj[u]; e != nullptr; e = e->next) {
            int v = e->to;
            in_degree[v]--;
            if (in_degree[v] == 0) {
                heap_push(v);
            }
        }
    }

    if (idx != N) {
        result[0] = -1;
    }
}

int main() {
    int D;
    std::cin >> D;
    while (D--) {
        int N, M;
        std::cin >> N >> M;
        init_graph(N);
        for (int i = 0; i < M; ++i) {
            int x, y;
            std::cin >> x >> y;
            add_edge(y, x); // 构建逆图
        }

        int result[MAX_N];
        topological_sort(N, result);

        if (result[0] == -1) {
            std::cout << "Impossible!" << std::endl;
        }
        else {
            for (int i = N - 1; i >= 0; --i) {
                std::cout << result[i] << (i == 0 ? "\n" : " ");
            }
        }
    }
    return 0;
}