#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int id;
    char name[30];
    float salary;
};

int main() {
    FILE *fp;
    struct Employee emp;
    int choice, rec_no;

    fp = fopen("employee.dat", "rb+");

    if (fp == NULL) {
        fp = fopen("employee.dat", "wb+");
        if (fp == NULL) {
            printf("Error opening file!\n");
            return 1;
        }
    }

    while (1) {
        printf("\n--- RANDOM ACCESS EMPLOYEE FILE ---\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee by Record Number\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter Employee ID: ");
            scanf("%d", &emp.id);
            printf("Enter Name: ");
            scanf("%s", emp.name);
            printf("Enter Salary: ");
            scanf("%f", &emp.salary);

            fseek(fp, 0, SEEK_END);  // Move to end for new record
            fwrite(&emp, sizeof(emp), 1, fp);
            printf("Employee Added Successfully!\n");
            break;

        case 2:
            rewind(fp);
            printf("\nEmployee Details:\n");

            while (fread(&emp, sizeof(emp), 1, fp))
                printf("ID: %d  Name: %s  Salary: %.2f\n",
                       emp.id, emp.name, emp.salary);
            break;

        case 3:
            printf("Enter Record Number (starting from 1): ");
            scanf("%d", &rec_no);

            fseek(fp, (rec_no - 1) * sizeof(emp), SEEK_SET);

            if (fread(&emp, sizeof(emp), 1, fp))
                printf("ID: %d  Name: %s  Salary: %.2f\n",
                       emp.id, emp.name, emp.salary);
            else
                printf("Record Not Found!\n");
            break;

        case 4:
            fclose(fp);
            exit(0);

        default:
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}
