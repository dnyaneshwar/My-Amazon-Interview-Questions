/* Program :  addition of two singly linked list and store a result in third singly linked list
 * 
 * Input   : Two Linked lists having number as a data
 *           e.g. 3450   will be store as  3 -> 4 -> 5 -> 0 -> null
 *              +  965   will be store as  9 -> 6 -> 5 -> null
 *
 * Output  : Resultant linked list.. 
 *               4415   will be store as 4 -> 4 -> 1 -> 5 -> null
 *
 * Contraints :  i) you can't reverse the linked list..
 *              ii) efficient solution should be there
 *             iii) in case of diffrent lenght of input linked list don't make them of same lenght for calculation 
 */


//header file 
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//structure of linked list
typedef struct node {

  int data;
  struct node *next;

}NODE;



//function prototypes
NODE *createLinkedList(int number);
NODE *additionOfLinkedList(NODE *firstList, NODE *secondList);
int pushLinkedListOnStack(NODE *list, NODE **stack);
int pop(NODE **stack);
int printList(NODE *list);

int main() {

  NODE *firstList = NULL;
  NODE *secondList = NULL;
  NODE *resultantList = NULL;
  int number;

  //reading the input number and creating a linked list from it
  printf("\nEnter the first number : ");
  scanf("%d", &number);  
  firstList  = createLinkedList(number);
  printList(firstList);
 
  //reading the input number and creating a linked list from it
  printf("\nEnter the second  number : ");
  scanf("%d", &number);  
  secondList = createLinkedList(number);
  printList(secondList);

  resultantList = additionOfLinkedList(firstList,  secondList);
  
  printf("\nResultant List :  \n");
  printList(resultantList);
 
  return 0;
}//main function


/* function  : additionOfLinkedList(firstList,  secondList)
 * parameter : two linked lists
 * Output    :  generate addition of given two linked list i.e. third linked list 
 * Return    : 
 *        NODE * : on sucess
*/
NODE *additionOfLinkedList(NODE *firstList, NODE *secondList) {
 
  NODE *resultantList = NULL;
  NODE *firstStack = NULL;
  NODE *secondStack = NULL;
  NODE *new = NULL;
  int carry = 0;
  int sum = 0;

  if(!firstList && !secondList) return NULL;            //if both lists are null  
  
  if(!firstList) return secondList;      //if first list is null
  
  if(!secondList) return firstList;      //if second list is null  

 
  pushLinkedListOnStack(firstList, &firstStack);
  pushLinkedListOnStack(secondList, &secondStack);
 
  while(firstStack && secondStack) {
    
    sum = firstStack -> data + secondStack -> data + carry;
    carry = 0;
    if (sum >= 10) {
      carry = 1;
      sum = sum - 10;
    }

    new = (NODE *)malloc(sizeof(NODE));
    new -> data =  sum;
    new -> next = NULL;
   
    if(!resultantList){
      resultantList = new;
    } else {
      new -> next = resultantList;
      resultantList = new; 
    }
 
    pop(&firstStack);
    pop(&secondStack);
 
  
  }//while
 
  //if second list is short than first one 
  while(firstStack) {
 
    sum = firstStack -> data + carry;
    carry = 0;
    if (sum >= 10) {
      carry = 1;
      sum = sum - 10;
    }
  
    new = (NODE *)malloc(sizeof(NODE));
    new -> data =  sum;
    new -> next = resultantList;
    resultantList = new; 
   
    pop(&firstStack);

  }//while
 
  //if first list is short than second one 
  while(secondStack) {
 
    sum = secondStack -> data + carry;
    carry = 0;
    if (sum >= 10) {
      carry = 1;
      sum = sum - 10;
    }

    new = (NODE *)malloc(sizeof(NODE));
    new -> data =  sum;
    new -> next = resultantList;
    resultantList = new; 
   
    pop(&secondStack);

  }//while
 
  if(carry > 0) {
 
    new = (NODE *)malloc(sizeof(NODE));
    new -> data =  carry;
    new -> next = resultantList;
    resultantList = new; 
  }
 
  return resultantList;
}//additionOfLinkedList



/* function  : pop(NODE **stack);
 * parameter : stack
 * Return    : 
 *        0 : on sucess
*/
int pop(NODE **stack) {
 
  NODE *temp = *stack;
  
  if(!(*stack)) return 0;

  *stack = (*stack) -> next;
  free(temp);
 
  return 0;
}//pop function



/* function  : pushLinkedListOnStack(NODE *list, NODE **stack);
 * parameter : linked list and stack
 * Return    : 
 *        0 : on sucess
*/
int pushLinkedListOnStack(NODE *list, NODE **stack) {

  NODE *new = NULL;

  if(!list) return -1;
 
  while(list) {
  
    //creating a temp node   
    new = (NODE *)malloc(sizeof(NODE));
    new -> data =  list -> data;
    new -> next = NULL;
  
    if(!(*stack)){
      *stack = new;
    } else {
      // append the new node to exiting list and make it head
      new -> next = *stack;
      *stack = new; 
    }
    list = list -> next;
  } 
 
  return 0;
}//pushLinkedListOnStack



/* function  : createLinkedList(int number)
 * parameter : number on which linked list will create
 *              e.g. 2314
 * Output    :  linked list 
 *              e.g  2 -> 3 -> 1 -> 4 -> null
 * Return    : 
         NODE * : on sucess
*/
NODE *createLinkedList(int number) {

  NODE *new  = NULL;
  NODE *head = NULL;

  while(number > 0){
   
    //creating a temp node   
    new = (NODE *)malloc(sizeof(NODE));
    new -> data =  number % 10; // assiging a remender as a data
    new -> next = NULL;
  
    // for first digit
    if(!head){
      head = new;
    } else {
      // append the new node to exiting list and make it head
      new -> next = head;  
      head = new; 
    } 

    number = number / 10;
  }//while

  return head;
}//createLinkedList



/* function  : printList(NODE *list)
 * parameter : linked list
 * Output    : will print the linked list 
 * Return    : 
           0   : on sucess
*/
int printList(NODE *list) {
 
  if(!list) return 0;

  while(list) {
       printf(" %d -> ", list -> data);
       list = list -> next;
  }//while
  printf("null \n");
  return 0;
}//printList
