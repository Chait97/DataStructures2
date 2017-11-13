/*Binomial heap with
    insert
    find Minimum
    union
    delete Minimum
*/

#include<iostream>
#include<cstdio>

using namespace std;

enum state: bool{open,close};

int getElement(){
    int element;
    cout<<endl<<"Enter an element(int): ";
    cin>>element;
    cout<<endl;
    return element;
}

char command(){
    char inp;
    cout<<"\n-Press 'i' to insert an element\n-Press 'x' to delete the Minimum\n-Press 'm' to print the Minimum\n-Press 'd' to display the heap\n-Press 'q' to quit\n>>>> ";
    cin>>inp;
    return inp;
}


//--------------------------------------------------------------Class Definitions-----------------------------------------------------------------------


class node{
public:
    node *child, *right, *parent;
    int data;
    node(int n){
        data = n;
        child = NULL;
        right= NULL;
        parent = NULL;
    }
};

class binomialHeap{
public:
    binomialHeap(){                                                             //initialiser empty heap
        root = NULL;
    }
    node *getRoot(){return root;}
    node* findMin();
    int delMin();
    void insert(int);
    int merge(node*,node*);
    void display();
protected:
    static node *root;
    void replace(node *);
    int level(node*);
};


//--------------------------------------------------------------Driver Program------------------------------------------------------------------------


int main(){
    binomialHeap H;
    node *result;
    while(1){
        switch(command()){
            case 'i':
                H.insert(getElement());
                break;

            case 'x':
                H.delMin();
                break;

            case 'm':
                result = H.findMin();
                if(result)cout<<"Minimum is: "<<result->data<<endl;
                else cout<<"Heap is empty."<<endl;
                break;

            case 'd':
                H.display();
                break;

            case 'q':
                return 0;

            case 'r':                                                                       //debugging purposes only
                cout<<(H.getRoot())->data;
                break;

            default:
                cout<<"Please give a valid input..."<<endl;
                break;
        }
    }
    return 0;
}

node* binomialHeap::root;


//--------------------------------------------------------------function Definitions-----------------------------------------------------------------------


void binomialHeap::insert(int n){                                               //inserts an element
    node *newNode = new node(n);
    newNode->right = root;
    root = newNode;
    if(root->right != NULL && level(root->right) == 1){
        merge(root, root->right);                                               //merges sizes 1 and 1 only
    }
}

int binomialHeap::merge(node *n1 = root, node *n2 = root->right){               //merges any two equal sizes
    if(level(n1) != level(n2) || n1->right != n2)return -1;
    if(n1->data >= n2->data){                   //n2 must end up as the parent
        n1->right = n2->child;
        n2->child = n1;
        n1->parent = n2;
        if(n1 == root) root = n2;
        if(n2->right!=NULL)merge(n2,n2->right);
    } else {                                    //n1 must end up as the parent
        n1->right = n2->right;
        n2->right = n1->child;
        n1->child = n2;
        if(n1->right!=NULL)merge(n1,n1->right);
    }
    return 0;
}

void binomialHeap::display(){                                                   //subheap by subheap traversal and display
    node *current = root;
    if(root == NULL){
        cout<<"Heap is empty, please insert some elements.";
        return;
    }
    while(current != NULL){
        cout<<" "<<current->data<<"("<<level(current)<<")";
        current = current->right;
    }
    return;
}


int binomialHeap::delMin(){                                                     //deletes smallest from heap
    node *target = findMin(), *current = NULL, *previous = NULL;
    if(target != NULL){
        replace(target->child);
        target->child = NULL;
        //display();                                                            //debugging
        cout<<endl;
        //cout<<"Root: "<<root->data<<endl;                             //debugging purposes only
        if(root != NULL){
            current = root;
            while(current->data != target->data){
                previous = current;
                current = current->right;
            }
            if(previous==NULL){
                if(root->right != NULL)
                    root = root->right;
            } else
                previous->right = target->right;
            delete target;
            if(target == root){
                root = NULL;
            }
            else {
                current = root;
                while(current->right != NULL){
                    if(merge(current,current->right) == 0)current = root;
                    else current = current->right;
                }
            }
        }
    }
    display();
    return 0;
}

void binomialHeap::replace(node *target){                                       //recusrively replaces to fix binomialHeap properties
    static node* place = NULL;
    if(target == NULL){
        place = NULL;
        return;
    }
    replace(target->right);
    target->parent = NULL;
    if(place == NULL){
        target->right = root;
        root = target;
        place = target;
        return;
    } else {
        target->right = place->right;
        place->right = target;
        place = target;
    }
    //cout<<"This is a pass and the current place pointer is at: "<<place->data<<" and the root is: "<<root->data<<endl; //debugging purposes only
    while(level(place) >= level(place->right))place = place->right;
}

node* binomialHeap::findMin(){                                                  //returns address of the smallest heap key
    node *current = root,*result = root;
    while(current != NULL){
        if(current->data <= result->data)result = current;
        current = current->right;
    }
    return result;
}

int binomialHeap::level(node *t){                                               //gives level of subheap
    int out = 0;
    while(t != NULL){
        out++;
        t = t->child;
    }
    return out;
}
