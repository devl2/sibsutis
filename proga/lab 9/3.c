#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct stud {
    char lname[30];
    int osenka[4];
    struct stud *left;
    struct stud *right;
} list;

list *new_stud(char lname[], int osenka[]) {
    list *new_node = (list *)malloc(sizeof(list));
    strcpy(new_node->lname, lname);
    for (int i = 0; i < 4; i++) {
        new_node->osenka[i] = osenka[i];
    }
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

list *add(list *kor, list *new_node) {
    if (kor == NULL) {
        return new_node;
    }
    if (strcmp(new_node->lname, kor->lname) < 0) {
        kor->left = add(kor->left, new_node);
    } else { 
        kor->right = add(kor->right, new_node);
    }
    return kor;
}

void print_inc(list *kor) {
    if (kor != NULL) {
        print_inc(kor->left);
        printf("%s\n", kor->lname);
        print_inc(kor->right);
    }
}

void print_dec(list *kor) {
    if (kor != NULL) {
        print_dec(kor->right);
        printf("%s\n", kor->lname);
        print_dec(kor->left);
    }
}

list *search(list *kor, char *lname) {
    if (kor == NULL) {
        return kor;
    }
    if (strcmp(lname, kor->lname) == 0) {
        return kor;
    } 
    if (strcmp(lname, kor->lname) < 0) {
        return search(kor->left, lname);
    }
    return search(kor->right, lname);
}

int main() {
    list *kor = NULL;

    kor = add(kor, new_stud("Пупкин", (int[]){5, 4, 3, 4}));
    kor = add(kor, new_stud("Иванов", (int[]){4, 2, 3, 4}));
    kor = add(kor, new_stud("Сидоров", (int[]){5, 5, 4, 4}));
    kor = add(kor, new_stud("Петров", (int[]){3, 4, 3, 4}));

    printf("по возрастанию:\n");
    print_inc(kor);
    printf("\n");
    
    printf("по убыванию:\n");
    print_dec(kor);
    printf("\n");

    char searchStud[30] = "Петров";
    
    list *searchlname = search(kor, searchStud);

    if (searchlname != NULL) {
        printf("студент найден: %s\n", searchlname->lname);
    } else {
        printf("студент не найден\n");
    }
    
    return 0;
}
