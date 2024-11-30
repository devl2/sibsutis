#include <stdio.h>
#include <string.h>

int main() 
{
    char st[100], m[200][40];
    int n = 0;

    FILE *f1 = fopen("input.txt", "r");
    FILE *f2 = fopen("output.txt", "w");

    printf("txt1 и txt2 файлы открыты\n");

    while (fgets(st, 100, f1)) 
    {
        char *sl= strtok(st, " \n");
        while (sl != NULL && n < 200) 
        {
            strcpy(m[n++], sl);
            sl = strtok(NULL, " \n");
        }
    } 
    
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (strcmp(m[j], m[j + 1]) > 0) 
            {
                char temp[40];
                strcpy(temp, m[j]);
                strcpy(m[j], m[j + 1]);
                strcpy(m[j + 1], temp);
            }
        }
    }
    
    for (int i = 0; i < n; i++) 
    {
        fprintf(f2, "%s\n", m[i]);
    }
    
    fclose(f1);
    fclose(f2);

    return 0;
}