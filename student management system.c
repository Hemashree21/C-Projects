#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a structure for a user (teacher or student)
struct User
{
    char username[50];
    char password[50];
    int isTeacher; // 1 for teacher, 0 for student
    struct User *next;
};
struct Task {
    char date[20];
    char description[100];
    int isDone; // 0 for not done, 1 for done
    int percentageCompleted; // Track the percentage of completion
};

// Function to create a new user node
struct User *createUser(const char *username, const char *password, int isTeacher)
{
    struct User *newUser = (struct User *)malloc(sizeof(struct User));
    if (newUser == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    strncpy(newUser->username, username, sizeof(newUser->username));
    strncpy(newUser->password, password, sizeof(newUser->password));
    newUser->isTeacher = isTeacher;
    newUser->next = NULL;

    return newUser;
}

// Function to add a new user to the linked list
void addUser(struct User **head, const char *username, const char *password, int isTeacher)
{
    struct User *newUser = createUser(username, password, isTeacher);
    newUser->next = *head;
    *head = newUser;
    printf("User added successfully.\n");
}

// Function to authenticate a user
struct User *authenticateUser(const struct User *head, const char *username, const char *password)
{
    while (head != NULL)
    {
        if (strcmp(head->username, username) == 0 && strcmp(head->password, password) == 0)
        {
            return (struct User *)head;
        }
        head = head->next;
    }
    return NULL; // User not found or invalid credentials
}

// Define a structure for a student
struct Student
{
    int rollNumber;
    char name[50];
    float marks;
    int attendance; // Added field for attendance
    struct Student *next;
};

// Function to create a new student node
struct Student *createStudent(int rollNumber, const char *name, float marks, int attendance)
{
    struct Student *newStudent = (struct Student *)malloc(sizeof(struct Student));
    if (newStudent == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    newStudent->rollNumber = rollNumber;
    strncpy(newStudent->name, name, sizeof(newStudent->name));
    newStudent->marks = marks;
    newStudent->attendance = 0;
    newStudent->next = NULL;

    return newStudent;
}

// Function to sort students based on roll numbers in ascending order
void sortStudents(struct Student *head)
{
    struct Student *current, *nextStudent;
    int tempRollNumber;
    char tempName[50];
    float tempMarks;

    if (head == NULL)
    {
        return;
    }

    for (current = head; current->next != NULL; current = current->next)
    {
        for (nextStudent = current->next; nextStudent != NULL; nextStudent = nextStudent->next)
        {
            if (current->rollNumber > nextStudent->rollNumber)
            {
                // Swap roll numbers
                tempRollNumber = current->rollNumber;
                current->rollNumber = nextStudent->rollNumber;
                nextStudent->rollNumber = tempRollNumber;

                // Swap names
                strncpy(tempName, current->name, sizeof(current->name));
                strncpy(current->name, nextStudent->name, sizeof(nextStudent->name));
                strncpy(nextStudent->name, tempName, sizeof(tempName));

                // Swap marks
                tempMarks = current->marks;
                current->marks = nextStudent->marks;
                nextStudent->marks = tempMarks;
            }
        }
    }
}

// Function to add a new student to the linked list
void addStudent(struct Student **head, int rollNumber, const char *name, float marks, int attendance)
{
    struct Student *newStudent = createStudent(rollNumber, name, marks, attendance);
    newStudent->next = *head;
    *head = newStudent;
    printf("Student added successfully.\n");
}

// Function to display all student details
void displayStudents(const struct Student *head)
{
    printf("Student Details:\n");
    while (head != NULL)
    {
        printf("Roll Number: %d, Name: %s, Marks: %.2f\n", head->rollNumber, head->name, head->marks);
        head = head->next;
    }
}

// Function to search for a student by roll number
struct Student *searchStudent(const struct Student *head, int rollNumber)
{
    while (head != NULL)
    {
        if (head->rollNumber == rollNumber)
        {
            return (struct Student *)head;
        }
        head = head->next;
    }
    return NULL; // Student not found
}

// Function to delete a student by roll number
void deleteStudent(struct Student **head, int rollNumber)
{
    struct Student *current = *head;
    struct Student *prev = NULL;

    while (current != NULL && current->rollNumber != rollNumber)
    {
        prev = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Student not found.\n");
        return;
    }

    if (prev == NULL)
    {
        *head = current->next;
    }

    else
    {
        prev->next = current->next;
    }

    free(current);
    printf("Student deleted successfully.\n");
}

// Function to update student information by roll number
void updateStudent(struct Student *head, int rollNumber, const char *newName, float newMarks)
{
    while (head != NULL)
    {
        if (head->rollNumber == rollNumber)
        {
            strncpy(head->name, newName, sizeof(head->name));
            head->marks = newMarks;
            printf("Student information updated successfully.\n");
            return;
        }
        head = head->next;
    }
    printf("Student not found.\n");
}

// Function to display the top N students based on marks
void displayTopNStudents(const struct Student *head, int n)
{
    // Copy the student data to an array for easier sorting
    int count = 0;
    struct Student *studentsArray[100]; // Assuming a maximum of 100 students, adjust as needed

    while (head != NULL && count < 100)
    {
        studentsArray[count++] = (struct Student *)head;
        head = head->next;
    }

    // Sort the array based on marks in descending order
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (studentsArray[j]->marks < studentsArray[j + 1]->marks)
            {
                struct Student *temp = studentsArray[j];
                studentsArray[j] = studentsArray[j + 1];
                studentsArray[j + 1] = temp;
            }
        }
    }

