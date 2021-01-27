/*
NABEEHA SAFFAT
SHUNTING YARD

for shunting yard algorithim https://en.wikipedia.org/wiki/Shunting-yard_algorithm

for binary expression tree https://en.wikipedia.org/wiki/Binary_expression_tree
                           https://www.youtube.com/watch?v=WHs-wSo33MM

for stack library info https://www.tutorialspoint.com/cpp_standard_library/stack.htm
 */

#include <string.h>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <stack>
#include <math.h>
#include <iostream>

using namespace std;

//node struct for linked lists. used for stack and queue
struct node {
  char data;
  node* next = NULL;
};

//binary node for expression tree
struct Bnode {
  char data;
  Bnode* left = NULL;
  Bnode* right = NULL;
};

//functions for stack
void push(node* &top, char data);
void pop(node* &top);
char peek(node* top);
void printS(node* top);


//functions for queue
void enqueue(node* &front, node* &back, char data);
void dequeue(node* &front, node* &back);
void printQ(node* front, node* back);

//infix to postfix functions
void InputPostfix(char input[100], node* &top, node* &front, node* &back);
int precedence(char ch);
bool isOperator(char token);



//tree functions
void createTree(stack<Bnode*> &Tree, node* front, node* back);
void infix(Bnode* root);
void prefix(Bnode* root);
void postfix(Bnode* root);



int main() {
  node* top = NULL; //creating operator stack

  node* front = NULL;   //creating output queue
  node* back = NULL;

  char input[100];
  stack<Bnode*> Tree; //Used stack library to create a stack for binary expression tree
  int trav = 0;

  cout << "Enter a mathematical expression. Use () for brackets. Single digit numbers only. No spaces\n";
  cin >> input;

  //converts input to postfix notation and prints output queue
  InputPostfix(input, top, front, back);
  //  cout << "Postfix: ";
  // printQ(front, back);

 
  // creates Binary expression tree using the output queue
  createTree(Tree, front, back);
  Bnode* root = Tree.top();
    
  while (trav != 4) {
    cout << "\n\nWhat next: 1. Prefix   2. Infix   3. Postfix   4. QUIT\n";
    cin >> trav;
    
    if (trav == 1) {
      cout << "Prefix: ";
      prefix(root);
    }
    if (trav == 2) {
      cout << "Infix: ";
      infix(root);
    }
    if (trav == 3) {
      cout << "Postfix: ";
      postfix(root);
    }
    if (trav == 4) {
      cout << "Peace out, girl scout! ";
      return 0;
    }
  }
}

void InputPostfix(char input[100], node* &top, node* &front, node* &back) {
  int i = 0;
  
  while (i < strlen(input)) {
    
    if ( isOperator( input[i]) ) {//if token is an operator
      if (top != NULL) { //if operator stack not empty  
	while ( ( precedence( peek(top) ) >= precedence(input[i]) ) && ( peek(top) != '^' )) { //pops operators from stack with greater precedence and pushes them to queue
	  enqueue ( front, back, peek(top) );
	  pop(top);
	  if ( top == NULL ) {
	    break;
	  }
	}
      }
      push(top, input[i]); 
    }
    
    else if ( input[i] == '(' ) { //if token is left paren, gets pushed to stack
      push(top, input[i]);
    }
    
    else if ( input[i] == ')' ) { //if token is right paren,
      while ( peek(top) != '(' ) { 
	enqueue ( front, back, peek(top) ); //adds operators to output queue until the top of the stack is a left parenthesis
	pop(top);
	
	if (top == NULL) {
	  cout << "expression entered wrong";
	  return;
	}
      }
      pop(top); //discard the left parenthesis
    }
      
    else if ( !isOperator( input[i]) ){ //if token is a operand, gets pushed to queue
      enqueue(front, back, input[i]);
    }
    i++;
  }
    
  while(top != NULL) { //pushes rest of the operators in the stack to the output queue
    enqueue ( front, back, peek(top) );
    pop(top);
  }
}

  int precedence(char ch) {  
    if (ch == '+' || ch == '-') {
      return 1;
    }
    else if (ch == '*' || ch == '/') {
      return 2;
    }
    else if (ch == '^') {
      return 3;
    }
    else {
      return 0;
    }
  }

bool isOperator(char token) {
  if (token == '+' || token == '-' || token == '*'  || token == '/'  || token == '^') {
    return true;
  }
  else {
    return false;
  }
}



void createTree(stack<Bnode*> &Tree, node* front, node* back) {
  while ( front != NULL ) { //while output queue is not empty
    if ( !isOperator(front->data) ) { //if token is an operand, push to stack
      Bnode* newB = new Bnode;
      newB->data = front->data;

      Tree.push(newB);
      dequeue(front, back);
    }
    else { //if token is an operator, pop two from stack and make those children of new Bnode (w ur token as the root) and push the new Bnode
      Bnode* newB = new Bnode;
      newB->data = front->data;

      newB->right = Tree.top();
      Tree.pop();
      newB->left = Tree.top();
      Tree.pop();

      Tree.push(newB);
      dequeue(front, back);
    }
  }
}

void prefix(Bnode* root) {
  if ( root != NULL ) { //if tree not empty
    cout << root->data <<" ";
    prefix(root->left);
    prefix(root->right);
  }
}

void infix(Bnode* root) {
  if ( root != NULL) { 
    infix(root->left);
    cout << root->data <<" ";
    infix(root->right);
  }
}

void postfix(Bnode* root) {
  if ( root != NULL) {
    postfix(root->left);
    postfix(root->right);
    cout << root->data <<" ";
  }
}

char peek(node* top){
  return top->data;
}

void push(node* &top, char data) {
  node* newn = new node;
  newn->data = data;
  newn->next = top;
  top = newn;
}

void pop(node* &top) {
  if (top == NULL) {
    cout << "\nStack empty";
    return;
  }
  node* temp = top;
  top = top->next;
  temp->next = NULL;
  delete temp;
}

void printS(node* top)  {
  node* temp = top;
  while (temp->next != NULL) {
    cout << temp->data << " ";
    temp = temp->next;
  }
  cout << temp->data;
}




void enqueue(node* &front, node* &back, char data){
  node* newn = new node;
  newn->data = data;
  //if queue is empty, assigns front and back to new node
  if(back == NULL) {
    front = newn;
    back = newn;
    return;
  }
  //adds node to end of queue and reaasigns back
  back->next = newn;
  back = newn;
}

void dequeue(node* &front, node* &back){
  if (front == NULL) {
    return;
  }  
  node* temp = front;
  front = front->next;
  if (front == NULL) {
    back = NULL;
  }
  delete temp;
}


void printQ(node* front, node* back)  {
  node* temp = front;
  while (temp != back) {
    cout << temp->data << " ";
    temp = temp->next;
  }
  cout << temp->data << endl;
}




