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

int max(int* nums, int N) {

    int max = nums[0];
    for (int i = 1; i < N; i++)
        if (nums[i] > max) 
            max = nums[i];

    return max;
}

void countSort(int* nums, int N, int exp) {

    int* output = (int*) malloc(sizeof(int) * N);
    int c[10] = { 0 };
    int i;

    for (i = 0; i < N; i++) {
        c[(nums[i] / exp) % 10]++;
    }

    for (i = 1; i < 10; i++) {
        c[i] = c[i - 1] + c[i];
    }

    for (i = N - 1; i >= 0; i--) {
        output[c[(nums[i] / exp) % 10] - 1] = nums[i];
        c[(nums[i] / exp) % 10]--;
    }

    for (i = 0; i < N; i++)
        nums[i] = output[i];
    delete[] output;
}

void radixSort(int* nums, int n) {

    int m = max(nums, n);

    for (int exp = 1; m / exp > 0; exp *= 10) 
        countSort(nums, n, exp);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Nedovoljno parametara!!! Pravilan poziv funkcije : .\\"<< argv[0] << "[ime fajla sa kog se cita] [broj brojeva] [ima fajla za upis]" << '\n';
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

    radixSort(nums, N);

    auto end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    ofstream output(argv[3], std::ios_base::app);
    output << "Radix sort : " << N << " elemenata\n"
           << "vreme : " << end - begSort << "ms\n"
           << "---------------------------------\n";
    output.close();
    delete[] nums;
    return 0;
}