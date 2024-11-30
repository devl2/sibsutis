#include <stdio.h>

typedef struct 
{
    int school_num;
    int vipusk;
    int postup;
}school;

void bubble(school schools[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            double procent1 = ((double)schools[j].postup / schools[j].vipusk) * 100; //школа 1
            double procent2 = ((double)schools[j + 1].postup / schools[j + 1].vipusk) * 100; //школа 2

            if (procent1 < procent2)
            {
                school temp = schools[j];
                schools[j] = schools[j + 1];
                schools[j + 1] = temp;
            }
        }
    }
}


int main()
{
    school schools[] = {
        {1, 200, 160},
        {2, 150, 90},
        {3, 250, 180},
        {4, 340, 200}
    };
    int n = sizeof(schools)/sizeof(school);

    bubble(schools, n);

    for (int i = 0; i < n; i++)
    {
        double procent = ((double)schools[i].postup / schools[i].vipusk) * 100;
        printf("в школе %d, количество выпускников - %d, процент поступивших - %.2f \n", schools[i].school_num ,schools[i].vipusk, procent);
    }
    
    
    return 0;
}