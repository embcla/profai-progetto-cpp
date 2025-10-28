#ifndef APPOINTMENTS_H
#define APPOINTMENTS_H

#include <chrono>
#include <list>
#include <string>

#include "items.h"

class appuntamento : Item {
public:
    appuntamento() = delete;
    appuntamento(std::chrono::system_clock::time_point timeDate, int clientIndex);
    appuntamento(std::chrono::system_clock::time_point timeDate, int clientIndex, std::string note);

    std::string toStr() const override;
    // bool operator==(const Item& other) const override;
    // bool operator<(const Item& other) const override;
    bool operator==(const appuntamento& other) const;
    bool operator<(const appuntamento& other) const;

private:
    std::string time_point_to_string(const std::chrono::system_clock::time_point& tp) const;
    std::chrono::system_clock::time_point _timeDate;
    int _clientIndex;
    std::string _note;
};

class appuntamenti : public ItemList<appuntamento> {
public:
    // appuntamenti();

    void aggiungiAppuntamento(appuntamento elem);
    void rimuoviAppuntamento(appuntamento elem);
    appuntamento cercaAppuntamento(std::chrono::system_clock::time_point timeDate);

private:
    ItemList<appuntamento> _lista_appuntamenti;
};

#endif // APPOINTMENTS_H