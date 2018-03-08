#include <iostream>
#include <cstring>

#define MAX_SIZE 500000
int a[MAX_SIZE];

long long merge(int list[], int low, int high) {
    static int combined[MAX_SIZE];
    int mid = (low + high) / 2;
    int i = low, j = mid + 1, k = 0;
    long long count = 0;
    
    while (i <= mid && j <= high) {
        if (list[i] <= list[j])
            combined[k++] = list[i++];
        else {
            combined[k++] = list[j++];
            count += mid - i + 1;
        }
    }
    while (i <= mid)
        combined[k++] = list[i++];
    while (j <= high)
        combined[k++] = list[j++];

    std::memcpy(&list[low], combined, (high - low + 1) * sizeof(int));
    return count;
}

long long mergeSort(int list[], int low, int high) {
    long long count = 0;    
    if (high > low) {
        count  = mergeSort(list, low, (low + high) / 2);
        count += mergeSort(list, (low + high) / 2 + 1, high);
        count += merge(list, low, high);
    }
    return count;
}


int main(void)
{
    int N;

    while (std::cin >> N && N != 0) {
        for (int i = 0; i < N; i++)
            std::cin >> a[i];

        std::cout << mergeSort(a, 0, N - 1) << "\n";
    }

    return 0;
}
