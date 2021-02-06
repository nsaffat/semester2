/*NABEEHA SAFFAT, RED BLACK INSERTION + DELETION

 *info abt helper functions and insertion from https://en.wikipedia.org/wiki/Red%E2%80%93black_tree#Terminology

 *info abt deletion from https://www.programiz.com/dsa/deletion-from-a-red-black-tree

 *some code copied from my bst project
 */

#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h> 
#include <iostream>
#include <math.h>  

using namespace std;

//node struct
struct node {
  int data;
  node* parent = NULL;
  node* left = NULL;
  node* right = NULL;
  bool red = true;
};

//helper functions
node* getParent(node*);
node* getGrandparent(node*);
node* getSibling(node*);
node* getUncle(node*);
void rotateLeft(node*);
void rotateRight(node*);

//insertion functions
node* insert(node*, node*);

void recurse(node*, node*);
void repair(node*);

void insertCase1(node*);
void insertCase2(node*);
void insertCase3(node*);
void insertCase4(node*);
void insertCase4step2(node*);

//deletion functions
void remove(node*, node*);
node* replace(node*);
node* search(node*, int);
node* nextMax(node*);
void fixDB(node*, node*);


//other
void print(node*, int);


int main() {

  char command[20];
  int add;
  ifstream file1;
  
  node* root = NULL;
  
  while (strcmp (command,"QUIT") != 0) {
    add = 1;
    cout << "\nEnter a command: ADD, FILE, PRINT, DELETE, QUIT \n";
    cin >> command;
    
    if (strcmp (command,"ADD") == 0) {
      while (add > 0) {
	cout << "\nEnter each number seperatley. Enter 0 to return to main menu\n";
	cin >> add;
	if (add > 0) {
	  node* newN = new node();
	  newN->data = add;
	  root = insert(root, newN);
	  cout << "root in main= " << root << endl;
	}
      }
    }

    if (strcmp (command,"FILE") == 0) {
      char ch, hold[10], txt[60];
      int i = 0;

      cout << "\nEnter the name of the text file you want to input. You can use int.txt \n";
      cin >> txt;

      ifstream myfile;
      file1.open(txt);

      while ( !file1.eof() ) {
	file1 >> hold;
	add = atoi(hold);
	if (add == 0) {
	  break;
	}
	node* newN = new node();
	newN->data = add;
	root = insert(root, newN);
	
	//   cout << "\nroot in main= " << root << endl;
      }
    
	
      file1.close(); 
    }
    

    if (strcmp (command,"PRINT") == 0) {   
      cout << endl;
      print(root, 0);
    }

    /*    if (strcmp (command,"DELETE") == 0) {
      cout << "\nEnter the number you want to delete\n";
      cin >> add;
      node* del = search(root, add);
  
      if (root != NULL) {
	remove(root, del);
      }
    }
    */
  }
}


node* getParent(node* n) {
  if (!n) {
    return NULL;
  }
  
    else {
      return n->parent;
    }
  }

  node* getGrandparent(node* n) {
    return getParent( getParent(n) );
  }

  node* getSibling(node* n) {
    if ( getParent(n) == NULL) {
      return NULL;
    }

    if (n ==  getParent(n)->left) {
      return  getParent(n)->right;
    }
    else {
      return getParent(n)->left;
    }
  }

  node* getUncle(node* n) {
    return getSibling( getParent(n) );
  }

  void rotateLeft(node* n) {
    node* newn = n->right;
    node* p = getParent(n);
  
    if (newn != NULL) {   
      n->right = newn->left;
      newn->left = n;
      n->parent = newn;

      if (n->right != NULL) {
	n->right->parent = n;
      }

      if (p != NULL) {
	if (n == p->left) {
	  p->left = newn;
	}
	else if (n == p->right) {
	  p->right = newn;
	}
      }
      newn->parent = p;
    }
  }

  void rotateRight(node* n) {
    node* newn = n->left;
    node* p = getParent(n);
    if (newn != NULL) {
    
      n->left = newn->right;
      newn->right = n;
      n->parent = newn;

      if (n->left != NULL) {
	n->left->parent = n;
      }

      if (p != NULL) {
	if (n == p->left) {
	  p->left = newn;
	} else if (n == p->right) {
	  p->right = newn;
	}
      }
      newn->parent = p;
    }
  }

  node* insert(node* root, node* n) {
    recurse(root, n);
    repair(n);
    root = n;
    while ( getParent(root) ) {
      root = getParent(root);
    }
    return root;
  }

  void recurse(node* root, node* n) {
    if (root != NULL) {
      if (n->data < root->data) {
	if (root->left != NULL) {
	  recurse(root->left, n);
	  return;
	}
	else {
	  root->left = n;
	}
      }
 
      else {
	if (root->right != NULL) {
	  recurse(root->right, n);
	  return;
	}
	else {
	  root->right = n;
	}
      }
    }
  
    n->parent = root;

  }

  void repair(node* n) {
    if ( getParent(n) == NULL) {     //1. the new node is the root and needs to be changed to black
      insertCase1(n);
    }
    else if (getParent(n)->red == false) {   //2. if parent is black everything is fine
      insertCase2(n);
    }
    else if ( getUncle(n) != NULL && getUncle(n)->red == true) {  //3. parent and uncle red
      insertCase3(n);
    }
    else {
      insertCase4(n);  //4. parent is red and uncle black
    }

  }

  void insertCase1(node* n) {
    n->red = false;
  }

  void insertCase2(node* n) {
    return;
  }

  void insertCase3(node* n) {
    getParent(n)->red = false;
    getUncle(n)->red = false;
    getGrandparent(n)->red = true;
    repair( getGrandparent(n) );
  }


  void insertCase4(node* n) {
    node* p = getParent(n);
    node* g = getGrandparent(n);

    if (n == p->right && p == g->left) {
      rotateLeft(p);
      n = n->left;
    }
    else if (n == p->left && p == g->right) {
      rotateRight(p);
      n = n->right;
    }
    insertCase4step2(n);
  }

  void insertCase4step2(node* n) {
    node* p = getParent(n);
    node* g = getGrandparent(n);

    if (n == p->left) {
      rotateRight(g);
    }
    else {
      rotateLeft(g);
    }
  
    p->red = false;
    g->red = true;
  }

  void print(node* root, int level) {

    if (root == NULL) {
      return;
    }
  
    print(root->right, level + 1);  
    for (int i = 0; i < level; i++) { //8 spaces for every level
      cout << "        ";
    }
    // cout << root->data << "\n";

    if (root->red == true) {
      cout << "\033[1m\033[31m" << root->data << "\033[0m" << endl;
    }
    else {
      cout << root->data << endl;
    } 
 
  
    print(root->left, level + 1);

  }


