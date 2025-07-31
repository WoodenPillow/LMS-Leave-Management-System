#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>

#define MAX_EMPLOYEES 50
#define MAX_LEAVES 10
#define MAX_DEPARTMENTS 4
#define MAX_LENGTH 100


struct Employee {
    char name[MAX_LENGTH];
    int id;
    int department;
    int leaves_remaining;
};

typedef enum {
    PENDING,
    APPROVED,
    REJECTED
} LeaveStatus;

struct Leave {
    int id;
    int employee_id;
    char start_date[MAX_LENGTH];
    char end_date[MAX_LENGTH];
    char reason[MAX_LENGTH];
    LeaveStatus status;
};

struct Employee employees[MAX_EMPLOYEES];
int employee_count = 0;

struct Leave leaves[MAX_LEAVES];
int leave_count = 0;

int department_leaves[MAX_DEPARTMENTS];

void display_admin_menu() {
    printf("Admin Menu\n");
    printf("1. Add Staff\n");
    printf("2. View Staff\n");
    printf("3. View Leave Summary\n");
    printf("4. Write staff to a text file\n");
    printf("5. Read staff from a text file\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}


void display_staff_menu() {
    printf("Staff Menu\n");
    printf("1. View Pending Leaves\n");
    printf("2. View Leaves\n");
    printf("3. Apply for Leave\n");
    printf("4. Cancel leave request\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}


void display_leave_approver_menu() {
    printf("Leave Approver Menu\n");
    printf("1. View Pending Leaves\n");
    printf("2. Approve Leave\n");
    printf("3. View Staff On Leave on a Specific Date\n");
    printf("4. Write leaves summary to text file\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}


void add_employee() {
    if (employee_count == MAX_EMPLOYEES) {
        printf("Error: Maximum number of employees reached\n");
        return;
    }

    printf("Enter employee name: ");
    scanf("%s", employees[employee_count].name);
    printf("Enter employee ID: ");
    scanf("%d", &employees[employee_count].id);
    printf("Enter the employee's department (1 to %d): ", MAX_DEPARTMENTS);
    scanf("%d", &employees[employee_count].department);
    printf("Enter the number of leaves for %s: ", employees[employee_count].name);
    scanf("%d", &employees[employee_count].leaves_remaining);

    employee_count++;
    printf("Employee added successfully\n");
}

void read_employees() {
    if (employee_count == MAX_EMPLOYEES) {
        printf("Error: Maximum number of employees reached\n");
        return;
    }
    
    FILE* fp = fopen("employees.txt", "r");
    if (fp == NULL) {
        printf("\nNo employees found\n");
        return;
    }
    char buffer[1024];
    fgets(buffer, 1024, fp);
    while (fscanf(fp, "%d%s%d%d", &employees[employee_count].id, employees[employee_count].name
                  , &employees[employee_count].department, &employees[employee_count].leaves_remaining)==4)
    {
        employee_count++;
    }
    printf("\nEmployees read from file successfully\n\n");
    fclose(fp);
}


void view_employees() {
    if (employee_count == 0) {
        printf("\nNo employees found\n");
        return;
    }
    printf("ID\tName\tDepartment\tLeaves Remaining\n");
    for (int i = 0; i < employee_count; i++) {
        printf("%d\t%s\t%d\t\t%d\n", employees[i].id, employees[i].name, employees[i].department, employees[i].leaves_remaining);
    }
}

void write_employees() {
    if (employee_count == 0) {
        printf("\nNo employees found\n\n");
        return;
    }
    FILE* fp = fopen("employees.txt", "w");
    fprintf(fp, "ID\tName\tDepartment\tLeaves Remaining\n");
    for (int i = 0; i < employee_count; i++) {
        fprintf(fp, "%d\t%s\t%d\t\t%d\n", employees[i].id, employees[i].name, employees[i].department, employees[i].leaves_remaining);
    }
    
    printf("\nEmployees written to file successfully\n\n");
    fclose(fp);
}


void apply_for_leave() {
    if (employee_count == 0) {
        printf("\nNo employees found\n");
        return;
    }
    if (leave_count == MAX_LEAVES) {
        printf("Error: Maximum number of leave requests reached\n");
        return;
    }

    int employee_id;
    printf("Enter your employee ID: ");
    scanf("%d", &employee_id);

    bool found = false;
    int employee_index = 0;
    for (int i = 0; i < employee_count; i++) {
        if (employees[i].id == employee_id) {
            found = true;
            employee_index = i;
            break;
        }
    }

    if (!found) {
        printf("Error: Employee not found\n");
        return;
    }

    // Check if the employee has any leaves remaining
    if (employees[employee_index].leaves_remaining <= 0) {
        printf("Error: No leaves remaining for the employee\n");
        return;
    }

    struct Leave leave;
    leave.id = leave_count + 1;
    leave.employee_id = employee_id;

    printf("Enter the start date of the leave (DD-MM-YYYY): ");
    scanf("%s", leave.start_date);
    printf("Enter the end date of the leave (DD-MM-YYYY): ");
    scanf("%s", leave.end_date);
    printf("Enter the reason for the leave (maternity, sickleave, etc): ");
    scanf("%s", leave.reason);
    leave.status = PENDING;

    leaves[leave_count] = leave;
    leave_count++;

    employees[employee_index].leaves_remaining--;

    printf("Leave request sent successfully\n");
}


void view_leaves() {
    if (leave_count == 0) {
        printf("\nNo leaves found\n");
        return;
    }
    printf("ID\tEmployee ID\tStart Date\tEnd Date\tReason\t\tStatus\n");
    for (int i = 0; i < leave_count; i++) {
        const char* status;
        switch (leaves[i].status) {
        case PENDING:
            status = "PENDING";
            break;
        case APPROVED:
            status = "APPROVED";
            break;
        case REJECTED:
            status = "REJECTED";
            break;
        }

        printf("%d\t%d\t\t%s\t%s\t%s\t%s\n", leaves[i].id, leaves[i].employee_id, leaves[i].start_date, leaves[i].end_date, leaves[i].reason, status);
    }
}


void approve_leave() {
    int leave_id;
    printf("Enter the ID of the leave request to approve: ");
    scanf("%d", &leave_id);

    
    bool found = false;
    int leave_index = 0;
    for (int i = 0; i < leave_count; i++) {
        if (leaves[i].id == leave_id) {
            found = true;
            leave_index = i;
            break;
        }
    }

    if (!found) {
        printf("Error: Leave request not found\n");
        return;
    }

    
    if (leaves[leave_index].status != PENDING) {
        printf("Error: Leave request already processed\n");
        return;
    }

    
    leaves[leave_index].status = APPROVED;
    department_leaves[employees[leave_index].department]++;
    printf("Leave request approved successfully\n");
}


void view_staff_on_leave() {
    if (leave_count == 0) {
        printf("\nNo leaves found\n");
        return;
    }
    char date[100];
    printf("Enter the date (DD-MM-YYYY): ");
    scanf("%s", date);

    printf("ID\tName\n");
    for (int i = 0; i < leave_count; i++) {
        if (leaves[i].status == APPROVED && (strcmp(leaves[i].start_date, date) <= 0) && (strcmp(leaves[i].end_date, date) >= 0)) {
            int employee_id = leaves[i].employee_id;
            for (int j = 0; j < employee_count; j++) {
                if (employees[j].id == employee_id) {
                    printf("%d\t%s\n", employees[j].id, employees[j].name);
                    break;
                }
            }
        }
    }
}


void view_pending_leaves() {
    if (leave_count == 0) {
        printf("\nNo leaves found\n");
        return;
    }
    printf("ID\tEmployee ID\tStart Date\tEnd Date\tReason\n");
    for (int i = 0; i < leave_count; i++) {
        if (leaves[i].status == PENDING) {
            printf("%d\t%d\t\t%s\t%s\t%s\n", leaves[i].id, leaves[i].employee_id, leaves[i].start_date, leaves[i].end_date, leaves[i].reason);
        }
    }
}


void cancel_leave_request() {
    int leave_id;
    printf("Enter the leave ID of the leave request to cancel: ");
    scanf("%d", &leave_id);
    
    bool found = false;
    int leave_index = 0;
    for (int i = 0; i < leave_count; i++) {
        if (leaves[i].id == leave_id) {
            found = true;
            leave_index = i;
            break;
        }
    }
    if (!found) {
        printf("Error: Leave request not found\n");
        return;
    }
    
    for (int i = leave_index; i < leave_count - 1; i++) {
        leaves[i] = leaves[i + 1];
    }
    leave_count--;
    printf("Leave request with ID %d has been cancelled\n", leave_id);
}

void view_leave_summary() {
    printf("Department\tLeaves\n");
    for (int i = 0; i < MAX_DEPARTMENTS; i++) {
        printf("%d\t\t\t%d\n", i + 1, department_leaves[i]);
    }
}

void write_leaves_summary() {
    FILE* fp = fopen("leaves_summary.txt", "w");
    fprintf(fp, "Department\tLeaves\n");
    for (int i = 0; i < MAX_DEPARTMENTS; i++) {
        fprintf(fp, "%d\t\t%d\n", i, department_leaves[i]);
    }
    printf("\nLeaves written to file successfully\n\n");
    fclose(fp);
}
