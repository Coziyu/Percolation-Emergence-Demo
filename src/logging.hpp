#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <string>
#include <iostream>

//! HEADER ONLY BECAUSE C++ CAN'T SPLIT TEMPLATES PROPERLY  
const bool PRINT_NON_CRITICAL = true;

#define RESET   "\033[0m"
#define BLACK   "\033[30m"                 /* Black */
#define RED     "\033[31m"                 /* Red */
#define GREEN   "\033[32m"                 /* Green */
#define YELLOW  "\033[33m"                 /* Yellow */
#define BLUE    "\033[34m"                 /* Blue */
#define MAGENTA "\033[35m"                 /* Magenta */
#define CYAN    "\033[36m"                 /* Cyan */
#define WHITE   "\033[37m"                 /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

inline void log_info_recur(){
    std::cout << RESET << "\n";
};

template<typename First, typename... Rest>
void log_info(const First& first, const Rest&... rest) {
    std::cout << GREEN << "[INFO] " << first << " ";
    log_info_recur(rest...);
}

template<typename First, typename... Rest>
void log_info_recur(const First& first, const Rest&... rest) {
    std::cout << first << " ";
    log_info_recur(rest...);
}




inline void log_warn_recur(){
    std::cout << RESET << "\n";
};

template<typename First, typename... Rest>
void log_warn(const First& first, const Rest&... rest) {
    std::cout << YELLOW << "[WARN] " << first << " ";
    log_warn_recur(rest...);
}

template<typename First, typename... Rest>
void log_warn_recur(const First& first, const Rest&... rest) {
    std::cout << first << " ";
    log_warn_recur(rest...);
}



inline void log_error_recur(){
    std::cout << RESET << "\n";
};
template<typename First, typename... Rest>
void log_error(const First& first, const Rest&... rest) {
    std::cout << RED << "[ERROR] " << first << " ";
    log_error_recur(rest...);
}

template<typename First, typename... Rest>
void log_error_recur(const First& first, const Rest&... rest) {
    std::cout << first << " ";
    log_error_recur(rest...);
}

#undef RESET
#undef BLACK
#undef RED
#undef GREEN
#undef YELLOW 
#undef BLUE
#undef MAGENTA
#undef CYAN
#undef WHITE
#undef BOLDBLACK
#undef BOLDRED
#undef BOLDGREEN
#undef BOLDYELLOW  
#undef BOLDBLUE
#undef BOLDMAGENTA
#undef BOLDCYAN
#undef BOLDWHITE

#endif // LOGGING_HPP
