#ifndef FUNCTIONSRC_H_INCLUDED
#define FUNCTIONSRC_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#define SIZE 200
#define SUBCOUNT 8
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct {
    int year, month, day;
} Birthday;

struct Person {
    char name[SIZE];
    char surname[SIZE];
    Birthday studentBirthday;
    int marks[SIZE];
    float avgMark;
};

typedef struct Student {
    struct Person SStudent;
    struct Student* mNext;
} Node;

void deleteWholeList(Node** headRef);
int checkCondition(const int marks[]);
void deleteNodeFromList(Node** head);
void checkForLoser(Node* head);
void readStudents(FILE* input, Node** head);
void insertStudentIntoList(Node** head, Node* pStud);
void printList(Node*);
void determineOldestYoungest(Node* head);
int compareBirthday(const Birthday *Bd1,const Birthday *Bd2);


#endif // FUNCTIONSRC_H_INCLUDED
