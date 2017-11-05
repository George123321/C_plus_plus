#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers;
    int tmp;
    std::cin >> tmp;
    while(tmp != 0) {
        numbers.insert(numbers.end(), tmp);
        std::cin >> tmp;
    }
    int length = 0;
    length = numbers.size();
    if(length == 0) {
        std::cout << "0" << " " << "-1";
        return 0;
    }
    std::vector<int> stack;
    for(int i = 0; i < length; i++) {
        if(numbers[i] > 0) {
            stack.insert(stack.end(), numbers[i]);
        }
        else if(numbers[i] < 0 and stack.size() != 0 and -numbers[i] < stack[stack.size()-1]) {
            stack[stack.size()-1] += numbers[i];
        }
        else if(numbers[i] < 0 and stack.size() != 0 and -numbers[i] >= stack[stack.size()-1]) {
            stack.erase(stack.end()-1);
        }
    }
    if(stack.size() == 0) {
        std::cout << "0" << " " << "-1";
        return 0;
    }
    std::cout << stack.size() << " " << stack[stack.size()-1];
    return 0;
}
