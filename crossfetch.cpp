#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/utsname.h>
#include <fstream>

#if defined(__linux__)
    #define CF_LINUX 1
#elif defined(__APPLE__) && defined(__MACH__)
    #define CF_MAC 1
    #include <sys/sysctl.h>
    #include <mach/mach.h>
#elif defined(__FreeBSD__) || defined(__OpenBSD__) || defined(__NetBSD__) || defined(__DragonFly__)
    #define CF_BSD 1
    #include <sys/sysctl.h>
#elif defined(__GNU__)
    #define CF_HURD 1
    #include <mach/mach.h>
#endif

// -----------------------------
// Helpers
// -----------------------------
std::string trim(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\n\r");
    size_t b = s.find_last_not_of(" \t\n\r");
    if (a == std::string::npos) return "";
    return s.substr(a, b - a + 1);
}

// -----------------------------
// Shared sysctl_str for BSD + macOS
// -----------------------------
#if CF_BSD || CF_MAC
std::string sysctl_str(const char* name) {
    char buf[256];
    size_t len = sizeof(buf);
    if (sysctlbyname(name, buf, &len, NULL, 0) == 0)
        return std::string(buf);
    return "Unknown";
}
#endif

// -----------------------------
// Linux
// -----------------------------
#if CF_LINUX
std::string read_line(const char* path, const char* key) {
    FILE* f = fopen(path, "r");
    if (!f) return "";
    char buf[512];
    while (fgets(buf, sizeof(buf), f)) {
        if (strncmp(buf, key, strlen(key)) == 0) {
            char* colon = strchr(buf, ':');
            fclose(f);
            return colon ? trim(colon + 1) : "";
        }
    }
    fclose(f);
    return "";
}

std::string get_cpu() {
    return read_line("/proc/cpuinfo", "model name");
}

std::string get_ram() {
    long total = 0, free = 0;
    FILE* f = fopen("/proc/meminfo", "r");
    if (!f) return "Unknown RAM";

    char key[64], unit[16];
    long value;
    while (fscanf(f, "%63s %ld %15s", key, &value, unit) == 3) {
        if (!strcmp(key, "MemTotal:")) total = value;
        if (!strcmp(key, "MemAvailable:")) free = value;
    }
    fclose(f);

    long used = total - free;
    return std::to_string(used/1024) + " MB / " + std::to_string(total/1024) + " MB";
}

std::string get_uptime() {
    FILE* f = fopen("/proc/uptime", "r");
    if (!f) return "Unknown uptime";
    double up;
    fscanf(f, "%lf", &up);
    fclose(f);
    return std::to_string((int)up) + " sec";
}
#endif

// -----------------------------
// BSD (FreeBSD, OpenBSD, NetBSD, DragonFly)
// -----------------------------
#if CF_BSD
std::string get_cpu() {
    return sysctl_str("hw.model");
}

std::string get_ram() {
    uint64_t mem;
    size_t len = sizeof(mem);
    if (sysctlbyname("hw.physmem", &mem, &len, NULL, 0) == 0)
        return std::to_string(mem/1024/1024) + " MB";
    return "Unknown RAM";
}

std::string get_uptime() {
    struct timeval boottime;
    size_t len = sizeof(boottime);
    int mib[2] = { CTL_KERN, KERN_BOOTTIME };
    if (sysctl(mib, 2, &boottime, &len, NULL, 0) == 0) {
        time_t now = time(NULL);
        return std::to_string((int)(now - boottime.tv_sec)) + " sec";
    }
    return "Unknown uptime";
}
#endif

// -----------------------------
// macOS (Darwin)
// -----------------------------
#if CF_MAC
std::string get_cpu() {
    return sysctl_str("machdep.cpu.brand_string");
}

std::string get_ram() {
    int64_t mem;
    size_t len = sizeof(mem);
    if (sysctlbyname("hw.memsize", &mem, &len, NULL, 0) == 0)
        return std::to_string(mem/1024/1024) + " MB";
    return "Unknown RAM";
}

std::string get_uptime() {
    return "Uptime unavailable on macOS (simple mode)";
}
#endif

// -----------------------------
// GNU/Hurd
// -----------------------------
#if CF_HURD
std::string get_cpu() {
    return "Hurd CPU info (Mach) not implemented";
}

std::string get_ram() {
    vm_statistics_data_t vm;
    mach_msg_type_number_t count = HOST_VM_INFO_COUNT;
    if (host_statistics(mach_host_self(), HOST_VM_INFO, (host_info_t)&vm, &count) == KERN_SUCCESS) {
        long total = vm.wire_count + vm.active_count + vm.inactive_count + vm.free_count;
        return std::to_string(total * 4) + " KB";
    }
    return "Unknown RAM";
}

std::string get_uptime() {
    return "Uptime unavailable on Hurd (simple mode)";
}
#endif

std::string get_distro() {
    std::ifstream f("/etc/os-release");
    if (!f.is_open()) return "Unknown distro";

    std::string line;
    while (std::getline(f, line)) {
        if (line.rfind("PRETTY_NAME=", 0) == 0) {
            std::string val = line.substr(12);
            // Strip quotes if present
            if (!val.empty() && val.front() == '"' && val.back() == '"') {
                val = val.substr(1, val.size() - 2);
            }
            return val;
        }
    }
    return "Unknown distro";
}

// -----------------------------
// Main
// -----------------------------
int main() {
    utsname u;
    uname(&u);

    char hostname_buf[256];
    gethostname(hostname_buf, sizeof(hostname_buf));

    std::cout << "Crossfetch\n";
    std::cout << "-----------\n";
    std::cout << "OS:        " << u.sysname << " " << u.release
              << " (" << get_distro() << ")\n";
    std::cout << "Host:      " << hostname_buf << "\n";
    std::cout << "CPU:       " << get_cpu() << "\n";
    std::cout << "RAM:       " << get_ram() << "\n";
    std::cout << "Uptime:    " << get_uptime() << "\n";

    return 0;
}
