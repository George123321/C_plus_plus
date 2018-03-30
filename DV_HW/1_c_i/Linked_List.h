//
// Created by George on 28.03.2018.
//

#ifndef DV_HW_LINKED_LIST_H
#define DV_HW_LINKED_LIST_H

struct Node {
    float x;
    float y;
    struct Node *next;
    struct Node *prev;
};

struct Linked_List {
    struct Node *begin;
    struct Node *end;
    int size;
};

void list_init(struct Linked_List *lst) {
    lst->begin = NULL;
    lst->end = NULL;
    lst->size = 0;
}

void node_init(struct Node *node, float data_x, float data_y) {
    node->x = data_x;
    node->y = data_y;
    node->next = NULL;
    node->prev = NULL;
}

void list_insert(struct Linked_List *lst, const float data_x, const float data_y) {
    lst->size += 1;

    struct Node *p = malloc(sizeof(*p));
    p->x = data_x;
    p->y = data_y;
    p->next = NULL;
    p->prev = NULL;
    if (lst->begin == NULL) {
        lst->begin = p;
        lst->end = p;
    }
    else {
        p->prev = lst->end;
        lst->end->next = p;
        lst->end = lst->end->next;
    }
}

void list_del(struct Linked_List *lst, struct Node *node) {
    if (lst->begin == NULL) {
        printf("List is empty\n");
    }
    if (node == NULL) {
        printf("Node is null\n");
    }
    else {
        /* отдельно обработаем случай, когда один элемент */
        if (lst->size == 1) {
            lst->size = 0;
            lst->begin = NULL;
            lst->end = NULL;
            free(node);
        } else {
            /* теперь хотя бы 2 элемента */
            if (node == lst->begin) {
                lst->begin = node->next;
                node->next->prev = NULL;
                node->next = NULL;
            } else if (node == lst->end) {
                lst->end = node->prev;
                node->prev->next = NULL;
                node->prev = NULL;
            } else {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
            node->next = NULL;
            node->prev = NULL;
            free(node);
            lst->size -= 1;
        }
    }
}

struct Node list_pop(struct Linked_List *lst) {
    list_del(lst, lst->end);
}

void list_print(struct Linked_List *lst) {
    struct Node *p = lst->begin;
    while (p) {
        printf("(%f, %f)\n", p->x, p->y);
        p = p->next;
    }
}

#endif //DV_HW_LINKED_LIST_H
