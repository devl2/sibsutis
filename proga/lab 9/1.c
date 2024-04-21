#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct stud {
    char lname[30];
    int osenka[4];
    struct stud *next;
} list;

list *new_stud(char lname[], int osenka[]) {
    list *new_node = (list *)malloc(sizeof(list));
    strcpy(new_node->lname, lname);
    for (int i = 0; i < 4; i++) {
        new_node->osenka[i] = osenka[i];
    }
    new_node->next = NULL;
    return new_node;
}

list *add(list *kor, char lname[], int osenka[]) {
    if (kor == NULL) {
        kor = new_stud(lname, osenka);
    } else {
        list *curs = kor;
        while (curs->next != NULL) {
            curs = curs->next;
        }
        list *new_node = new_stud(lname, osenka);
        curs->next = new_node;
    }
    return kor;
}

void SortStudents(list *kor) {
    list *current, *nextStud;
    char temp[30];
    int tempOsenka[4];

    if (kor == NULL) {
        return;
    }

    current = kor;
    while (current != NULL) {
        nextStud = current->next;
        while (nextStud != NULL) {
            if (strcmp(current->lname, nextStud->lname) > 0) {
                strcpy(temp, current->lname);
                strcpy(current->lname, nextStud->lname);
                strcpy(nextStud->lname, temp);

                for (int i = 0; i < 4; ++i) {
                    tempOsenka[i] = current->osenka[i];
                    current->osenka[i] = nextStud->osenka[i];
                    nextStud->osenka[i] = tempOsenka[i];
                }
            }
            nextStud = nextStud->next;
        }
        current = current->next;
    }
}

int main() {
    list *kor = NULL;

    kor = add(kor, "Пупкин", (int[]){5, 4, 3, 4});
    kor = add(kor, "Иванов", (int[]){4, 2, 3, 4});
    kor = add(kor, "Сидоров", (int[]){5, 5, 4, 4});
    kor = add(kor, "Петров", (int[]){3, 4, 3, 4});

    SortStudents(kor);

    printf("Отсортированный массив:\n");
    printf("Фамилия и оценки\n");
    while (kor != NULL) {
        printf("%s ", kor->lname);
        for (int i = 0; i < 4; i++) {
            printf("%d ", kor->osenka[i]);
        }
        printf("\n");
        kor = kor->next;
    }

    return 0;
}
