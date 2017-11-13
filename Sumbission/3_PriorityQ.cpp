#include<iostream>
#include<cstdio>
#include<string>

#define MAX_SIZE 1000

using namespace std;

int getElement(){
    int element;
    cout<<endl<<"Enter an element(int): ";
    cin>>element;
    cout<<endl;
    return element;
}

string getString(){
    string element;
    cout<<endl<<"Enter a element(string): ";
    cin>>element;
    cout<<endl;
    return element;
}

char command(){
    char inp;
    cout<<"\n-Press 'i' to insert an element\n-Press 'x' to extract the top of the Priority Queue\n-Press 's' to sort the Priority Queue (and quit)\n-Press 'd' to display the Queue inorder (for debugging)\n-Press 'q' to quit\n>>>> ";
    cin>>inp;
    return inp;
}


//--------------------------------------------------------------Class Definition------------------------------------------------------------------------


class node{
    public:
        string el;
        int p;
        node(){};
        node(string element, int priority){
            el= element;
            p = priority;
        }
};

class heap{
protected:
    int heapSize=0;
    node *heapArr=NULL;
public:
    heap(){
        heapArr = new node[MAX_SIZE];
        //buildHeap();
    }
    void inorder(int index = 0){
        if(index >= heapSize)return;
        inorder(left(index));
        cout<<heapArr[index].el<<" ";
        inorder(right(index));
        return;
    }

    void heapSort(){
        int originalSize = heapSize;
        node temp;
        for(int i = heapSize; i >0; i--){
            temp = heapArr[i];
            heapArr[i] = heapArr[0];
            heapArr[0] = temp;
            heapSize--;
            heapify(0);
        }
        heapSize = originalSize;
        for(int i = heapSize; i > 0; i--) cout<<heapArr[i].el<<" ";
    }
    string extTop(){
        if(heapSize == 0){
            cout<<"Queue empty >>";
            return "NULL";
        }
        node output = heapArr[0];
        heapArr[0] = heapArr[heapSize-1];
        heapSize--;
        heapify(0);
        return output.el;
    }
    void insert(int x,string s){
        if(heapSize + 1 >= MAX_SIZE){
            cout<<"Heap is full";
            return;
        }
        heapArr[heapSize].p = x;
        heapArr[heapSize].el = s;
        int index = heapSize;
        while(index != 0){
            int p;
            if(index%2 == 0 )p = index/2 -1;
            else p = index/2;
            if(heapArr[p].p > heapArr[index].p){
                node temp = heapArr[p];
                heapArr[p] = heapArr[index];
                heapArr[index] = temp;
            }
            index = p;
        }
        heapSize++;
    }

private:
    int left(int x){return (2*x + 1);}
    int right(int x){return (2*x +2);}
    void heapify(int x){
        int smallest, l=left(x), r= right(x);
        if(l <heapSize && heapArr[x].p > heapArr[l].p) smallest = l;
        else smallest = x;
        if(r <heapSize && heapArr[smallest].p > heapArr[r].p) smallest = r;
        if(smallest != x){
            node temp = heapArr[smallest];
            heapArr[smallest] = heapArr [x];
            heapArr[x] = temp;
            heapify(smallest);
        }
    }
    void buildHeap(){
        for(int i = (heapSize-1)/2; i >= 0; i--)heapify(i);
    }
};


int main(){
    heap A;
    while(1){
        switch(command()){
            case 'i':
                A.insert(getElement(),getString());
                break;

            case 'x':
                cout<<A.extTop();
                break;

            case 's':
                A.heapSort();
                return 0;

            case 'd':                                                           //debugging
                cout<<endl<<"\t";
                A.inorder();
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
