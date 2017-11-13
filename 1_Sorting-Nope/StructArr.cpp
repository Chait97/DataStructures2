#include<iostream>
#include<string>

using namespace std;

struct node{
    string RollNo;
    float age;
    string name;
    string gender;
};

void insertionSort (struct node *a, int n){
	int j;
    struct node temp;
	for (int i = 0; i < n; i++){
		j = i;
		while ((j > 0) && (a[j].RollNo).compare(a[j-1].RollNo)){    //j>0 and a.RollNo[j] < a.RollNo[j-1])
			  temp = a[j];
			  a[j] = a[j-1];
			  a[j-1] = temp;
			  j--;
			  }
		}
    return;
}

int takeRecord(struct node *arr,int index){
    string Roll;
    cout<<"\tEnter Roll No: ";
    cin>>Roll;
    for(int i=0;i<index;i++){
        if(arr[i].RollNo==Roll){
            cout<<"This roll number already exists, please enter another...\n";
            return 1;
        }
    }
    arr[index].RollNo=Roll;
    cout<<"\tEnter age: ";
    cin>>arr[index].age;
    cout<<"\tEnter Name: ";
    cin>>arr[index].name;
    cout<<"\tEnter gender: ";
    cin>>arr[index].gender;
    cout<<endl;
    return 0;
}

int main(){
    int n;
    cout<<"Enter the number of records to store: ";
    cin>>n;
    struct node arr[n];
    cout<<"Enter the details of each record\n";
    for(int i=0;i<n;i++){
        while(takeRecord(arr,i));
    }
    insertionSort(arr,n);
    for(int ix=n-1;ix>=0;ix--){
        cout<<arr[ix].RollNo<<endl;
    }
}
