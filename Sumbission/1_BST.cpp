#include<iostream>

using namespace std;

struct node{
        int data;
        struct node *left;
        struct node *right;
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


class binarySearchTree{

        public:

            binarySearchTree(){
                root=NULL;
            }

            void insert(int);

            void search(int key){                                               //overloaded definitions for easy code
                struct node* result =  search(root,key);
                if(result==NULL)cout<<"\tElement not found"<<endl;
                else cout<<"\tElement found at: "<<result<<endl;
            }

            void del(int key){                                                  //overloaded definitions for easy code
                int result =  del(search(root,key));
                if(result)cout<<"\tElement deleted successfully."<<endl;
                else cout<<"\tNo such element in BST"<<endl;
            }

            void inorder(){
                if( root == NULL){
                    cout<<"Tree is empty. Please insert elements."<<endl;
                }
                else inorder(root);
            }

            struct node *getRoot(){                                             //resturns the root of BST
                return root;
            }

        protected:

            struct node *root;
            struct node* search(struct node*,int);
            int del(struct node *);
            void inorder(struct node*);

            struct node* parent(struct node* child, struct node* subtree){      // a function to give parent of specified node
                if (child == root || child == NULL || subtree == NULL) return NULL;
                if(subtree->left == child || subtree->right == child)return subtree;
                else {
                    if(child->data < subtree-> data)return parent(child, subtree->left);
                    else return parent(child, subtree->right);
                }
            }

            struct node* parent(struct node* child){
                return parent(child,root);
            }

            void fill(struct node* n,int y){
                n->data = y;
                n->left = NULL;
                n->right = NULL;
                return;
            }
};


//-----------------------------------------------------------------------main---------------------------------------------------------------------------


int main(){
    binarySearchTree tree;
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
                cout<<endl<<"\t";
                tree.inorder();
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


void binarySearchTree::insert(int x){
    struct node *current = root;
    if(current==NULL){
        struct node *newNode=new struct node;
        fill(newNode,x);
        root=newNode;                                                           //gets address of prefilled node and stores it  as root
        return;
    }
    while(1){
        if(current->data==x)return;
        if(x>current->data){                                                    //searching the place to store the new node
            if(current->right==NULL){
                struct node *newNode = new struct node;
                current->right = newNode;
                fill(newNode,x);
                return;
            } else {
                current = current->right;
            }
        }
        else{
            if(current->left==NULL){
                struct node *newNode = new struct node;
                current->left = newNode;
                fill(newNode,x);
                return;
            } else {
                current = current->left;
            }
        }
    }
}

void binarySearchTree::inorder (struct node *current){                          //display and traversal
    if(current!=NULL){
        inorder(current->left);                                                 //recursive definition
        cout<<current->data<<" ";
        inorder(current->right);
    }
    return;
}

int binarySearchTree::del (struct node* target){
    if(target == NULL)return 0;
    struct node *par;
    if(target->left==NULL && target->right==NULL){                              //target has no children
        if(target == root
            delete target;
            root = NULL;
            return 1;
        }
        par=parent(target);
        if(par->left == target)par->left = NULL;                                //parent's pointers must be set
        else par-> right = NULL;
        delete target;                                                          //deleting the target
        return 1;                                                               //return success
    }

    par = NULL;                                                                 //par will finally hold the target's parent
    if(target->left != NULL){
        struct node *delT = target->left;
        while (delT->right != NULL){
            par = delT;
            delT = delT->right;
        }
        target->data = delT->data;
        if(par != NULL)par->right = delT->left;
        else target->left = NULL;
        delete delT;
    } else {
        struct node *delT = target->right;
        while (delT->left != NULL){
            par = delT;
            delT = delT->left;
        }
        target->data = delT->data;
        if(par != NULL)par->left = delT->right;
        else target->right = NULL;
        delete delT;
    }

    return 1;
}

struct node* binarySearchTree::search(struct node *current,int x){              //to search the tree for an element
    if(current == NULL)return NULL;
    if(current->data==x)return current;
    if(x>current->data && current->right!=NULL){
        return search(current->right,x);                                        //recusrive definition
    }
    else if(current->left!=NULL){
        return search(current->left,x);
    }else{
        return NULL;
    }
}
