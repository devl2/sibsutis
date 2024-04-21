#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define PI 3.14159265358979323846

// Структура для точки
typedef struct {
    double x;
    double y;
} Point;

// Структура для треугольника
typedef struct {
    Point p1;
    Point p2;
    Point p3;
} Triangle;

// Структура для круга
typedef struct {
    Point center;
    double radius;
} Circle;

// Функция для вычисления расстояния между двумя точками
double distance(Point p1, Point p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

// Функция для вычисления периметра круга
double circle_perimeter(double radius) {
    return 2 * PI * radius;
}

// Функция для вычисления площади круга
double circle_area(double radius) {
    return PI * pow(radius, 2);
}

// Функция для вычисления периметра треугольника
double triangle_perimeter(Triangle triangle) {
    double side1 = distance(triangle.p1, triangle.p2);
    double side2 = distance(triangle.p2, triangle.p3);
    double side3 = distance(triangle.p3, triangle.p1);
    return side1 + side2 + side3;
}

// Функция для вычисления площади треугольника
double triangle_area(Triangle triangle) {
    double a = distance(triangle.p1, triangle.p2);
    double b = distance(triangle.p2, triangle.p3);
    double c = distance(triangle.p3, triangle.p1);
    double s = (a + b + c) / 2.0;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

// Функция для проверки пересечения круга и треугольника
int intersects_circle_triangle(Circle circle, Triangle triangle) {
    Point closest_point;
    if (circle.center.x < triangle.p1.x) {
        closest_point.x = triangle.p1.x;
    } else if (circle.center.x > triangle.p2.x) {
        closest_point.x = triangle.p2.x;
    } else {
        closest_point.x = circle.center.x;
    }

    if (circle.center.y < triangle.p3.y) {
        closest_point.y = triangle.p3.y;
    } else if (circle.center.y > triangle.p1.y) {
        closest_point.y = triangle.p1.y;
    } else {
        closest_point.y = circle.center.y;
    }

    double dist = distance(circle.center, closest_point);
    return dist < circle.radius;
}

int main() {
    Triangle triangles[3];
    Circle circle;

    // Чтение входных данных
    for (int i = 0; i < 3; ++i) {
        char shape[10];
        if (scanf("%9s", shape) != 1) {
            printf("Error: unable to read shape type\n");
            exit(EXIT_FAILURE);
        }

        if (strcmp(shape, "triangle") == 0) {
            if (scanf("((%lf %lf, %lf %lf, %lf %lf, %lf %lf))", &triangles[i].p1.x, &triangles[i].p1.y, &triangles[i].p2.x, &triangles[i].p2.y, &triangles[i].p3.x, &triangles[i].p3.y) != 6) {
                printf("Error: unable to read triangle vertices\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(shape, "circle") == 0) {
            if (scanf("((%lf %lf), %lf)", &circle.center.x, &circle.center.y, &circle.radius) != 3) {
                printf("Error: unable to read circle parameters\n");
                exit(EXIT_FAILURE);
            }
        } else {
            printf("Error: invalid shape type\n");
            exit(EXIT_FAILURE);
        }
    }

    // Вывод результатов
    for (int i = 0; i < 3; ++i) {
        printf("%d. triangle((%.1lf %.1lf, %.1lf %.1lf, %.1lf %.1lf, %.1lf %.1lf))\n", i + 1, triangles[i].p1.x, triangles[i].p1.y, triangles[i].p2.x, triangles[i].p2.y, triangles[i].p3.x, triangles[i].p3.y, triangles[i].p1.x, triangles[i].p1.y);
        printf("    perimeter = %.3lf\n", triangle_perimeter(triangles[i]));
        printf("    area = %.1lf\n", triangle_area(triangles[i]));
        printf("    intersects:\n");
        if (intersects_circle_triangle(circle, triangles[i])) {
            printf("      circle\n");
        }
    }

printf("%d. circle((%.1lf %.1lf), %.1lf)\n", 2, circle.center.x, circle.center.y, circle.radius);
    printf("    perimeter = %.4lf\n", circle_perimeter(circle.radius));
    printf("    area = %.4lf\n", circle_area(circle.radius));
    printf("    intersects:\n");
    for (int i = 0; i < 3; ++i) {
        if (intersects_circle_triangle(circle, triangles[i])) {
            printf("      triangle\n");
        }
    }

    return 0;
}