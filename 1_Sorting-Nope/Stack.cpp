#include<iostream>
#define size 10                 //size of stack is 10

using namespace std;

char command(){                 //this fn takes an input from the user to get functionality
    char inp;
    cout<<"\n-Press 's' to check the status of the stack\n-press 'P' to push\n-Press 'p' to pop\n-Press 'd' to display the stack\n-Press 'q' to quit\n>>>> ";
    cin>>inp;
    return inp;
}

class stack{
        private:
            int mem[size];      //declaration of the actual stack memory (size = 10)
            int stackPtr;       //stackPtr maps to the elements of the stack
        public:
            stack(){
                stackPtr=0;     //stackPtr is always mapped to the next empty element in the stack
            }

            int stackFlow(){        //stackflow checks the status of the stack and returns an int accordingly
                if(stackPtr==0)return -1;           // -1 for stack underflow
                if(stackPtr==size)return 1;         // +1 for stack overflow
                return 0;                           //0 for all other cases
            }

            void display(){                         //displays stack from start to end
                if(stackPtr==0){
                    cout<<"Stack is empty"<<endl;       //checking for stackunderflow
                    return;
                }
                cout<<"Here's your stack: \n";
                int x;
                cout<<endl;
                for(x=0;x<stackPtr;x++)cout<<mem[x]<<" ";
                cout<<endl;
            }

            void PUSH(int x){                       //function to implement PUSH
                if(stackPtr<size){                  //checking for stackoverflow
                    mem[stackPtr++]=x;              //increments stackPtr AFTER pushing an element
                    return;
                }
                else{
                    cout<<"Stack is full"<<endl;
                    return;
                }
            }

            void POP(){                             //function to implement POP
                if(stackPtr>0){                     //checking for stackunderflow
                    cout<<mem[--stackPtr];          //stackPtr is decremented before POP
                    return;
                }

                else{
                    cout<<"Stack is empty";
                    return;
                }
            }
};


int main(){
    stack s;
    while(1){
        switch(command()){                  //takes user input commands and executes respective functions
            case 's':
                switch(s.stackFlow()){
                    case -1:
                    cout<<"\nStack is empty"<<endl;
                    break;

                    case 0:
                    cout<<"\nStack is neither empty nor full"<<endl;
                    break;

                    case 1:
                    cout<<"\nStack is full"<<endl;
                    break;
                }
                break;

            case 'P':
                int ele;
                cout<<">>";
                cin>>ele;
                s.PUSH(ele);
                break;
            case 'p':
                s.POP();
                break;

            case 'd':
                s.display();
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
