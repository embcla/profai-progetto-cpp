#ifndef APPOINTMENTS_H
#define APPOINTMENTS_H

#include <chrono>
#include <list>
#include <string>

class appuntamento {
public:
    appuntamento();
    appuntamento(std::chrono::system_clock::time_point timeDate, int clientIndex);
    appuntamento(std::chrono::system_clock::time_point timeDate, int clientIndex, std::string note);

    bool operator==(const appuntamento& other) const;
    bool operator<(const appuntamento& other) const;

private:
    std::chrono::system_clock::time_point _timeDate;
    int _clientIndex;
    std::string _note;
};

class appuntamenti {
public:
    appuntamenti();

    void aggiungiAppuntamento(appuntamento elem);
    void rimuoviAppuntamento(appuntamento elem);
    std::list<appuntamento> cercaAppuntamento(std::chrono::system_clock::time_point timeDate);

private:
    std::list<appuntamento> _lista_appuntamenti;
};

#endif // APPOINTMENTS_H