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

class node{
public:
    node *child, *right, *parent;
    int data, num;
    node(int n){
        data = n;
        child, right, parent = NULL;
        num = 0;
    }
};

class binomialHeap{
public:
    binomialHeap(){
        root = NULL;
    }
    node *getRoot(){return root;}
    node* findMin();
    int delMin();
    void insert(int);
    int merge(node*,node*);
    void display();
protected:
    node *root;
    void display(node *);
    void replace(node *);
    int level(node*)
};

int main(){
    binomialHeap H;
    while(1){
        switch(command()){
            case 'i':
                H.insert(getElement());
                break;

            case 'x':
                H.delMin();
                break;

            case 'm':
                H.findMin();
                break;

            case 'd':
                H.display();
                break;

            case 'q':
                return 0;

            case 'r':                                                                       //debugging purposes only
                //cout<<(H.getRoot())->data;
                break;

            default:
                cout<<"Please give a valid input..."<<endl;
                break;
        }
    }
    return 0;
}

void binomialHeap::insert(int n){
    node *newNode = new node(n);
    newNode->right = root;
    root = newNode;
    if(root->right != NULL && root->right->num == 0){
        cout<<"Merge karra";
        merge(root, root->right);
    }
}

int binomialHeap::merge(node *n1,node *n2){
    if(n1->num != n2->num || n1->right != n2)return -1;
    if(n1->data >= n2->data){
        n1->right = n2->child;
        n2->child = n1;
        n1->parent = n2;
        n2->num++;
        if(n1 == root) root = n2;
    } else {
        n1->right = n2->right;
        n2->right = n1->child;
        n1->child = n2;
        n1->num++;
    }
    if(n2 == root && root->right!=NULL)merge(root,root->right);
}

void binomialHeap::display(){
    node *current = root;
    while(current != NULL){
        cout<<"Heap: \n";
        display(current);
        cout<<"End Heap\n";
        current = current->right;
    }
}

void binomialHeap::display(node* current){
    cout<<current->data<<" ";
    for(node *N = current->child; N != NULL; N = N->right){
        display(N);
        cout<<endl;
    }
    return;
}

int binomialHeap::delMin(){
    node *target = findMin();
    //node *place = root;
    replace(target->child);
}

void binomialHeap::replace(node *target){
    static node* place = NULL;
    if(target == NULL)return;
    replace(target->right);
    target->parent = NULL;
    if(place == NULL){
        target->right = root;
        root = target;
    }
    else {
        target->right = place ->right;
        place->right = target;
    }
    place = target;
    if(level(place) == level(place->next))place = place->next;
}

node* binomialHeap::findMin(){
    node *current = root,*result = root;
    while(current != NULL){
        if(result->data <= current->data)result = current;
        current = current->right;
    }
    return result;
}

int binomialHeap::level(node *t){
    int out = 0;
    while(t != NULL){
        out++;
        t = t->child;
    }
    return out;
}
