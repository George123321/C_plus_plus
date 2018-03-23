#include <stdio.h>
#include <malloc.h>
#include <math.h>

#define MAX 10
#define N 100

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

int main() {
    struct Linked_List points;
    struct Linked_List polygon;
    list_init(&points);
    list_init(&polygon);

    for (int point = 0; point < N; point++) {
        list_insert(&points, rand() % (MAX + 1), rand() % (MAX + 1));
    }
    /*  запишем точки в файл */
    points_in_file(&points);

    struct Node *p = points.begin;
    struct Node *p_min = points.begin;
    int min = points.begin->y;
    for (int i = 0; i < N; i++) {
        if (p->y < min) {
            min = p->y;
            p_min = p;
        }
        p = p->next;
    }
    list_insert(&polygon, p_min->x, p_min->y);
    // list_del(&points, p_min); не будем удалять начальную точку
    /* будем искать точку с минимальным полярным углом*/
    p = points.begin;
    p_min = points.begin;
    double min_angle = 4;
    int i = 0;
    while (p) {
        if (p->x == polygon.begin->x && p->y == polygon.begin->y) {
            p = p->next;
            continue;
        }
        else if (polar_angle(p->x, p->y) < min_angle) {
            p_min = p;
            min_angle = polar_angle(p->x, p->y);
        }
        p = p->next;
    }
    /* p_min указывает на элемент с минимальным полярным уголом */
    list_insert(&polygon, p_min->x, p_min->y);
    list_del(&points, p_min);
    /* теперь пройдемся по оставшимся. Для каждой новой вершины будем смотреть минимальный угол между новым векторм, и предыдущим */
    //struct Node *res_p = polygon.begin->next; // выбрали не начальную точку
    p_min = polygon.begin->next; // выбрали не начальную ночку
    struct Node *current_vertex = polygon.begin->next;
    while (p_min->x != polygon.begin->x && p_min->y != polygon.begin->y) {
        p = points.begin;
        min_angle = 4;
        p_min = points.begin;
        while (p) {
            double angle = angle_between_vec(current_vertex->x - current_vertex->prev->x,
                                             current_vertex->y - current_vertex->prev->y,
                                             p->x - current_vertex->x, p->y - current_vertex->y);
            if (angle < min_angle) {
                min_angle = angle;
                p_min = p;
            }
            p = p->next;
        }
        list_insert(&polygon, p_min->x, p_min->y);
        list_del(&points, p_min);
        current_vertex = current_vertex->next;
    }
    // не будем /* удалим теперь последнюю точку, т.к. она совпадает с начальной */
    //list_pop(&polygon);
    list_print(&polygon);
    polygon_in_file(&polygon);
    return 0;
}