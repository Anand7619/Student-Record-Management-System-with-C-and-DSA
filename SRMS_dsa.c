#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SUBJECTS 5

// Define a structure to represent subject details
struct Subject {
    char name[30];
    float marks;
};

// Define a structure to represent contact details
struct Contact {
    char mobileNumber[15];
    char email[50];
};

// Define a structure to represent a student
struct Student {
    char name[50];
    char SRN[15];
    struct Contact contact;
    struct Subject subjects[NUM_SUBJECTS];
    struct Student* next; // Pointer to the next student in the linked list
};

// Define a structure to represent a stack node
struct StackNode {
    struct Student* data; // Pointer to the student in the linked list
    struct StackNode* next; // Pointer to the next node in the stack
};

// Define a structure to represent a queue node
struct QueueNode {
    int taskType; // 1 for add student, 2 for delete student, 3 for search student, 4 for edit student details
    struct Student* student; // Pointer to the student structure
    struct QueueNode* next; // Pointer to the next node in the queue
};

// Function to create a new node for the linked list
struct Student* createStudent(char name[], char SRN[], struct Contact contact, struct Subject subjects[NUM_SUBJECTS]) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    strcpy(newStudent->name, name);
    strcpy(newStudent->SRN, SRN);
    strcpy(newStudent->contact.mobileNumber, contact.mobileNumber);
    strcpy(newStudent->contact.email, contact.email);
    for (int i = 0; i < NUM_SUBJECTS; ++i) {
        strcpy(newStudent->subjects[i].name, subjects[i].name);
        newStudent->subjects[i].marks = subjects[i].marks;
    }
    newStudent->next = NULL;
    return newStudent;
}

// Function to insert a student at the beginning of the linked list
struct Student* insertStudent(struct Student* head, char name[], char SRN[], struct Contact contact, struct Subject subjects[NUM_SUBJECTS]) {
    struct Student* newStudent = createStudent(name, SRN, contact, subjects);
    newStudent->next = head;
    return newStudent;
}

// Function to display information of a student
void displayStudent(struct Student* student) {
    printf("Name: %s\n", student->name);
    printf("SRN: %s\n", student->SRN);
    printf("Contact Details:\n");
    printf("  Mobile Number: %s\n", student->contact.mobileNumber);
    printf("  Email: %s\n", student->contact.email);
    printf("Subject Details:\n");
    for (int i = 0; i < NUM_SUBJECTS; ++i) {
        printf("  Subject %d: %s - %.2f\n", i + 1, student->subjects[i].name, student->subjects[i].marks);
    }
    printf("\n"); 
}

// Function to push a student onto the stack
struct StackNode* push(struct StackNode* top, struct Student* student) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    newNode->data = student;
    newNode->next = top;
    return newNode;
}

// Function to pop a student from the stack
struct StackNode* pop(struct StackNode* top) {
    if (top == NULL) {
        printf("Stack is empty.\n");
        return NULL;
    }

    struct StackNode* temp = top;
    top = top->next;
    free(temp);
    return top;
}

// Function to enqueue a task into the queue
struct QueueNode* enqueue(struct QueueNode* rear, int taskType, struct Student* student) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->taskType = taskType;
    newNode->student = student;
    newNode->next = NULL;

    if (rear == NULL) {
        return newNode;
    } else {
        rear->next = newNode;
        return newNode;
    }
}

// Function to dequeue a task from the queue
struct QueueNode* dequeue(struct QueueNode* front) {
    if (front == NULL) {
        printf("Queue is empty.\n");
        return NULL;
    }

    struct QueueNode* temp = front;
    front = front->next;
    free(temp);
    return front;
}

// Function to display all students in the linked list
void displayAllStudents(struct Student* head) {
    struct Student* current = head;
    printf("\nStudent Records:\n");
    while (current != NULL) {
        displayStudent(current);
        current = current->next;
    }
}