    // Display the top N students
    printf("Top %d Students based on Marks:\n", n);
    for (int i = 0; i < n && i < count; i++)
    {
        printf("Roll Number: %d, Name: %s, Marks: %.2f\n", studentsArray[i]->rollNumber, studentsArray[i]->name, studentsArray[i]->marks);
    }
}

// Function to display the class average marks
void displayClassAverage(const struct Student *head)
{
    if (head == NULL)
    {
        printf("No students in the class.\n");
        return;
    }

    float totalMarks = 0;
    int studentCount = 0;

    while (head != NULL)
    {
        totalMarks += head->marks;
        studentCount++;
        head = head->next;
    }

    float classAverage = totalMarks / studentCount;
    printf("Class Average Marks: %.2f\n", classAverage);
}

// Function to display attendance for all students
void displayAttendance(const struct Student *head)
{
    printf("Attendance Details:\n");
    while (head != NULL)
    {
        printf("Roll Number: %d, Name: %s, Attendance: %d%%\n", head->rollNumber, head->name, head->attendance);
        head = head->next;
    }
}

// Function to update attendance for a specific student
void updateAttendance(struct Student *head, int rollNumber, int newAttendance)
{
    while (head != NULL)
    {
        if (head->rollNumber == rollNumber)
        {
            head->attendance = newAttendance;
            printf("Attendance updated successfully for Roll Number %d.\n", rollNumber);
            return;
        }
        head = head->next;
    }
    printf("Student not found.\n");
}

