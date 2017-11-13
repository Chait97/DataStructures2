//redBlackTree with insert, search, delete
//amazing test case  i 8 i 10 i 9 i 12 i 11 i 13 i 14 i 15 i 16 i 17 i 4 i 6 i 5 i 7 i 3 i 2 i 1
//followed by x

#include<iostream>

using namespace std;

enum colors: bool{red, black};

struct node{
        int data;
        colors color;
        struct node *left, *right, *parent;
};

int getElement(){
    int element;
    cout<<endl<<"Enter an element(int): ";
    cin>>element;
    cout<<endl;
    return element;
}

char command(){
    char inp;
    cout<<"\n-Press 'i' to insert an element\n-Press 'x' to delete an element\n-Press 's' to search for an element\n-Press 'd' to display the tree inorder\n-Press 'q' to quit\n>>>> ";
    cin>>inp;
    return inp;
}

//--------------------------------------------------------------Class Definition------------------------------------------------------------------------

class redBlackTree{
public:
    struct node *sentinel;
    redBlackTree(){
        sentinel = new struct node;
        sentinel->color = black;
        sentinel->left = NULL;
        sentinel->right = NULL;
        root = sentinel;
    }
    void insert(int);

    void search(int key){
        struct node* result =  search(root,key);
        if(result==sentinel)cout<<"\tElement not found"<<endl;
        else cout<<"\tElement found at: "<<result<<endl;
    }

    void del(int key){
        struct node* target = search(root,key);
        if(target == sentinel){
            cout<<"\tNo such element in Tree"<<endl;
            return;
        }
        else {
            del(target);
            cout<<"\tElement deleted successfully."<<endl;
        }
    }

    void inorder(struct node*);
    void preorder(struct node*);
    void postorder(struct node*);

    struct node *getRoot(){
        return root;
    }

protected:

    struct node *root;
    struct node* search(struct node*,int);
    int del(struct node *);
    void insertFix(struct node*);
    void deleteFix(struct node*);
    struct node* fill(int y){
        struct node *newNode = new struct node;
        newNode->data = y;
        newNode->left = sentinel;
        newNode->right = sentinel;
        newNode->parent = sentinel;
        newNode->color = red;
        return newNode;
    }
    struct node* min(struct node* x){
            while(x->left != sentinel){
                x = x->left;
            }
            return x;
    }

    void transplant(struct node* x, struct node *y){
        if (x->parent == sentinel)root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->parent = x->parent;
    }


        void rotate(struct node* target, char direction){                                   //single function to rotate left or right
            struct node* y;
            if(direction == 'l'){                                               //left rotate
                y = target->right;
                target->right = y->left;
                if(y->left != sentinel)
                    y->left->parent = target;
                y->parent = target->parent;
                if(target->parent == sentinel)
                    root = y;
                else {
                    if(target == target->parent->left)
                        target->parent->left = y;
                    else target->parent->right = y;
                }
                y->left = target;
                target->parent = y;
            } else if(direction == 'r'){                                        //right rotate
                y = target->left;
                target->left = y->right;
                if(y->right != sentinel)
                    y->right->parent = target;
                y->parent = target->parent;
                if(target->parent == sentinel)
                    root = y;
                else {
                    if(target == target->parent->right)
                        target->parent->right = y;
                    else target->parent->left = y;
                }
                y->right = target;
                target->parent = y;
            }
            return;
        }

};


//-----------------------------------------------------------------------main---------------------------------------------------------------------------


int main(){
    redBlackTree tree;
    while(1){
        switch(command()){
            case 'i':
                tree.insert(getElement());
                break;

            case 'x':
                tree.del(getElement());
                break;

            case 's':
                tree.search(getElement());
                break;

            case 'd':
                cout<<endl<<"\tInorder"<<endl<<"\t";
                tree.inorder(tree.getRoot());
                cout<<endl<<"\tPreorder"<<endl<<"\t";
                tree.preorder(tree.getRoot());
                cout<<endl;
                break;

            case 'q':
                return 0;

            case 'r':                                                                       //debugging purposes only
                cout<<(tree.getRoot())->data;
                break;

            default:
                cout<<"Please give a valid input..."<<endl;
                break;
        }
    }
    return 0;
}


//----------------------------------------------------------function definitions-----------------------------------------------------


void redBlackTree::insert(int x){
    struct node *current = root; struct node *previous = sentinel;
    while (current != sentinel) {
        previous = current;
        if( x < current->data )current = current->left;
        else current = current->right;
    }
    struct node *newNode = fill(x);
    newNode->parent = previous;
    if(previous == sentinel ){
        root = newNode;
    }
    else if (newNode->data < previous->data) previous->left = newNode;
    else previous->right = newNode;
    insertFix(newNode);
}