// Function to search for a student by SRN
struct Student* searchStudent(struct Student* head, char SRN[]) {
    struct Student* current = head;
    while (current != NULL) {
        if (strcmp(current->SRN, SRN) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// Function to edit student details
// Function to edit student details
void editStudentDetails(struct Student* student) {
    printf("Editing Student Details for SRN: %s\n", student->SRN);

    int editChoice;
    do {
        printf("\nEdit Options:\n");
        printf("1. Edit Name\n");
        printf("2. Edit Mobile Number\n");
        printf("3. Edit Email\n");
        printf("4. Edit Subject Details\n");
        printf("5. Done Editing\n");
        printf("Enter your choice: ");
        scanf("%d", &editChoice);

        switch (editChoice) {
            case 1: {
                printf("Enter the new name: ");
                scanf("%s", student->name);
                printf("Name updated successfully.\n");
                break;
            }
            case 2: {
                printf("Enter the new mobile number: ");
                scanf("%s", student->contact.mobileNumber);
                printf("Mobile number updated successfully.\n");
                break;
            }
            case 3: {
                printf("Enter the new email: ");
                scanf("%s", student->contact.email);
                printf("Email updated successfully.\n");
                break;
            }
            case 4: {
                printf("Enter details for each subject:\n");
                for (int i = 0; i < NUM_SUBJECTS; ++i) {
                    printf("Subject %d Name: ", i + 1);
                    scanf("%s", student->subjects[i].name);
                    printf("Subject %d Marks: ", i + 1);
                    scanf("%f", &student->subjects[i].marks);
                }
                printf("Subject details updated successfully.\n");
                break;
            }
            case 5:
                printf("Done editing.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (editChoice != 5);
}
struct Student* deleteStudent(struct Student* head, char deleteSRN[]) {
    struct Student* current = head;
    struct Student* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->SRN, deleteSRN) == 0) {
            // Found the student to delete
            if (prev == NULL) {
                // If the student is the first in the list
                head = current->next;
            } else {
                // If the student is not the first in the list
                prev->next = current->next;
            }

            // Free the memory for the deleted student
            free(current);
            return head;
        }

        // Move to the next student
        prev = current;
        current = current->next;
    }

    // Student with the given SRN not found
    return head;
}


// Function to free memory allocated for the linked list
void freeStudentList(struct Student* head) {
    struct Student* current = head;
    struct Student* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

// Function to free memory allocated for the stack
void freeStack(struct StackNode* top) {
    struct StackNode* current = top;
    struct StackNode* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

// Function to free memory allocated for the queue
void freeQueue(struct QueueNode* front) {
    struct QueueNode* current = front;
    struct QueueNode* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

void aboutUs() {
    printf("\nAbout Us:\n");
    printf("This program is a Student Record Management System.\n");
    printf("It allows you to add, delete, display, search, and edit student details.\n");
     printf("Used data structures are array,structures,linkedlist,stack,queue,trees.\n");

    printf("Developed by AAA foundation.\n");
    // You can customize this message as needed.
}

int main() {
    struct Student* head = NULL;
    struct StackNode* stackTop = NULL;
    struct QueueNode* front = NULL;
    struct QueueNode* rear = NULL;

    int choice;
    do {
       
        printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
        printf("@@                                                @@");
        printf("\n@@      ' Student Record Management System '      @@\n");
        printf("@@                                                @@\n");
        printf("@@  1. Add Student                                @@\n");
        printf("@@  2. Delete Student                             @@\n");
        printf("@@  3. Display All Students                       @@\n");
        printf("@@  4. Search Student                             @@\n");
        printf("@@  5. Edit Student Details                       @@\n");
        printf("@@  6. About Us                                   @@\n");
        printf("@@  7. Exit                                       @@\n" );
        printf("@@                                                @@\n");
         printf("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n");
         
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                char name[50];
                char SRN[15];
                struct Contact contact;
                struct Subject subjects[NUM_SUBJECTS];

                printf("Enter details for the new student:\n");
                printf("Name: ");
                scanf("%s", name);
                printf("SRN: ");
                scanf("%s", SRN);
                printf("Mobile Number: ");
                scanf("%s", contact.mobileNumber);
                printf("Email: ");
                scanf("%s", contact.email);
                printf("Enter details for each subject:\n");
                for (int i = 0; i < NUM_SUBJECTS; ++i) {
                    printf("Subject %d Name: ", i + 1);
                    scanf("%s", subjects[i].name);
                    printf("Subject %d Marks: ", i + 1);
                    scanf("%f", &subjects[i].marks);
                }

                // Add student to the linked list
                head = insertStudent(head, name, SRN, contact, subjects);

                // Push onto the stack
                stackTop = push(stackTop, head);

                // Enqueue task for asynchronous processing
                rear = enqueue(rear, 1, head);

                printf("Student added successfully.\n");
                break;
            }
             case 2: {
                char deleteSRN[15];
                printf("Enter the SRN to delete: ");
                scanf("%s", deleteSRN);

                // Search for the student
                struct Student* foundStudent = searchStudent(head, deleteSRN);

                if (foundStudent != NULL) {
                    // Remove the student from the linked list
                    head = deleteStudent(head, deleteSRN);

                    // Push onto the stack
                    stackTop = push(stackTop, head);

                    // Enqueue task for asynchronous processing
                    rear = enqueue(rear, 2, head);

                    printf("Student with SRN %s deleted successfully.\n", deleteSRN);
                } else {
                    printf("Student with SRN %s not found.\n", deleteSRN);
                }
                break;
            }
            case 3:
                // Display all student records
                displayAllStudents(head);
                break;
            case 4: {
                char SRN[15];
                printf("Enter the SRN to search: ");
                scanf("%s", SRN);

                // Search for the student
                struct Student* foundStudent = searchStudent(head, SRN);

                if (foundStudent != NULL) {
                    printf("Student found:\n");
                    displayStudent(foundStudent);
                } else {
                    printf("Student not found.\n");
                }
                break;
            }
            case 5: {
                char SRN[15];
                printf("Enter the SRN to edit: ");
                scanf("%s", SRN);

                // Search for the student
                struct Student* foundStudent = searchStudent(head, SRN);

                if (foundStudent != NULL) {
                    // Edit student details
                    editStudentDetails(foundStudent);
                    printf("Student details edited successfully.\n");
                } else {
                    printf("Student not found.\n");
                }
                break;
            }

             case 6:
                // About Us
                aboutUs();
                break;

            case 7:
                // Exit the program
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

        // Dequeue and process tasks asynchronously
        while (front != NULL) {
            struct QueueNode* task = front;
            front = dequeue(front);

            switch (task->taskType) {
                case 1:
                    // Task type 1: Add student
                    printf("Processing asynchronous task: Adding student.\n");
                    break;
                case 2:
                    // Task type 2: Delete student
                    printf("Processing asynchronous task: Deleting student.\n");
                    break;
                case 4:
                    // Task type 4: Edit student details
                    printf("Processing asynchronous task: Editing student details.\n");
                    break;
                // Add more task types as needed

                default:
                    printf("Invalid task type.\n");
            }

            free(task);
        }

    } while (choice != 6);

    // Free memory allocated for the linked list, stack, and queue
    freeStudentList(head);
    freeStack(stackTop);
    freeQueue(front);

    return 0;
}

