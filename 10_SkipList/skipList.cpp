#include<iostream>
#include<cstdlib>
#include<climits>
#include<time.h>

#define MAX_LEVEL 6

using namespace std;


//--------------------------------------------------------------Class Definitions------------------------------------------------------------------------


class node{
public:
        int data;
        node *left;
        node *right;
        node *up;
        node *down;
        node(int x){
            data = x;
            up = left = right = down = NULL;
        }
};

class skipList{
public:
    node *header;
    int level;                                                                  //no of levels in current skipList
    void insert(int);
    void del(int);
    node *search(int);
    void display();
    skipList()                                                                  //constuctor creates an empty level
    :level(0)
    {
            header = new node(INT_MIN);                                         //analogous to -infinity
            header->right = new node(INT_MAX);                                  //analogous to +infinity
            header->right->left = header;
    }
protected:
    node* inject(node*, node*);
    node* findClosest(int, int = 0);
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
    cout<<"\n-Press 'i' to insert an element\n-Press 'x' to delete an element\n-Press 's' to search for an element\n-Press 'd' to display the list\n-Press 'q' to quit\n>>>> ";
    cin>>inp;
    return inp;
}


//--------------------------------------------------------------Driver Program------------------------------------------------------------------------



int main(){
    srand(time(NULL));
    skipList list;
    while(1){
        switch(command()){
            case 'i':
                list.insert(getElement());
                break;

            case 'x':
                list.del(getElement());
                break;

            case 's':
                list.search(getElement());
                break;

            case 'd':
                list.display();
                cout<<endl;
                break;

            case 'q':
                return 0;

            case 'h':                                                                       //debugging purposes only
                cout<<list.header->data;
                break;

            default:
                cout<<"Please give a valid input..."<<endl;
                break;
        }
    }
    return 0;
}


//----------------------------------------------------------function definitions-----------------------------------------------------

void skipList::insert(int key){
    node *link;
    node *ins = inject(new node(key),findClosest(key));                         //inserts in the right position
    if(ins == NULL)return;
    int nextLevel = 1;
    while(rand()%2){                                                            //a random function to promote keys into the next level
        if(nextLevel <= level){                                                 //if current levels are not more than the limit
            link = inject(new node(key),findClosest(key,nextLevel++));
            link->down = ins;
            ins->up = link;
            ins = link;
        } else if(level <= MAX_LEVEL){                                          //if a new level can be created
            cout<<"Promoting";
            node *h;
            h = new node(INT_MIN);                                              //creation of a new level
            h->right = new node(INT_MAX);
            header->up = h;
            h->down = header;
            header = h;
            link = inject(new node(key),header);                                //inserting in the right place
            link->down = ins;
            ins->up = link;
            ins = link;
            nextLevel++;
            level++;
        }
    }
}

node* skipList::inject(node *insert, node* place){                              //this fuction injects into the skiplist and sets the left and right nodes accordingly
    if(place->data == insert->data)return NULL;
    insert->left = place;
    insert->right = place->right;
    place->right = insert;
    insert->right->left = insert;
    return insert;
}

node* skipList::search(int key){                                                //search function, works in O(logn) worst case time
    node *current = header;
    while(1){                                                                   //search from top level until bottom
        while(current->right->right != NULL && current->right->data <= key){
            current = current->right;
        }
        if(current->data == key){
            cout<<"Data Found."<<endl;
            return current;
        }
        else {
            if(current->down != NULL){
                current = current->down;                                        //go down one level
            } else {
                cout<<"Data not found."<<endl;
                return NULL;
            }
        }
    }
}

node* skipList::findClosest(int key, int lowLevel){                             //finds closest key less than input, and in the specified level
    node *current = header;
    int l = level;
    while(l >= lowLevel){
        while(current->right->right != NULL && current->right->data <= key){
            current = current->right;
        }
        if(l == lowLevel)break;
        else {
            current = current->down;
            l--;
        }
    }
    return current;
}

void skipList::display(){                                                       //traversal is from top level upto bottom
    node* start = header;
    if(header->right->right == NULL){
        cout<<"List empty. Please insert some elements."<<endl;
        return;
    }
    while(start != NULL){
        node *current = start->right;
        cout<<"-∞ --- ";
        while(current->right != NULL){
            cout<<current->data<<" --- ";
            current=current->right;
        }
        cout<<"+∞"<<endl;
        start = start->down;
    }
}

void skipList::del(int key){                                                    //deletion is from top level to bottom
    node* next, *target = search(key);
    while(target != NULL){
        target->left->right = target->right;
        target->right->left = target->left;
        next = target->down;
        delete target;
        target = next;
    }
    while(header->right->right == NULL){                                        //if a level becomes empty
        if(header->down == NULL)return;
        next = header->down;
        delete header->right;                                                   //level is removed
        delete header;
        header = next;
        level--;                                                                //no of levels decremented
    }
}
