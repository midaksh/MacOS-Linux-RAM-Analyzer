// TOPIC - List out memory block of RAM in Linux OS

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void readDisplaying_memory_blocks () {
    ifstream meminfo("/proc/meminfo");

    if (!meminfo) {
        cerr << "Error: Unable to open /proc/meminfo" << endl;
        return;
    }

    cout << "=== Memory Information (RAM Status) ===" << endl;
    string line;

    while (getline(meminfo, line)) {
        cout << line << endl;
    }
    meminfo.close();
}

void listingDisplay_memory_blocks () {
    ifstream maps("/proc/self/maps");
    if (!maps) {
        cerr << "Error: Unable to open /proc/self/maps" << endl;
        return;
    }

    cout << "\n=== Memory Blocks of This Process ===" << endl;
    string line;
    while (getline(maps, line)) {
        cout << line << endl;
    }
    maps.close();
}

int main() {
    cout << "Fetching Current ProcessMemory Details...\n" << endl;
    
    readDisplaying_memory_blocks();
    listingDisplay_memory_blocks();
    
    return 0;
}
