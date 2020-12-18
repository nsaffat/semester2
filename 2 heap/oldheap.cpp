#include <fstream> //info about opening and reading text files from http://www.cplusplus.com/doc/tutorial/files/
#include <string>
#include <cstring>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <math.h>   //info about exponents from http://www.cplusplus.com/reference/cmath/pow/

using namespace std;

//function protoypes
void AddFile();
void AddManual(int (&MyHeap)[102]);
void Print(int MyHeap[102]);
void Remove();

void insert(int(&MyHeap)[102], int A);


  
int main () {

  char command[20];
  int MyHeap[102];

  //fill array with negative values
  for (int i = 0; i < 102; i++) {
    MyHeap[i] = -1;
  }
  
  while (strcmp (command,"QUIT") != 0) {
    cout << "\nEnter one of the following commands: ADD, PRINT, REMOVE, QUIT \n";
    cin >> command;
    
    if (strcmp (command,"ADD") == 0) {
      cout << "\nEnter how you want to add to heap: FILE or MANUAL \n";
      cin >> command;
      
      if (strcmp (command,"FILE") == 0) {
	//  AddFile();
      }
      if (strcmp (command,"MANUAL") == 0) {
	AddManual(MyHeap);
      }
    }
    
    if (strcmp (command,"REMOVE") == 0) {
      //      Remove();
    }
    
    if (strcmp (command,"PRINT") == 0) {
      Print(MyHeap);
    }
  }
  return 0;
}

void AddManual(int (&MyHeap)[102]) {
  int input;

  cout << "\n Type in a number and press enter. Type 0 to stop\n";
  while (input != 0) {
    cin >> input;
    insert(MyHeap, input);
  }
}


void Print(int MyHeap[102]) {
  int i = 0, p = 0;
 
  //fill array with index values. this is just for printing tree. delete later
  for (int j = 1; j < 101; j++) {
    MyHeap[j] = j;
  }

  
  while ( MyHeap[ (int)(pow(2,p)+i) ] > 0 ) {
    
    while ( pow(2,p)+i < pow(2,p+1) ) {
      if ( MyHeap[ (int)(pow(2,p)+i) ] < 0 ) {
	return;
      }

      cout << MyHeap[ (int)(pow(2,p)+i) ] << " " ;
      i++;
    }
    cout << "\n";
    p++;
    i = 0;
  }
}
