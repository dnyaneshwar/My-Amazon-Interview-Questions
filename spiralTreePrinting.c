/* Program    : Travals the given tree spirally... 
 * Author     : Dnyaneshwar Patil
 * Input      : Tree 
 *
 *                     1 ------->
 *                 /      \     |
 *        <----  2   <----  3 <-- 
 *       |     /  \       /   \
 *        -->4 --> 5 --> 6 --> 7 ----->
 *          / \   / \   / \   / \     |
 *         8  9  10 11 12 13 14 15 <--
 *
 * Output     :  Travals the given tree spirally  
 *
 *                     1
 *                 /      \
 *               3          2
 *             /  \       /   \
 *            4    5     6     7
 *          / \   / \   / \   / \
 *         15 14 13 12 11 10 9  8 
*/

//header files 
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//structure of tree 
typedef struct tree {
  
  int data;
  struct tree *left;
  struct tree *right;
 
}TREE;

//structure of stack
typedef struct stack {
  TREE *node;
  struct stack *next;
}STACK;


/* function prototypes */
TREE *createTree();
int travalsTreeSpirally(TREE *root);
int PUSH(TREE *node, STACK **stack);
TREE *POP(STACK **stack);
int isEmpty(STACK *stack);
int insert(TREE **root, int number);

//main function
int main(int argc, char *args[]) {
  TREE *root = NULL;  
  root = createTree();
  travalsTreeSpirally(root);
  return 0;
} // main function 



int PUSH(TREE *node, STACK **stack) {
 
  STACK *temp = (STACK *)malloc(sizeof(STACK));
  temp -> node =node;
  temp -> next = *stack;
  *stack = temp;

  return 0;
}//PUSH a node in stack

TREE *POP(STACK **stack) {

  if(*stack == NULL) return NULL;
  STACK *temp = *stack; 
  TREE *popedNode = (*stack)->node;
   
  *stack =  (*stack) -> next;
  free(temp);
  return popedNode;

}//POP a node from stack

int isEmpty(STACK *stack) {

  if(stack == NULL) return 1; //stack is empty
  return 0; //stack is not empty

}//check for stack isEmpty or not 



TREE *createTree(){
  TREE *root = NULL;
  int number, nodeValue;

  
  printf("\n Enter the number of nodes :");
  scanf("%d", &number);
 
  while(number-- > 0) {

    printf("\n Enter the node value");
    scanf("%d", &nodeValue);
   
    insert(&root, nodeValue);  
  
  }//while
 
  return root;
}

int insert(TREE **root, int number) {
  
   
  if((*root)==NULL)
    {
      *root=(TREE *)malloc(sizeof(TREE));
      (*root)->data = number;
      (*root)->left = NULL;
      (*root)->right = NULL;     
    }
  else  
    {
      if(number<(*root)->data)
	{
	  insert(&((*root)-> left),number);
	}
      else
	{
	  insert(&((*root)-> right),number);
	}
    }
  return 0;
}//insert


/* Function  : travalsTreeSpirally(TREE *root)
 * Parameter : Tres 
 * Output    : Travals and print a tree spirally
 * Return 
 *        0  : Sucess
 *        1  : Fail/Error
 */
int travalsTreeSpirally(TREE *root){
  
  STACK *stackLeftToRight = NULL;
  STACK *stackRightToLeft = NULL;

 if(!root) return 0;
 
  if(!(root -> left) && !(root -> right)) {
    printf(" %d ", root -> data); 
    return 0;
  }//if

  // push root node into stack
  PUSH(root, &stackLeftToRight);

  // while both stacks become empty i.e. whole tree has travels 
  while( !isEmpty(stackLeftToRight) || !isEmpty(stackRightToLeft) ) {
  
   // while stack left to right is not empty
    while(!isEmpty(stackLeftToRight)) {
  
      TREE *node = POP(&stackLeftToRight);    // pop the node from one stack
      printf("%d ", node->data);              // prints it's data
  

      if(node -> left) PUSH(node->left, &stackRightToLeft);  //push it's leftchild into another stack
      if(node -> right) PUSH(node->right, &stackRightToLeft); // push it's right child into another stack

    }// while 

    printf("\n");// for printing of next level 
     

   // while stack right to left is not empty
    while(!isEmpty(stackRightToLeft)) {
     
      TREE *node = POP(&stackRightToLeft); // pop the node from one stack
     
      printf("%d ", node->data);            // prints it's data

      if(node -> right) PUSH(node->right, &stackLeftToRight); //push it's right child into another stack
      if(node -> left) PUSH(node->left, &stackLeftToRight); // push it's left child into another stack
    }// while 

      printf("\n");// for printing of next level 
  }// while 

  return 0;
}//travalsTreeSpirally
