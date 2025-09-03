// ######################### cri debug da qui #######################
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

namespace dbg {

inline std::string currentTimestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm{};
#ifdef _WIN32
    localtime_s(&local_tm, &t);
#else
    localtime_r(&t, &local_tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

inline std::ofstream& getLogStream() {
    static std::ofstream out("log.txt", std::ios::app); // aperto una sola volta
    return out;
}

template <typename... Args>
inline void print_debug_hell_yeah(Args&&... args) {
    auto& out = getLogStream();
    if (!out) { std::cerr << "Impossibile aprire log.txt\n"; return; }
    out << "[" << currentTimestamp() << "] ";
    (out << ... << args) << std::endl;
    out.flush();
}

} // namespace dbg
// ######################### a qui #######################