#include <iostream>
#include <vector>
#include <thread>
#include <functional>

using namespace std;

class MergeSort {
public:
    void Sort(vector<int>& array) {
        if (array.size() > 1) {
            MergeSortRecursive(array, 0, array.size() - 1);
        }
    }

private:
    void MergeSortRecursive(vector<int>& array, int left, int right) {
        if (left < right) {
            int middle = left + (right - left) / 2;

            MergeSortRecursive(array, left, middle);
            MergeSortRecursive(array, middle + 1, right);

            Merge(array, left, middle, right);
        }
    }

    void Merge(vector<int>& array, int left, int middle, int right) {
        int n1 = middle - left + 1;
        int n2 = right - middle;

        vector<int> leftArray(n1);
        vector<int> rightArray(n2);

        for (int i = 0; i < n1; i++)
            leftArray[i] = array[left + i];
        for (int i = 0; i < n2; i++)
            rightArray[i] = array[middle + 1 + i];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (leftArray[i] <= rightArray[j]) {
                array[k] = leftArray[i]; 
                i++;
            }
            else {
                array[k] = rightArray[j]; 
                j++;
            }
            k++;
        }

        while (i < n1) {
            array[k] = leftArray[i]; 
            i++;
            k++;
        }

        while (j < n2) {
            array[k] = rightArray[j];
            j++;
            k++;
        }
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    vector<int> array(10);

    cout << "Введите 10 целых чисел: ";
    for (int i = 0; i < 10; ++i) {
        cin >> array[i];
    }

    MergeSort mergeSort;

    auto sortFunction = [&mergeSort](vector<int>& arr) {
        mergeSort.Sort(arr);
        };

    thread mergeSortThread(sortFunction, ref(array));

    mergeSortThread.join();

    cout << "Отсортированный массив: ";
    for (const auto& num : array) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}