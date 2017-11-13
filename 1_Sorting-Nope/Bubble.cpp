#include<iostream>

using namespace std;

void bubbleSort (int *arr, int n){
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n - i - 1; ++j){
            if (arr[j] > arr[j + 1]){
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
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
    bubbleSort(a,n);
    cout<<"The sorted array is:";
    for(i=0;i<n;i++){
      cout<<a[i]<<" ";
    }
    return 0;
}
