#include <iostream>
#include <chrono>
#include <math.h>
#include <random>

using namespace std;
using namespace std::chrono;


//UTILITY _________________________________________________________________________________________________________

void fill_array_random(int arr[], int size) {

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, 99);

    for (int i = 0; i < size; i++)

        arr[i] = dis(gen);
}

void fill_array_ascend(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
}

void fill_array_descend(int arr[], int size) {
    int value = size-1;
    for (int i = 0; i < size; i++) {
        arr[i] = value;
        value--;
    }
}

void print_array(int A[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}


//INSERTION __________________________________________________________________________________________________________


void insert_sort(int arr[], int low, int high) {

    for(int i = low + 1; i < high; i++)
    {
        int value = arr[i];
        int j = i;

        while(j > low && arr[j - 1] > value)
        {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = value;
    }
}


//MERGE ______________________________________________________________________________________________________________

void merge(int arr[], int low, int mid, int high) {

    int i = low; //index pointer for lower half
    int j = mid+1; //index pointer for upper half
    int k = 0; // index pointer for temp array

    int *temp = new int[high-low+1];

    while (i <= mid && j <= high) {
        if (arr[i] < arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= high)
        temp[k++] = arr[j++];

    k = 0;
    for (i = low; i <= high;)
        arr[i++] = temp[k++];

    delete [] temp;
}



void merge_sort(int arr[], int low, int high) {

    if (low < high){
        int mid = (low + high)/2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid+1, high);
        merge(arr, low, mid, high);
    }
}


//QUICK 1 ____________________________________________________________________________________________________________

void partition(int arr[], int low, int high, int &pivot_point) {

    int i;
    int j = low;
    int pivot_item = arr[low];

    for (i = low+1; i <= high; i++) {
        if (arr[i] < pivot_item) {
            j++;
            swap(arr[i], arr[j]);
        }
    }

    pivot_point = j;
    swap(arr[low], arr[pivot_point]);
};

void quick_sort_1(int arr[], int low, int high) {
    int pivot_point;
    if (low < high) {
        partition(arr, low, high, pivot_point);
        quick_sort_1(arr, low, pivot_point-1);
        quick_sort_1(arr, pivot_point+1, high);
    }
}


//QUICK 2 _________________________________________________________________________________________________________

void quick_sort_2(int arr[], int low, int high) {

    int pivot_point;

    if(low < high) {

        if (high - low <= 16) {
            insert_sort(arr, low, high+1);

        }
        else {
            partition(arr, low, high, pivot_point);
            quick_sort_2(arr, low, pivot_point-1);
            quick_sort_2(arr, pivot_point+1, high);
        }

    }
}


//QUICK 3 _________________________________________________________________________________________________________

void partition_random(int arr[], int low, int high, int &pivot_point) {

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(low, high);

    int random = dis(gen);

    swap(arr[low], arr[random]);

    return partition(arr, low, high, pivot_point);
}

void quick_sort_3(int arr[], int low, int high) {

    int pivot_point;

    if (low < high) {
        if ((high+1) - low > 16) {

            partition_random(arr, low, high, pivot_point);
            quick_sort_3(arr, low, pivot_point-1);
            quick_sort_3(arr, pivot_point+1, high);
        }
        else {

            partition(arr, low, high, pivot_point);
            quick_sort_3(arr, low, pivot_point-1);
            quick_sort_3(arr, pivot_point+1, high);
        }

    }
}


//MAIN _______________________________________________________________________________________________________________

int main() {

    // test for n = 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 8192, 16384, 32768


    for (int i = 1; i <= 16; i++) {

        int nval = static_cast<int>(pow(2,i));
        int *test_random = new int[nval];
        fill_array_random(test_random,nval);

        auto start_random = high_resolution_clock::now();
        //insert_sort(test_random, 0, nval-1);
        //merge_sort(test_random, 0, nval-1);
        //quick_sort_1(test_random, 0, nval-1);
        //quick_sort_2(test_random, 0, nval-1);
        quick_sort_3(test_random, 0, nval-1);
        auto stop_random = high_resolution_clock::now();
        auto duration_random = duration_cast<nanoseconds >(stop_random - start_random);
        cout << i << " random duration: " << duration_random.count() << " nanoseconds" << endl;

        delete []test_random;

    }

}



