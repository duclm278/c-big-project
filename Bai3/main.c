#include <stdio.h>
#include <string.h>
#include "student.h"

void option1(void);
void option2(void);
void option3(void);

int main(void)
{
    int option;

    do
    {
        // Print out menu
        printf("+--------------------------------------+\n");
        printf("| Chuong trinh quan ly sinh vien       |\n");
        printf("+--------------------------------------+\n");
        printf("| 1. Xem danh sach sinh vien           |\n");
        printf("| 2. Nhap them sinh vien               |\n");
        printf("| 3. Tim sinh vien theo ten            |\n");
        printf("| 4. Thoat                             |\n");
        printf("+--------------------------------------+\n");

        // Read option
        printf("Choose an option: ");
        if (scanf("%d", &option) != 1)
            return 1;

        // Perform option
        switch (option)
        {
        case 1:
            option1();
            break;
        case 2:
            option2();
            break;
        case 3:
            option3();
            break;
        case 4:
            return 0;
        default:
            return 1;
        }

        printf("\n");
    }
    while (1);
}

void option1(void)
{
    student somebody;

    // Open SV2021.dat
    FILE *input = fopen("SV2021.dat", "r");

    // Print out SV2021.dat
    while (fscanf(input, "%[^\t]\t%lf\n", somebody.name, &somebody.score) != EOF)
    {
        printf("- %s\t%.2lf\n", somebody.name, somebody.score);
    }

    // Close SV2021.dat
    fclose(input);
}

void option2(void)
{
    student new_student;

    // Open SV2021.dat
    FILE *input = fopen("SV2021.dat", "a");

    // Get input and update SV2021.dat
    printf("Enter name: ");
    getchar();
    gets(new_student.name);
    printf("Enter score: ");
    scanf("%lf", &new_student.score);
    fprintf(input, "%-*s\t%.2lf\n", MAX_LENGTH, new_student.name, new_student.score);

    // Close SV2021.dat
    fclose(input);
}

void option3(void)
{
    student student_from_SV2021;
    char search[MAX_LENGTH + 1];
    int count = 0;

    // Open SV2021.dat
    FILE *input = fopen("SV2021.dat", "r");

    // Get input
    printf("Enter name: ");
    getchar();
    gets(search);

    // Read SV2021.dat and print out result
    while (fscanf(input, "%[^\t]\t%lf\n", student_from_SV2021.name, &student_from_SV2021.score) != EOF)
    {
        if (strstr(student_from_SV2021.name, search) != NULL)
        {
            printf("- %-*s\t%.2lf\n", MAX_LENGTH, student_from_SV2021.name, student_from_SV2021.score);
            count++;
        }
    }
    if (count == 0)
        printf("Not found!\n");

    // Close SV2021.dat
    fclose(input);
}
