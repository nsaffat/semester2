#include <fstream> //info about opening and reading text files from http://www.cplusplus.com/doc/tutorial/files/
#include <string>
#include <cstring>
#include <stdlib.h> //info about converting char array into int from https://www.cplusplus.com/reference/cstdlib/atoi/
#include <iostream>
#include <math.h>   //info about exponents from http://www.cplusplus.com/reference/cmath/pow/

//MAX HEAP INFO https://www.geeksforgeeks.org/max-heap-in-java/

using namespace std;

class Heap {

private:
  int size;
  int heap[];

public:
  
  Heap() {
    heap[0] = 10000;
    size = 0;
  }

  //returns value at given index
  int value(int i) {
    return heap[i];
  }

  //swaps to values given their index
  void swap(int a, int b) {
    int temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
  }

  
  //inserts value in the next available index in heap
  void insert(int a) {
    heap[size+1] = a;
    size++;
    traverse(size);
  }
  
  //starts with child, swaps if value is greater than parent. floor(i/2) is formula for parent node
  void traverse(int i) {
    if ( heap[i] > heap[ (int)floor(i/2) ] ) {
      swap( i, (int)floor(i/2) );
      //calls function again on the parent node. traverses all the way up
      traverse( (int)floor(i/2) );
    }
  }

  //removes max element from heap. returns the removed element.
  int remove() {
    int old = heap[1];
    heap[1] = 0;
    size = size - 1;
    //heapify corrects the tree
    heapify(1);
    return old;
  }
  
  //readjusts tree
  void heapify(int i) {
    if (  (heap[i*2] > heap[i]) ||  (heap[i*2+1] > heap[i])  ) {
      if ( heap[i*2] > heap[i*2+1] ) {
	swap(i,i*2);
	heapify(i*2);
      }
    
      else {
	swap(i,i*2+1);
	heapify(i*2+1);
      }
    }
  }
  
  //prints heap in array format, used for debugging only
  void arrayprint() {
    cout << "\n";
    for (int i = 1; i < (size+1); i++) {
      cout << i << ", " << heap[i] << "\n";
    }
  }

  //prints heap in tree form
  void treeprint() {
    int i = 0, p = 0;
  
    while ( (int)(pow(2,p)+i) <  size+1 ) {
      while ( pow(2,p)+i < pow(2,p+1) ) {
	if ( heap[ (int)(pow(2,p)+i) ] == 0 ) {
	return;
	}
	cout << heap[ (int)(pow(2,p)+i) ] << " " ;
	i++;
      }
      cout << "\n";
      p++;
      i = 0;
    }
  }
  
};


  
int main () {

  char command[20], hold[5];
  int add=1;
  ifstream file1;
  
  Heap* MyHeap = new Heap;
  
  while (strcmp (command,"QUIT") != 0) {
    cout << "\nEnter a command: ADD, PRINT, REMOVE, QUIT \n";
    cin >> command;
    
    if (strcmp (command,"ADD") == 0) {
      cout << "\nEnter how you want to add to heap: FILE or MANUAL \n";
      cin >> command;
      
      if (strcmp (command,"FILE") == 0) {

	file1.open("integers.txt"); {
	  for (int j = 0; j < 100; j++) {
	    file1 >> hold;
	    add = atoi(hold);
	    MyHeap->insert(add);
	  }
	  file1.close();
	}
	
      }
      
      if (strcmp (command,"MANUAL") == 0) {
	while (add > 0) {
	  cout << "\nType in a number and press enter. Type 0 to stop\n";
	  cin >> add;
	  if (add > 0) {
	    MyHeap->insert(add);
	  }
	}  
      }
    }
    
    if (strcmp (command,"REMOVE") == 0) {
      cout << "\nOoutput: ";
      while ( MyHeap->value(1) > 0) {
	cout <<  MyHeap->remove() << " ";
	//	MyHeap->arrayprint();
      }
    }
  
    if (strcmp (command,"PRINT") == 0) {
      MyHeap->arrayprint();
      cout << "\n\n";
      MyHeap->treeprint();
    }
  }
  return 0;
}