// Function to free the memory allocated for the linked list
void freeList(struct User *head)
{
    struct User *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void freelist(struct Student *head)
{
    struct Student *temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}
void studentUpdateInfo(struct Student *students, int numStudents, int rollNumber) {
    char newName[50];
    printf("Enter your new name: ");
    scanf("%s", newName);

    // Find the student by roll number and update the name
    for (int i = 0; i < numStudents; i++) {
        if (students[i].rollNumber == rollNumber) {
            strncpy(students[i].name, newName, sizeof(students[i].name));
            printf("Name updated successfully.\n");
            return;
        }
    }

    printf("Student not found.\n");
}

void taskManager(struct Task tasks[100], int *numTasks) {
     tasks[*numTasks].percentageCompleted = 0;
    int choice;
    do {
        printf("\nTask Manager:\n");
        printf("1. Add Task\n");
        printf("2. Display Tasks\n");
        printf("3. Mark Task as Done\n");
        printf("4. Update Task Progress\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                {
                    if (*numTasks < 100) { // Check if there is space for a new task
                        printf("Enter task date (YYYY-MM-DD): ");
                        scanf("%s", tasks[*numTasks].date);
                        printf("Enter task description: ");
                        scanf("%s", tasks[*numTasks].description);
                        tasks[*numTasks].isDone = 0;
                        tasks[*numTasks].percentageCompleted = 0;
                        (*numTasks)++;
                        printf("Task added successfully.\n");
                    } else {
                        printf("Maximum number of tasks reached.\n");
                    }
                    break;
                }
            case 2:
                {
                    printf("Task List:\n");
                    for (int i = 0; i < *numTasks; i++) {
                        printf("Date: %s, Description: %s, Status: %s, Progress: %d%%\n", tasks[i].date, tasks[i].description,
                               tasks[i].isDone ? "Done" : "Not Done", tasks[i].percentageCompleted);
                    }
                    break;
                }
            case 3:
                {
                    char date[20];
                    printf("Enter the date of the task to mark as done (YYYY-MM-DD): ");
                    scanf("%s", date);

                    for (int i = 0; i < *numTasks; i++) {
                        if (strcmp(tasks[i].date, date) == 0) {
                            tasks[i].isDone = 1;
                            tasks[i].percentageCompleted = 100;
                            printf("Task marked as done.\n");
                            break;
                        }
                    }
                    break;
                }
            case 4:
                {
                    char date[20];
                    int progress;
                    printf("Enter the date of the task to update progress (YYYY-MM-DD): ");
                    scanf("%s", date);

                    for (int i = 0; i < *numTasks; i++) {
                        if (strcmp(tasks[i].date, date) == 0) {
                            printf("Enter the progress percentage (0-100): ");
                            scanf("%d", &progress);
                            if (progress >= 0 && progress <= 100) {
                                tasks[i].percentageCompleted = progress;
                                printf("Task progress updated.\n");
                            } else {
                                printf("Invalid progress percentage. Please enter a value between 0 and 100.\n");
                            }
                            break;
                        }
                    }
                    break;
                }
            case 5:
                printf("Exiting task manager.\n");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
        }
    } while (choice != 5);
}


