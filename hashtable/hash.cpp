#include <fstream> //info about opening and reading text files from http://www.cplusplus.com/doc/tutorial/files/

#include <stdlib.h>  // info about random number generators from https://www.cplusplus.com/reference/cstdlib/rand/
#include <time.h>

#include <string>
#include <stdio.h>
#include <vector>
#include <iostream>

using namespace std;


struct Student {
  string firstname;
  string lastname;
  int ID;
  float GPA;
};

class Node {
private:
  Node *Next;
  Student *Stud;

public:
  Node(Student* newStudent) {
    Stud = newStudent;
    Next = NULL;
  }
  ~Node() {
    Next = NULL;
    Stud = NULL;
  }  
  Student* getStudent() {
    return Stud;
  }  
  Node* getNext() {
    return Next;
  }  
  void setNext(Node* newNext) {
    Next = newNext;
  }
};

//function prototypes
void Add(Node* (&MyHash)[100]); //will generate a chosen number of students and and them to the hash table
void Delete(Node* (&MyHash)[100]);
void Insert(Node* newN, Node* (&MyHash)[100]); //insters Node into hash table
void Print(Node* table[100]);  //prints index and then the Student info


int main () {
  char command[20];
  Node* MyHash[100];

  //filling MyHash with NULL values
  for (int i = 0; i < 100; i++) {
    MyHash[i] = NULL;
  }
  
  while (strcmp (command,"QUIT") != 0) {
    cout << "\nEnter one of the following commands: ADD, PRINT, DELETE, QUIT \n";
    cin >> command;
    if (strcmp (command,"ADD") == 0) {
      Add(MyHash);
    }   
    if (strcmp (command,"PRINT") == 0) {
      Print(MyHash);
    }
    if (strcmp (command,"DELETE") == 0) {
      Delete(MyHash);
    }
  }
  return 0;
}


void Add(Node* (&MyHash)[100]) {
  int x, random, first;
  ifstream file1, file2;

  cout << "\nEnter the number of students you want to add \n";
  cin >> x;

  srand (time(NULL));  //creates a random seed based on the current time
  first = rand() % 1000000; //first ID number
  
  //this for loop creates a new Student/Node and gives it a name, ID number, GPA, and stores it in MyHash
  for (int i = 0; i < x; i++ ) {
    Student* newS = new Student;
    Node* newN = new Node(newS);   //creates new Node using new Student pointer

    //random number 1 to 200 inclusive to select first name from the text file
    random = rand() % 200 + 1;
    file1.open("firstnames.txt"); {
      for (int j = 0; j < 200; j++) {
	file1 >> (newN->getStudent())->firstname;
	if (j == random) {
	  break;
	}
      }
      file1.close();
    }
    random = rand() % 200 + 1;
    file2.open("lastnames.txt"); {
      for (int j = 0; j < 200; j++) {
	file2 >> (newN->getStudent())->lastname;
	if (j == random) {
	  break;
	}
      }
      file2.close();
    }

    //creates and stores a random GPA between 1.00 and 4.00
    random = rand() % 300 + 101;
    (newN->getStudent())->GPA = random * .01;

    //generating ID numbers. takes ID seed from earlier, increments by 12037. the %899999 + 100000 part is to ensure a 6 digit ID
    (newN->getStudent())->ID = (first + i*12037) % 899999 + 100000;

    Insert(newN, MyHash);
  }
}


void Insert(Node* newN, Node* (&MyHash)[100]) {
  int index;
  Node* temp;
  
  //HASH FUNCTION MOD 100
  index = (newN->getStudent())->ID  % 100;

  //inserting node. returns fucntion if chaining is not required
  if (MyHash[index] == NULL) {
    MyHash[index] = newN;
    return;
  }
  
  ///chaining if nesscary
  temp = MyHash[index];
  while (temp->getNext() != NULL) {
    temp = temp->getNext();
  }
  temp->setNext(newN);
}

void Print(Node* table[100]) {
  Node* temp;

  //for loop that also prints chained entries
  for (int i = 0; i < 100; i++) {
    temp = table[i];   
    while (temp != NULL) {
      cout << i << " " << (temp->getStudent())->firstname << " " << (temp->getStudent())->lastname << ", " << (temp->getStudent())->GPA <<", " << (temp->getStudent())->ID << "\n";
      temp = temp->getNext();
    }
    cout << "\n";
  }
}

void Delete(Node* (&MyHash)[100]) { 
  int ID, index;
  Node* temp;
  
  cout << "\nEnter the ID of the student you want to delete \n";
  cin >> ID;

  //HASH FUNCTION MOD 100
  index = ID % 100;

  //while loop that searches the linked list at specified index for correct Student
  temp = MyHash[index];
  if ( ( temp->getNext()->getStudent() )->ID != ID ) {
    temp = temp->getNext();
  }
  temp->setNext( temp->getNext()->getNext() );
}


