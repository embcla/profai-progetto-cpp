#include <chrono>
#include <ctime>  
#include <string>
#include <sstream>
#include <iomanip>

#include "appointments.h"

appuntamento::appuntamento(std::chrono::system_clock::time_point timeDate, int clientIndex) {
    _timeDate = timeDate;
    _clientIndex = clientIndex;
}

appuntamento::appuntamento(std::chrono::system_clock::time_point timeDate, int clientIndex, std::string note) {
    _timeDate = timeDate;
    _clientIndex = clientIndex;
    _note = note;
}

std::string appuntamento::time_point_to_string(const std::chrono::system_clock::time_point& tp) const {  
    // // Convert time_point to time_t (C-compatible type)  
    // std::time_t t = std::chrono::system_clock::to_time_t(tp);  

    // // Convert to tm (local time; not thread-safe - use mutex or localtime_r in production)  
    // std::tm tm = *std::localtime(&t);  

    // // Format tm into a readable string  
    // char buffer[40];  
    // std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm);  

    // return buffer;  

    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

std::string appuntamento::toStr() const {
    std::string ret = "Date: " + time_point_to_string(_timeDate) + "\nClient ID: " + std::to_string(_clientIndex) + "\nNote: " + _note;
    return ret;
}

bool appuntamento::operator==(const appuntamento& other) const {
    return (other._clientIndex == _clientIndex && other._id == _id && other._note == _note && other._timeDate == _timeDate);
}

bool appuntamento::operator<(const appuntamento& other) const {
    return (_timeDate < other._timeDate);
}