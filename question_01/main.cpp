#include <iostream>
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

void quickSort_itteration(int *arr, int start, int pivot) {
    stack<pair<int, int>> st;
    st.push(make_pair(start, pivot)); // we just stored the strt and pivot indexes in the stack as a tuple

    while (!st.empty()) {
        start = st.top().first;
        pivot = st.top().second;
        st.pop();

        int new_pivot = partitioning(arr, start,
                                     pivot); // this will give us the new location of the previous call pivot element

        if (new_pivot - 1 > start) { // we need to exclude the new position of the pivot element
            st.push(make_pair(start, new_pivot - 1));
        }
        if (pivot > new_pivot + 1) {// we need to exclude the new position of the pivot element
            st.push(make_pair(new_pivot + 1, pivot));
        }
    }
}

int *randomArray(int size) {
    /* Creates a random integer array of given size
     * */
    int *arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 10000;
    }
    return arr;
}

int *arrayCopy(int size, int *original) {
    /*generates a copy  of an integer array*/
    int *arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = original[i];
    }
    return arr;
}


void time_cal(int array_sizes[], int size) {
    /* this function calculates the average execution time for a given sizes, for each algorithm
     * For each size this function calculates the execution time for 20 random arrays,
     * Here we use the 2 identical arrays for each comparison
     * */

    for (int i = 0; i < size; i++) {
        double t_tot_recursive = 0;
        double t_tot_itterative = 0;

        for (int j = 0; j < 20; j++) {
            int *x = randomArray(array_sizes[i]);
            int *y = arrayCopy(array_sizes[i], x);

            auto start = std::chrono::high_resolution_clock::now(); // get the starting time
            quickSort_recursion(x, 0, array_sizes[i] - 1);
            auto stop = std::chrono::high_resolution_clock::now(); // get the ending time
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
                    stop - start); // calculate the elapsed time

            t_tot_recursive += duration.count();


            auto start2 = std::chrono::high_resolution_clock::now(); // get the starting time
            quickSort_itteration(y, 0, array_sizes[i] - 1);
            auto stop2 = std::chrono::high_resolution_clock::now(); // get the ending time
            auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(
                    stop2 - start2); // calculate the elapsed time
            t_tot_itterative += duration2.count();

        }
        cout << "Array_size_of " << array_sizes[i] << " quickSort_recursion " << "Elapsed time: "
             << t_tot_recursive/20 << " microseconds" << endl;
        cout << "Array_size_of " << array_sizes[i] << " quickSort_itteration " << "Elapsed time: "
             << t_tot_itterative/20 << " microseconds" << endl;
        cout << endl;

    }

}
    int main() {

        /*int * b = randomArray(10000);
        auto start = std::chrono::high_resolution_clock::now(); // get the starting time
        quickSort_recursion(b,0,9999);
        auto stop = std::chrono::high_resolution_clock::now(); // get the ending time
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        cout <<"Array_size_of "<<10000 <<" quickSort_recursion "<< "Elapsed time: " << duration.count() << " microseconds" << endl;
    */

        int sizes[5] = {10000, 20000, 30000, 40000, 50000};
        time_cal(sizes, 5);
        return 0;
    }
