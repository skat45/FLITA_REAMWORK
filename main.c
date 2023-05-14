#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void UsrArrayInput(int arr[], int values_number) {
    int i;
    for (i = 0; i < values_number; i++) {
        printf("\nEnter arr[%d] = ", i + 1);
        scanf("%d", & arr[i]);
    }
}
void Swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void initRandomArray(int arr[], int n, int k) {
    srand(time(NULL));
    int randNum = 0, i;
    for (i = 0; i < n; i++) {
        randNum = rand() % k - 100;
        arr[i] = randNum;
    }
}

void BubbleSort(int arr[], int n) {
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = n - 1; j > i; j--)
            if (arr[j] < arr[j - 1]) {
                Swap( & arr[j], & arr[j - 1]);
                swapped = true ;
            }
        if(swapped == false)
            break;
    }
}

void Heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;
    if (largest != i) {
        Swap( & arr[i], & arr[largest]);
        Heapify(arr, n, largest);
    }
}

void HeapSort(int arr[], int n) {
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
        Heapify(arr, n, i);
    for (i = n - 1; i >= 0; i--) {
        Swap( & arr[0], & arr[i]);
        Heapify(arr, i, 0);
    }
}

int main() {
    int values_number, choise, k = 200;
    clock_t start, end;
    FILE * file;
    printf("\nEnter values_number= ");
    scanf("%d", & values_number);
    int * arr = (int * ) malloc(values_number * sizeof(int));
    printf("How to enter an array?\n1.Random\n2.Enter array values manually\n");
    printf("Your choice : ");
    scanf("%d", &choise);
    if (choise == 2) {
        UsrArrayInput(arr, values_number);
        printf("\n");
    } else {
        initRandomArray(arr, values_number, k);
    }
    printf("\nAlgorithm:\n1.BubbleSort\n2.HeapSort\n");
    printf("Your choice : ");
    scanf("%d", &choise);
    if (choise == 1) {
        printf(".BubbleSort\n");
        start = clock();
        printf("Processing...");
        BubbleSort(arr, values_number);
        end = clock();
        double search_time = 1.0 * (end - start) / CLOCKS_PER_SEC;
        printf("\rYour array successfully sorted for %.50f seconds\n", search_time);
        if ((file = fopen("BubbleSort_file.txt", "a")) == NULL) {
            printf("Cannot open BubbleSort_file.\n");
            exit(1);
        } else {
            fprintf(file, "%d;", values_number);
            fprintf(file, "%.50f\n", search_time);
        }
        fclose(file);
    } else {
        printf(".HeapSort\n");
        start = clock();
        printf("Processing...");
        HeapSort(arr, values_number);
        end = clock();
        double search_time = 1.0 * (end - start) / CLOCKS_PER_SEC;
        printf("\rYour array successfully sorted for %.50f seconds\n", search_time);
        if ((file = fopen("HeapSort_file.txt", "a")) == NULL) {
            printf("Cannot open HeapSort_file.\n");
            exit(1);
        } else {
            fprintf(file, "%d;", values_number);
            fprintf(file, "%.50f\n", search_time);
        }
        fclose(file);
    }
    free(arr);
    return 0;
}
