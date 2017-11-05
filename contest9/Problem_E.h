#include <iostream>
#include <vector>
#include <map>

int main() {
    int n = 0;
    std::cin >> n;
    std::map<int, std::pair<int, int> > res;
    for(int i = 0; i < n; i++) {
        int vertex = 0, neighbour = 0, weight = 0;
        std::cin >> vertex >> neighbour >> weight;
        res.insert(std::pair<int, std::pair<int, int> >(vertex, std::pair<int, int>(0, 0)) );
        (res.find(vertex)->second).first++;
        (res.find(vertex)->second).second += weight;
    }
    for(auto it = res.begin(); it != res.end(); it++) {
        std::cout << it->first << " " << (it->second).first << " " << (it->second).second << std::endl;
    }
    return 0;
}