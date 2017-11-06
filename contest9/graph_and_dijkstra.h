#include <iostream>
#include <vector>
#include <map>
#include <set>


auto dijkstra(const std::map<int, std::map<int, int> > &G, int start) {
    std::map<int, int> d;
    return d;
}


int main() {
    int n = 0;
    std::cin >> n; // n - количество ребер
    std::map<int, std::map<int, int> > graph;
    std::set<int> used;
    for(int i = 0; i < n; i++) {
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
    }
    for(auto it = graph.begin(); it != graph.end(); it++) {
        for(auto inf = (it->second).begin(); inf != (it->second).end(); inf++) {
            std::cout << it->first << " " << inf->first << " " << inf->second << std::endl;
        }
    }
    return 0;
}