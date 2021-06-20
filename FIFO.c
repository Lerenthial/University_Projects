#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Collection
{
  char element;
  struct Collection *pNext;
} *first, *last;

void displayCollectionStatus() 
{
  if(last == NULL)
  {
    printf("Collection is empty \n");
  }
    else
  {
    struct Collection *tmp=last;
    int elementsCount = 0; 
    while (tmp != NULL) 
    {  
      elementsCount++;      //Simple collection element counter
      tmp = tmp->pNext;     
    }
    printf("Collection items count: %d\n", elementsCount);
  }
}

void push(char c)
{
  struct Collection *tmp;
  tmp = (struct Collection*)malloc(sizeof(struct Collection));
  tmp->element = c;
  if (first == NULL) 
  {
    first=tmp;
    first->pNext=NULL; //Since it's a first element - next element doesn't exist yet
    last=first;        //which also makes it the last element
  } 
    else 
  {
    first->pNext=tmp; //Assigning next element of collection
    first=tmp; 
    first->pNext=NULL;
  }
}

void delete()
{
  if(last != NULL)
  {
    struct Collection *tmp;
    tmp = last->pNext; //Temporarily saving the next element
    last = NULL; //Assigning NULL value to actual element
    last = tmp; //Setting last element as the one in line 55
    printf("\n[DELETE]");
    displayCollectionStatus();
  }
    else
  {
    printf("\n[DELETE]");
    displayCollectionStatus();
  }
}

void display()
{
  printf("\n---=== DISPLAY ===---\n\n");
  struct Collection *tempLast=last;
  if(tempLast != NULL)
  {
    displayCollectionStatus();
    printf("Collection items: ");
    while(tempLast != NULL)
    {
      printf("%c", tempLast->element);
      tempLast = tempLast->pNext;
    }
  }
    else
  {
    displayCollectionStatus();
  }
  printf("\n\n---=== END OF DISPLAY ===---\n\n");
}

int main(int argc, char const *argv[])
{
  char userInput[100];
  printf("\nInsert string: ");
  gets(userInput);
  for(int i=0; i<strlen(userInput); i++)
  {
    push(userInput[i]);
  }

  char firstChar;
  firstChar = userInput[0];
  delete();
  
  push('x');
  display();

  return 0;
}
