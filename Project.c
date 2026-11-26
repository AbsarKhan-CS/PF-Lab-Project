#include <stdio.h>
#include <string.h>

#define MAX 100

/* Structures */

struct Student {
    char name[50];
    char id[20];
    char department[40];
    int semester;
};

struct Course {
    char code[20];
    char name[50];
    int creditHours;
    float marks;
};

struct Assignment {
    char title[50];
    char course[30];
    int completed;
};

struct Task {
    char description[100];
    char deadline[30];
    int completed;
};

/* Global variables */

struct Student student;

struct Course courses[MAX];
struct Assignment assignments[MAX];
struct Task tasks[MAX];

int courseCount = 0;
int assignmentCount = 0;
int taskCount = 0;

float totalFee = 0;
float paidFee = 0;

int totalClasses = 0;
int attendedClasses = 0;

int profileCreated = 0;

/* Input functions */

void clearInput(void) {
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
        /* Clear remaining input characters. */
    }
}

void readString(char text[], int size) {
    if (fgets(text, size, stdin) != NULL) {
        text[strcspn(text, "\n")] = '\0';
    } else {
        text[0] = '\0';
    }
}

int readInt(void) {
    int value;

    while (scanf("%d", &value) != 1) {
        printf("Invalid input. Enter an integer: ");
        clearInput();
    }

    clearInput();
    return value;
}

float readFloat(void) {
    float value;

    while (scanf("%f", &value) != 1) {
        printf("Invalid input. Enter a number: ");
        clearInput();
    }

    clearInput();
    return value;
}

/* 1. Student Profile Management */

void studentProfile(void) {
    int choice;

    printf("\n--- STUDENT PROFILE MANAGEMENT ---\n");

    if (!profileCreated) {
        printf("1. Create Profile\n");
        printf("0. Back\n");
        printf("Enter choice: ");

        choice = readInt();

        if (choice == 0)
            return;

        if (choice != 1) {
            printf("Invalid choice.\n");
            return;
        }

        printf("Enter student name: ");
        readString(student.name, 50);

        printf("Enter student ID: ");
        readString(student.id, 20);

        printf("Enter department: ");
        readString(student.department, 40);

        printf("Enter semester: ");
        student.semester = readInt();

        profileCreated = 1;
        printf("\nProfile created successfully!\n");
    } else {
        printf("\nStudent Name: %s\n", student.name);
        printf("Student ID: %s\n", student.id);
        printf("Department: %s\n", student.department);
        printf("Semester: %d\n", student.semester);

        printf("\n1. Update Profile\n");
        printf("0. Back\n");
        printf("Enter choice: ");

        choice = readInt();

        if (choice == 1) {
            printf("Enter new name: ");
            readString(student.name, 50);

            printf("Enter new department: ");
            readString(student.department, 40);

            printf("Enter new semester: ");
            student.semester = readInt();

            printf("Profile updated successfully!\n");
        } else if (choice != 0) {
            printf("Invalid choice.\n");
        }
    }
}

/* 2. Course Management */

