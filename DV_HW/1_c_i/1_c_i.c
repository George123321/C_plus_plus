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

struct Node list_del(struct Linked_List *lst, struct Node *node) {
    if (lst->begin == NULL) {
        printf("List is empty\n");
        struct Node *p = malloc(sizeof(struct Node));
        return *p;
    }
    if (node == NULL) {
        printf("Node is null\n");
        struct Node *p = malloc(sizeof(struct Node));
        return *p;
    }
    struct Node *p = lst->begin;
    while (p != node) {
        p = p->next;
    }
    /* отдельно обработаем случай, когда один элемент */
    if (lst->size == 1) {
        lst->size = 0;
        lst->begin = NULL;
        lst->end = NULL;
        return *p;
    }
    /* теперь хотя бы 2 элемента */
    if (p == lst->begin) {
        lst->begin = p->next;
        p->next->prev = NULL;
        p->next = NULL;
    }
    else if (p == lst->end) {
        lst->end = p->prev;
        p->prev->next = NULL;
        p->prev = NULL;
    }
    else {
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }
    p->next = NULL;
    p->prev = NULL;
    lst->size -= 1;
    return *p;
}

struct Node list_pop(struct Linked_List *lst) {
    list_del(lst, lst->end);
}

void list_print(struct Linked_List *lst) {
    struct Node *p = lst->begin;
    while (p) {
        printf("(%d, %d)\n", p->x, p->y);
        p = p->next;
    }
}

int main() {
    struct Linked_List a;
    list_init(&a);
    list_insert(&a, 1, 0);
    list_insert(&a, 5, 2);
    list_insert(&a, 3, 1);

    struct Node *p = a.begin;
    while (p) {
        p = a.begin;
        list_print(&a);
        list_del(&a, p);
    }
    list_del(&a, NULL);
    list_print(&a);
    return 0;
}