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
    ofstream file(argv[2]);
    int amount = 0;

    string am(argv[1]);
    stringstream(am) >> amount;

    srand(time(NULL));
    auto millsStart = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    int broj;
    for (int i = 0; i < amount; i++) {
        broj = rand();
        file << broj << " ";
    }

    auto mills = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - millsStart;
    file.close();
    cout << "Generated in " << mills << "ms\n";
}