int main()
{
    struct User *userHead = NULL;       // Head of the user linked list
    struct Student *studentHead = NULL; // Head of the student linked list
    int choice;
    char username[50], password[50];
    printf("*******student management*******\n");
    int decide;
    struct Task tasks[100]; 
    int numTasks = 0;
	int numStudents = sizeof(username) / sizeof(username[0]);
	int studentRollNumber;
    do
    {
        printf("do you want to proceed...? ");
		printf("if yes press 1 or else press 0 ");
        scanf("%d",&decide);
		if(decide==1)
		{
        printf("Are you a teacher or a student..?\n");
        printf("If you are a student,enter 0\n");
        printf("If you are a teacher enter 1\n");
        scanf("%d", &choice);
		}
		else
		{
			printf("thanking you for visiting");
			break;
		}

        if (choice == 0)
        {
            int ch;
            printf("are you a new student ..is yes press 1 or press 0");
            scanf("%d", &ch);
            if (ch == 1)
            {
                printf("Enter username for student signup: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
				printf("enter rollnumber");
				scanf("%d",&studentRollNumber);
                addUser(&userHead, username, password, 0); // 0 represents student
            }
            else
            {
                printf("Enter student username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                struct User *studentUser = authenticateUser(userHead, username, password);
                if (studentUser != NULL && studentUser->isTeacher == 0)
                {
                    // Student is authenticated, proceed with student-related operations
                    // You can implement student-specific functionalities here
                    printf("Student login successful.\n");
	// Allow students to update their name and add tasks
                //studentUpdateInfo(studentHead, numStudents, studentRollNumber);

                taskManager(tasks, &numTasks);
                }
	


                else
                {
                    printf("Invalid credentials or not a student account.\n");
                }
            }
        }

        else
        {
            int op;
            printf("are you a new teacher ..is yes press 1 or press 0");
            scanf("%d", &op);
            if (op == 1)
            {
                printf("Enter username for teacher signup: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                addUser(&userHead, username, password, 1); // 1 represents teacher
            }
            else
            {
                printf("Enter teacher username: ");
                scanf("%s", username);
                printf("Enter password: ");
                scanf("%s", password);
                struct User *teacherUser = authenticateUser(userHead, username, password);
                if (teacherUser != NULL && teacherUser->isTeacher == 1)
                {
                    printf("Teacher login successful.\n");
                    do
                    {
                        printf("\nMenu:\n");
                        printf("1. Add Student\n");
                        printf("2. Display Students\n");
                        printf("3. Search Student\n");
                        printf("4. Delete Student\n");
                        printf("5. Update Student\n");
                        printf("6. Display top N students\n");
                        printf("7. Display Class Average\n");
                        printf("8. Display Attendance\n");
                        printf("9. Update Attendance\n");
                        printf("10.exit\n");
                        printf("Enter your choice: ");
                        scanf("%d", &choice);

                        switch (choice)
                        {
                        case 1:
                        {
                            int rollNumber;
                            char name[50];
                            float marks;
                            int attendance;
                            printf("Enter Roll Number: ");
                            scanf("%d", &rollNumber);
                            printf("Enter Name: ");
                            scanf("%s", name);
                            printf("Enter Marks: ");
                            scanf("%f", &marks);
                            addStudent(&studentHead, rollNumber, name, marks, attendance);
                            sortStudents(studentHead);
                            break;
                        }
                        case 2:
                        {
                            displayStudents(studentHead);
                            break;
                        }
                        case 3:
                        {
                            int searchRollNumber;
                            printf("Enter Roll Number to search: ");
                            scanf("%d", &searchRollNumber);
                            struct Student *foundStudent = searchStudent(studentHead, searchRollNumber);
                            if (foundStudent != NULL)
                            {
                                printf("Student found - Roll Number: %d, Name: %s, Marks: %.2f\n", foundStudent->rollNumber, foundStudent->name, foundStudent->marks);
                            }
                            else
                            {
                                printf("Student with Roll Number %d not found.\n", searchRollNumber);
                            }
                            break;
                        }
                        case 4:
                        {
                            int deleteRollNumber;
                            printf("Enter Roll Number to delete: ");
                            scanf("%d", &deleteRollNumber);
                            deleteStudent(&studentHead, deleteRollNumber);
                            break;
                        }
                        case 5:
                        {
                            int updateRollNumber;
                            char newName[50];
                            float newMarks;
                            printf("Enter Roll Number to update: ");
                            scanf("%d", &updateRollNumber);
                            printf("Enter New Name: ");
                            scanf("%s", newName);
                            printf("Enter New Marks: ");
                            scanf("%f", &newMarks);
                            updateStudent(studentHead, updateRollNumber, newName, newMarks);
                            break;
                        }
                        case 6:
                        {
                            int topN;
                            printf("enter the number of top students  you want to display: ");
                            scanf("%d", &topN);
                            displayTopNStudents(studentHead, topN);
                            break;
                        }

                        case 7:
                            displayClassAverage(studentHead);
                            break;

                        case 8:
                            displayAttendance(studentHead);
                            break;

                        case 9:
                        {
                            int updateRollNumber, newAttendance;
                            printf("Enter Roll Number to update attendance: ");
                            scanf("%d", &updateRollNumber);
                            printf("Enter New Attendance (in percentage): ");
                            scanf("%d", &newAttendance);
                            updateAttendance(studentHead, updateRollNumber, newAttendance);
                            break;
                        }

                        case 10:
                        {
                           
                            printf("Exiting program.\n");
                            break;
                        }

                        default:
                            printf("Invalid choice. Please enter a number between 1 and 15.\n");
                        }
                    } while (choice != 10);
                }
                else
                {
                    printf("Invalid credentials or not a teacher account.\n");
                }
            }
        }
    }while(decide!=0);

    freeList(userHead);
    freelist(studentHead);

    return 0;
}
