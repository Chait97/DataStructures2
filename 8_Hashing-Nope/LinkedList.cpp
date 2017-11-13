#include<iostream>
#include<cstdio>

#DEFINE SIZE 10

using namespace std;

int getElement(){
    int element;
    cout<<endl<<"Enter an element(int): ";
    cin>>element;
    cout<<endl;
    return element;
}

char command(){
    char inp;
    cout<<"\n-Press 'i' to insert an element\n-Press 'x' to delete an element\n-Press 's' to search\n-Press 'd' to display the table\n-Press 'q' to quit\n>>>> ";
    cin>>inp;
    return inp;
}

class node{
public:
    int data;
    node *next;
    node *previous;
    node(int key){
        data = key;
        next = NULL;
        previous = NULL;
    }
};

int hash(int key, int m = SIZE){
    return key%(m-1);
}

void insert(int key, node *table, int size = SIZE){
    int index = hash(key);
    if(table[index] == NULL){
        table[index] = new node(key);
    }
    else{
        node *ins = new node(key);
        ins->next = table[index];
        table[index]->previous = ins;
        table[index] = ins;
    }
}

node* search(int key, node *table, int size = SIZE){

}

void delete(node* target){

}

void display(){

}

int main(){
    node table[SIZE];
    while(1){
        switch(command()){
            case 'i':
                insert(getElement(),table)
                break;

            case 'x':
                del(search(getElement(),table))
                break;

            case 's':
                node* result = search(getElement(),table);
                if(node)cout<<"Element found"<<endl;
                else cout<<"Element not found"<<endl;
                break;

            case 'd':
                display()
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
