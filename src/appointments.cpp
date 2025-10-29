#include <chrono>
#include <ctime>  
#include <string>
#include <sstream>
#include <iomanip>
#include <array>

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
    std::string ret = "Date: " + time_point_to_string(_timeDate) + "\tClient ID: " + std::to_string(_clientIndex) + "\tNote: " + _note;
    return ret;
}

bool appointment::operator==(const appointment& other) const {
    return (other._clientIndex == _clientIndex && other._id == _id && other._note == _note && other._timeDate == _timeDate);
}

bool appointment::operator<(const appointment& other) const {
    return (_timeDate < other._timeDate);
}

namespace {
bool validateTm(const std::tm& tm) {
    if (tm.tm_year < 0) return false;
    if (tm.tm_mon < 0 || tm.tm_mon > 11) return false;
    if (tm.tm_mday < 1 || tm.tm_mday > 31) return false;
    if (tm.tm_hour < 0 || tm.tm_hour > 23) return false;
    if (tm.tm_min < 0 || tm.tm_min > 59) return false;
    if (tm.tm_sec < 0 || tm.tm_sec > 60) return false; // allow leap second
    return true;
}

std::optional<std::tm> tryParseWithFormat(const std::string& input, const std::string& format) {
    std::tm tm{};
    std::istringstream iss(input);
    iss >> std::ws;
    iss >> std::get_time(&tm, format.c_str());
    if (iss.fail() || !iss.eof()) {
        return std::nullopt;
    }
    tm.tm_isdst = -1;
    if (!validateTm(tm)) {
        return std::nullopt;
    }
    return tm;
}
} // namespace

std::optional<std::tm> appointment::parseDateTime(const std::string& dateTime) {
    if (dateTime.empty()) {
        return std::nullopt;
    }

    constexpr std::array<const char*, 4> formats = {
        "%Y-%m-%d %H:%M:%S",
        "%Y-%m-%d %H:%M",
        "%d/%m/%Y %H:%M:%S",
        "%d/%m/%Y %H:%M"
    };

    for (const auto& fmt : formats) {
        if (auto parsed = tryParseWithFormat(dateTime, fmt)) {
            return parsed;
        }
    }

    return std::nullopt;
}

std::optional<std::tm> appointment::parseDateTime(const std::string& date, const std::string& time) {
    if (date.empty() || time.empty()) {
        return std::nullopt;
    }

    constexpr std::array<const char*, 2> dateFormats = { "%Y-%m-%d", "%d/%m/%Y" };
    constexpr std::array<const char*, 2> timeFormats = { "%H:%M:%S", "%H:%M" };

    for (const auto& df : dateFormats) {
        for (const auto& tf : timeFormats) {
            std::tm tm{};

            std::istringstream dateStream(date);
            dateStream >> std::ws;
            dateStream >> std::get_time(&tm, df);
            if (dateStream.fail() || !validateTm(tm)) {
                continue;
            }

            std::istringstream timeStream(time);
            timeStream >> std::ws;
            timeStream >> std::get_time(&tm, tf);
            if (timeStream.fail()) {
                continue;
            }

            if (!validateTm(tm)) {
                continue;
            }

            tm.tm_isdst = -1;
            return tm;
        }
    }

    return std::nullopt;
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

std::list<appointment> appointmentList::searchFrom(std::chrono::system_clock::time_point timeDate, int clientId) {
    std::list<appointment> results;
    for (const auto& app : _items) {
        if (app._timeDate >= timeDate && app._clientIndex == clientId) {
            results.push_back(app);
        }
    }
    return results;
}

std::list<appointment> appointmentList::searchTo(std::chrono::system_clock::time_point timeDate, int clientId) {
    std::list<appointment> results;
    for (const auto& app : _items) {
        if (app._timeDate <= timeDate && app._clientIndex == clientId) {
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
