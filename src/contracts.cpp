#include "contracts.h"

contract::contract(std::chrono::system_clock::time_point begin, std::chrono::system_clock::time_point end, int clientIndex) {
    _begin = begin;
    _end = end;
    _clientIndex = clientIndex;
    _note = "";
}

contract::contract(std::chrono::system_clock::time_point begin, std::chrono::system_clock::time_point end, int clientIndex, std::string note) {
    _begin = begin;
    _end = end;
    _clientIndex = clientIndex;
    _note = note;
}

std::string contract::toStr() const {
    std::string ret = "Begin: " + std::to_string(std::chrono::system_clock::to_time_t(_begin)) + "\nEnd: " + std::to_string(std::chrono::system_clock::to_time_t(_end)) + "\nClient ID: " + std::to_string(_clientIndex) + "\nNote: " + _note;
    return ret;
}

bool contract::operator==(const contract& other) const {
    return other._begin == _begin && other._end == _end && other._clientIndex == _clientIndex && other._id == _id && other._note == _note;
}

bool contract::operator<(const contract& other) const {
    return _end < other._end;
}

std::string contractList::itemToCSVLine(const contract& item) const {
    std::time_t begin_t = std::chrono::system_clock::to_time_t(item._begin);
    std::time_t end_t = std::chrono::system_clock::to_time_t(item._end);
    std::string note_escaped = item._note;
    // Escape double quotes in note
    size_t pos = 0;
    while ((pos = note_escaped.find('"', pos)) != std::string::npos) {
        note_escaped.insert(pos, 1, '"');
        pos += 2; // Move past the escaped quote
    }
    return std::to_string(item.getId()) + "," + std::to_string(begin_t) + "," + std::to_string(end_t) + "," + std::to_string(item._clientIndex) + ",\"" + note_escaped + "\"";
}


contract contractList::csvLineToItem(const std::string& line) const {
    size_t pos1 = line.find(',');
    size_t pos2 = line.find(',', pos1 + 1);
    size_t pos3 = line.find(',', pos2 + 1);
    size_t pos4 = line.find(',', pos3 + 1);

    int id = std::stoi(line.substr(0, pos1));
    std::time_t begin_t = static_cast<std::time_t>(std::stoll(line.substr(pos1 + 1, pos2 - pos1 - 1)));
    std::time_t end_t = static_cast<std::time_t>(std::stoll(line.substr(pos2 + 1, pos3 - pos2 - 1)));
    int clientIndex = std::stoi(line.substr(pos3 + 1, pos4 - pos3 - 1));
    std::string note = line.substr(pos4 + 2, line.length() - pos4 - 3); // Remove surrounding quotes
    // Unescape double quotes in note
    size_t pos = 0;
    while ((pos = note.find("\"\"", pos)) != std::string::npos) {
        note.erase(pos, 1); // Remove one of the double quotes
        pos += 1; // Move past the quote
    }
    contract cntr(std::chrono::system_clock::from_time_t(begin_t), std::chrono::system_clock::from_time_t(end_t), clientIndex, note);
    cntr.setId(id);
    return cntr;
}

void contractList::add(contract elem) {
    ItemList<contract>::add(elem);
}

void contractList::add(std::chrono::system_clock::time_point begin,  std::chrono::system_clock::time_point end, int clientIndex, std::string note) {
    contract cntr(begin, end, clientIndex, note);
    ItemList<contract>::add(cntr);
}

void contractList::remove(contract elem) {
    ItemList<contract>::remove(elem);
}

void contractList::remove(std::chrono::system_clock::time_point begin,  std::chrono::system_clock::time_point end,  int clientIndex) {
    auto it = std::find_if(this->begin(), this->end(), [this, &begin, &end, &clientIndex](contract& cntr) {
        return (cntr._begin == begin && cntr._end == end && cntr._clientIndex == clientIndex);
    });
    if (it != this->end()) {
        ItemList<contract>::remove(*it);
    }
}

std::list<contract> contractList::contractSearchFrom(std::chrono::system_clock::time_point timeDate) {
    std::list<contract> results;
    for (const auto& cntr : _items) {
        if (cntr._begin >= timeDate) {
            results.push_back(cntr);
        }
    }
    return results;
}

std::list<contract> contractList::contractSearchTo(std::chrono::system_clock::time_point timeDate) {
    std::list<contract> results;
    for (const auto& cntr : _items) {
        if (cntr._end <= timeDate) {
            results.push_back(cntr);
        }
    }
    return results;
}

std::list<contract> contractList::contractSearchClient(int clientIndex) {
    std::list<contract> results;
    for (const auto& cntr : _items) {
        if (cntr._clientIndex == clientIndex) {
            results.push_back(cntr);
        }
    }
    return results;
}