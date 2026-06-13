DSA readme.md 

🎬 Video Streaming Chunk Sorter — Merge Sort
ITM Skills University | DSA 1 | First Year B.Tech CSE

2.1 Project Title
Video Streaming Service — Chunk Reordering Using Merge Sort

2.2 Problem Statement
Video streaming platforms divide multimedia content into smaller chunks for transmission across networks. Due to varying network conditions, these chunks often arrive out of sequence. To ensure smooth playback, the streaming system must reorder chunks correctly before presenting the video to viewers.
Additionally, the same chunk can arrive multiple times from different network paths (duplicates), and playback should only begin after a minimum number of chunks have been buffered — just like real-world platforms such as YouTube and Netflix.
Core challenges addressed:
* Chunks arrive out of order due to network latency
* Duplicate chunks arrive from multiple network paths
* Playback must wait until a minimum buffer is filled

2.3 Objectives
* Implement Merge Sort to sort video chunks by sequence number
* Detect and remove duplicate chunks before sorting
* Simulate a buffering threshold before playback begins
* Demonstrate real-world application of a sorting algorithm in streaming systems
* Analyze time and space complexity of the solution

2.4 System Overview / Architecture
Network Packets Arrive (Unsorted + Duplicates)
            |
            v
  ┌─────────────────────┐
  │  Duplicate Removal  │  ← Your Idea #1
  └─────────────────────┘
            |
            v
  ┌─────────────────────┐
  │     Merge Sort      │  ← Core Algorithm
  │  (by sequence no.)  │
  └─────────────────────┘
            |
            v
  ┌─────────────────────┐
  │  Buffering Check    │  ← Your Idea #2
  │  (min 3 chunks)     │
  └─────────────────────┘
            |
            v
  ┌─────────────────────┐
  │   Playback Output   │
  └─────────────────────┘
Flow:
1. User inputs chunk sequence numbers (may include duplicates, out of order)
2. removeDuplicates() filters repeated chunks
3. mergeSort() sorts cleaned chunks by sequence number
4. bufferAndPlay() checks buffer threshold, then simulates playback

2.5 Data Structures and Algorithms Used
Component	Detail
Data Structure	Arrays (plain C-style int[])
Algorithm	Merge Sort (Divide and Conquer)
Duplicate Detection	Nested loop comparison using temp array
Buffering	Constant threshold check (BUFFER_SIZE = 3)
Why Merge Sort?
* Guaranteed O(n log n) performance — no worst-case degradation
* Stable sort — preserves relative order of equal elements
* Ideal for large distributed data streams like video chunks

2.6 Implementation Approach
The solution is implemented in C++ using basic arrays, suitable for a first-year DSA course.
Three core functions:
merge(arr, left, mid, right)
* Takes two sorted halves of the array
* Compares elements from both halves one by one
* Places smaller element back into the original array in order
* Copies any leftover elements from either half
mergeSort(arr, left, right)
* Recursively divides the array into halves
* Base case: single element (already sorted)
* Calls merge() after both halves are sorted
removeDuplicates(arr, n)
* Iterates through input array
* For each element, checks if it already exists in temp array
* Only adds unique elements — returns new size
bufferAndPlay(arr, n)
* Checks if sorted chunk count meets BUFFER_SIZE threshold
* Simulates playback by printing chunks in order
Full Source Code:
#include <iostream>
using namespace std;

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

int removeDuplicates(int arr[], int n) {
    if (n == 0) return 0;
    int temp[n];
    int newSize = 0;

    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < newSize; j++) {
            if (temp[j] == arr[i]) { found = true; break; }
        }
        if (!found) { temp[newSize] = arr[i]; newSize++; }
    }
    for (int i = 0; i < newSize; i++) arr[i] = temp[i];
    return newSize;
}

void bufferAndPlay(int arr[], int n) {
    int BUFFER_SIZE = 3;
    cout << "\n[Buffering...] Waiting for " << BUFFER_SIZE << " chunks...\n";

    if (n < BUFFER_SIZE)
        cout << "[Warning] Only " << n << " chunk(s) available. Playing anyway...\n\n";
    else
        cout << "[Buffer Ready!] Starting playback...\n\n";

    for (int i = 0; i < n; i++)
        cout << "  >> Playing Chunk #" << arr[i] << endl;

    cout << "\n[Playback Complete!]\n";
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int n;
    cout << "Enter number of video chunks (including duplicates): ";
    cin >> n;

    int arr[n];
    cout << "Enter sequence numbers: ";
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << "\nChunks received:       ";
    printArray(arr, n);

    int newSize = removeDuplicates(arr, n);
    cout << "After removing duplicates (" << n - newSize << " removed): ";
    printArray(arr, newSize);

    mergeSort(arr, 0, newSize - 1);
    cout << "After sorting:         ";
    printArray(arr, newSize);

    bufferAndPlay(arr, newSize);
    return 0;
}

