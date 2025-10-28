#include "contracts.h"

contratto::contratto(std::chrono::system_clock::time_point begin, std::chrono::system_clock::time_point end, int clientIndex) {

}

contratto::contratto(std::chrono::system_clock::time_point begin, std::chrono::system_clock::time_point end, int clientIndex, std::string note) {

}

std::string contratto::toStr() const {

}

bool contratto::operator==(const contratto& other) const {
    return other._begin == _begin && other._end == _end && other._clientIndex == _clientIndex && other._id == _id && other._note == _note;
}

bool contratto::operator<(const contratto& other) const {
    return _end < other._end;
    
}