#include <stdio.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void buildMaxHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

void printHeap(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void heapSort(int arr[], int n) {
    // 초기 힙 구성
    for (int i = 1; i <= n; i++) {
        buildMaxHeap(arr, i);
        printHeap(arr, i);
    }

    // 힙 정렬 수행
    for (int i = n - 1; i > 0; i--) {
        // 루트(최대값)과 마지막 원소를 교환
        swap(&arr[0], &arr[i]);

        // 교환 후 힙 크기를 줄이고, 힙 재정렬
        heapify(arr, i, 0);

        // 현재 힙 상태 출력
        printHeap(arr, i);
    }
}

int main() {
    int inputData[] = { 34, 12, 76, 59, 32, 55, 88, 26, 16, 79, 35, 85, 29, 78, 41, 56, 86 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    printf("<Sort>\n");
    heapSort(inputData, size);

    printf("\nSorted Array:\n");
    for (int i = 0; i < size; i++) {
        printf("%d ", inputData[i]);
    }
    printf("\n");

    return 0;
}
