#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

#define MAX_RANGE 10000

// Declare global arrays to avoid memory overflow
int arr1[1000000];
int arr2[1000000];
int arr3[1000000];
int C[1000000];   // Temporary array created globally for Improved Merge Sort

// CSV files used to store tables of different questions 
FILE* file1;
FILE* file2;
FILE* file3;
FILE* file4;

// QUICK SORT IMPLEMENTATION

//Partition Function
int partition(int* arr, int start, int end, long long int* comp) {
    // Choosing first element as pivot
    int pivot = start;
    int curr_idx = start;

    // This will ensure that all elements smaller than pivot are at the start of the array
    int curr;
    for(int i=start+1;i<=end;i++) {
        *comp += 1;
        if(arr[i] < arr[pivot]) {
            curr_idx++;
            curr = arr[curr_idx];
            arr[curr_idx] = arr[i];
            arr[i] = curr;
        }
    }

    // One final swap to put the pivot in its correct position
    curr = arr[curr_idx];
    arr[curr_idx] = arr[pivot];
    arr[pivot] = curr;

    // This is the index at which the element is at its correct position
    return curr_idx;
}

// Recursive Quicksort implementation
void quickSort(int* arr, int start, int end, long long int* comp) {
    if(start < end) {
        // This is the index which is correctly placen in sorted array
        int correct_idx = partition(arr, start, end, comp);

        // Recursively sort the remaining left and right arrays
        quickSort(arr, start, correct_idx-1, comp);
        quickSort(arr, correct_idx+1, end, comp);
    }
}

// MERGE SORT IMPLEMENTATION

// Merge funciton of Merge Sort
void merge(int* arr, int start, int mid, int end, long long int* comp) {
    int C[end-start+1];    // Temporary array to initially store the merged array

    int idx_left = start;
    int idx_right = mid+1;
    int idx_C = 0;

    // Check arr[idx_left] with arr[idx_right] and put the smalled in C and move ahead appropriately
    while((idx_left <= mid) && (idx_right <= end)) {
        *comp += 1;
        if(arr[idx_left] <= arr[idx_right]) {
            C[idx_C] = arr[idx_left];
            idx_left++;
        }
        else {
            C[idx_C] = arr[idx_right];
            idx_right++;
        }
        idx_C++;
    }

    // If any array is remaining fill it in 'arr'(input array)
    while(idx_left <= mid) {
        C[idx_C] = arr[idx_left];
        idx_left++;
        idx_C++;
    }
    while(idx_right <= end) {
        C[idx_C] = arr[idx_right];
        idx_right++;
        idx_C++;
    }

    // Copy C array back to original array
    for(int i=start;i<=end;i++) {
        arr[i] = C[i-start];
    }
}

void mergeSort(int* arr, int start, int end, long long int* comp) {
    if(start < end) {
        int mid = start + (end-start)/2;

        // Recursively call mergeSort to get sorted subarrays
        mergeSort(arr, start, mid, comp);
        mergeSort(arr, mid+1, end, comp);

        // Combine the above two calls into a final merged array
        merge(arr, start, mid, end, comp);
    }
}

void improvedMerge(int* arr, int start, int mid, int end, long long int* comp) {
    int idx_left = start;
    int idx_right = mid+1;
    int idx_C = start;

    // Check arr[idx_left] with arr[idx_right] and put the smalled in C and move ahead appropriately
    while((idx_left <= mid) && (idx_right <= end)) {
        *comp += 1;
        if(arr[idx_left] <= arr[idx_right]) {
            C[idx_C] = arr[idx_left];
            idx_left++;
        }
        else {
            C[idx_C] = arr[idx_right];
            idx_right++;
        }
        idx_C++;
    }

    // If any array is remaining fill it in 'arr'(input array)
    while(idx_left <= mid) {
        C[idx_C] = arr[idx_left];
        idx_left++;
        idx_C++;
    }
    while(idx_right <= end) {
        C[idx_C] = arr[idx_right];
        idx_right++;
        idx_C++;
    }

    // Copy C array back to original array
    for(int i=start;i<=end;i++) {
        arr[i] = C[i];
    }
}

void improvedMergeSort(int* arr, int start, int end, long long int* comp) {
    if(start < end) {
        int mid = start + (end-start)/2;

        // Recursively call mergeSort to get sorted subarrays
        improvedMergeSort(arr, start, mid, comp);
        improvedMergeSort(arr, mid+1, end, comp);

        // Combine the above two calls into a final merged array
        improvedMerge(arr, start, mid, end, comp);    // Improved Merge function does not create temp array withing but used
                                                      // global temp array  
    }
}

// HELPER FUNCTIONS
// Populates arr1 and/or arr2 and/or arr3 depeneding of which pointer is null and which is not
void populateArray(int* arr1, int* arr2, int* arr3, int n) {
    for(int i=0;i<n;i++) {
        double random_num = (int)rand()%(int)MAX_RANGE;
        if(arr1 != NULL)
            arr1[i] = random_num;
        if(arr2 != NULL)    
            arr2[i] = random_num;
        if(arr3 != NULL)    
            arr3[i] = random_num;
    }
}

