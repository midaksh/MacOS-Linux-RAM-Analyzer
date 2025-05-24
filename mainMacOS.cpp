#include <iostream>
#include <mach/mach.h>
#include <sys/sysctl.h>

using namespace std;

void getMemoryInfo() {
    uint64_t total_memory;
    size_t size = sizeof(total_memory);
    sysctlbyname("hw.memsize", &total_memory, &size, NULL, 0);
    cout << "\n====> Total Physical RAM: " << total_memory / (1024 * 1024) << " MB <====\n" << endl;

    mach_msg_type_number_t count = HOST_VM_INFO64_COUNT;
    vm_statistics64_data_t vm_stats;
    
    vm_size_t page_size;
    host_page_size(mach_host_self(), &page_size);

    if (host_statistics64(mach_host_self(), HOST_VM_INFO64, (host_info64_t)&vm_stats, &count) 
        != KERN_SUCCESS) {
        cerr << "Failed to fetch VM statistics!" << endl;
        return;
    }

    uint64_t free_memory = vm_stats.free_count * page_size;
    uint64_t active_memory = vm_stats.active_count * page_size;
    uint64_t inactive_memory = vm_stats.inactive_count * page_size;
    uint64_t wired_memory = vm_stats.wire_count * page_size;
    uint64_t compressed_memory = vm_stats.compressor_page_count * page_size;
    uint64_t purgeable_memory = vm_stats.purgeable_count * page_size;
    uint64_t speculative_memory = vm_stats.speculative_count * page_size;

    uint64_t total_calculated_memory = free_memory + active_memory + inactive_memory + wired_memory + 
            compressed_memory + purgeable_memory + speculative_memory;
    

    if (total_calculated_memory < total_memory) {
        free_memory += (total_memory - total_calculated_memory);
    }
    
    cout << "Free         Memory :     " << free_memory / (1024 * 1024) << " MB" << endl;
    cout << "Active       Memory :     " << active_memory / (1024 * 1024) << " MB" << endl;
    cout << "Inactive     Memory :     " << inactive_memory / (1024 * 1024) << " MB" << endl;
    cout << "Wired        Memory :     " << wired_memory / (1024 * 1024) << " MB" << endl;
    cout << "Compressed   Memory :     " << compressed_memory / (1024 * 1024) << " MB" << endl;
    cout << "Purgeable    Memory :     " << purgeable_memory / (1024 * 1024) << " MB" << endl;
    cout << "Speculative  Memory :     " << speculative_memory / (1024 * 1024) << " MB" << endl;
}

int main() {
    cout << "=== Memory Block Details for macOS ===" << endl;
    getMemoryInfo();

    cout << "\n=== MacOS for ARM64 has a var-fixed RAM allocation ====" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "Miscellaneous (I/O buffers, caches, etc.)" << endl;
    cout << "our case (3MB/4MB)\n" << endl;
    
    return 0;
}
