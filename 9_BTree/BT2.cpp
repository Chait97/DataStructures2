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
    void split(node*,int);
    void insertHere(node*, int);
    void del(node*, int);
    node *parent(node*);
    void fix(node*);
    void merge(node*, int);
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
    void del(int);
};

//-----------------------------------------------------------------------main---------------------------------------------------------------------------

int main(){
    BTree tree;
    node* result;
    while(1){
        switch(command()){
            case 'i':
                tree.insert(getElement());
                break;

            case 'x':
                tree.del(getElement());
                break;

            case 's':
                result = tree.search(tree.getRoot(),getElement());
                if(result)cout<<"\tData found in the node at addr:"<<result<<endl;
                else cout<<"\tNot found"<<endl;
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
    cout<<"\t";
    node* par = parent(x);
    if(par == NULL)
        cout<<"Root\t";
    else
        cout<<"Par: "<<par->keys[0]<<" Keys: ";
    for (i = 0; i < x->n; i++){                                                 //inorder recursive traversal
        cout<<x->keys[i] << " " ;
    }
    cout<<endl;
    for (i = 0; i <= x->n; i++){                                                 //inorder recursive traversal
        if (x->leaf == false){
            cout<<"\t"<<"#:"<<i+1;
            display2(x->C[i]);
        }
    }
}

node* BTree::search(node* target,int k){                                        //searches for key in the  specified node (or subtree)
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
    insertHere(r,k);
    if (root->n == t){
        node *s = new node(false);
        s->C[0] = root;
        root = s;
        split(root,0);                                                          //split the old root and move 1 key to the new root
    }                                                                           //if root is not full, call insertHere for root
}
// A utility function to insert a new key in this node
// The assumption is, the node must be non-full when this
// function is called
void BTree::insertHere(node* x, int k){
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
        insertHere(x->C[i+1],k);
        if (x->C[i+1]->n == t){                                                 //child is full? then split it
            split(x,i+1);
        }
    }
}

// A utility function to split the child y of this node
// Note that y must be full when this function is called
void BTree::split(node *x, int i){
    node* y = x->C[i];                                                          //y will be split
    if(y->n != t){
        cout<<"Fault";
        return;
    }
    node *z = new node(y->leaf);
    z->n = t/2;
    for (int j = 0; j < t/2; j++)                                               // Copy the last t/2 keys of y to z
        z->keys[j] = y->keys[j + 1 + t/2];
    if (y->leaf == false){                                                      // Copy the last t/2+1 children of y to z
        for (int j = 0; j <= t/2; j++)
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

void BTree::del(int key){
    node* target = search(root,key);                                            //address of node to delete
    if(target == NULL){
        cout<<"Element not in B-Tree."<<endl;
        return;
    }
    else {
        int position = 0;
        for(int i = 0; i < target->n; i++){
            if(target->keys[i] == key){
                position = i;                                                   //index of key to be deleted
                break;
            }
        }
        del(target, position);
    }
}


void BTree::del(node* target, int pos){                                         //actually performs deletion recursively
    if(target->leaf == true){
        for(int j = pos; j < target->n - 1 ; j++){
            target->keys[j] = target->keys[j+1];                                //simple removal and shift of subsequent keys
        }
        target->n = target->n - 1;
        if(target != root && target->n < t/2)fix(target);
    }
    else {                                                                       //non leaf target
        target->keys[pos] = target->C[pos + 1]->keys[0];
        del(target->C[pos + 1],0);
    }
}

void BTree::fix(node* target){
    node *p = parent(target);
    int posT;                                                                   //child's index in parent
    for(int i=0; i <= p->n; i++)                                                //finding the position of child in parent
        if(p->C[i]==target){
            posT = i;
            break;
        }
    if(posT < p->n){                                                            //target has a right sibling
        node* rightSib = p->C[posT + 1];                                        //right sibling of target
        if(rightSib->n > t/2){                                                  //right sibling has enough keys
            target->keys[target->n] = p->keys[p->n -1];                         //right rotation of keys via parent
            p->keys[p->n -1] = rightSib->keys[0];
            target->n ++;
            for(int j = 0; j < rightSib->n -1; j++){                            //left shift of keys in rightSib
                rightSib->keys[j] = rightSib->keys[j+1];
            }
            rightSib->n--;
            return;
        }
    }
    if(posT > 0){                                                               //target has a left sibling
        node* leftSib = p->C[posT - 1];                                         //left sibling of target
        if(leftSib->n > t/2){                                                   //left sibling has enough keys
            for(int j = 0; j < target->n; j++){                                 //right shift of keys in left sibling
                target->keys[j+1] = target->keys[j];
            }
            target->n ++;
            target->keys[0] = p->keys[posT - 1];
            p->keys[posT -1] = leftSib->keys[leftSib->n - 1];
            leftSib->n--;
            return;
        }
    }
    //if program reaches here, it means neither left sibling nor right sibling have enough keys. We must merge
    merge(p,posT);
}

void BTree::merge(node* p, int posT){
    node* left, *right;
    int position;
    if(posT > 0){                                                               //left sibling exists
        position = posT -1;
        left = p->C[posT - 1];
        right = p->C[posT];
    } else {                                                                    //right sibling exists
        position = posT;
        left = p->C[posT];
        right = p->C[posT + 1];
    }
    left->keys[left->n] = p->keys[position];                                    //demote parent key to leaf
    for(int i=position; i< p->n -1; i++){                                       //shift parent data left
        p->keys[i] = p->keys[i+1];                                              //shift parent keys
        p->C[i+1] = p->C[i+2];                                                  //shift parent data
    }
    p->n --;
    for(int i = 0; i < right->n; i++){
        left->keys[left->n + 1 + i] = right->keys[i];
    }
    left-> n = left->n + right->n + 1;
    delete right;
    if(p == root){
        if(p->n == 0){
            delete root;
            root = left;
        }
        return;
    }
    else if(p->n < t/2){
        node *_p = parent(p);
        int _posT;                                                                   //child's index in parent
        for(int i=0; i <= p->n; i++)                                                //finding the position of child in parent
            if(_p->C[i]==p){
                _posT = i;
                break;
            }
        merge(_p,_posT);
    }
}

node* BTree::parent(node* target){
    if(target == root)return NULL;
    node* current = root;
    node* previous = current;
    int k = target->keys[0];
    while(1){
        int i = 0;
        while (i < current->n && k > current->keys[i])                              //find key comparable to k in node
            i++;
        previous = current;
        current = current->C[i];
        if(current == target)
            return previous;
    }
}
