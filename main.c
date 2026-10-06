#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "students.dat"

struct Student {
    int id;
    char name[50];
    int classNo;
    char address[100];
    float marks;
};

void clearInputBuffer() {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

void printHeader(const char *title) {
    printf("\n=================================================\n");
    printf("%s\n", title);
    printf("=================================================\n");
}

void addStudent() {
    FILE *fp;
    struct Student s;

    fp = fopen(FILENAME, "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n--------------- ADD STUDENT ----------------\n");
    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    clearInputBuffer();

    printf("Enter Student Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    s.name[strcspn(s.name, "\n")] = '\0';

    printf("Enter Class: ");
    scanf("%d", &s.classNo);
    clearInputBuffer();

    printf("Enter Address: ");
    fgets(s.address, sizeof(s.address), stdin);
    s.address[strcspn(s.address, "\n")] = '\0';

    printf("Enter Marks: ");
    scanf("%f", &s.marks);
    clearInputBuffer();

    fwrite(&s, sizeof(struct Student), 1, fp);
    fclose(fp);

    printf("Record added successfully!\n");
}

void displayAllStudents() {
    FILE *fp;
    struct Student s;
    int count = 0;

    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    printf("\n--------------- STUDENT RECORDS ----------------\n");
    printf("ID\tName\t\tClass\tMarks\n");
    printf("-------------------------------------------------------------\n");

    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        printf("%d\t%s\t\t%d\t%.2f\n", s.id, s.name, s.classNo, s.marks);
        count++;
    }

    fclose(fp);
    printf("\nTotal Records: %d\n", count);
}

void searchStudent() {
    FILE *fp;
    struct Student s;
    int id, found = 0;

    printf("\n--------------- SEARCH RECORD ------------------\n");
    printf("Enter Student ID: ");
    scanf("%d", &id);
    clearInputBuffer();

    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.id == id) {
            found = 1;
            printf("Record Found!\n");
            printf("Student ID : %d\n", s.id);
            printf("Student Name : %s\n", s.name);
            printf("Class : %d\n", s.classNo);
            printf("Address : %s\n", s.address);
            printf("Marks : %.2f\n", s.marks);
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("Record not found!\n");
    }
}

void updateStudent() {
    FILE *fp;
    FILE *tmp;
    struct Student s;
    int id, found = 0;

    printf("\n--------------- UPDATE RECORD -----------------\n");
    printf("Enter Student ID to update: ");
    scanf("%d", &id);
    clearInputBuffer();

    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    tmp = fopen("temp.dat", "wb");
    if (tmp == NULL) {
        printf("Error opening temporary file.\n");
        fclose(fp);
        return;
    }

    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.id == id) {
            found = 1;
            printf("Current Name : %s\n", s.name);
            printf("Current Class : %d\n", s.classNo);
            printf("Current Marks : %.2f\n", s.marks);

            printf("Enter New Name: ");
            fgets(s.name, sizeof(s.name), stdin);
            s.name[strcspn(s.name, "\n")] = '\0';

            printf("Enter New Class: ");
            scanf("%d", &s.classNo);
            clearInputBuffer();

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);
            clearInputBuffer();

            printf("Record updated successfully!\n");
        }
        fwrite(&s, sizeof(struct Student), 1, tmp);
    }

    fclose(fp);
    fclose(tmp);

    if (!found) {
        remove("temp.dat");
        printf("Record not found!\n");
    } else {
        remove(FILENAME);
        rename("temp.dat", FILENAME);
    }
}

void deleteStudent() {
    FILE *fp;
    FILE *tmp;
    struct Student s;
    int id, found = 0;
    char choice;

    printf("\n--------------- DELETE RECORD -----------------\n");
    printf("Enter Student ID to delete: ");
    scanf("%d", &id);
    clearInputBuffer();

    fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("No records found.\n");
        return;
    }

    tmp = fopen("temp.dat", "wb");
    if (tmp == NULL) {
        printf("Error opening temporary file.\n");
        fclose(fp);
        return;
    }

    while (fread(&s, sizeof(struct Student), 1, fp) == 1) {
        if (s.id == id) {
            found = 1;
            printf("Student Record:\n");
            printf("ID : %d\n", s.id);
            printf("Name : %s\n", s.name);
            printf("Class : %d\n", s.classNo);
            printf("Marks : %.2f\n", s.marks);
            printf("Are you sure you want to delete? (Y/N): ");
            scanf(" %c", &choice);
            clearInputBuffer();

            if (choice == 'Y' || choice == 'y') {
                printf("Record deleted successfully!\n");
                continue;
            } else {
                printf("Deletion cancelled.\n");
                fwrite(&s, sizeof(struct Student), 1, tmp);
                continue;
            }
        }
        fwrite(&s, sizeof(struct Student), 1, tmp);
    }

    fclose(fp);
    fclose(tmp);

    if (!found) {
        remove("temp.dat");
        printf("Record not found!\n");
    } else {
        remove(FILENAME);
        rename("temp.dat", FILENAME);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n=================================================\n");
        printf("STUDENT RECORD MANAGEMENT SYSTEM\n");
        printf("\nCCRC\n");
        printf("=================================================\n");
        printf("1. Add Student Record\n");
        printf("2. Display All Records\n");
        printf("3. Search Student Record\n");
        printf("4. Update Student Record\n");
        printf("5. Delete Student Record\n");
        printf("6. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        clearInputBuffer();

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("\nThank you for using Student Record Management System!\n");
                printf("=================================================\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
