#include <iostream>
using namespace std;

// ─── MERGE SORT ───────────────────────────────────────────

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) { arr[k] = L[i]; i++; k++; }
        else               { arr[k] = R[j]; j++; k++; }
    }
    while (i < n1) { arr[k] = L[i]; i++; k++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; }
}

void mergeSort(int arr[], int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

// ─── YOUR IDEA 1: DUPLICATE DETECTION ────────────────────

int removeDuplicates(int arr[], int n) {
    if (n == 0) return 0;

    int temp[n];
    int newSize = 0;

    for (int i = 0; i < n; i++) {
        bool found = false;

        for (int j = 0; j < newSize; j++) {
            if (temp[j] == arr[i]) {
                found = true;
                break;
            }
        }

        if (!found) {
            temp[newSize] = arr[i];
            newSize++;
        }
    }

    // Copy back to original array
    for (int i = 0; i < newSize; i++)
        arr[i] = temp[i];

    return newSize; // return new size after removing duplicates
}

// ─── YOUR IDEA 2: BUFFERING ───────────────────────────────

void bufferAndPlay(int arr[], int n) {
    int BUFFER_SIZE = 3; // wait for 3 chunks before starting playback

    cout << "\n[Buffering...] Waiting for " << BUFFER_SIZE << " chunks to load...\n";

    if (n < BUFFER_SIZE) {
        cout << "[Warning] Not enough chunks to fill buffer! Only " << n << " chunk(s) available.\n";
        cout << "[Playing anyway with available chunks...]\n\n";
    } else {
        cout << "[Buffer Ready!] Starting playback...\n\n";
    }

    for (int i = 0; i < n; i++) {
        cout << "  >> Playing Chunk #" << arr[i] << endl;
    }

    cout << "\n[Playback Complete!]\n";
}

// ─── PRINT ARRAY ──────────────────────────────────────────

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// ─── MAIN ─────────────────────────────────────────────────

int main() {
    int n;
    cout << "Enter number of video chunks (including duplicates): ";
    cin >> n;

    int arr[n];
    cout << "Enter sequence numbers: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    // Step 1: Show received chunks
    cout << "\nChunks received:       ";
    printArray(arr, n);

    // Step 2: Remove duplicates
    int newSize = removeDuplicates(arr, n);
    cout << "After removing duplicates (" << n - newSize << " removed): ";
    printArray(arr, newSize);

    // Step 3: Sort using Merge Sort
    mergeSort(arr, 0, newSize - 1);
    cout << "After sorting:         ";
    printArray(arr, newSize);

    // Step 4: Buffer and Play
    bufferAndPlay(arr, newSize);

    return 0;
}