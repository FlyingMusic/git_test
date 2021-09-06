#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void swap(int &lef, int &rig) {
    int tmp = lef;
    lef = rig;
    rig = tmp;
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

int partation(int *arr, int lef, int rig) {
    if (lef == rig) {
        return lef;
    }
    int i = lef;
    int j = lef + 1;
    while (j <= rig) {
        if (arr[j] < arr[lef]) {
            swap(arr[++i], arr[j]);
        }
        ++j;
    }
    swap(arr[lef], arr[i]);
    return i;
}
int kmax(int *arr, int n, int k) {
    k--;
    if (k > n-1) {
        k = n-1;
    } 
    if (k < 0) {
        k = 0;
    }
    int lef = 0;
    int rig = n - 1;
    while (true) {
        int priv = partation(arr, lef, rig);
        if (priv < k) {
            lef = priv + 1;
        } else if(priv > k) {
            rig = priv - 1;
        } else {
            return arr[k];
        }
    }
}
int main() {
    srand((unsigned)time(NULL));
    const int N = 20;
    int a[N] = {0};
    int b[N] = {0};
    for (int i = 0; i < N; ++i) {
        a[i] = b[i] = rand() % N;
    }
#if 1
    for (int i = 0; i < N; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
#endif
    heapSort(a, N);
#if 1
    for (int i = 0; i < N; ++i) {
        printf("%d ", a[i]);
    }
    printf("\n");
#endif
    int kth = N / 2 + 1;
    int kMax = kmax(a, N, kth);
    printf("kth = %d, kMax = %d\n", kth, kMax);
    return 0;
}
