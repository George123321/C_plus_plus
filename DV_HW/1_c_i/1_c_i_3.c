#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include "Linked_List.h"

#define MAX 10
#define N 10

void make_points(struct Linked_List *points) {
    for (int point = 0; point < N; point++) {
        list_insert(points, MAX *((float) rand()/RAND_MAX), MAX *((float) rand()/RAND_MAX));
    }
}

struct Node *find_start_point(struct Linked_List *points) {
    struct Node *p = points->begin;
    struct Node *p_min_y = points->begin;
    float min_y = points->begin->y;
    while (p) {
        if (p->y < min_y) {
            min_y = p->y;
            p_min_y = p;
        }
        p = p->next;
    }
    /* нашли минимум по y. Ищем минимум по x */
    struct Node *p_min = p_min_y; // может уже минимум по x?
    p = points->begin;
    float min_x = p_min_y->x;
    while (p) {
        if (p->x < min_x && p->y == p_min_y->y) {
            min_x = p->x;
            p_min = p;
        }
        p = p->next;
    }
    return p_min;
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
            fprintf(f, "%f,%f\n", p->x, p->y);
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
            fprintf(f, "%f,%f\n", p->x, p->y);
            p = p->next;
        }
    }
}

double polar_angle(float x, float y) {
    return acos(x/pow(x * x + y * y, 0.5));
}

double relative_polar_angle(struct Node *start_p, struct Node *p) {
    return polar_angle(p->x - start_p->x, p->y - start_p->y);
}

void sort_by_polar_angle(struct Node *start_p, struct Linked_List *points, struct Linked_List *polygon) {
    while (points->size != 0) {
        struct Node *p = points->begin;
        struct Node *p_min = points->begin;
        double min_angle = relative_polar_angle(start_p, p_min);
        while (p) {
            double current_angle = relative_polar_angle(start_p, p);
            float relative_x = p->x - start_p->x;
            float relative_y = p->y - start_p->y;
            if (current_angle == min_angle) {
                if (relative_x * relative_x + relative_y * relative_y >
                    (p_min->x - start_p->x) * (p_min->x - start_p->x) +
                    (p_min->y - start_p->y) * (p_min->y - start_p->y)) {
                    min_angle = current_angle;
                    p_min = p;
                }
            }
            else if (current_angle < min_angle) {
                min_angle = current_angle;
                p_min = p;
            }
            p = p->next;
        }
        list_insert(polygon, p_min->x, p_min->y);
        list_del(points, p_min);
    }
}

float type_of_rotate(struct Node *a, struct Node *b, struct Node *c) {
    return (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x); // компонента z вектора из векторного произведения
}

void cut_angles(struct Linked_List *polygon) {
    /* первые две вершины точно принадлежат оболочке. переместимся в эту точку */
    struct Node *p = polygon->begin->next;

    while (p != polygon->end) {
        if (p->x == p->next->x && p->y == p->next->y) {
            list_del(polygon, p->next);
            continue;
        }
        while (type_of_rotate(p->prev, p, p->next) <= 0) {
            p = p->prev;
            list_del(polygon, p->next);
        }
        p = p->next;
    }
}

void del_repetitions(struct Linked_List *lst, struct Node *node) {
    struct Node *p = lst->begin;
}

void make_polygon(struct Linked_List *points, struct Linked_List *polygon) {

}

int main() {
    struct Linked_List points;
    struct Linked_List polygon;
    list_init(&points);
    list_init(&polygon);

    make_points(&points);
    points_in_file(&points);

    struct Node *start_p = find_start_point(&points);
    list_insert(&polygon, start_p->x, start_p->y);
    list_del(&points, start_p);
    list_insert(&points, start_p->x, start_p->y); // теперь она в конце

    make_polygon(&points, &polygon);

    polygon_in_file(&polygon);
}