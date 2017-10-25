//============================================================================
// Name        : LinkedList.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "linked_list.hpp"

int main() {
    List<int> intList;
    list_init(intList);
    for(int i = 0; i < 10; ++i) {
        list_insert_front(intList, i);
    }
    list_print(intList, std::cout);
    std::cout << std::endl;
    for(int i = 90; i < 100; i++) {
    	list_insert_back(intList, i);
    }
    list_insert(intList, -1, intList.size/2);
    list_print(intList, std::cout);
    std::cout << list_swap(intList, 1, 2);
    list_print(intList, std::cout);
    list_destroy(intList);
}
