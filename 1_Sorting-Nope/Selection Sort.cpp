#include<iostream>

using namespace std;

void selectionSort(int *arr, int n){
	int min,temp;
	for (int i=0; i < n-1; i++){
	    min = i;
		for (int j=i+1; j < n; j++){
            if (arr[j] < arr[min])
                min=j;
	    }
		if (min != i){
             temp = arr[i];
             arr[i] = arr[min];
             arr[min] = temp;
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
    selectionSort(a,n);
    cout<<"The sorted array is:";
    for(i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
    return 0;
}
