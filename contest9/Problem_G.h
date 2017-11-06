#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

auto dijkstra(const std::map<int, std::map<int, int> > &G, int start) {
    std::map<int, int> d;
    std::vector<int> p(G.size());
    int INF = 1000000000;
    for(int i = 0; i < G.size(); i++) {
        d.insert(std::pair<int, int>(i, INF));
    }
    d[start] = 0;
    std::set<int> used;
    int current = 0;
    while(used.size() != G.size()) { // скатано с лекций прошлого года
        int min_d = INF;
        for(auto v = d.begin(); v != d.end(); v++) {
            if(v->second < min_d and used.count(v->first) == 0) {
                current = v->first;
                min_d = v->second;
            }
        }
        for(auto neighbour = (G.find(current)->second).begin(); neighbour != (G.find(current)->second).end(); neighbour++) {
            int l = d[current] + neighbour->second;
            if(l < d[neighbour->first]) {
                d[neighbour->first] = l;
                p[neighbour->first] = current;
            }
        }
        used.insert(used.end(), current);
    }
    // d хранит расстояний от нашей вершины до всех, p хранит предки всех вершин
    return p;
}

int main() {
    int n = 0, m = 0, s = 0, f = 0;
    std::cin >> n >> m >> s >> f;
    std::map<int, std::map<int, int> > graph;
    std::set<int> used;
    for(int i = 0; i < m; i++) {
        int vertex = 0, neighbour = 0, weight = 0; // считываем тройки <вершина> <куда ведет> <вес>
        std::cin >> vertex >> neighbour >> weight;
        if(used.count(vertex) == 0) {
            std::map<int, int> information;
            information.insert(std::pair<int, int>(neighbour, weight));
            graph.insert(std::pair<int, std::map<int, int> >(vertex, information));

            used.insert(vertex);
        }
        else {
            (graph.find(vertex)->second).insert(std::pair<int, int>(neighbour, weight));
        }
        // если граф ориаентированный - далее закомментировать
        if(used.count(neighbour) == 0) {
            std::map<int, int> information_1;
            information_1.insert(std::pair<int, int>(vertex, weight));
            graph.insert(std::pair<int, std::map<int, int> >(neighbour, information_1));

            used.insert(neighbour);
        }
        else {
            (graph.find(neighbour)->second).insert(std::pair<int, int>(vertex, weight));
        }
    }
    //print_graph_map(graph);
    auto p = dijkstra(graph, s);
    // далее какая-то магия с списокм предков
    std::vector<int> path;
    for(int v = f; v!= s; v = p[v]) {
        path.push_back (v);
    }
    path.push_back (s);
    reverse (path.begin(), path.end());
    for(auto it = path.begin(); it != path.end(); it++) {
        std::cout << *it << " ";
    }
    return 0;
}