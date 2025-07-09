//This program is taken from website: https://www.tutorialspoint.com/data_structures_algorithms/quick_sort_program_in_c.htm

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 


#define MAX 8

int intArray[MAX];

void getdata(int* argv[]){
    intArray[0]=atoi(argv[1]);
    intArray[1]=atoi(argv[2]);
    intArray[2]=atoi(argv[3]);
    intArray[3]=atoi(argv[4]);
    intArray[4]=atoi(argv[5]);
    intArray[5]=atoi(argv[6]);
    intArray[6]=atoi(argv[7]);
    intArray[7]=atoi(argv[8]);
}

void printline(int count) {
   int i;
	
   for(i = 0;i < count-1;i++) {
      printf("=");
   }
	
   printf("=\n");
}

void display() {
   int i;
   printf("[");
	
   // navigate through all items 
   for(i = 0;i < MAX;i++) {
      printf("%d ",intArray[i]);
   }
	
   printf("]\n");
}

void swap(int num1, int num2) {
   int temp = intArray[num1];
   intArray[num1] = intArray[num2];
   intArray[num2] = temp;
}

int partition(int left, int right, int pivot) {
   int leftPointer = left -1;
   int rightPointer = right;

   while(true) {
      while(intArray[++leftPointer] < pivot) {
        printf("Do nothing\n");
      }
		
      while(rightPointer > 0 && intArray[--rightPointer] > pivot) {
        printf("Do nothing\n");
      }

      if(leftPointer > rightPointer) {
         break;
      } else {
         printf(" item swapped :%d,%d\n", intArray[leftPointer],intArray[rightPointer]);
         swap(leftPointer,rightPointer);
      }
   }
	
   printf(" pivot swapped :%d,%d\n", intArray[leftPointer],intArray[right]);
   swap(leftPointer,right);
   printf("Updated Array: "); 
   display();
   return leftPointer;
}

void quickSort(int left, int right) {
   if(right-left <= 0) {
      return;   
   } else {
      int pivot = intArray[right];
      int partitionPoint = partition(left, right, pivot);
      quickSort(left,partitionPoint-1);
      quickSort(partitionPoint+1,right);
   }        
}

int main(int argc, int* argv[]) {
    getdata(argv);
   printf("Input Array: ");
   display();
   printline(50);
   quickSort(0,MAX-1);
   printf("Output Array: ");
   display();
   printline(50);
}
