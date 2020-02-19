#include "functionSrc.h"

void readStudents(FILE* input, Node** headRef) {

  // allocate student for filling the other ones
  Node* studInf;
  studInf = (Node*)malloc(sizeof(struct Student));

  // checking for correct allocation
  if (!studInf)
  {
  	printf("[SysMsg Memory cannot be allocated!]\n");
  	exit(0);
  }

  // checking for the end of file
  while(!feof(input)) {

  if(fscanf(input, "%s %s %d %d %d", studInf->SStudent.surname, studInf->SStudent.name, &(studInf->SStudent.studentBirthday.day),
	&(studInf->SStudent.studentBirthday.month), &(studInf->SStudent.studentBirthday.year)) != 5)
    exit(0);
	// check whether the reading was successful

	float average = 0;


     for(int i = 0; i < SUBCOUNT; i++) {
        fscanf(input, "%d", &(studInf->SStudent.marks[i]));
        average += (studInf->SStudent.marks[i]);
     }

     average /= SUBCOUNT;
     studInf->SStudent.avgMark = average;

     insertStudentIntoList(headRef, studInf);
  }
  printf("\n\n[SysMsg Reading has been done successfully!]\n\n");
}


void insertStudentIntoList(Node** headRef, Node* pStud) {
  Node* newNode = (Node*)malloc(sizeof(struct Student));
  // check for successful allocation
  if(newNode) {
    newNode->SStudent = pStud->SStudent;

  if(*headRef == NULL) {
    *headRef = newNode;
    newNode->mNext = NULL;
  } else {
      if(((*headRef)->SStudent.avgMark) <= (newNode->SStudent.avgMark)) {
        newNode->mNext = *headRef;
        *headRef = newNode;

      } else {
        Node* temp = *headRef;

        while(temp->mNext != NULL && (temp->mNext->SStudent.avgMark) > newNode->SStudent.avgMark) {
          temp = temp->mNext;
        }

        if(temp->mNext == NULL) {
          newNode->mNext = NULL;
          temp->mNext = newNode;

        } else {
          newNode->mNext = temp->mNext;
          temp->mNext = newNode;

        }
      }
    }
  } else {
    printf("[SysMsg Not enough memory for allocation!\n\nІ");
    exit(0);
  }

}


void checkForLoser(Node* head) {
	// check for any element in the list
	if (head == NULL) return;
    Node* tempNode = head;
    printf("You think you have bad marks? Check out these guys!\n");
    while(tempNode) {
        int five = 0;
            for(int j = 0; j < SUBCOUNT; j++)  {
        if(tempNode->SStudent.marks[j] == 5) {  // checking whether student has at least 1 5-mark
        five++;                       // if it's true quit the loop
        break;
        }
    }
    if(!five) // if student has no 5 let this run

    printf("%10s | %10s | %02d | %02d | %4d | %2.2lf\n", tempNode->SStudent.name, tempNode->SStudent.surname, tempNode->SStudent.studentBirthday.year,
	tempNode->SStudent.studentBirthday.month, tempNode->SStudent.studentBirthday.day, tempNode->SStudent.avgMark);

	// loop through
	tempNode = tempNode->mNext;
    }
}





void showDataInList(Node* head) {

    if(head == NULL) {
        printf("The list is empty");
    }
    else {
        printf("The linked list data:\n");
        while(head){
            printf("%10s | %10s | %02d | %02d | %4d | %2.2lf\n", head->SStudent.name, head->SStudent.surname, head->SStudent.studentBirthday.year,
			head->SStudent.studentBirthday.month, head->SStudent.studentBirthday.day, head->SStudent.avgMark);


            // loop through
            head = head->mNext;
        }
    }
}

int compareBirthday(const Birthday *Bd1,const Birthday *Bd2) {

	if (Bd2->year - Bd1->year) return Bd2->year - Bd1->year;
	else   // returns > 0 if Bd1 is older than Bd2
	if (Bd2->month - Bd1->month) return Bd2->month - Bd1->month;
	else
	return Bd2->day - Bd1->day;

}



void determineOldestYoungest(Node* head) {
	if (head == NULL) return;

    Node* tempNode = head;
    Node* oldestStudent = head;
    Node* youngestStudent = head;
    while(tempNode) {

       if(compareBirthday(&(tempNode->SStudent.studentBirthday), &(oldestStudent->SStudent.studentBirthday) ) > 0) {
                oldestStudent = tempNode;

        }
       if(compareBirthday(&(tempNode->SStudent.studentBirthday), &(oldestStudent->SStudent.studentBirthday) ) < 0) {
                youngestStudent = tempNode;

       }

       // loop through
       tempNode = tempNode->mNext;
    }
    printf("\nThe oldest student from this list is: %s %s\n", oldestStudent->SStudent.name , oldestStudent->SStudent.surname);
    printf("\nThe youngest student from this list is: %s %s\n\n", youngestStudent->SStudent.name, youngestStudent->SStudent.surname);
}


int checkCondition(const int marks[]) {
	// function-checker for first and third exam
        int flag = 0;
        if((marks[0] == 3) && (marks[2] == 3)) {
            flag = 1;
    }
    return flag;
}

void deleteNodeFromList(Node** headRef) {
    Node* currentNode = *headRef, *prevNode;

    // check whether head itself holds any occurrences of the key
    while(currentNode && (checkCondition(currentNode->SStudent.marks) > 0)) {
        *headRef = currentNode->mNext;
        free(currentNode);
        currentNode = *headRef;

    }

    // deleting all other occurreces
    while(currentNode) {

        while(currentNode && (checkCondition(currentNode->SStudent.marks) == 0)) {
            prevNode = currentNode;
            currentNode = currentNode->mNext;
        }

        if(currentNode == NULL) return;

        prevNode->mNext = currentNode->mNext;
        free(currentNode);
        currentNode = prevNode->mNext;

    }
}

void deleteWholeList(Node** headRef) {
    Node* currentNode = *headRef;
    Node* nextNode;


    // traverse the list and free all incoming nodes
    while(currentNode) {
        nextNode = currentNode->mNext;
        free(currentNode);
        currentNode = nextNode;
    }

    *headRef = NULL;
    printf("\n\n [SysMsg The list has been deleted successfully. Allocated memory is now free] \n");
}


void correctString(char* ptr,const int sizeOfPtr)
{
  for (int i = 0; i < sizeOfPtr; ++i)
  {
    if (ptr[i]== '\n')
    {
    ptr[i] = '\0';
      break;
    }
  }
}


