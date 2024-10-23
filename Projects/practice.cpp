#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <climits>
#include <cstring>
#include <vector>

using namespace std;

void sortI(const vector<int>& data1, const vector<int>& data2);
void MergeSort(vector<int>& list, int i, int k);
void Merge(vector<int>& list, int i, int j, int k);
void QSort(vector<string>& list, int i, int k);
void sortS(const vector<string>& data1, const vector<string>& data2);
int Partition(vector<string>& list, int i, int k);

int main(int argc, char *argv[]) {
    if (argc != 4) { // command line argument fail
        cout << "Usage myprog.exe i/s file1.txt file2.txt" << endl;
        return 1;
    }

    string filename1 = argv[2];
    string filename2 = argv[3];

    ifstream inF1, inF2;

    inF1.open(filename1);
    inF2.open(filename2);

    if (!inF1.is_open()) {
        cout << "Could not open file: " << filename1 << endl;
        return 2;
    }

    if (!inF2.is_open()) {
        cout << "Could not open file: " << filename2 << endl;
        return 2;
    }

    char command = argv[1][0];

    if (command == 'i') { // integer or string
        vector<int> data1, data2;
        int temp;

        while (inF1 >> temp) {
            data1.push_back(temp);
        }

        while (inF2 >> temp) {
            data2.push_back(temp);
        }

        sortI(data1, data2);
    }

    if (command == 's') {
        vector<string> data1, data2;
        string temp;

        while (inF1 >> temp) {
            data1.push_back(temp);
        }

        while (inF2 >> temp) {
            data2.push_back(temp);
        }

        sortS(data1, data2);

    }

    inF1.close();
    inF2.close();

    return 0;
}

void sortI(const vector<int>& data1, const vector<int>& data2) {
    vector<int> list; 
    
    for (int i = 0; i < data1.size(); i++) { // finds common item
        for (int j = 0; j < data2.size(); j++) {
            if (data1.at(i) == data2.at(j)) {
                list.push_back(data1.at(i));
            }
        }
    }

    for (int k = 0; k < list.size(); k++) { // removes duplicates
        for (int l = k+1; l < list.size(); l++) {
            if (list.at(k) == list.at(l)) {
                list.erase(list.begin() + l);
                l--;
            }
        }
    }

    

    // call merge sort

    MergeSort(list, 0, list.size() - 1);

    for (int n = 0; n < list.size(); n++) {
        cout << list.at(n) << endl;
    }

}

void MergeSort(vector<int>& list, int i, int k) {
   int j;
   
    if (i < k) {
        j = (i + k) / 2;  // Find the midpoint in the partition
      
        // Recursively sort left and right partitions
        MergeSort(list, i, j);
        MergeSort(list, j + 1, k);
      
        // Merge left and right partition in sorted order
        Merge(list, i, j, k);
   }
}

void Merge(vector<int>& list, int i, int j, int k) {
    int mergedSize;                            // Size of merged partition
    int mergePos;                              // Position to insert merged number
    int leftPos;                               // Position of elements in left partition
    int rightPos;                              // Position of elements in right partition
    int* mergedNumbers = nullptr;

    mergePos = 0;
    mergedSize = k - i + 1;
    leftPos = i;                               // Initialize left partition position
    rightPos = j + 1;                          // Initialize right partition position
    mergedNumbers = new int[mergedSize];       // Dynamically allocates temporary array
                                               // for merged numbers
   
    // Add smallest element from left or right partition to merged numbers
    while (leftPos <= j && rightPos <= k) {
        if (list[leftPos] < list[rightPos]) {
            mergedNumbers[mergePos] = list[leftPos];
            ++leftPos;
        }
        else {
            mergedNumbers[mergePos] = list[rightPos];
            ++rightPos;
         
        }
        ++mergePos;
    }
   
    // If left partition is not empty, add remaining elements to merged numbers
    while (leftPos <= j) {
        mergedNumbers[mergePos] = list[leftPos];
        ++leftPos;
        ++mergePos;
    }
   
    // If right partition is not empty, add remaining elements to merged numbers
    while (rightPos <= k) {
        mergedNumbers[mergePos] = list[rightPos];
        ++rightPos;
        ++mergePos;
    }
   
    // Copy merge number back to numbers
    for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
        list[i + mergePos] = mergedNumbers[mergePos];
    }
    delete[] mergedNumbers;
}

void sortS(const vector<string> &data1, const vector<string> &data2) {
    vector<string> list;

    for (int i = 0; i < data1.size(); i++) { // finds common item
        for (int j = 0; j < data2.size(); j++) {
            if (data1.at(i) == data2.at(j)) {
                list.push_back(data1.at(i));
            }
        }
    }

    for (int k = 0; k < list.size(); k++) { // removes duplicates
        for (int l = k+1; l < list.size(); l++) {
            if (list.at(k) == list.at(l)) {
                list.erase(list.begin() + l);
                l--;
            }
        }
    }

    // call quick sort

    QSort(list, 0, list.size() - 1);

    for (int n = 0; n < list.size(); n++) {
        cout << list.at(n) << endl;
    }
}

void QSort(vector<string>& list, int i, int k) {
    int j;
   
    /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
    if (i >= k) {
        return;
    }
   
    /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
    j = Partition(list, i, k);
   
    /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
    QSort(list, i, j);
    QSort(list, j + 1, k);
}

int Partition(vector<string>& list, int i, int k) {
    int l;
    int h;
    int midpoint;
    string pivot;
    string temp;
    bool done;
   
    /* Pick middle element as pivot */
    midpoint = i + (k - i) / 2;
    pivot = list[midpoint];
   
    done = false;
    l = i;
    h = k;
   
    while (!done) {
      
        /* Increment l while numbers[l] < pivot */
        while (list[l] < pivot) {
            ++l;
        }
      
        /* Decrement h while pivot < numbers[h] */
        while (pivot < list[h]) {
            --h;
        }
      
        /* If there are zero or one elements remaining,
        all numbers are partitioned. Return h */
        if (l >= h) {
            done = true;
        }
        else {
            /* Swap numbers[l] and numbers[h],
            update l and h */
            temp = list[l];
            list[l] = list[h];
            list[h] = temp;
         
            ++l;
            --h;
        }
    }
   
    return h;
}