#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct passenger
{
    char name[200];
    int mesto;
    double ves;
} pas;

void create_file(int N)
{
    FILE *file = fopen("pas.txt", "w");

    pas passenger;
    if (N > 0) {
        for (int i = 0; i < N; i++) {
            printf("Введите ФИО пассажира, количество занимаемых багажом мест и его общий вес: ");
            if (scanf("%s", passenger.name) != 1) {
                printf("Ошибка: Некорректный ввод для имени.\n");
                fclose(file);
                return;
            }
            if (scanf("%d", &passenger.mesto) != 1 || passenger.mesto <= 0) {
                printf("Ошибка: Некорректный ввод для количества мест.\n");
                i--; // уменьшаем счетчик, чтобы повторно запросить ввод для текущего пассажира
                while (getchar() != '\n'); // очищаем буфер ввода
                continue; // переходим к следующей итерации цикла
            }
            if (scanf("%lf", &passenger.ves) != 1 || passenger.ves <= 0) {
                printf("Ошибка: Некорректный ввод для веса.\n");
                i--; // уменьшаем счетчик, чтобы повторно запросить ввод для текущего пассажира
                while (getchar() != '\n'); // очищаем буфер ввода
                continue; // переходим к следующей итерации цикла
            }
            fprintf(file, "%s %d %.2f\n", passenger.name, passenger.mesto, passenger.ves);
        }
        printf("Успех! Создан файл из %d записей\n", N);
    } else {
        printf("Ошибка: Некорректное количество пассажиров.\n");
    }
    fclose(file);
}



void prosmotr()
{
    FILE *file = fopen("pas.txt", "r");

    printf("содержимое:\n");
    char line[300];
    while (fgets(line, sizeof(line), file))
    {
        printf("%s", line);
    }

    fclose(file);
}

void dobav()
{
    FILE *file = fopen("pas.txt", "a");
    pas passenger;
    printf("введите ФИО пассажира, кол-во занимаемых багажом мест и общий вес багажа: ");

    if(scanf("%s %d %lf", passenger.name, &passenger.mesto, &passenger.ves) != 3 && !isdigit(&passenger.mesto && &passenger.ves)){ //isdigit - проверка является ли введенное значение числом
        printf("ошибка: некорректный ввод");
        fclose(file);
        return;
    } else {
        fprintf(file, "%s %d %.2f\n", passenger.name, passenger.mesto, passenger.ves);
    }

    fclose(file);
    printf("успех! люди добавлены");
}

void del()
{
    FILE *file = fopen("pas.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    
    pas passenger;
    
    while(fscanf(file, "%s %d %lf", passenger.name, &passenger.mesto, &passenger.ves) != EOF)
    {
        if (passenger.ves >= 10.0)
        {
            fprintf(temp, "%s %d %.2f\n", passenger.name, passenger.mesto, passenger.ves);
        }
    }

    fclose(file);
    fclose(temp);

    remove("pas.txt");
    rename("temp.txt", "pas.txt");
    
    printf("успех! записи о пассажирах с весом меньше 10кг удалены");
}


void modify_ves()
{
    char name[200];
    printf("введите фамилию пассажира, чей вес вещей необходимо изменить: ");
    scanf("%s", name);
    
    FILE *file = fopen("pas.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    
    int found = 0;
    
    pas passenger;
    while (fscanf(file, "%s %d %lf", passenger.name, &passenger.mesto, &passenger.ves) != EOF) {
        if (strcmp(passenger.name, name) == 0) {
            found = 1;
            printf("текущий вес вещей для %s: %.2f\n", passenger.name, passenger.ves);
            printf("Введите новый вес вещей: ");
            scanf("%lf", &passenger.ves);
        }
        fprintf(temp, "%s %d %.2f\n", passenger.name, passenger.mesto, passenger.ves);
    }

    fclose(file);
    fclose(temp);
    
    if (!found){
        printf("данный пассажир с фамилией %s не найден!\n", name);
        remove("temp.txt");
        return;
    }

    remove("pas.txt");
    rename("temp.txt", "pas.txt");
    printf("успех! вес изменен");
}

int main()
{
    int ch, N;
    char name[200];
    do{
        printf("\nменю:\n");
        printf("1. Создать файл\n");
        printf("2. Посмотреть файл\n");
        printf("3. Добавить в конец новую запись\n");
        printf("4. Найти и удалить из файла пассажира с весом меньше 10кг\n");
        printf("5. Изменить вес по определенной фамилии\n");
        printf("0. Выйти.\n");
        printf("Выберите пункт: ");
        scanf("%d", &ch);
        
        switch (ch)
        {
        case 1:
            printf("введите кол-во записей: ");
            scanf("%d", &N);
            create_file(N);
            break;
    
        case 2:
            prosmotr();
            break;
        
        case 3:
            dobav();
            break;
    
        case 4:
            del();
            break;
        
        case 5:
            modify_ves();
            break;
        
        case 0:
            printf("программа завершена!");
            break;
    
        default:
                printf("неверный выбор операции \n");
                break;
        }
        
    } while(ch != 0);
    return 0;
}       