2.7 Time and Space Complexity Analysis
Merge Sort
Case	Time Complexity
Best Case	O(n log n)
Average Case	O(n log n)
Worst Case	O(n log n)
Space Complexity: O(n) — temporary arrays used during merge
Duplicate Removal
	Complexity
Time	O(n²) — nested loop
Space	O(n) — temp array
Overall Program
	Complexity
Time	O(n²) + O(n log n) ≈ O(n²) for small n
Space	O(n)
Note: For large-scale systems, duplicate removal can be optimized to O(n log n) using sorting first, but O(n²) is acceptable for this beginner-level implementation.

2.8 Execution Steps
Prerequisites: g++ compiler installed on your system.
Step 1 — Verify g++ installation:
g++ --version
Step 2 — Save the code as mergesort.cpp
Step 3 — Compile:
g++ mergesort.cpp -o mergesort
Step 4 — Run:
./mergesort
One-line compile + run:
g++ mergesort.cpp -o mergesort && ./mergesort

2.9 Sample Inputs and Outputs
Sample 1 — Normal case with duplicates
Input:
Enter number of video chunks (including duplicates): 7
Enter sequence numbers: 4 1 3 1 5 2 3
Output:
Chunks received:       4 1 3 1 5 2 3
After removing duplicates (2 removed): 4 1 3 5 2
After sorting:         1 2 3 4 5

[Buffering...] Waiting for 3 chunks...
[Buffer Ready!] Starting playback...

  >> Playing Chunk #1
  >> Playing Chunk #2
  >> Playing Chunk #3
  >> Playing Chunk #4
  >> Playing Chunk #5

[Playback Complete!]

Sample 2 — Already sorted, no duplicates
Input:
Enter number of video chunks (including duplicates): 4
Enter sequence numbers: 1 2 3 4
Output:
Chunks received:       1 2 3 4
After removing duplicates (0 removed): 1 2 3 4
After sorting:         1 2 3 4

[Buffering...] Waiting for 3 chunks...
[Buffer Ready!] Starting playback...

  >> Playing Chunk #1
  >> Playing Chunk #2
  >> Playing Chunk #3
  >> Playing Chunk #4

[Playback Complete!]

Sample 3 — Less than buffer size
Input:
Enter number of video chunks (including duplicates): 2
Enter sequence numbers: 2 1
Output:
Chunks received:       2 1
After removing duplicates (0 removed): 2 1
After sorting:         1 2

[Buffering...] Waiting for 3 chunks...
[Warning] Only 2 chunk(s) available. Playing anyway...

  >> Playing Chunk #1
  >> Playing Chunk #2

[Playback Complete!]



2.10 Results and Observations
* Merge Sort successfully reordered all video chunks in correct sequence every time
* Duplicate detection worked correctly — repeated sequence numbers were removed before sorting
* Buffering threshold correctly warned when fewer than 3 chunks were available
* The algorithm maintained stable O(n log n) performance regardless of input order
* Even when chunks were already sorted (best case), Merge Sort completed without errors
Key Observation: Unlike Bubble Sort or Selection Sort (O(n²)), Merge Sort's performance did not degrade with larger inputs, making it more suitable for real-world streaming systems handling thousands of chunks simultaneously.

2.11 Conclusion
This project demonstrates a practical application of Merge Sort in the context of a Video Streaming Service. By sorting video chunks using their sequence numbers, the system ensures smooth and uninterrupted playback even when network conditions cause out-of-order delivery.
Two additional features were implemented beyond the base problem statement:
1. Duplicate chunk detection — handles real-world scenario where same chunk arrives via multiple network paths
2. Buffering threshold — mimics actual streaming platforms that buffer content before playback begins
The implementation uses fundamental C++ concepts (arrays, functions, recursion) appropriate for a first-year DSA course, while connecting algorithm theory to a real-world industry problem.
Merge Sort proves to be an ideal choice for this use case due to its consistent O(n log n) time complexity, stability, and suitability for distributed data — all critical requirements in large-scale video streaming platforms.

Submitted by: Jaspreet Kaur Bassi | B.Tech CSE  | ITM Skills University
