#include <stdio.h>
#include <stdlib.h>
#include "functionSrc.c"
#include <string.h>



int main()
{

    FILE* fp;
    Node* head = NULL;
    char address[SIZE];
  int val = 1;
  do
  {
    if (val)
    {
      printf("Enter address of text file\t\n");
      --val;
    }
    else {
      printf("Something went wrong. File was not opened. Try again\t\n");
    }
    fgets(address, SIZE - 1, stdin);
    correctString(address, SIZE);
    fp = fopen(address, "r");
  } while (!fp);
    readStudents(fp, &head);

    showDataInList(head);
    checkForLoser(head);
    determineOldestYoungest(head);
    deleteNodeFromList(&head);
    showDataInList(head);
    deleteWholeList(&head);
    return 0;
}
