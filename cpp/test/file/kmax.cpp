#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int &lef, int &rig) {
    int tmp = lef;
    lef = rig;
    rig = tmp;
}

int part(int a[], int low, int high)
{
    int i = low;
    int x = a[i]; 
   
    for(int j = low+1; j <= high; j++) {
        if (a[j] >= x) {
            i++;
            swap(a[i], a[j]);
        }
	}
    swap(a[low], a[i]);
    return i;
}

int main()
{
    srand(NULL);
    int arr[100] = {0};
    for(int i = 0; i < 100; ++i) {
        arr[i] = rand()%100;
    }
    int k = 20;
    k--;
    int lef = 0;
    int rig = 100-1;
    while(true){
        int pvt = part(arr, lef, rig);
        if(pvt > k){
            rig = pvt - 1;
        } else if(pvt < k){
            lef = pvt + 1;
        } else {
            break;
        }
    }
    for(int i = 0; i < 100; ++i) {
        printf("%d ", arr[i]);
        if(i%10 == 9) printf("\n");
    }
    printf("\n");
    return 0;
}
