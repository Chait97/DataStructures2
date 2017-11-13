#include<iostream>
#include<cstdio>

#define ORDER 5                                                             //max degree
using namespace std;

int t = ORDER;

int getElement(){
    int element;
    cout<<endl<<"Enter an element(int): ";
    cin>>element;
    cout<<endl;
    return element;
}

char command(){
    char inp;
    cout<<"\n-Press 'i' to insert an element into BTree\n-Press 'x' delete an element\n-Press 's' to search an element in BTree\n-Press 'd' to display the BTree\n-Press 'q' to quit\n>>>> ";
    cin>>inp;
    return inp;
}

//--------------------------------------------------------------Class Definition------------------------------------------------------------------------

class node{
public:
    int *keys;                                                                  //keys
    node **C;                                                                   //child pointers
    int n;                                                                      //number of keys in node
    bool leaf;                                                                  //is leaf?
    node(bool leaf){
        this->leaf = leaf;
        keys = new int[t-1];
        C = new node *[t];
        n = 0;
    }
};

class BTree{
protected:
    node *root;                                                                 // Pointer to root node
    void splitChild(node*, int);
    void insertNonFull(node*, int);
public:
    BTree(){
        root = new node(true);
        root->n = 0;
    }
    node* getRoot(){
        return root;
    }
    void display(node*);
    void display2(node*);
    node* search(node*, int);
    void insert(int);
};

//-----------------------------------------------------------------------main---------------------------------------------------------------------------

int main(){
    BTree tree;
    while(1){
        switch(command()){
            case 'i':
                tree.insert(getElement());
                break;

            case 'x':
                // tree.del(getElement());
                break;

            case 's':
                tree.search(tree.getRoot(),getElement());
                break;

            case 'd':
                cout<<endl<<"\t";
                tree.display(tree.getRoot());
                cout<<endl;
                break;

            case 'z':
                tree.display2(tree.getRoot());
                cout<<endl;
                break;

            case 'q':
                return 0;

            default:
                cout<<"Please give a valid input..."<<endl;
                break;
        }
    }
    return 0;
}

//----------------------------------------------------------function definitions-----------------------------------------------------

void BTree::display(node *x){                                                   //traverses this and all children
    int i;
    for (i = 0; i < x->n; i++){                                                 //inorder recursive traversal
        if (x->leaf == false)
            display(x->C[i]);
        cout << " " << x->keys[i];
    }
    if (x->leaf == false)                                                       //last case that isn't included in the loop
        display(x->C[i]);
}

void BTree::display2(node *x){                                                   //traverses this and all children
    int i;
    cout<<"\t"<<x->n<<"\t";
    for (i = 0; i < x->n; i++){                                                 //inorder recursive traversal
        cout << " " << x->keys[i];
    }
    cout<<endl;
    for (i = 0; i <= x->n; i++){                                                 //inorder recursive traversal
        if (x->leaf == false)
            display2(x->C[i]);
    }
}

node* BTree::search(node* target,int k){                                        //searches for key in specified node (subtree)
    int i = 0;
    while (i < target->n && k > target->keys[i])                                //find key comparable to k in node
        i++;
    if (i< target->n && target->keys[i] == k)
        return target;                                                          //found key is equal to k? return itself
    else if (target->leaf == true)
        return NULL;                                                            //leaf means that k doesn't exist in subtree
    else
        return search(target->C[i],k);                                                  //search for k in ith subtree
}

void BTree::insert(int k){
    node* r = root;
    if (root->n == t-1){
        node *s = new node(false);
        s->C[0] = root;
        root = s;
        splitChild(s,0);                                                        //split the old root and move 1 key to the new root
        insertNonFull(s,k);
    } else {                                                                    //if root is not full, call insertNonFull for root
        insertNonFull(r,k);
    }
}

// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void BTree::insertNonFull(node* x, int k){
    int i = x->n - 1;                                                           //index of rightmost element
    if (x->leaf == true){
        while (i >= 0 && x->keys[i] > k){
            x->keys[i+1] = x->keys[i];                                          //shifts all keys one ahead
            i--;
        }                                                                       //this i is the new insert postion
        x->keys[i+1] = k;                                                       //Insert the new key at found location
        x->n = x->n + 1;
    }
    else {
        while (i >= 0 && x->keys[i] > k)
            i--;                                                                //this i is the new insert postion
        if (x->C[i+1]->n == t-1){                                             //child is full? then split it
            splitChild(x,i+1);
            if (x->keys[i+1] < k)
                i++;                                                            //this i is the new insert postion
        }
    insertNonFull(x->C[i+1],k);
    }
}

// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTree::splitChild(node *x, int i){
    node* y = x->C[i];                                                          //y will be split
    if(y->n != t-1){
        cout<<"Fault";
        return;
    }
    node *z = new node(y->leaf);
    z->n = t/2 - 1;
    for (int j = 0; j < t/2 -1; j++)                                               // Copy the last t/2 -1 keys of y to z
        z->keys[j] = y->keys[j + 1 + t/2];
    if (y->leaf == false){                                                      // Copy the last t/2 children of y to z
        for (int j = 0; j < t/2; j++)
            z->C[j] = y->C[j + t/2 + 1];
    }
    y->n = t/2;                                                                 // Reduce the number of keys in y
    for (int j = x->n; j >= i+1; j--)                                           //make space for a new child
        x->C[j+1] = x->C[j];
    x->C[i+1] = z;                                                              // Link the new child to this node

    for (int j = x->n-1; j >= i; j--)                                           //make space for a new key
        x->keys[j+1] = x->keys[j];
    x->keys[i] = y->keys[t/2];                                                  // Copy the middle key of y to this node
    x->n = x->n + 1;                                                            // Increment count of keys in this node
}
