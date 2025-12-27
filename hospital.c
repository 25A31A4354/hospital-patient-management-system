#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Clear input buffer */
void clearInputBuffer() {
    while (getchar() != '\n');
}

/* Convert string to lowercase */
void toLowerCase(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = tolower(str[i]);
    }
}

/* Safe integer input */
int readInt(char message[]) {
    int value;
    while (1) {
        printf("%s", message);
        if (scanf("%d", &value) == 1) {
            clearInputBuffer();
            return value;
        } else {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
        }
    }
}

/* Safe float input */
float readFloat(char message[]) {
    float value;
    while (1) {
        printf("%s", message);
        if (scanf("%f", &value) == 1) {
            clearInputBuffer();
            return value;
        } else {
            printf("Invalid input. Please enter a numeric value.\n");
            clearInputBuffer();
        }
    }
}

/* Add patient record (STRUCTURED STORAGE) */
void addPatient() {
    FILE *fp = fopen("hospital_data.txt", "a");
    char severity[10], name[50], medicine[50];
    int id, age, bp, sugar;
    float temperature;

    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\n--- Add Patient Record ---\n");

    id = readInt("Enter Patient ID: ");

    printf("Enter Patient Name: ");
    scanf("%s", name);
    clearInputBuffer();

    age = readInt("Enter Age: ");
    bp = readInt("Enter BP: ");
    sugar = readInt("Enter Sugar Level: ");
    temperature = readFloat("Enter Temperature: ");

    printf("Enter Medicine Name: ");
    scanf("%s", medicine);
    clearInputBuffer();

    printf("Enter Severity (Mild / Moderate / Severe): ");
    scanf("%s", severity);
    clearInputBuffer();

    toLowerCase(severity);

    fprintf(fp, "----------------------------\n");
    fprintf(fp, "Patient ID      : %d\n", id);
    fprintf(fp, "Name            : %s\n", name);
    fprintf(fp, "Age             : %d\n", age);
    fprintf(fp, "BP              : %d\n", bp);
    fprintf(fp, "Sugar Level     : %d\n", sugar);
    fprintf(fp, "Temperature     : %.1f\n", temperature);
    fprintf(fp, "Medicine        : %s\n", medicine);
    fprintf(fp, "Severity        : %s\n", severity);
    fprintf(fp, "----------------------------\n\n");

    fclose(fp);

    printf("\n✅ Patient record saved successfully.\n");
}

/* View all patient records */
void viewPatients() {
    FILE *fp = fopen("hospital_data.txt", "r");
    char ch;

    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    printf("\n--- ALL PATIENT RECORDS ---\n\n");

    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }

    fclose(fp);
}

/* Filter patients by severity (READABLE FILE FILTERING) */
void filterPatientsBySeverity() {
    FILE *fp = fopen("hospital_data.txt", "r");
    char line[200], severityInput[10];
    char record[1000];
    int matchFound = 0;

    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    printf("\nEnter Severity to filter (Mild / Moderate / Severe): ");
    scanf("%s", severityInput);
    clearInputBuffer();
    toLowerCase(severityInput);

    record[0] = '\0';

    while (fgets(line, sizeof(line), fp)) {
        strcat(record, line);

        if (strncmp(line, "Severity", 8) == 0) {
            char fileSeverity[20];
            sscanf(line, "Severity        : %s", fileSeverity);

            if (strcmp(fileSeverity, severityInput) == 0) {
                matchFound = 1;
            }
        }

        if (strncmp(line, "----------------------------", 28) == 0 &&
            strlen(record) > 30) {

            if (matchFound) {
                printf("\n%s", record);
            }

            record[0] = '\0';
            matchFound = 0;
        }
    }

    fclose(fp);

    if (!matchFound && record[0] == '\0') {
        printf("\n(No more matching records)\n");
    }
}

/* Main menu */
int main() {
    int choice;

    do {
        printf("\n--- Hospital Patient Management System ---\n");
        printf("1. Add Patient Record\n");
        printf("2. View Patient Records\n");
        printf("3. Filter Patients by Severity\n");
        printf("4. Exit\n");

        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1:
                addPatient();
                break;
            case 2:
                viewPatients();
                break;
            case 3:
                filterPatientsBySeverity();
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice.\n");
        }

    } while (choice != 4);

    return 0;
}
