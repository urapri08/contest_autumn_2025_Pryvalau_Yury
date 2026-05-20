#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

const long long cInf = 1'000'000'000'000'000'000LL;

struct Edge {
  long long cap;
  long long flow;
  long long cost;
  int to;
  int rev;
};

struct Graph {
  std::vector<std::vector<Edge>> adj;
  std::vector<long long> dist;
  std::vector<int> parent_node;
  std::vector<int> parent_edge;
  std::vector<long long> pot;
  int n;

  Graph(int nodes) : adj(nodes + 1), n(nodes) {}
};

void AddEdge(int u, int v, long long cap, long long cost, Graph& g) {
  g.adj[u].push_back({ cap, 0, cost, v, static_cast<int>(g.adj[v].size()) });
  g.adj[v].push_back({ 0, 0, -cost, u, static_cast<int>(g.adj[u].size()) - 1 });
}

bool RunDijkstra(int source, int sink, Graph& g) {
  g.dist.assign(g.n + 1, cInf);
  g.parent_edge.assign(g.n + 1, -1);
  g.parent_node.assign(g.n + 1, -1);
  std::priority_queue<std::pair<long long, int>,
    std::vector<std::pair<long long, int>>,
    std::greater<std::pair<long long, int>>>
    pq;
  g.dist[source] = 0;
  pq.push({ 0, source });
  while (!pq.empty()) {
    long long d = pq.top().first;
    int u = pq.top().second;
    pq.pop();
    if (d > g.dist[u]) {
      continue;
    }
    for (int i = 0; i < static_cast<int>(g.adj[u].size()); ++i) {
      const Edge& e = g.adj[u][i];
      if (e.cap - e.flow > 0) {
        long long new_dist = g.dist[u] + e.cost + g.pot[u] - g.pot[e.to];
        if (new_dist < g.dist[e.to]) {
          g.dist[e.to] = new_dist;
          g.parent_node[e.to] = u;
          g.parent_edge[e.to] = i;
          pq.push({ g.dist[e.to], e.to });
        }
      }
    }
  }
  return g.dist[sink] != cInf;
}

long long MinCostMaxFlow(int source, int sink, Graph& g) {
  long long min_cost = 0;
  g.pot.assign(g.n + 1, 0);
  while (RunDijkstra(source, sink, g)) {
    for (int i = 1; i <= g.n; ++i) {
      if (g.dist[i] != cInf) {
        g.pot[i] += g.dist[i];
      }
    }
    long long push_flow = cInf;
    int curr = sink;
    while (curr != source) {
      int p = g.parent_node[curr];
      int idx = g.parent_edge[curr];
      push_flow = std::min(push_flow, g.adj[p][idx].cap - g.adj[p][idx].flow);
      curr = p;
    }
    curr = sink;
    while (curr != source) {
      int p = g.parent_node[curr];
      int idx = g.parent_edge[curr];
      int rev_idx = g.adj[p][idx].rev;
      g.adj[p][idx].flow += push_flow;
      g.adj[curr][rev_idx].flow -= push_flow;
      min_cost += push_flow * g.adj[p][idx].cost;
      curr = p;
    }
  }
  return min_cost;
}

void SolveTask() {
  int n = 0;
  int m = 0;
  if (!(std::cin >> n >> m)) {
    return;
  }
  Graph g(n);
  for (int i = 0; i < m; ++i) {
    int u = 0;
    int v = 0;
    long long cap = 0;
    long long cost = 0;
    std::cin >> u >> v >> cap >> cost;
    AddEdge(u, v, cap, cost, g);
  }
  long long total_cost = MinCostMaxFlow(1, n, g);
  std::cout << total_cost << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  SolveTask();
  return 0;
}