#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct stud {
    char lname[30];
    int osenka[4];
    struct stud *next;
    struct stud *prev;
} list;

list *new_stud(char lname[], int osenka[]) {
    list *new_node = (list *)malloc(sizeof(list));
    strcpy(new_node->lname, lname);
    for (int i = 0; i < 4; i++) {
        new_node->osenka[i] = osenka[i];
    }
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

list *add(list *head, char lname[], int osenka[]) {
    if (head == NULL) {
        head = new_stud(lname, osenka);
    } else {
        list *curs = head;
        while (curs->next != NULL) {
            curs = curs->next;
        }
        list *new_node = new_stud(lname, osenka);
        curs->next = new_node;
        new_node->prev = curs;
    }
    return head;
}

list *del_stud(list *head)
{
    list *curs = head;
    while (curs != NULL) {
        int low_osenka = 0;
        for (int i = 0; i < 4; i++) {
            if (curs->osenka[i] < 3) {
                low_osenka = 1;
                break;
            }
        }
        if (low_osenka) {
            if (curs->prev != NULL) {
                curs->prev->next = curs->next;
            } else {
                head = curs->next;
            }
            if (curs->next != NULL) {
                curs->next->prev = curs->prev;
            }
            list *temp = curs;
            curs = curs->next;
            free(temp);
        } else {
            curs = curs->next;
        }
    }
}

list print_stud(list *head) {
    printf("студенты: \n");
    while (head != NULL)
    {
        printf("Фамилия: %s | оценки: ", head -> lname);
        for (int i = 0; i < 4; i++)
        {
            printf("%d ", head -> osenka[i]);
        }
        head = head -> next;
        printf("\n");
    }
}

int main() {
    list *head = NULL;

    head = add(head, "Пупкин", (int[]){5, 3, 4, 4});
    head = add(head, "Иванов", (int[]){4, 2, 3, 4});
    head = add(head, "Сидоров", (int[]){2, 5, 4, 4});
    head = add(head, "Петров", (int[]){4, 4, 3, 4});

    print_stud(head);

    del_stud(head);

    print_stud(head);

    list *curs = head;
    while (curs != NULL) {
        list *next = curs->next;
        free(curs);
        curs = next;
    }
    
    return 0;
}
