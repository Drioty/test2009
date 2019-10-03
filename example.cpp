#include <iostream>
#include <map>
#include <queue>
#include <vector>

int INT_MAX = 2000000000;
std::vector<int> G;

struct vertex {
    int to, cap, flow, reverse;

    vertex(int to, int capacity, int reverse) : to(to), cap(capacity), flow(0), reverse(reverse) {}
};

int dfs(int v, int flow, std::vector<std::vector<vertex>> &graph, std::vector<int> &d, int to, int amount) {
    if (flow == 0)
        return 0;
    if (v - amount == to)
        return flow;
    int res = 0;
    for (; d[v] < graph[v].size(); ++d[v]) {
        auto &elm = graph[v][d[v]];
        if (elm.cap > elm.flow && G[v] == G[elm.to] - 1) {
            int f1 = std::min(flow, elm.cap - elm.flow);
            int f2 = dfs(elm.to, f1, graph, d, to, amount);
            res += f2;
            flow -= f2;
            elm.flow += f2;
            graph[elm.to][elm.reverse].flow -= f2;
            if (flow == 0)
                return res;
        }
    }
    return res;
}

bool bfs(int from, int to, int n, std::vector<std::vector<vertex>> &graph) {
    G.assign(n, INT_MAX);
    std::queue<int> queue;
    queue.push(from);
    G[from] = 0;
    while (queue.size()) {
        int v = queue.front();
        queue.pop();
        for (auto &elm: graph[v]) {
            if (elm.cap - elm.flow > 0 && G[elm.to] > G[v] + 1) {
                G[elm.to] = G[v] + 1;
                queue.push(elm.to);
            }
        }
    }
    return (G[to] != INT_MAX);
}

int res(int n, int from, int to, int amount, std::vector<std::vector<vertex>> &graph) {
    std::vector<int> G;
    int max = 0;
    while (bfs(from, to, n, graph)) {
        G.assign(n, 0);
        max += dfs(from, 1, graph, G, to, amount);
    }
    return max;
}

int main() {
    int n;
    std::cin >> n;
    std::map<std::pair<int, int>, int> points;
    std::vector<std::pair<int, int>> newed;
    std::vector<std::pair<int, int>> Inlet(n);
    int amount = 0;
    for (int i = 0; i < n; ++i) {
        int v0, v1;
        int x0, y0, x1, y1;
        std::cin >> x0 >> y0 >> x1 >> y1;
        std::pair<int, int> temp1 = std::make_pair(x0, y0);
        std::pair<int, int> temp2 = std::make_pair(x1, y1);
        if (points.find(temp1) == points.end()) {
            points[temp1] = amount;
            amount++;
        }
        if (points.find(temp2) == points.end()) {
            points[temp2] = amount;
            amount++;
        }
        v0 = points[temp1];
        v1 = points[temp2];
        newed.push_back(std::make_pair(v0, v1));
    }
    std::vector<std::vector<vertex>> graph;
    int br = amount * 2;
    graph.resize(br);
    for (int i = 0; i < amount; ++i) {
        int b = i;
        int a = amount + i;
        graph[a].push_back(vertex(b, 1, graph[b].size()));
        graph[b].push_back(vertex(a, 0, graph[a].size() - 1));
    }
    for (auto elm : newed) {
        int first = elm.first;
        int a = first;
        int second = elm.second;
        int b = second + amount;
        graph[a].push_back(vertex(b, 1, graph[b].size()));
        graph[b].push_back(vertex(a, 0, graph[a].size() - 1));
        b = first + amount;
        a = second;
        graph[a].push_back(vertex(b, 1, graph[b].size()));
        graph[b].push_back(vertex(a, 0, graph[a].size() - 1));
    }
    int from, to;
    int j, o, p, a;
    std::cin >> j >> o >> p >> a;
    std::pair<int, int> temp1 = std::make_pair(j, o);
    std::pair<int, int> temp2 = std::make_pair(p, a);
    if (points.find(temp1) == points.end()) {
        points[temp1] = amount;
        amount++;
    }
    if (points.find(temp2) == points.end()) {
        points[temp2] = amount;
        amount++;
    }
    from = points[temp1];
    to = points[temp2];
    std::cout << res(br, from, to, amount, graph);
}
