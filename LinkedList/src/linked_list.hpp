/*
 * linked_list.hpp
 *
 *  Created on: 25 окт. 2017 г.
 *      Author: gosha
 */
#ifndef __linked_list_hpp
#define __linked_list_hpp

#include <ostream>

#define nullptr     NULL


template<typename DataType>
struct tNode {
    DataType data;
    tNode* next;
};


template<typename DataType>
struct List {
    tNode<DataType> *begin;
    tNode<DataType> *end;
    int size;
};

template<typename DataType>
void list_init(List<DataType> &lst)
{
    lst.begin = nullptr;
    lst.end = nullptr;
    lst.size = 0;
}

template<typename DataType>
tNode<DataType> * insert_node_front(tNode<DataType> *p_begin, DataType data)
{
    tNode<DataType> *p = new tNode<DataType>;
    p->data = data;
    p->next = p_begin;
    return p;
}

template<typename DataType>
void list_insert_front(List<DataType> &lst, const DataType &value)
{
    lst.size += 1;
    lst.begin = insert_node_front(lst.begin, value);
    if (lst.end == nullptr) {
    	lst.end = lst.begin;
    }
}

///

//добавление в i позицию
template<typename DataType>
void list_insert(List<DataType> & lst, const DataType &value, int k) {
	if (k == 0) {
		list_insert_front(lst, value);
	}
	if (k == lst.size - 1) {
		list_insert_back(lst, value);
	}
	else{
		lst.size++;
		tNode<DataType> *node = new tNode<DataType>;
		node->data = value;
		tNode<DataType> *p = lst.begin;
		for(int i = 0; i < k - 1; i++) {
			p = p->next;
		}
		tNode<DataType> *tmp = p->next;
		p->next = node;
		node->next = tmp;
	}
}

template<typename DataType>
tNode<DataType> * insert_node_back(tNode<DataType> *p_end, DataType data)
{
    tNode<DataType> *p = new tNode<DataType>;
    p->data = data;
    p->next = nullptr;
    p_end->next = p;
    return p;
}

template<typename DataType>
void list_insert_back(List<DataType> &lst, const DataType &value)
{
    lst.size += 1;
    lst.end = insert_node_back(lst.end, value);
}

template<typename DataType>
bool list_swap(List<DataType> & lst, int i, int j) {
	if(i < 0 or j < 0 or i >= lst.size or j >= lst.size or i == j) {
		return false;
	}
	//если соседи
	if(i - j == 1 or i - j == -1) {
		//сделаем i < j
		if (i > j){
			int tmp = j; j = i; i = tmp;
		}
		tNode<DataType> *pi = lst.begin;
		tNode<DataType> *pj = lst.begin;
		for(int k = 0; k < i; k++) {
			pi = pi->next;
		}
		for(int k = 0; k < j; k++) {
			pj = pj->next;
		}
		// pi, pj - указатели на i,j-е ноды
		tNode<DataType> *tmp = new tNode<DataType>;
		tmp->data = pj->data;
		pj->data = pi->data;
		pi->data = tmp->data;
		// pi.next = pj.next, pj.next = pi, pi-1.next = pj
		pi->next = pj->next;
		pj->next = pi;
		tNode<DataType> *tmp1 = lst.begin;
		for(int k = 0; k < i-1; k++) {
			tmp1 = tmp1->next;
		}
		tmp1->next = pj;
		return true;
	}
}
///

template<typename DataType>
void list_print(const List<DataType> &lst, std::ostream &out)
{
    tNode<DataType> *p = lst.begin;
    for(; p; p = p->next)
    {
        out << p->data << '\t';
    }
    std::cout << '\n';
}

template<typename DataType>
void list_destroy(List<DataType> &lst)
{
    tNode<DataType> *p = lst.begin;
    tNode<DataType> *prev;
    while (p) {
        prev = p;
        p = p->next;
        delete prev;
    }
    lst.size = 0;
    lst.begin = nullptr;
}


#endif
