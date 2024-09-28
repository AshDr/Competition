template<class T>
struct Dijkstra {
    const int n;
    struct Edge {
        int to;
        T d;
        Edge(int to, T d) : to(to), d(d) {}
    };
    std::vector<std::vector<Edge>> g;
    std::vector<T> dis;
    std::vector<int> vis;
    Dijkstra(int n) : n(n), g(n),dis(n),vis(n) {}
    
    T work(int s, int t) {
        dis.assign(n, std::numeric_limits<T>::max());
        std::priority_queue<std::pair<T, int>,
            std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>>> que;
        dis[s] = 0;
        que.push({0, s});
        while (!que.empty()) {
            auto [curd, u]= que.top();
            que.pop();
            if(vis[u]) continue;
            vis[u] = 1;
            for(auto [v, w]: g[u]) {
                if(dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    que.push({dis[v], v});
                }
            }
        }
        return dis[t];
    }
    void addEdge(int u, int v, T c) {
        g[u].emplace_back(v, c);
    }
};