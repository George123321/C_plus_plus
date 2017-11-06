#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

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
    return graph;
}

void print_graph_map(const std::map<int, std::map<int, int> > & graph) {
    for(auto it = graph.begin(); it != graph.end(); it++) {
        std::cout << it->first << " : ";
        for(auto inf = (it->second).begin(); inf != (it->second).end(); inf++) {
            std::cout  << "(" <<inf->first << ", " << inf->second << ") ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

auto dijkstra(const std::map<int, std::map<int, int> > &G, int start, int final) {
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
    std::vector<int> path;
    for(int v = final; v!= start; v = p[v]) {
        path.push_back (v);
    }
    path.push_back (start);
    reverse (path.begin(), path.end());
    return std::pair<std::map<int, int>, std::vector<int> >(d, path); // d хранит расстояний от нашей вершины до всех, path хранит кратчайший путь между вершиной start и final
}

void print_short_way(const std::map<int, std::map<int, int> > &G, int start, int final) { // печатает кратчайший путь между верщиной start и final
    auto path = dijkstra(G, start, final).second;
    std::cout << "The shortest way from vertex " << start << " to vertex " << final << " is: ";
    for(auto it = path.begin(); it != path.end(); it++) {
        std::cout <<*it << " ";
    }
    std::cout << std::endl;
}

void print_short_distances(const std::map<int, std::map<int, int> > &G, int start) { // печататет дилины кратчайших путей от вершины start до всех - короче, обычный дейкстра
    auto dist = dijkstra(G, start, 0).first;
    for(auto it = dist.begin(); it != dist.end(); it++) {
        std::cout << "The distance of the shortest way from vertex 0 to vertex " <<it->first << " is " << it->second << std::endl;
    }
    std::cout << std::endl;
}

int main() {
    auto g = input_graph_as_map();
    print_graph_map(g);
    print_short_way(g, 0, 4);
    print_short_distances(g, 0);
    return 0;
}