void courseManagement(void) {
    int choice;

    do {
        printf("\n--- COURSE MANAGEMENT ---\n");
        printf("1. Add Course\n");
        printf("2. Display Courses\n");
        printf("0. Back\n");

        printf("Enter choice: ");
        choice = readInt();

        switch (choice) {
            case 1:
                if (courseCount >= MAX) {
                    printf("Course limit reached.\n");
                    break;
                }

                printf("Enter course code: ");
                readString(courses[courseCount].code, 20);

                printf("Enter course name: ");
                readString(courses[courseCount].name, 50);

                printf("Enter credit hours: ");
                courses[courseCount].creditHours = readInt();

                courses[courseCount].marks = -1;
                courseCount++;

                printf("Course added successfully!\n");
                break;

            case 2:
                if (courseCount == 0) {
                    printf("No courses available.\n");
                    break;
                }

                for (int i = 0; i < courseCount; i++) {
                    printf("\nCourse %d\n", i + 1);
                    printf("Code: %s\n", courses[i].code);
                    printf("Name: %s\n", courses[i].name);
                    printf("Credit Hours: %d\n", courses[i].creditHours);

                    if (courses[i].marks >= 0)
                        printf("Marks: %.2f\n", courses[i].marks);
                    else
                        printf("Marks: Not entered\n");
                }
                break;

            case 0:
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

/* 3. Marks and Grade Management */

void marksManagement(void) {
    char code[20];
    int found = 0;

    if (courseCount == 0) {
        printf("Add courses first.\n");
        return;
    }

    printf("\n--- MARKS MANAGEMENT ---\n");
    printf("Enter course code: ");
    readString(code, 20);

    for (int i = 0; i < courseCount; i++) {
        if (strcmp(code, courses[i].code) == 0) {
            float marks;

            printf("Enter marks out of 100: ");
            marks = readFloat();

            if (marks < 0 || marks > 100) {
                printf("Invalid marks. Enter between 0 and 100.\n");
                return;
            }

            courses[i].marks = marks;
            printf("Marks saved successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Course not found!\n");
}

/* Grade Point Calculation */

float getGradePoint(float marks) {
    if (marks >= 85)
        return 4.0;
    else if (marks >= 80)
        return 3.7;
    else if (marks >= 75)
        return 3.3;
    else if (marks >= 70)
        return 3.0;
    else if (marks >= 65)
        return 2.7;
    else if (marks >= 61)
        return 2.3;
    else if (marks >= 58)
        return 2.0;
    else if (marks >= 55)
        return 1.7;
    else if (marks >= 50)
        return 1.0;
    else
        return 0.0;
}

/* 4. GPA Calculation */

void calculateGPA(void) {
    float totalPoints = 0;
    int totalCredits = 0;

    printf("\n--- GPA CALCULATION ---\n");

    if (courseCount == 0) {
        printf("No courses available.\n");
        return;
    }

    for (int i = 0; i < courseCount; i++) {
        if (courses[i].marks < 0) {
            printf("Enter marks for all courses first.\n");
            return;
        }

        float gradePoint = getGradePoint(courses[i].marks);
        totalPoints += gradePoint * courses[i].creditHours;
        totalCredits += courses[i].creditHours;
    }

    if (totalCredits == 0) {
        printf("Total credit hours cannot be zero.\n");
        return;
    }

    float GPA = totalPoints / totalCredits;

    printf("Total Credit Hours: %d\n", totalCredits);
    printf("Semester GPA: %.2f / 4.00\n", GPA);
}

/* 5. Attendance Management */

void attendanceManagement(void) {
    int choice;

    do {
        printf("\n--- ATTENDANCE MANAGEMENT ---\n");
        printf("1. Enter Attendance\n");
        printf("2. Display Attendance\n");
        printf("0. Back\n");

        printf("Enter choice: ");
        choice = readInt();

        switch (choice) {
            case 1:
                printf("Enter total classes: ");
                totalClasses = readInt();

                printf("Enter attended classes: ");
                attendedClasses = readInt();

                if (totalClasses <= 0 ||
                    attendedClasses < 0 ||
                    attendedClasses > totalClasses) {
                    printf("Invalid attendance data.\n");
                    totalClasses = 0;
                    attendedClasses = 0;
                    break;
                }

                printf("Attendance recorded!\n");
                break;

            case 2:
                if (totalClasses == 0) {
                    printf("No attendance data available.\n");
                    break;
                }

                printf("Total Classes: %d\n", totalClasses);
                printf("Attended Classes: %d\n", attendedClasses);
                printf("Attendance Percentage: %.2f%%\n",
                       (attendedClasses * 100.0) / totalClasses);
                break;

            case 0:
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

/* 6. Assignment Management */

void assignmentManagement(void) {
    int choice;

    do {
        printf("\n--- ASSIGNMENT MANAGEMENT ---\n");
        printf("1. Add Assignment\n");
        printf("2. Display Assignments\n");
        printf("3. Mark Assignment Completed\n");
        printf("0. Back\n");

        printf("Enter choice: ");
        choice = readInt();

        switch (choice) {
            case 1:
                if (assignmentCount >= MAX) {
                    printf("Assignment limit reached.\n");
                    break;
                }

                printf("Enter assignment title: ");
                readString(assignments[assignmentCount].title, 50);

                printf("Enter course name: ");
                readString(assignments[assignmentCount].course, 30);

                assignments[assignmentCount].completed = 0;
                assignmentCount++;

                printf("Assignment added!\n");
                break;

            case 2:
                for (int i = 0; i < assignmentCount; i++) {
                    printf("\nAssignment: %s\n", assignments[i].title);
                    printf("Course: %s\n", assignments[i].course);
                    printf("Status: %s\n",
                           assignments[i].completed ? "Completed" : "Pending");
                }

                if (assignmentCount == 0)
                    printf("No assignments available.\n");
                break;

            case 3: {
                int number;

                if (assignmentCount == 0) {
                    printf("No assignments available.\n");
                    break;
                }

                printf("Enter assignment number (1-%d): ", assignmentCount);
                number = readInt();

                if (number >= 1 && number <= assignmentCount) {
                    assignments[number - 1].completed = 1;
                    printf("Assignment marked completed!\n");
                } else {
                    printf("Invalid assignment number.\n");
                }
                break;
            }

            case 0:
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

/* 7. Fee Management */

void feeManagement(void) {
    int choice;

    do {
        printf("\n--- FEE MANAGEMENT ---\n");
        printf("1. Enter Fee Details\n");
        printf("2. Display Fee Details\n");
        printf("0. Back\n");

        printf("Enter choice: ");
        choice = readInt();

        switch (choice) {
            case 1:
                printf("Enter total semester fee: ");
                totalFee = readFloat();

                printf("Enter amount already paid: ");
                paidFee = readFloat();

                if (totalFee < 0 || paidFee < 0 || paidFee > totalFee) {
                    printf("Invalid fee information.\n");
                    totalFee = 0;
                    paidFee = 0;
                    break;
                }

                printf("Fee information saved!\n");
                break;

            case 2:
                printf("Total Fee: %.2f\n", totalFee);
                printf("Paid Fee: %.2f\n", paidFee);
                printf("Remaining Fee: %.2f\n", totalFee - paidFee);
                break;

            case 0:
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

/* 8. Study Planner */

void studyPlanner(void) {
    int choice;

    do {
        printf("\n--- STUDY PLANNER ---\n");
        printf("1. Add Study Task\n");
        printf("2. Display Study Tasks\n");
        printf("3. Complete Study Task\n");
        printf("0. Back\n");

        printf("Enter choice: ");
        choice = readInt();

        switch (choice) {
            case 1:
                if (taskCount >= MAX) {
                    printf("Task limit reached.\n");
                    break;
                }

                printf("Enter task description: ");
                readString(tasks[taskCount].description, 100);

                printf("Enter deadline: ");
                readString(tasks[taskCount].deadline, 30);

                tasks[taskCount].completed = 0;
                taskCount++;

                printf("Study task added!\n");
                break;

            case 2:
                for (int i = 0; i < taskCount; i++) {
                    printf("\nTask %d\n", i + 1);
                    printf("Description: %s\n", tasks[i].description);
                    printf("Deadline: %s\n", tasks[i].deadline);
                    printf("Status: %s\n",
                           tasks[i].completed ? "Completed" : "Pending");
                }

                if (taskCount == 0)
                    printf("No study tasks available.\n");
                break;

            case 3: {
                int number;

                if (taskCount == 0) {
                    printf("No tasks available.\n");
                    break;
                }

                printf("Enter task number (1-%d): ", taskCount);
                number = readInt();

                if (number >= 1 && number <= taskCount) {
                    tasks[number - 1].completed = 1;
                    printf("Task completed!\n");
                } else {
                    printf("Invalid task number.\n");
                }
                break;
            }

            case 0:
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

/* 9. Academic Performance Statistics */

void academicStatistics(void) {
    float totalMarks = 0;
    int count = 0;
    int completed = 0;

    printf("\n--- ACADEMIC STATISTICS ---\n");

    if (courseCount > 0) {
        for (int i = 0; i < courseCount; i++) {
            if (courses[i].marks >= 0) {
                totalMarks += courses[i].marks;
                count++;
            }
        }

        printf("Total Courses: %d\n", courseCount);

        if (count > 0)
            printf("Average Marks: %.2f\n", totalMarks / count);
        else
            printf("No marks entered yet.\n");
    } else {
        printf("No courses registered.\n");
    }

    if (totalClasses > 0) {
        printf("Attendance: %.2f%%\n",
               attendedClasses * 100.0 / totalClasses);
    }

    for (int i = 0; i < assignmentCount; i++) {
        if (assignments[i].completed)
            completed++;
    }

    printf("Assignments Completed: %d / %d\n",
           completed, assignmentCount);

    completed = 0;

    for (int i = 0; i < taskCount; i++) {
        if (tasks[i].completed)
            completed++;
    }

    printf("Study Tasks Completed: %d / %d\n",
           completed, taskCount);

    printf("Remaining Fee: %.2f\n", totalFee - paidFee);
}

/* 10. Searching Records */

void searchRecords(void) {
    char searchCode[20];
    int found = 0;

    if (courseCount == 0) {
        printf("No course records available.\n");
        return;
    }

    printf("\n--- SEARCH COURSE RECORDS ---\n");
    printf("Enter course code to search: ");
    readString(searchCode, 20);

    for (int i = 0; i < courseCount; i++) {
        if (strcmp(searchCode, courses[i].code) == 0) {
            printf("\nCourse Found!\n");
            printf("Course Code: %s\n", courses[i].code);
            printf("Course Name: %s\n", courses[i].name);
            printf("Credit Hours: %d\n", courses[i].creditHours);

            printf("Marks: ");
            if (courses[i].marks >= 0)
                printf("%.2f\n", courses[i].marks);
            else
                printf("Not entered\n");

            found = 1;
            break;
        }
    }

    if (!found)
        printf("Course not found!\n");
}

/* MAIN FUNCTION */

int main(void) {
    int choice;

    do {
        printf("\n\n");
        printf("============================================\n");
        printf("       FAST STUDENT LIFE MANAGEMENT SYSTEM  \n");
        printf("============================================\n");

        printf("1. Student Profile Management\n");
        printf("2. Course Management\n");
        printf("3. Marks and Grade Management\n");
        printf("4. GPA Calculation\n");
        printf("5. Attendance Management\n");
        printf("6. Assignment Management\n");
        printf("7. Fee Management\n");
        printf("8. Study Planner\n");
        printf("9. Academic Statistics\n");
        printf("10. Search Records\n");
        printf("0. Exit\n");

        printf("\nEnter your choice: ");
        choice = readInt();

        switch (choice) {
            case 1:
                studentProfile();
                break;

            case 2:
                courseManagement();
                break;

            case 3:
                marksManagement();
                break;

            case 4:
                calculateGPA();
                break;

            case 5:
                attendanceManagement();
                break;

            case 6:
                assignmentManagement();
                break;

            case 7:
                feeManagement();
                break;

            case 8:
                studyPlanner();
                break;

            case 9:
                academicStatistics();
                break;

            case 10:
                searchRecords();
                break;

            case 0:
                printf("\nThank you for using Student Life Management System!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}
