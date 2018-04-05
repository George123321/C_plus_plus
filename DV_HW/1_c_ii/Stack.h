#ifndef DV_HW_STACK_H
#define DV_HW_STACK_H

#include <math.h>

struct Node {
    float x;
    struct Node *next;
};

struct Stack {
    struct Node *head;
    int size;
};

void stack_init(struct Stack *st) {
    st->head = NULL;
    st->size = 0;
}

void stack_push(struct Stack *st, const float data) {
    st->size += 1;

    struct Node *p = malloc(sizeof(*p));
    p->x = data;
    p->next = NULL;
    if (st->head == NULL) {
        st->head = p;
    }
    else {
        p->next = st->head;
        st->head = p;
    }
}

int is_empty(struct Stack *st) {
    return (st->size == 0) ? 1 : 0 ;
}

float stack_pop(struct Stack *st) {
    if (is_empty(st)) {
        return NAN;
    }
    else {
        float to_return = st->head->x;
        struct Node *to_del = st->head;
        st->head = st->head->next;
        to_del->next = NULL;
        free(to_del);
        return to_return;
    }
}

void stack_print(struct Stack *st) {
    struct Node *p = st->head;
    while (p) {
        printf("%f\n", p->x);
        p = p->next;
    }
}

#endif //DV_HW_STACK_H