// Compare Quick Sort with Merge Sort and Improved Merge Sort in terms of Avg comparisons and Avg Running Time
void compareSortingAlgos(int n) {
    double total_time_q_sort = 0, total_time_m_sort = 0, total_time_m_sort_improved = 0;
    long long int comp, total_comp_q_sort, total_comp_m_sort;

    clock_t t, time_taken;
    int times_m_sort_better_q_sort, times_m_sort_improved_better_q_sort;
    for(int i=0;i<500;i++) {
        times_m_sort_better_q_sort = 0;
        times_m_sort_improved_better_q_sort = 0;
        comp = 0;
        populateArray(arr1, arr2, arr3, n);
        
        t = clock();
        quickSort(arr1, 0, n-1, &comp);              // Quick Sort
        time_taken = (clock()-t);

        double time_ms1 = ((double)time_taken*(1e6))/CLOCKS_PER_SEC;
        total_time_q_sort += time_ms1;
        total_comp_q_sort += comp;

        comp = 0;

        t = clock();
        mergeSort(arr2, 0, n-1, &comp);              // Merge Sort
        time_taken = (clock()-t);

        double time_ms2 = ((double)time_taken*(1e6))/CLOCKS_PER_SEC;
        total_time_m_sort += time_ms2;
        total_comp_m_sort += comp;

        if(time_ms2 <= time_ms1)
            times_m_sort_better_q_sort++;

        comp = 0;

        t = clock();
        improvedMergeSort(arr3, 0, n-1, &comp);              // Imroved Merge Sort
        time_taken = (clock()-t);

        double time_ms3 = ((double)time_taken*(1e6))/CLOCKS_PER_SEC;
        total_time_m_sort_improved += time_ms3;
        if(time_ms3 <= time_ms1)
            times_m_sort_improved_better_q_sort++;
    }
    double avg_time_q_sort = (double)total_time_q_sort/500;
    double avg_comp_q_sort = (double)total_comp_q_sort/500;
    double avg_time_m_sort = (double)total_time_m_sort/500;
    double avg_comp_m_sort = (double)total_comp_m_sort/500;
    double avg_time_m_sort_improved = (double)total_time_m_sort_improved/500;
    fprintf(file1, "%d,%lf,%lf,%lf,%lf\n",n,avg_comp_q_sort,2*n*log(n),avg_comp_m_sort,n*log2(n));
    fprintf(file3, "%d,%lf,%lf,%d\n",n,avg_time_q_sort,avg_time_m_sort,times_m_sort_better_q_sort);
    fprintf(file4, "%d,%lf,%lf,%d\n",n,avg_time_q_sort,avg_time_m_sort_improved,times_m_sort_improved_better_q_sort);
}

// Function for Q 1.2 that finds avg time of Quick Sort
void avgTimeQuickSort(int n) {
    double total_time = 0;
    long long int comp;

    clock_t t, time_taken;
    for(int i=0;i<500;i++) {
        comp = 0;
        populateArray(arr1, NULL, NULL, n);
        
        t = clock();
        quickSort(arr1, 0, n-1, &comp);
        time_taken = (clock()-t);

        double time_ms = ((double)time_taken*(1e6))/CLOCKS_PER_SEC;
        total_time += time_ms;
    }
    double avg_time = (double)total_time/500;
    fprintf(file2, "%d,%lf\n",n,avg_time);
}

int getError(int x, int avg) {
    if(x > (double)2*(double)avg) return 100;
    else if(x > (double)1.5*(double)avg) return 50;
    else if(x > (double)1.3*(double)avg) return 30;
    else if(x > (double)1.2*(double)avg) return 20;
    else if(x > (double)1.1*(double)avg) return 10;
    else return 0;
}


int main() {
    int n = 100000;
    srand(time(NULL));


    // For calculating deviation from average we had modified the return type of evaluate functions. The code for the logic used is given below;
    // int err[101];
    // int t = 0;
    
    // long long int c = 0;
    // for(long long int i=100;i<10000000;i = i*10) {
    //     c = 0;
    //     err[5] = err[10] = err[20] = err[30] = err[50] = err[100] = 0;
    //     for(int j=0;j<500;j++) {
    //         populateArray(a, i);
    //         int curr_time = evalTimeQSort(i);
            // err[getError(curr_time, avg[t])]++;
    //     }
    //     t++;
    //     printf("%d %d %d %d %d %d\n", err[5],err[10],err[20],err[30],err[50],err[100]);
    // }

    file1 = fopen("Q1.1.csv", "w");
    file2 = fopen("Q1.2.csv", "w");
    file3 = fopen("Q1.3.csv", "w");
    file4 = fopen("Q1.4.csv", "w");

    fprintf(file1,"n,Average Comparisons by Quick Sort,2nlog(n),Average Comparisons by Merge Sort,nlog2(n)\n");
    fprintf(file2,"nlog10(n),Average Running Time of Quick Sort\n");
    fprintf(file3,"n,Average Running Time of Quick Sort, Average Running Time of Merge Sort, Number of Times Merge Sort Outperformed Quick Sort\n");
    fprintf(file4,"n,Average Running Time of Quick Sort, Average Running Time of Improved Merge Sort, Number of Times Improved Merge Sort Outperformed Quick Sort\n");
    
    
    for(int i=100;i<=1000000;i=i*10) {    // This for loop is for Q1.1, Q1.3 and Q1.4
        compareSortingAlgos(i);
    }

    for(int i=100000;i<=900000;i=i+200000) {   // This for loop is for Q1.2
        avgTimeQuickSort(i);
    }
    return 0;
}