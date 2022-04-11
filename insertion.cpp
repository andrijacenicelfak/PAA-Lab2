#include <stdlib.h>
#include <time.h>

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

void insertionSort(int nums[], int n) {
    int i, k, j;
    for (i = 1; i < n; i++) {
        k = nums[i];
        j = i - 1;
        while (j >= 0 && nums[j] > k) {
            nums[j + 1] = nums[j];
            j = j - 1;
        }
        nums[j + 1] = k;
    }
}
void printArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}
int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Nedovoljno parametara!!! Pravilan poziv funkcije : .\\inserion.exe [ime fajla sa kog se cita] [broj brojeva] [ima fajla za upis]" << '\n';
        return -1;
    }
    srand(time(NULL));
    int N = 0;
    string n(argv[2]);
    stringstream(n) >> N;
    int* nums = (int*)malloc(sizeof(int) * N);

    ifstream input(argv[1], ios::binary);
    auto millsStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    input.read((char*)nums, sizeof(int) * N);
    input.close();
    auto begSort = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    insertionSort(nums, N);

    auto end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    ofstream output(argv[3], std::ios_base::app);
    output << "Insert sort : " << N << " elemenata\n"
           << "vreme : " << end - begSort << "ms\n"
           << "---------------------------------\n";
    output.close();
    delete[] nums;
    return 0;
}