void remove(node* root, node* del) {
  // cout << "del " << del->data << endl;

  node* u = replace(del);
  node* p = del->parent;

  cout << "del " << del->data << endl;
  cout << "u " << u->data << endl;

    
  if (u == NULL) { 
    if (del == root) { 
      cout <<"\nv is root, making root null ";
      root = NULL; 
    }
    else { 
      if ( ( (u->red == false || u == NULL) && del->red == false) == true) { 
	// u and v both black 
	// v is leaf, fix double black at v
	cout << "\nright before first fix db";

	fixDB(del, root); 
      }
      else { 
	// u or v is red 
	if ( getSibling(del) != NULL) {
	  // sibling is not null, make it red
	  getSibling(del)->red = true; 
	} 
      }
      // delete v from the tree 
      if (p->left == del) { 
	p->left = NULL; 
      }
      else { 
	p->right = NULL; 
      } 
    } 
    //  delete del; 
    return; 
  } 
  
  if (del->left == NULL || del->right == NULL) { 
    // v has 1 child 
    if (del == root) { 
      // v is root, assign the value of u to v, and delete u 
      del->data = u->data; 
      del->left = NULL;
      del->right = NULL; 
      delete u; 
    }
    else { 
      // Detach v from tree and move u up 
      if (p->left == del) { 
	p->left = u; 
      }
      else { 
	p->right = u; 
      } 
      //   delete del; 
      u->parent = p; 
      if ( ((u->red == false  || u == NULL) && del->red == false) == true) { 
	// u and v both black, fix double black at u 
	fixDB(u, root); 
      }
      else { 
	// u or v red, color u black 
	u->red = false; 
      } 
    } 
    return; 
  } 
  
  // v has 2 children

  int udata = u->data;
  u->data = del->data;
  del->data = udata; 
    
  remove(root, u); 
}


void fixDB(node* x, node* root) {
  cout<< "\nIN fix DB";
  if (x == root) {
    return;
  }
  
  node *s = getSibling(x);
  node* p = x->parent;
  
  if (s == NULL) { 
    // No sibiling, double black pushed up 
    fixDB(p, root); 
  }
  else { 
    if (s->red == true) { 
      // Sibling red 
      p->red = true; 
      s->red = false; 
      if (s->parent->left == s) { 
	// left case 
	rotateRight(p); 
      }
      else { 
	// right case 
	rotateLeft(p); 
      }
      fixDB(x, root); 
    }

    else { 
      // Sibling black
      if (  ( s->right != NULL && s->right->red == true) ||  ( s->left != NULL && s->left->red == true) ) { 
	// at least 1 red children 
	if (s->left != NULL and s->left->red == true) { 
	  if (p->left == s) { 
	    // left left 
	    s->left->red = s->red; 
	    s->red = p->red; 
	    rotateRight(p); 
	  }
	  else { 
	    // right left 
	    s->left->red = p->red; 
	    rotateRight(s); 
	    rotateLeft(p); 
	  } 
	}
	else { 
	  if (p->left == s) { 
	    // left right 
	    s->right->red = p->red; 
	    rotateLeft(s); 
	    rotateRight(p); 
	  }
	  else { 
	    // right right 
	    s->right->red = s->red; 
	    s->red = p->red; 
	    rotateLeft(p); 
	  } 
	} 
	p->red = false; 
      }
      
      else { 
	// 2 black children 
	s->red = true; 
	if (p->red == false)  {
	  fixDB(p,root);
	}
	else {
	  p->red = false;
	}
      }
    }
  } 
}



node* search(node* root, int k) {
  if (root == NULL) {
    cout << "The number " << k << " is NOT present\n";
    return NULL;
  }

  if (k == root->data) {
    cout << "Inside search\n";
    return root;
  }

  if  (k < root->data) {
    return search(root->left, k);
  }
  
  else {
    return search(root->right, k);
  }

}


node* replace(node* n) {
  if (n->right != NULL && n->left != NULL) {
    return nextMax(n->right);
  }
  // if leaf
  if (n->left == NULL && n->right == NULL) {
    return NULL;
  }
  // if single child
    if (n->left != NULL) {
        return n->left;
    }
    else {
      return n->right;
    }

}

node* nextMax(node* n) {
 
  if (n->left == NULL) {
    return n;
  }
  else {
    return nextMax( n->left );
    } 
}


