/*NABEEHA SAFFAT, BINARY SEARCH TREE

 *info abt insertion and deletion from  https://en.wikipedia.org/wiki/Binary_search_tree

 *info abt printing sideways using reverse in-order traversal from  https://en.wikipedia.org/wiki/Tree_traversal#In-order,_LNR

 *some code copied from my heap project
 */

#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h> 
#include <iostream>
#include <math.h>  

using namespace std;

struct Node {
  int data;
  Node* left = NULL;
  Node* right = NULL;
};

//function prototypes
Node* insert(Node* root, int val);
void search(Node* root, int val);
Node* remove(Node* root, int val);
void print(Node* root, int level);

Node* nextMax(Node* node);


int main () {

  char command[20], hold[5], txt[50];
  int add;
  ifstream file1;
  
  Node* root = NULL;
  
  while (strcmp (command,"QUIT") != 0) {
    add = 1;
    cout << "\nEnter a command: ADD, PRINT, REMOVE, SEARCH, QUIT \n";
    cin >> command;
    
    if (strcmp (command,"ADD") == 0) {
      cout << "\nEnter how you want to add: FILE or MANUAL \n";
      cin >> command;
      
      if (strcmp (command,"FILE") == 0) {

	cout << "\nEnter the name of the text file you want to input. You can use int.txt \n";
	cin >> txt;
	file1.open(txt); {
	  for (int j = 0; j < 100; j++) {
	    file1 >> hold;
	    add = atoi(hold);
	    root = insert(root, add);
	    //   cout << "\nroot in main= " << root << endl;
	  }
	  file1.close();
	}
	
      }
      
      if (strcmp (command,"MANUAL") == 0) {
	while (add > 0) {
	  cout << "\nEnter each number seperatley. Enter 0 to return to main menu\n";
	  cin >> add;
	  if (add > 0) {
	    root = insert(root, add);
	    // cout << "\nroot in main= " << root << endl;
	  }
	}
	
	/*  	cout << "\n head = " << root->data;
	cout << "\n L = " <<  root->left->data;
	cout << "\n R = " <<  root->right->data;
	cout << "\n LL = " <<  root->left->left->data;
	cout << "\n LR = " <<  root->left->right->data;
	cout << "\n RL = " <<  root->right->left->data;
	cout << "\n RR = " <<  root->right->right->data;
	cout << "\n RRL = " << root->right->right->left->data; */

      }
    }

    if (strcmp (command,"SEARCH") == 0) {
      cout << "\nType in the number you are searching for\n";
      cin >> add;

      search(root, add);
    }
       
    if (strcmp (command,"REMOVE") == 0) {
      cout << "\nType in the number you want removed\n";
      cin >> add;
      
      root = remove(root, add);
  
    }
  
    if (strcmp (command,"PRINT") == 0) {
      cout << endl;
      print(root, 0);
    }
  }
  return 0;
}



Node* insert(Node* root, int val) { //insert using recursion, no duplicates alllowed

  if (root == NULL) { // creates new node and inserts value if the there is space (NULL pointer)
    root = new Node;
    root->data = val;
    //  cout << "just inserted " << val;
    return root;
  }
  
  if (val > root->data) { // if value is greater than the current node value, it calls insert on the right subtree
    root->right = insert(root->right, val);
  }
  if (val < root->data) { 
    root->left = insert(root->left, val);
  }
  return root;
}

void print(Node* root, int level) { 
  if (root == NULL) {
    for (int i = 0; i < level; i++) { //8 spaces for every level
      cout << "        ";
    }
    cout  << "E\n";  
    return;
  }
  print(root->right, level + 1);  
  for (int i = 0; i < level; i++) { //8 spaces for every level
      cout << "        ";
  }
  cout << root->data << "\n"; //access node
  print(root->left, level + 1); 
}


void search(Node* root, int val) {

  if (root == NULL) {
    cout << "The number " << val << " is NOT present\n";

    return;
  }

  if (val == root->data) {
    cout << "The number " << val << " is present\n";

    return;
  }

  if  (val < root->data) {
    search(root->left, val);
  }
  
  else {
    search(root->right, val);
  }
}


Node* remove(Node* root, int val) {
  //traverses tree until the correct node
  if  (val < root->data) {
    root->left =  remove(root->left, val);
    return root;
  }
  
  if  (val > root->data)  {
    root->right = remove(root->right, val);
    return root;

  }
  
 
  if ( root->left && root->right ) { //2 children, returns the next largest
    root->data = nextMax(root)->data;  
    root->right = remove( root->right , nextMax(root)->data );
    return root;
  }

  else { //0 or 1 child
    if (root->left != NULL) {
      return root->left;
    }
    else {
      return root->right; 
    }
  }
  
  
}


Node* nextMax(Node* node) {
  node = node->right;
  while( node->left != NULL) {
    node = node->left;
  }    //node now equals the next largest from the one you want to delete
  
  return node;
}
