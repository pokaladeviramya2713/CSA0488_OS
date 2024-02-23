#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int empId;
    char empName[50];
    float empSalary;
};

void addEmployee(FILE *file) {
    struct Employee newEmployee;

    printf("Enter Employee ID: ");
    scanf("%d", &newEmployee.empId);

    printf("Enter Employee Name: ");
    scanf("%s", newEmployee.empName);

    printf("Enter Employee Salary: ");
    scanf("%f", &newEmployee.empSalary);

    fseek(file, (newEmployee.empId - 1) * sizeof(struct Employee), SEEK_SET);
    fwrite(&newEmployee, sizeof(struct Employee), 1, file);

    printf("Employee added successfully!\n");
}

void displayAllEmployees(FILE *file) {
    struct Employee employee;

    rewind(file);

    printf("\nEmployee Details:\n");

    while (fread(&employee, sizeof(struct Employee), 1, file) == 1) {
        printf("ID: %d, Name: %s, Salary: %.2f\n", employee.empId, employee.empName, employee.empSalary);
    }
}

void searchEmployee(FILE *file) {
    int empId;
    struct Employee employee;

    printf("Enter Employee ID to search: ");
    scanf("%d", &empId);

    fseek(file, (empId - 1) * sizeof(struct Employee), SEEK_SET);
    if (fread(&employee, sizeof(struct Employee), 1, file) == 1) {
        printf("Employee Found!\n");
        printf("ID: %d, Name: %s, Salary: %.2f\n", employee.empId, employee.empName, employee.empSalary);
    } else {
        printf("Employee with ID %d not found.\n", empId);
    }
}

int main() {
    FILE *employeeFile;

    // Open the file for random access
    employeeFile = fopen("employee.dat", "r+");

    if (employeeFile == NULL) {
        // If the file doesn't exist, create a new one
        employeeFile = fopen("employee.dat", "w+");
        if (employeeFile == NULL) {
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
    }

    int choice;
    do {
        printf("\nMenu:\n");
        printf("1. Add Employee\n");
        printf("2. Display All Employees\n");
        printf("3. Search Employee\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee(employeeFile);
                break;
            case 2:
                displayAllEmployees(employeeFile);
                break;
            case 3:
                searchEmployee(employeeFile);
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);

    // Close the file
    fclose(employeeFile);

    return 0;
}