void redBlackTree::insertFix(struct node* target){
    while(target->parent->color == red){
        if(target->parent ==  target->parent->parent->left){                    //if parent is a left child
            struct node *uncle = target->parent->parent->right;                     //store the uncle
            if(uncle->color == red){                                                //CASE 1 - red uncle
                target->parent->color = black;
                uncle->color = black;
                target->parent->parent->color = red;
                target = target->parent->parent;
            }
            else {
                if( target == target->parent->right){                              //CASE 2 - uncle black and target is a right child
                    target = target->parent;
                    rotate(target,'l');                                                 //this makes target a left child
                }
                target->parent->color = black;                                      //CASE 3 - uncle black and left child
                target->parent->parent->color = red;
                rotate(target->parent->parent,'r');
            }
        } else {
            struct node *uncle = target->parent->parent->left;                     //exactly the mirror image of the upper block of code
            if(uncle->color == red){
                target->parent->color = black;
                uncle->color = black;
                target->parent->parent->color = red;
                target = target->parent->parent;
            }
            else {
                if( target == target->parent->left){
                    target = target->parent;
                    rotate(target,'r');
                }
                target->parent->color = black;
                target->parent->parent->color = red;
                rotate(target->parent->parent,'l');
            }
        }
    }
    root->color = black;
}

int redBlackTree::del (struct node* target){
    struct node* o = target;
    struct node* child;
    bool originalColor = o->color;
    if( target->left == sentinel){
        child = target->right;
        transplant(target, child);
    } else if(target->right == sentinel){
        child = target->left;
        transplant(target, child);
    } else {
        o = min(target->right);
        originalColor = o->color;
        child = o->right;
        if(o->parent == target && child != sentinel) child->parent = o;
        else {
            transplant(o, o->right);
            o->right = target->right;
            o->right->parent = o;
        }
        transplant(target,o);
        o->left = target->left;
        o->left->parent = o;
        o->color = target->color;
    }
    if(originalColor == black) deleteFix(child);
}

void redBlackTree::deleteFix(struct node* target){
    while(target != root && target->color == black){
        if(target == target->parent->left){
            struct node* w = target->parent->right;
            if(w->color == red){
                w->color = black;                                               //CASE1
                target->parent->color = red;
                rotate(target->parent, 'l');
                w = target->parent->right;
            }
            if(w->left->color == black && w->right->color == black){
                w->color = red;                                                 //CASE 2
                target = target->parent;
            } else {
                if(w->right->color == black){
                    w->left->color = black;                                         //CASE 3
                    w->color = red;
                    rotate(w,'r');
                    w = target->parent->right;
                }
                w->color = target->parent->color;                               //CASE 4
                target->parent->color = black;
                w->right->color = black;
                rotate(target->parent,'l');
                target = root;
            }
        } else {
            struct node* w = target->parent->left;
            if(w->color == red){
                w->color = black;                                               //CASE1
                target->parent->color = red;
                rotate(target->parent, 'r');
                w = target->parent->left;
            }
            if(w->right->color == black && w->left->color == black){
                w->color = red;                                                 //CASE 2
                target = target->parent;
            } else {
                if(w->left->color == black){
                    w->left->color = black;                                         //CASE 3
                    w->color = red;
                    rotate(w,'l');
                    w = target->parent->left;
                }
                w->color = target->parent->color;                               //CASE 4
                target->parent->color = black;
                w->left->color = black;
                rotate(target->parent,'l');
                target = root;
            }
        }
    }
    target->color = black;
}

struct node* redBlackTree::search(struct node *current,int x){                  //recursively searches using the increasing order property
    if(current == sentinel)return sentinel;                                     //same as a regular BST
    if(current->data==x)return current;
    if(x>current->data && current->right!=sentinel){
        return search(current->right,x);
    }
    else if(current->left!=sentinel){
        return search(current->left,x);
    }else{
        return sentinel;
    }
}
                        //------------traversal methods below-----------
void redBlackTree::inorder (struct node *current){
    if(current!=sentinel){
        inorder(current->left);
        cout<<current->data<<":"<<(current->color?"b":"r")<<" ";
        inorder(current->right);
    }
    return;
}

void redBlackTree::preorder (struct node *current){
    if(current!=sentinel){
        cout<<current->data<<":"<<(current->color?"b":"r")<<" ";
        preorder(current->left);
        preorder(current->right);
    }
    return;
}

void redBlackTree::postorder (struct node *current){
    if(current!=sentinel){
        postorder(current->left);
        postorder(current->right);
        cout<<current->data<<":"<<(current->color?"b":"r")<<" ";
    }
    return;
}
