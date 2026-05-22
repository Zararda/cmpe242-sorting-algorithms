#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <cmath>
using namespace std;

// ─────────────────────────────────────────────
//  UTILITY
// ─────────────────────────────────────────────

void printArray(int* arr, int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int* createRandomArray(int n) {
    int* arr = new int[n];
    for (int i = 0; i < n; i++)
        arr[i] = rand() % (n * 10) + 1;
    return arr;
}

int* copyArray(int* src, int n) {
    int* dst = new int[n];
    for (int i = 0; i < n; i++)
        dst[i] = src[i];
    return dst;
}

// ─────────────────────────────────────────────
//  TASK 1 & 2  —  Verbose (step-by-step)
//  Prints array BEFORE every change
// ─────────────────────────────────────────────

// SELECTION SORT
void selectionSort_verbose(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[minIdx])
                minIdx = j;

        if (minIdx != i) {
            cout << "Before change: "; printArray(arr, n);
            int tmp = arr[i]; arr[i] = arr[minIdx]; arr[minIdx] = tmp;
        }
    }
}

// INSERTION SORT
void insertionSort_verbose(int* arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            cout << "Before change: "; printArray(arr, n);
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// HEAPSORT
void heapify_verbose(int* arr, int n, int i) {
    int largest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;
    if (left  < n && arr[left]  > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        cout << "Before change: "; printArray(arr, n);
        int tmp = arr[i]; arr[i] = arr[largest]; arr[largest] = tmp;
        heapify_verbose(arr, n, largest);
    }
}

void heapSort_verbose(int* arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify_verbose(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        cout << "Before change: "; printArray(arr, n);
        int tmp = arr[0]; arr[0] = arr[i]; arr[i] = tmp;
        heapify_verbose(arr, i, 0);
    }
}

// QUICKSORT
int partition_verbose(int* arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            cout << "Before change: "; printArray(arr, high + 1);
            int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        }
    }
    cout << "Before change: "; printArray(arr, high + 1);
    int tmp = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = tmp;
    return i + 1;
}

void quickSort_verbose(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition_verbose(arr, low, high);
        quickSort_verbose(arr, low, pi - 1);
        quickSort_verbose(arr, pi + 1, high);
    }
}

// ─────────────────────────────────────────────
//  TASK 3  —  Silent + opCount versions
// ─────────────────────────────────────────────

// SELECTION SORT
void selectionSort_measure(int* arr, int n, long long& opCount) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            opCount++;                   // comparison
            if (arr[j] < arr[minIdx]) minIdx = j;
        }
        if (minIdx != i) {
            int tmp = arr[i]; arr[i] = arr[minIdx]; arr[minIdx] = tmp;
            opCount += 3;                // swap = 3 assignments
        }
    }
}

// INSERTION SORT
void insertionSort_measure(int* arr, int n, long long& opCount) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            opCount++;                   // comparison
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                opCount++;               // assignment
                j--;
            } else { break; }
        }
        arr[j + 1] = key;
    }
}

// HEAPSORT
void heapify_measure(int* arr, int n, int i, long long& opCount) {
    int largest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;
    if (left  < n) { opCount++; if (arr[left]  > arr[largest]) largest = left;  }
    if (right < n) { opCount++; if (arr[right] > arr[largest]) largest = right; }
    if (largest != i) {
        int tmp = arr[i]; arr[i] = arr[largest]; arr[largest] = tmp;
        opCount += 3;
        heapify_measure(arr, n, largest, opCount);
    }
}

void heapSort_measure(int* arr, int n, long long& opCount) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify_measure(arr, n, i, opCount);
    for (int i = n - 1; i > 0; i--) {
        int tmp = arr[0]; arr[0] = arr[i]; arr[i] = tmp;
        opCount += 3;
        heapify_measure(arr, i, 0, opCount);
    }
}

// QUICKSORT
int partition_measure(int* arr, int low, int high, long long& opCount) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        opCount++;                       // comparison
        if (arr[j] < pivot) {
            i++;
            int tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
            opCount += 3;
        }
    }
    int tmp = arr[i+1]; arr[i+1] = arr[high]; arr[high] = tmp;
    opCount += 3;
    return i + 1;
}

void quickSort_measure(int* arr, int low, int high, long long& opCount) {
    if (low < high) {
        int pi = partition_measure(arr, low, high, opCount);
        quickSort_measure(arr, low, pi - 1, opCount);
        quickSort_measure(arr, pi + 1, high, opCount);
    }
}

