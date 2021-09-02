#include <time.h>
#include <stdio.h>
#include <stdlib.h>

inline void swap(int &lef, int &rig) {
    int tmp = lef;
    lef = rig;
    rig = tmp;
}
static int partation(int *arr, int lef, int rig) {
    int i = lef;
    int j = lef + 1;
    while (j <= rig) {
        if (arr[j] < arr[lef]) {
            swap(arr[++i], arr[j]);
        } 
        ++j;
    }
    swap(arr[i], arr[lef]);
    return i;
}
static void doQuickSort(int *arr, int lef, int rig) {
    if (lef >= rig) {
        return;
    }
    int priv = partation(arr, lef, rig);
    doQuickSort(arr, lef, priv - 1);
    doQuickSort(arr, priv + 1, rig);
}

void quickSort(int *arr, int n) {
    doQuickSort(arr, 0, n-1);    
}

void doMergeSort(int *arr, int lef, int rig) {
    if (lef >= rig) {
        return;
    }
    int mid = (lef + rig) / 2;
    doMergeSort(arr, lef, mid);
    doMergeSort(arr, mid + 1, rig);
    int *p = (int*)malloc(sizeof(int) * (rig - lef + 1));
    int i = lef;
    int j = mid + 1;
    int k = 0;
    while (i <= mid && j <= rig) {
        if (arr[i] <= arr[j]) {
            p[k++] = arr[i++];
        } else {
            p[k++] = arr[j++];
        }
    }
    while(i <= mid) { p[k++] = arr[i++]; }
    while(j <= rig) { p[k++] = arr[j++]; }
    k = 0;
    for (int i = lef; i <= rig; ++i) {
        arr[i] = p[k++];
    }
    free(p);
    p = NULL;
}
void mergeSort(int *arr, int n) {
    return doMergeSort(arr, 0, n - 1); 
}

void adjustToMaxHeap(int *arr, int last, int index) {
    if (index >= last) {
        return;
    }
    int tmp = arr[index];
    int lef = index * 2 + 1;
    int rig = (index + 1) * 2;
    while (lef <= last) {
        if (rig <= last) {
            if(tmp >= arr[lef] && tmp >= arr[rig]) {
                break;
            }  else if (arr[lef] > tmp && arr[lef] >= arr[rig]) {
                arr[index] = arr[lef];
                index = lef;
            } else {
                arr[index] = arr[rig];
                index = rig;
            }

        } else {
            if (tmp >= arr[lef]) {
                break;
            } else {
                arr[index] = arr[lef];
                index = lef;
            }
        }
        lef = index * 2 + 1;
        rig = (index + 1) * 2;
    }
    arr[index] = tmp;
} 
void doHeapSort(int *arr, int last) {
    for (int i = (last+1) / 2; i >= 0; --i) {
        adjustToMaxHeap(arr, last, i);
    }
    for (int i = last; i > 0; --i) {
        swap(arr[0], arr[i]);
        adjustToMaxHeap(arr, i-1, 0);
    }
}
void heapSort(int *arr, int n) {
    return doHeapSort(arr, n - 1);
}

int main() {
    srand((unsigned)time(NULL));
    const int N = 20;
    int a[N] = {0};
    int b[N] = {0};
    for (int i = 0; i < N; ++i) {
        a[i] = b[i] = rand() % N;
    }
    clock_t start; 
    clock_t end;
    double cost_time = 0.0;
#if 1
    for (int i = 0; i < N; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
#endif
    start = clock();
    //quickSort(a, N);
    //mergeSort(a, N);
    heapSort(a, N);
    end = clock();
    cost_time = (double)(end - start) / CLOCKS_PER_SEC;
    printf("my quick sort time cost: %lf\n", cost_time);

#if 1

    for (int i = 0; i < N; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
#endif
    return 0;
}
