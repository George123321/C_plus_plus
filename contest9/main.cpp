#include <iostream>
#include <vector>
#include <map>
#include <set>


auto dijkstra(const std::map<int, std::map<int, int> > &G, int start) {
    std::map<int, int> d;
    for(int i = 0; i < G.size(); i++) {
        d.insert(std::pair<int, int>(i, 10^9));
    }
    d[start] = 0;
    std::set<int> used;
    int current = 0;
    while(used.size() != G.size()) { // скатано с лекций прошлого года
        int min_d = 10^9;
        for(auto v = d.begin(); v != d.end(); v++) {
            if(v->second < min_d and used.count(v->first)) {
                current = v->first;
                min_d = v->second;
            }
        }
        for(auto neighbour = (G.find(current)->second).begin(); neighbour != (G.find(current)->second).end(); neighbour++) {
            int l = d[current] + neighbour->second;
            if(l< d.find(current)->second) {
                d.find(neighbour->first)->second = l;
            }
        }
        used.insert(used.end(), current);
    }
    return d;
}

auto input_graph_as_map() {
    int m = 0;
    std::cin >> m; // m - количество ребер
    std::map<int, std::map<int, int> > graph;
    std::set<int> used;
    for(int i = 0; i < m; i++) {
        int vertex = 0, neighbour = 0, weight = 0; // считываем тройки <вершина> <куда ведет> <вес>
        std::cin >> vertex >> neighbour >> weight;
        if(used.count(vertex) == 0) {
            std::map<int, int> information;
            information.insert(std::pair<int, int>(neighbour, weight));
            graph.insert(std::pair<int, std::map<int, int> >(vertex, information));

            std::map<int, int> information_1;
            information_1.insert(std::pair<int, int>(vertex, weight));
            graph.insert(std::pair<int, std::map<int, int> >(neighbour, information_1));

            used.insert(vertex);
        }
        else {
            (graph.find(vertex)->second).insert(std::pair<int, int>(neighbour, weight));
            (graph.find(neighbour)->second).insert(std::pair<int, int>(vertex, weight));
        }
    }
    return graph;
}

void print_graph_map(const std::map<int, std::map<int, int> > & graph) {
    for(auto it = graph.begin(); it != graph.end(); it++) {
        for(auto inf = (it->second).begin(); inf != (it->second).end(); inf++) {
            std::cout << it->first << " " << inf->first << " " << inf->second << std::endl;
        }
    }
}

int main() {
    auto g = input_graph_as_map();
    print_graph_map(g);
    auto res = dijkstra(g, 0);
    for(auto it = res.begin(); it != res.end(); it++) {
        std::cout << it->first << " " << it->second << std::endl;
    }
    return 0;
}