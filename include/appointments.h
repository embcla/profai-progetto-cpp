#ifndef appointments_H
#define appointments_H

#include <chrono>
#include <list>
#include <string>

#include "items.h"

class appointment : public Item {
public:
    // appointment() = delete;
    appointment(std::chrono::system_clock::time_point timeDate, int clientIndex);
    appointment(std::chrono::system_clock::time_point timeDate, int clientIndex, std::string note);

    std::string toStr() const override;
    // bool operator==(const Item& other) const override;
    // bool operator<(const Item& other) const override;
    bool operator==(const appointment& other) const;
    bool operator<(const appointment& other) const;

private:
    std::string time_point_to_string(const std::chrono::system_clock::time_point& tp) const;
    std::chrono::system_clock::time_point _timeDate;
    int _clientIndex;
    std::string _note;

friend class appointmentList;
};

class appointmentList : public ItemList<appointment> {
public:
    // appointmentList() = delete;
    explicit appointmentList(std::string filename = "appointments.csv") : ItemList(std::move(filename)) {
        if (!fileExists(_filename)) {
            std::ofstream{_filename};
        }
        ItemList<appointment>::readFromCSV(_filename);
    }

    void add(appointment elem);
    void add(std::chrono::system_clock::time_point timeDate, int clientIndex, std::string note = "");
    void remove(appointment elem);
    void remove(std::chrono::system_clock::time_point timeDate, int clientIndex);
    std::list<appointment> searchFrom(std::chrono::system_clock::time_point timeDate);
    std::list<appointment> searchTo(std::chrono::system_clock::time_point timeDate);
    std::list<appointment> searchClient(int clientIndex);
    // appointment search(std::chrono::system_clock::time_point timeDate);

private:
    std::string itemToCSVLine(const appointment& item) const override;
    appointment csvLineToItem(const std::string& line) const override;
};

#endif // appointmentList_H