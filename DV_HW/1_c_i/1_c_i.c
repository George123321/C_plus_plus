#include <stdio.h>
#include <malloc.h>

struct Node {
    int x;
    int y;
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

struct Node *insert_node(struct Node *p_begin, const int data_x, const int data_y) {
    struct Node *p = malloc(sizeof(*p));
    p->x = data_x;
    p->y = data_y;
    p->next = p_begin;
    p->prev = NULL;
    return p;
}

void list_insert(struct Linked_List *lst, const int data_x, const int data_y) {
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

struct Node list_pop(struct Linked_List *lst) { // TODO: что-то не так, когда 1 элемент
    if (lst->end == NULL) {
        printf("List is empty");
    }
    else {
        lst->size -= 1;
        lst->end = lst->end->prev;
        lst->end->next->prev = NULL;
        struct Node *res = lst->end->next;
        free(lst->end->next);
        lst->end->next = NULL;
        return *res;
    }
}

int main() {
    struct Linked_List a;
    list_init(&a);
    list_insert(&a, 1, 0);
    list_insert(&a, 5, 2);
    list_insert(&a, 3, 1);
    list_pop(&a);
    list_pop(&a);
    list_pop(&a);
    list_pop(&a);
    printf("0");

    return 0;
}