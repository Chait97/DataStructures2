/*
1. Inserting a node at the end of the queue. The value to be put in the node will be passed as a function parameter.
2. Searching for a value in the linked list.
3. Displaying the entire linked list. While displaying, print (a) the value contained in the node and (b) the address of the node.
4. Deleting the entire linked list.
*/

#include<iostream>
#include<string>

using namespace std;

char command(){                 //this fn takes an input from the user to get functionality
    char inp;
    cout<<"\n-Press 'i' to insert an element\n-Press 's' to search for an element\n-Press 'd' to display the list\n-Press 'x' to delete an element\n-Press 'q' to quit\n>>>> ";
    cin>>inp;
    return inp;
}

struct node{                    //definition of the required structure
    int Roll,age;
    string name,gender;
    struct node *next;
};

class queue{
    public:
        queue();
        struct node dequeue(int);
        struct node* search(int);
        void display();
        void enqueue(int);
    protected:
        struct node *start,*end;
};

int main(){
    queue list;                                                          //sets the start and end
    while(1){
        switch(command()){                                                  //user inputs the commands
            case 'i':
                int element;
                cout<<"Enter an integer element to enqueue: ";
                cin>>element;
                list.enqueue(element);
                break;

            case 'x':
                cout<<"Enter an integer element to dequeue: ";
                cin>>element;
                if(list.dequeue(element))cout<<"\nElement deleted successfully\n";
                else cout<<"\nNo such element exists\n"<<endl;
                break;

            case 's':
            {
                int srch;
                cout<<"Enter an integer element to search: ";
                cin>>srch;
                struct node *result=list.search(srch);
                if(result)cout<<cout<<"\nThe element was found at:"<<result<<endl;
                else cout<<"Element not found."<<endl;
                break;
            }

            case 'd':
                list.display();
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

queue::queue(){              //sets/reserts the start and end pointers
    start = new struct node;
    start->next=NULL;
    end=start;
    return;
}

void queue::display(){
    struct node *current;
    cout<<endl;
    for(current=start->next;current!=NULL;current=current->next){           //from starting to ending of the list, current takes the next address in the for loop step itself
        cout<<"\t\tValue: "<<current->Roll<<"      at Address: "<<current<<endl;
    }
    cout<<"\n--linked list was printed--\n\n";                              //log
    return;
}

void queue::enqueue(int newVal){
    struct node *newEnd = new struct node;       //dynamically allocates memory for accomodating a new node
    newEnd->Roll=newVal;                                                     //value is stored in the newly created node
    end->next=newEnd;                                                       //the end is now pointing to the new node
    newEnd->next=NULL;                                                      //the new node is globally declared as the end of the list
    end=newEnd;
    this->display();
    return;
}

struct node* queue::search(int searchVal){
    struct node *current;                                                   //current to iterate over the list
    for(current=start->next;current!=NULL;current=current->next){
        if(current->Roll==searchVal){                                        //checking for the value
            return current;                                                         //returns if found
        }
    }
    return NULL;
}

struct node queue::dequeue(){
    struct node temp = *(head->next);
    delete (head->next);
    head->next = temp->next
    return temp;
}
