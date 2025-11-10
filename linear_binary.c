#include <stdio.h>
#include <time.h>

void search(int arr[], int num, int n) {
    
    int k = 0;

    

    for (int i = 0; i < n; i++) {
        if (arr[i] == num) {
            k = 1;
            printf("YES\n");
            break;
        }
    }

    if (k == 0) {
        printf("NO\n");
    }

    
}

void linearrecurr(int arr[], int num, int n, int i) {
    if (i >= n) { 
        printf("NO\n"); 
        return;
    }
    if (arr[i] == num) {
        printf("YES\n");
    } else {
        i++;
        linearrecurr(arr, num, n, i);
    }
}

void binarysearch(int arr[], int num, int n) {
    int high = n - 1;
    int low = 0;
    int mid;
    while (low <= high) {
        mid = low + (high - low) / 2;
        if (arr[mid] == num) {
            printf("YES\n");
            break;
        } else if (num > arr[mid]) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    if (low > high) {
        printf("NO\n");
    }
}


void binaryrecurr(int arr[], int num, int low, int high) {
    if (low > high) {
        printf("NO\n");
        return;
    }

    int mid = low + (high - low) / 2;

    if (arr[mid] == num) {
        printf("YES\n");
        return;
    } else if (num > arr[mid]) {
        binaryrecurr(arr, num, mid + 1, high);
    } else {
        binaryrecurr(arr, num, low, mid - 1);
    }
}

int main() {
    clock_t start, end;
    int n;
    printf("Enter size of array: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter the elements of sorted array:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int num;
    printf("Enter the element to be searched: ");
    scanf("%d", &num);
     printf("Using iterative linear search:\n");
    start = clock();
    search(arr, num, n);
    end = clock();
    double tli = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%lf seconds\n", tli);
   
   
     printf("Using recursive linear search:\n");
    start = clock();
    linearrecurr(arr, num, n,0);
    end = clock();
    double tlr = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%lf seconds\n", tlr);
   
    printf("Using iterative binary search:\n");
    start = clock();
    binarysearch(arr, num, n);
    end = clock();
    double tbi = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%lf seconds\n", tbi);

 
    printf("Using recursive binary search:\n");
    start = clock();
    binaryrecurr(arr, num, 0, n - 1);
    end = clock();
    double tbr = (double)(end - start) / CLOCKS_PER_SEC;
    printf("%lf seconds\n", tbr);
   


   
    return 0;
}
