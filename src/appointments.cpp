#include <chrono>
#include <ctime>  
#include <string>
#include <sstream>
#include <iomanip>

#include "appointments.h"

appointment::appointment(std::chrono::system_clock::time_point timeDate, int clientIndex) {
    _timeDate = timeDate;
    _clientIndex = clientIndex;
    _note = "";
}

appointment::appointment(std::chrono::system_clock::time_point timeDate, int clientIndex, std::string note) {
    _timeDate = timeDate;
    _clientIndex = clientIndex;
    _note = note;
}

std::string appointment::time_point_to_string(const std::chrono::system_clock::time_point& tp) const {  
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

std::string appointment::toStr() const {
    std::string ret = "Date: " + time_point_to_string(_timeDate) + "\nClient ID: " + std::to_string(_clientIndex) + "\nNote: " + _note;
    return ret;
}

bool appointment::operator==(const appointment& other) const {
    return (other._clientIndex == _clientIndex && other._id == _id && other._note == _note && other._timeDate == _timeDate);
}

bool appointment::operator<(const appointment& other) const {
    return (_timeDate < other._timeDate);
}

std::string appointmentList::itemToCSVLine(const appointment& item) const {
    std::time_t t = std::chrono::system_clock::to_time_t(item._timeDate);
    std::string note_escaped = item._note;
    // Escape double quotes in note
    size_t pos = 0;
    while ((pos = note_escaped.find('"', pos)) != std::string::npos) {
        note_escaped.insert(pos, 1, '"');
        pos += 2; // Move past the escaped quote
    }
    std::ostringstream oss;
    oss << item.getId() << "," << t << "," << item._clientIndex << ",\"" << note_escaped << "\"";
    return oss.str();
}

appointment appointmentList::csvLineToItem(const std::string& line) const {
    size_t pos1 = line.find(',');
    size_t pos2 = line.find(',', pos1 + 1);
    size_t pos3 = line.find(',', pos2 + 1);

    int id = std::stoi(line.substr(0, pos1));
    std::time_t t = static_cast<std::time_t>(std::stoll(line.substr(pos1 + 1, pos2 - pos1 - 1)));
    int clientIndex = std::stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
    std::string note = line.substr(pos3 + 2, line.length() - pos3 - 3); // Remove surrounding quotes

    // Unescape double quotes in note
    size_t pos = 0;
    while ((pos = note.find("\"\"", pos)) != std::string::npos) {
        note.erase(pos, 1); // Remove one of the double quotes
        pos += 1; // Move past the quote
    }

    appointment app(std::chrono::system_clock::from_time_t(t), clientIndex, note);
    app.setId(id);
    return app;
}

void appointmentList::add(appointment elem) {
    ItemList<appointment>::add(elem);
}

void appointmentList::add(std::chrono::system_clock::time_point timeDate, int clientIndex, std::string note) {
    appointment app(timeDate, clientIndex, note);
    ItemList<appointment>::add(app);
}

void appointmentList::remove(appointment elem) {
    ItemList<appointment>::remove(elem);
}

void appointmentList::remove(std::chrono::system_clock::time_point timeDate, int clientIndex) {
    auto it = std::find_if(this->begin(), this->end(), [this, &timeDate, &clientIndex](appointment& app) {
        return (app._timeDate == timeDate && app._clientIndex == clientIndex);
    });
    if (it != this->end()) {
        ItemList<appointment>::remove(*it);
    }
}

std::list<appointment> appointmentList::searchFrom(std::chrono::system_clock::time_point timeDate) {
    std::list<appointment> results;
    for (const auto& app : _items) {
        if (app._timeDate >= timeDate) {
            results.push_back(app);
        }
    }
    return results;
}

std::list<appointment> appointmentList::searchTo(std::chrono::system_clock::time_point timeDate) {
    std::list<appointment> results;
    for (const auto& app : _items) {
        if (app._timeDate <= timeDate) {
            results.push_back(app);
        }
    }
    return results;
}

std::list<appointment> appointmentList::searchClient(int clientIndex) {
    std::list<appointment> results;
    for (const auto& app : _items) {
        if (app._clientIndex == clientIndex) {
            results.push_back(app);
        }
    }
    return results;
}