#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define MAX 10
#define N 150

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

double polar_angle(int x, int y) {
    return acos(x/pow(x * x + y * y, 0.5));
}

double angle_between_vec(int x_1, int y_1, int x_2, int y_2) {
    return acos((x_1 * x_2 + y_1 * y_2)/(pow((x_1 * x_1 + y_1 * y_1) * (x_2 * x_2 + y_2 * y_2), 0.5)));
}

void polygon_in_file(struct Linked_List *lst) {
    FILE *f = fopen("C:/Users/George/Desktop/git_projects/C_plus_plus/DV_HW/1_c_i/polygon.csv", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
    }
    else {
        struct Node *p = lst->begin;
        fprintf(f, "x,y\n");
        while (p) {
            fprintf(f, "%d,%d\n", p->x, p->y);
            p = p->next;
        }
    }
}

void points_in_file(struct Linked_List *lst) {
    FILE *f = fopen("C:/Users/George/Desktop/git_projects/C_plus_plus/DV_HW/1_c_i/points.csv", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
    }
    else {
        struct Node *p = lst->begin;
        fprintf(f, "x,y\n");
        while (p) {
            fprintf(f, "%d,%d\n", p->x, p->y);
            p = p->next;
        }
    }
}

int type_of_rotate(struct Node *a, struct Node *b, struct Node *c) {
    return (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x); // компонента z вектора из векторного произведения
}

int main() {
    struct Linked_List points;
    struct Linked_List polygon;
    list_init(&points);
    list_init(&polygon);

    for (int point = 0; point < N; point++) {
        list_insert(&points, rand() % (MAX + 1), rand() % (MAX + 1));
    }
    // запишем точки в файл
    points_in_file(&points);

    // найдем точку с наименьшей ординатой
    struct Node *p = points.begin;
    struct Node *p_min = points.begin;
    int min_y = p->y;
    while (p) {
        if (p->y < min_y) {
            min_y = p->y;
            p_min = p;
        }
        p = p->next;
    }
    /* p_min указывает на node с минимальной ординатой. Добавляем! */
    list_insert(&polygon, p_min->x, p_min->y);
    list_del(&points, p_min);
    /* добавим в polygon остальные точки в порядке возрастания полярного угла */
    while (points.size != 0) {
        p = points.begin;
        double min_angle = 10;
        while (p) {
            double current_angle = polar_angle(p->x, p->y);
            if (current_angle < min_angle) {
                min_angle = current_angle;
                p_min = p;
            }
            /*
            if (current_angle == min_angle && (p->x * p->x + p->y * p->y > p_min->x * p_min->x + p_min->y * p_min->y)) { // TODO: проблема здесь
                min_angle = current_angle;
                p_min = p;
            }*/
            p = p->next;
        }
        list_insert(&polygon, p_min->x, p_min->y);
        list_del(&points, p_min);
    }
    /* добавим в конец первую точку */
    list_insert(&polygon, polygon.begin->x, polygon.begin->y);

    /* теперь нужно срезать все углы, т.е. удалить те вершины, для которых выполнен левый поворот */
    /* первые две вершины точно принадлежат оболочке. переместимся в эту точку */
    p = polygon.begin->next;

    while (p != polygon.end) {
        if (p->x == p->next->x && p->y == p->next->y) {
            list_del(&polygon, p->next);
            continue;
        }
        while (type_of_rotate(p->prev, p, p->next) < 0) {
            p = p->prev;
            list_del(&polygon, p->next);
        }
        if (type_of_rotate(p->prev, p, p->next) >= 0) {
            p = p->next;
        }
    }
    list_print(&polygon);
    polygon_in_file(&polygon);

    return 0;
}