// Wrapper so all functions have the same signature
void quickSort_wrapper(int* arr, int n, long long& opCount) {
    quickSort_measure(arr, 0, n - 1, opCount);
}

// ─────────────────────────────────────────────
//  TASK 3  —  LAB-2 style analysis table
// ─────────────────────────────────────────────

void runAnalysis(const char* name,
                 void (*sortFn)(int*, int, long long&),
                 int sizes[], int numSizes, int batchSize)
{
    cout << "\n===============================================================\n";
    cout << "Algorithm : " << name << "\n";
    cout << "===============================================================\n";
    cout << left
         << setw(10) << "n"
         << setw(10) << "Batch"
         << setw(18) << "Avg opCount"
         << setw(16) << "T/n"
         << setw(16) << "T/n^2"
         << setw(16) << "T/n*log2(n)"
         << endl;

    for (int s = 0; s < numSizes; s++) {
        int n = sizes[s];
        long long totalCost = 0;

        for (int run = 0; run < batchSize; run++) {
            long long opCount = 0;
            int* arr = createRandomArray(n);
            sortFn(arr, n, opCount);
            totalCost += opCount;
            delete[] arr;
        }

        double avg     = (double)totalCost / batchSize;
        double ratioN  = avg / n;
        double ratioN2 = avg / ((double)n * n);
        double ratioNL = avg / (n * log2((double)n));

        cout << fixed << setprecision(4);
        cout << left
             << setw(10) << n
             << setw(10) << batchSize
             << setw(18) << (long long)avg
             << setw(16) << ratioN
             << setw(16) << ratioN2
             << setw(16) << ratioNL
             << endl;
    }
}

// ─────────────────────────────────────────────
//  MAIN
// ─────────────────────────────────────────────

int main() {
    srand((unsigned)time(0));

    // ── TASK 1 & 2 ───────────────────────────
    cout << "===============================================================\n";
    cout << " CMPE 242 - Term Project  |  Task 1 & 2: Step-by-Step\n";
    cout << "===============================================================\n";

    int demo[]   = {64, 25, 12, 22, 11, 90, 3, 47};
    int demoSize = 8;
    int* arr;

    cout << "\n--- SELECTION SORT ---\n";
    arr = copyArray(demo, demoSize);
    cout << "Original: "; printArray(arr, demoSize);
    selectionSort_verbose(arr, demoSize);
    cout << "Sorted:   "; printArray(arr, demoSize);
    delete[] arr;

    cout << "\n--- INSERTION SORT ---\n";
    arr = copyArray(demo, demoSize);
    cout << "Original: "; printArray(arr, demoSize);
    insertionSort_verbose(arr, demoSize);
    cout << "Sorted:   "; printArray(arr, demoSize);
    delete[] arr;

    cout << "\n--- HEAP SORT ---\n";
    arr = copyArray(demo, demoSize);
    cout << "Original: "; printArray(arr, demoSize);
    heapSort_verbose(arr, demoSize);
    cout << "Sorted:   "; printArray(arr, demoSize);
    delete[] arr;

    cout << "\n--- QUICK SORT ---\n";
    arr = copyArray(demo, demoSize);
    cout << "Original: "; printArray(arr, demoSize);
    quickSort_verbose(arr, 0, demoSize - 1);
    cout << "Sorted:   "; printArray(arr, demoSize);
    delete[] arr;

    // ── TASK 3 ───────────────────────────────
    cout << "\n\n===============================================================\n";
    cout << " CMPE 242 - Term Project  |  Task 3: Complexity Analysis\n";
    cout << "===============================================================\n";

    int sizes[]  = {100, 1000, 10000};
    int numSizes = 3;
    int batchSize = 20;

    runAnalysis("Selection Sort", selectionSort_measure, sizes, numSizes, batchSize);
    runAnalysis("Insertion Sort", insertionSort_measure, sizes, numSizes, batchSize);
    runAnalysis("Heap Sort",      heapSort_measure,      sizes, numSizes, batchSize);
    runAnalysis("Quick Sort",     quickSort_wrapper,     sizes, numSizes, batchSize);

    cout << "\n===============================================================\n";
    cout << "ANALYSIS GUIDE:\n";
    cout << "If T/n       stays ~constant  ->  complexity is O(n)\n";
    cout << "If T/n^2     stays ~constant  ->  complexity is O(n^2)\n";
    cout << "If T/n*log2n stays ~constant  ->  complexity is O(n log n)\n";
    cout << "===============================================================\n";

    return 0;
}