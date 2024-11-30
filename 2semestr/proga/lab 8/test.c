#include <stdio.h>
#include <string.h>

typedef struct 
{
    int num_room;
    double ploshad;
    char fakult[10];
    int kol_people;
} room;

void fakult_count(const room rooms[], char fakult[][6], int rooms_num, int *num_fackult)
{
    *num_fackult = 0;

    for(int i = 0; i < rooms_num; i++)
    {
        int nashel = 0;
        for (int j = 0; j < *num_fackult; j++)
        {
            if(strcmp(rooms[i].fakult, fakult[j]) == 0)
            {
                nashel += 1;
                break;
            }
        }

        if(!nashel)
        {
            strcpy(fakult[*num_fackult], rooms[i].fakult);
            (*num_fackult)++;
        }
    }
}

void fakult_stat(const room rooms[], int *num_fakult, int rooms_num, char fakult[][6])
{
    int total_rooms = 0, total_stud = 0;
    double ploshad = 0, sred_ploshad = 0;
    int i;
    for(int i = 0; i < *num_fakult; i++)
    {
        for (int j = 0; j < rooms_num; j++)
        {
            if(strcmp(rooms[j].fakult, fakult[i]) == 0)
            {
                total_rooms++;
                total_stud += rooms[j].kol_people;
                ploshad += rooms[j].ploshad;
            }
        }

        if (total_stud > 0)
        {
            sred_ploshad = ploshad / total_stud;
        } else {
            sred_ploshad = 0;
        }
    }
    printf("факультет - %s, кол-во комнат - %d, кол - во студентов - %d, средняя площадь - %.2f", fakult[i], total_rooms, total_stud, sred_ploshad);
}

int main()
{
    room rooms[] = {
        {36, 23.3, "IVT", 3},
        {99, 25.4, "IB", 4},
        {39, 22.1, "IT", 4},
        {57, 20.7, "IZ", 2},
        {101, 24.7, "IVT", 2},
        {84, 23.7, "IB", 2}
    };

    int rooms_num = 6;
    int num_fackult;
    char fakult[10][6];

    fakult_count(rooms, fakult, rooms_num, &num_fackult);

    printf("факультеты:\n");
    for (int i = 0; i < num_fackult; i++) {
        printf("%s ", fakult[i]);
    }
    printf("\nколичество факультетов - %d\n", num_fackult);
    
    for (int i = 0; i < num_fackult; i++)
    {
        fakult_stat(rooms, &num_fackult, rooms_num, fakult);
    }
    
    return 0;
}
