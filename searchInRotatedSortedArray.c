/* PROGRAM    : Search Element In Rotated Sorted Array... 
 *              e.g.  5 7 8 11 14 17 this a sorted array 
 *                    7 8 11 14 17 5 rotated by 1
 *                    8 11 14 17 5 7 rotated by 2 
 *
 * INPUT      : Rotated Sorted Array (don't know how much it is rotated)  
 *              Element to Search
 *
 * OUTPUT     : Index of Element if present 
 *              Else -1 if element is not present
 *
 * 
 * CONTRAINTS : Search Should Not Be Linear...
 * 
 */


// header files
#include <stdio.h>
#include <malloc.h>

//functions prototypes
int searchElementInRaotatedSortArray(int *rsortedArray, int elementToSearch, int arrayLength );
int binarySearch(int *rsortedArray, int elementToSearch, int lowerIndex, int upperIndex);
int findRoatedIndex(int *rsortedArray, int lowerIndex, int upperIndex);

//main function 
int main() {

  //local variables 
  int i;
  int noOfEle;
  int result;
  int elementToSearch;
  int *rsortedArray;
 
  //reading Inputs 
  printf("\n Enter The No Of Elements : ");
  scanf("%d", &noOfEle);

  //allocate the memory for array
  rsortedArray = (int *)malloc(sizeof(int) * noOfEle);
  
  //reading array
  printf("\n Enter The Elements : ");
  for( i = 0; i < noOfEle; i++) {
       scanf("%d", &rsortedArray[i]);
  }//for

  printf("\n Enter The Element To Search");
  scanf("%d", &elementToSearch);

  //call function to search the element
  result = searchElementInRaotatedSortArray(rsortedArray, elementToSearch, noOfEle);
 
  if(result != -1) 
    printf("\n Element %d Is Present At %d Position \n", elementToSearch, result);
  else
    printf("\n Element %d Is Not Present In Given Array..", elementToSearch);

  return 0;
}//main



/* Function     :  searchElementInRaotatedSortArray(int *rsortedArray, int elementToSearch, int arrayLength )
 * Parameters   :  rotatedSortedArray, elementToSearch, arrayLength 
 * Return value :  
 *            index  :  If element to search is present  
 *              -1   :  If element to search is not present  
 */
int searchElementInRaotatedSortArray(int *rsortedArray, int elementToSearch, int arrayLength ){
   
  int lowerIndex = 0;
  int upperIndex = arrayLength - 1;
  int mid; 
  int result;

  if(arrayLength <= 0 ) return -1; //no elements in array 

  if(rsortedArray == NULL) return -1; //no elements in array 

  //will find out how much it is roated and return index 
  mid = findRoatedIndex(rsortedArray, lowerIndex, upperIndex);

  // if array is not rotated, we simply apply binary search - O(log n)
  if ( mid == 0 ) return binarySearch(rsortedArray, elementToSearch, lowerIndex, upperIndex); 
  
  //if array is roated then split it into two sorted array, and apply binary sort on each
  result = binarySearch(rsortedArray, elementToSearch, lowerIndex, mid);

  // if element is not in first sorted array
  if(result == -1 )
    return binarySearch(rsortedArray, elementToSearch, mid+1, upperIndex);  
 
  return result; // index of element to search

}//searchElementInRaotatedSortArray



/* Function     : findRoatedIndex(int *rsortedArray, int lowerIndex, int upperIndex);
 * Parameters   :  rotatedSortedArray, lowerIndex, upperIndex 
 * Return value :  
 *            index  :  upto which array is rotated  
 *            0      :  array is not rotated
 */
int findRoatedIndex(int *rsortedArray, int lowerIndex, int upperIndex) {
  
  int mid;

  if(rsortedArray[lowerIndex]  < rsortedArray[upperIndex]) return 0; //array is not ratated
 
  mid = (lowerIndex + upperIndex)/2;

  if(rsortedArray[mid] > rsortedArray[mid+1]) return mid; //got the index, upto which array is raotated


  if(rsortedArray[mid] >= rsortedArray[lowerIndex]) {
    lowerIndex = mid;         
  }else if(rsortedArray[mid] < rsortedArray[lowerIndex]) {
    upperIndex = mid;
  }//if

  //recursively call to function 
 return findRoatedIndex(rsortedArray, lowerIndex, upperIndex);

}//findRoatedValue



/* Function     :  binarySearch(array, elementTosearch, lowerIndex, upperIndex)
 * Parameters   :  rotatedSortedArray, elementToSearch, lowerIndex, upperIndex 
 * Return value :  
 *            index  :  If element to search is present  
 *              -1   :  If element to search is not present  
 */
int binarySearch(int *rsortedArray, int elementToSearch, int lowerIndex, int upperIndex){
  
  int mid; 
  if(lowerIndex > upperIndex) return -1;
 
  mid = (lowerIndex + upperIndex)/2;
  
  if(rsortedArray[mid] == elementToSearch) return mid;
 
  if(rsortedArray[mid] > elementToSearch) {
    upperIndex = mid - 1;
  } else {
    lowerIndex = mid + 1;
  }
 
  return  binarySearch(rsortedArray, elementToSearch, lowerIndex, upperIndex); 
 
}//binarySearch
