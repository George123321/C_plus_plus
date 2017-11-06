#include <iostream>
#include <vector>
#include <map>
#include <set>

void dfs(int vertex, const std::vector<std::vector<int> > & graph, std::set<int> & used) {
    used.insert(vertex);
    for(auto neighbour = graph[vertex].begin(); neighbour != graph[vertex].end(); neighbour++) {
        if(used.count(*(neighbour)) == 0) {
            dfs(*(neighbour), graph, used);
        }
    }
}

int count_number_of_components(const std::vector<std::vector<int> > & graph) {
    std::set<int> used;
    int number_of_components = 0;
    for(int i = 0; i < graph.size(); i++) {
        if(used.count(i) == 0){
            dfs(i, graph, used);
            number_of_components++;
        }
    }
    return number_of_components;
}

bool is_graph_connected(const std::vector<std::vector<int> > & graph) { // graph - список смежностей
    if(count_number_of_components(graph) == 1) {
        return true;
    }
    else {
        return false;
    }
}

auto input_graph_as_list() {
    int n = 0, m = 0;
    std::cin >> n >> m; // n - количество вершин, m - ребер
    std::vector<std::vector<int> > graph(n);
    for(int i = 0; i < m; i++) {
        int vertex = 0, neighbour = 0;
        std::cin >> vertex >> neighbour;
        graph[vertex].insert(graph[vertex].end(), neighbour);
        graph[neighbour].insert(graph[neighbour].end(), vertex);
    }
    return graph;
}

void print_graph(const std::vector<std::vector<int> > & graph) {
    for(auto vertex = graph.begin(); vertex != graph.end(); vertex++){
        std::cout << std::distance(graph.begin(), vertex) << " : ";
        for(auto neighbour = (*(vertex)).begin(); neighbour != (*(vertex)).end(); neighbour++) {
            std::cout << *(neighbour) << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    int n = 0, m = 0;
    std::cin >> n >> m; // n - количество вершин, m - ребер
    std::vector<std::vector<int> > graph(n);
    for(int i = 0; i < m; i++) {
        int vertex = 0, neighbour = 0;
        std::cin >> vertex >> neighbour;
        graph[vertex].insert(graph[vertex].end(), neighbour);
        graph[neighbour].insert(graph[neighbour].end(), vertex);
        if(is_graph_connected(graph)) {
            std::cout << i+1;
            return 0;
        }
    }
    return 0;
}