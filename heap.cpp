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

void heapify(int *nums, int N, int i){
    int najveci = i;
    int l = 2*i+1;
    int d = 2*i+2;
    if(l < N && nums[l] > nums[najveci])
        najveci = l;
        
    if(d < N && nums[d] > nums[najveci])
        najveci = d;
    
    if(najveci != i){
        int pom = nums[i];
        nums[i] = nums[najveci];
        nums[najveci] = pom;

        heapify(nums, N, najveci);
    }
}

void buildHeap(int *nums, int N){
    for(int i = N/2 - 1; i >= 0; i--)
        heapify(nums, N, i);
}

void heapSort(int *nums, int N){

    buildHeap(nums, N);

    for(int i = N-1; i> 0; i--){
        int pom = nums[0];
        nums[0] = nums[i];
        nums[i] = pom;

        heapify(nums, i, 0);
    }
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

    heapSort(nums, N);

    auto end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    ofstream output(argv[3], std::ios_base::app);
    output << "Heap sort : " << N << " elemenata\n"
           << "vreme : " << end - begSort << "ms\n"
           << "---------------------------------\n";
    output.close();
    delete[] nums;
    return 0;
}