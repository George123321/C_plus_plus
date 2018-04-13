#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <time.h>
#include "Linked_List.h"

#define MAX 100
#define N 50

void make_points(struct Linked_List *points) {
    for (int point = 0; point < N; point++) {
        list_insert(points, MAX * ((float) rand() / RAND_MAX), MAX * ((float) rand() / RAND_MAX));
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
    FILE *f = fopen("C:/Users/George/Desktop/git_projects/C_plus_plus/DV_HW/1_c_i/Output/polygon.csv", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
    } else {
        struct Node *p = lst->begin;
        fprintf(f, "x,y\n");
        while (p) {
            fprintf(f, "%f,%f\n", p->x, p->y);
            p = p->next;
        }
    }
}

void points_in_file(struct Linked_List *lst) {
    FILE *f = fopen("C:/Users/George/Desktop/git_projects/C_plus_plus/DV_HW/1_c_i/Output/points.csv", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
    } else {
        struct Node *p = lst->begin;
        fprintf(f, "x,y\n");
        while (p) {
            fprintf(f, "%f,%f\n", p->x, p->y);
            p = p->next;
        }
    }
}

void del_repetitions(struct Linked_List *lst, struct Node *node) {
    struct Node *p = lst->begin;
    while (p) {
        if (p != node && p->x == node->x && p->y == node->y) {
            struct Node *to_del = p;
            p = p->next;
            list_del(lst, to_del);
        } else {
            p = p->next;
        }
    }
    // в итоге остался только node
}

double angle_between_vecs(float x_1, float y_1, float x_2, float y_2) {
    if ((x_1 == 0 && y_1 == 0) & (x_2 == 0 && y_2 == 0)) {
        return (double) 1.0 / 0.0;
    } else {
        return acos((x_1 * x_2 + y_1 * y_2) / (pow((x_1 * x_1 + y_1 * y_1) * (x_2 * x_2 + y_2 * y_2), 0.5)));
    }
}

double vec_length_sq(float x, float y) {
    return x * x + y * y;
}

// ищет точку с минимальным полярным углом относительно данной оси относительно последний точки в конце многоугольника
struct Node *find_point_min_polar_angle(struct Linked_List *polygon, struct Linked_List *points, const float axis_vec_x,
                                        const float axis_vec_y) {
    struct Node *p = points->begin;
    struct Node *p_min = points->begin;
    double min_angle = 10;
    while (p) {
        double current_angle = angle_between_vecs(p->x - polygon->end->x, p->y - polygon->end->y, axis_vec_x,
                                                  axis_vec_y);
        if (current_angle < min_angle) {
            p_min = p;
            min_angle = current_angle;
        }
        if (current_angle == min_angle) {
            if (vec_length_sq(p->x - polygon->end->x, p->y - polygon->end->y) >
                vec_length_sq(p_min->x - polygon->end->x, p_min->y - polygon->end->y)) {
                p_min = p;
            }
        }
        p = p->next;
    }
    return p_min;
}

void make_polygon(struct Linked_List *points, struct Linked_List *polygon) {
    // найдем точку с минимальным полярным углом, относительно оси x
    struct Node *new_vertex = find_point_min_polar_angle(polygon, points, 1, 0);
    list_insert(polygon, new_vertex->x, new_vertex->y);
    //list_del(points, new_vertex);
    while (!(polygon->end->x == polygon->begin->x && polygon->end->y == polygon->begin->y)) {
        new_vertex = find_point_min_polar_angle(polygon, points, polygon->end->x - polygon->end->prev->x,
                                                polygon->end->y - polygon->end->prev->y);
        list_insert(polygon, new_vertex->x, new_vertex->y);
        //list_del(points, new_vertex);
    }
}

int main() {
    clock_t begin = clock();

    struct Linked_List points;
    struct Linked_List polygon;
    list_init(&points);
    list_init(&polygon);

    make_points(&points);
    points_in_file(&points);

    struct Node *start_p = find_start_point(&points);

    list_insert(&polygon, start_p->x, start_p->y);
    list_insert(&points, start_p->x, start_p->y);
    //list_del(&points, start_p);
    // теперь стартовая точка находится в конце

    make_polygon(&points, &polygon);

    polygon_in_file(&polygon);

    clock_t end = clock();
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("Spent time: %lf\n", time_spent);
}