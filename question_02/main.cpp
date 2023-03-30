#include <iostream>
#include <cstdio>
#include <stack>
#include <cstdlib>
#include <chrono>

using namespace std;


int partitioning(int *arr, int start, int pivot) { // start and pivot are both indexes of those items
    int j = start - 1;
    int temp;
    for (int i = start; i < pivot + 1; i++) {
        if (arr[i] < arr[pivot]) {
            j += 1;
            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    temp = arr[++j]; // because the new position of the pivot will be j = j+1
    arr[j] = arr[pivot];
    arr[pivot] = temp;
    return j;
}

void quickSort_recursion(int *arr, int start, int pivot) {
    if (pivot > start) {
        int new_pivot = partitioning(arr, start, pivot);
        quickSort_recursion(arr, start, new_pivot - 1);
        quickSort_recursion(arr, new_pivot + 1, pivot);
    }
}
void median(int * array,int size){
    //quickSort_recursion(array,0,size-1);
    quickSort_recursion(array,0,size-1);
    double num;
    if (size%2!=0){
        num = array[size%2];
    }
    else{
        num = (1.0*array[(size-1)%2]+1.0*array[(size)%2])/2;
    }
    cout<<"[";
    for (int i=0; i<size; i++){
        cout<<array[i]<<",";
    }
    cout<<"\b] ";
    printf("%.1f\n", num);
}

int main(){
    int size;
    cout<<"Enter the size of stream of integer";
    cin>>size;
    int arr[size];
    for (int i= 0 ; i<size;i++){
        cout<<"Enter the "<< i+1<<" th element :";
        cin>>arr[i];
    }
    cout<<endl;

    for (int i= 0 ; i<size;i++){
        median(arr,i+1);
    }


    return 0;
}
