#include<iostream>

using namespace std;

char command(){
    char inp;
    cout<<"\n-Press 'e' to enter an element\n-Press 'x' to delete an element\n-Press 'd' to display the queue\n-Press 'q' to quit\n>>>> ";
    cin>>inp;
    return inp;
}

class queue{
    private:
        int size,front,end, array[10000],checkFull;
    public:
        queue(){
            cout<<"Enter the size of the circular queue: ";
            cin>>size;
            front=0;
            end=0;
            checkFull=0;
        }
        void insert_in_queue(int element){
            if(checkFull==0){
                array[end]=element;
                end++;
                end%=size;
                if(end==front){
                    checkFull=1;cout<<"Queue full";
                    cout<<"Position of end="<<end;
            }
            } else {cout<<"Queue is full"<<endl;}
        }

        int delete_from_queue(){
                cout<<"The dequeued element is: "<<array[front];
                front++;
                front%=size;
                cout<<"Position of front="<<front;
        }

        int display_queue(){
            if(front==end){
                cout<<"The queue is: ";
                for(int i=0;i<size;i++){
                    cout<<array[(front+i)%size]<<" ";
                    if((front+i)%size==end)return 0;
                }
            }
        }
};

int main(){
    queue Q;
    while(1){
        switch(command()){
            case 'e':
                int element;
                cout<<"Enter an element to enqueue: ";
                cin>>element;
                Q.insert_in_queue(element);
                break;

            case 'x':
                if(!Q.delete_from_queue())cout<<"Queue is empty"<<endl;
                break;

            case 'd':
                Q.display_queue();
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
