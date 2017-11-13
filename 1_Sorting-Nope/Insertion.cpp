#include<iostream>

using namespace std;

void insertionSort (int *arr, int n){
	int j, temp;
	for (int i = 0; i < n; i++){
		j = i;
		while (j > 0 && arr[j] < arr[j-1]){
			  temp = arr[j];
			  arr[j] = arr[j-1];
			  arr[j-1] = temp;
			  j--;
			  }
		}
    return;
}

int main(){
    int n;
    cout<<"Enter number of elements: ";
    cin>>n;
    int a[n];
    cout<<"Enter the "<<n<<" values: ";
    int i;
    for(i=0;i<n;i++){
        cin>>a[i];
    }
    insertionSort(a,n);
    cout<<"The sorted array is:";
    for(i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
    return 0;
}
