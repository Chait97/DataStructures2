#include<iostream>
#include<cstdio>

using namespace std;

class heap{                                                                     //heap class
protected:
    int heapSize=0,*heapArr=NULL;
public:
    heap(){
        cout<<"Enter the number of elements in the heap: ";
        cin>>heapSize;                                                          //user inputs heapsize
        heapArr = new int[heapSize];
        cout<<"Enter a space separated list of "<<heapSize<<" integers to create a heap: ";
        for(int i=0;i<heapSize;i++)cin>>heapArr[i];
        buildHeap();
    }
    void inorder(int index = 0){                                                //for increasing order traversal
        if(index >= heapSize)return;
        inorder(left(index));                                                   //recusrive definition
        cout<<heapArr[index]<<" ";
        inorder(right(index));
        return;
    }
    void heapSort(){                                                            //works by putting first element last
        int originalSize = heapSize,temp;
        for(int i = heapSize-1; i >0; i--){                                     //largest element goes to the end after each iteration
            temp = heapArr[i];
            heapArr[i] = heapArr[0];
            heapArr[0] = temp;
            heapSize--;                                                         //heapsize is reduced to perform operations on remaining heap
            heapify(0);                                                         //restores heap properties
        }
        heapSize = originalSize;
        for(int i = 0; i< heapSize; i++) cout<<heapArr[i]<<" ";
    }
private:
    int left(int x){return (2*x + 1);}
    int right(int x){return (2*x +2);}
    void heapify(int x){                                                        //restores heap properties
        int largest, l=left(x), r= right(x);
        if(l <heapSize && heapArr[x] < heapArr[l]) largest = l;
        else largest = x;
        if(r <heapSize && heapArr[largest] < heapArr[r]) largest = r;
        if(largest != x){
            int temp = heapArr[largest];
            heapArr[largest] = heapArr [x];
            heapArr[x] = temp;
            heapify(largest);                                                   //recursive definition
        }
    }
    void buildHeap(){
        for(int i = (heapSize-1)/2; i >= 0; i--){
            heapify(i);                                                         //repeatedly restores heap properties
        }
    }
};


int main(){
    heap A;
    A.heapSort();
}
