#include <string>
#include <cstring>
#include <stdlib.h>
#include <math.h>
#include <iostream>

using namespace std;

struct node {
  char data;
  node* next = NULL;
};



class stack {
public:
  stack() {
    head = NULL;
  }
  
  bool isEmpty() {
    if (head == NULL) {
      return true;
    }
    else {
      return false;
    }
  }
  
  void push(char push){
    node* temp = head;

    //if stack is empty then pushes value and reassigns head
    if (isEmpty() == true) {
      head = new node;
      head->data = push;
      return;
    }
    
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = new node;
    (temp->next)->data = push;
    
  }
  
  char pop() {
    node* temp = head;
    char pop;
    
    //if stack is empty
    if (isEmpty() == true) {
      cout << "\nStack empty ";
      return 0;
    }

    //if there is only 1 element in stack, reassigns head
    if (temp->next == NULL) {
      head = NULL;
      pop = temp->data;
      return pop;
    }

    //if there is more than 1 element in stack
    while ((temp->next)->next != NULL) {
      temp = temp->next;
    }    
    pop = (temp->next)->data;
    temp->next = NULL;
    
    return pop;
  }

  
  char peek() {
    return 0;
  }

  void print() {
    node* temp = head;
    
    while (temp != NULL) {
      cout << temp->data << " ";
      temp = temp->next;
    }
    return;
  }
  
private:
  node* head;
};


class queue {  
public:
  void endqueue(int a){
    return;
  }
  int dequeue(){
    return 0;
  }
  
private:
  node* head;
};


int main() {

  stack* MyStack = new stack();

  MyStack->push(5);
  MyStack->push(3);
  MyStack->push(7); 
  MyStack->push(9); 

  cout << "\ndisplay: ";
  MyStack->print();

  cout << "\njust popped " <<  MyStack->pop();
  cout << "\ndisplay: ";
  MyStack->print();
  
  cout << "\njust popped " <<  MyStack->pop();
  // cout << "\njust popped " <<  MyStack->pop();
  // cout << "\njust popped " <<  MyStack->pop();

  cout << "\ndisplay: ";
  MyStack->print();
}
