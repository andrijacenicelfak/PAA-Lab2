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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "NEDOVOLJNO PARAMETARA! Pravila poziv : .\\numgen.exe [broj elemenata] [ime fajla]" << '\n';
        return -1;
    }
    ofstream file(argv[2], ios::out | ios::binary);
    int N = 0;

    string am(argv[1]);
    stringstream(am) >> N;

    srand(time(NULL));
    int* nums = (int*)malloc(sizeof(int) * N);
    auto millsStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    for (long i = 0; i < N; i++) {
        nums[i] = rand();
    }
    file.write((char*)nums, sizeof(int) * N);
    auto mills = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millsStart;
    file.close();
    cout << "Generated in " << mills << "ms\n";

    delete[] nums;
    return 0;
}