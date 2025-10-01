#ifndef APPOINTMENTS_H
#define APPOINTMENTS_H

#include <chrono>
#include <list>
#include <string>

class contratto {
public:
    contratto();
    contratto(std::chrono::system_clock::time_point being, std::chrono::system_clock::time_point end, int clientIndex);
    contratto(std::chrono::system_clock::time_point being, std::chrono::system_clock::time_point end, int clientIndex, std::string note);

    bool operator==(const contratto& other) const;
    bool operator<(const contratto& other) const;

private:
    std::chrono::system_clock::time_point _begin;
    std::chrono::system_clock::time_point _end;
    int _clientIndex;
    std::string _note;
};

class contratti {
public:
    contratti();

    void aggiungiContratto(contratto elem);
    void rimuoviContratto(contratto elem);
    std::list<contratto> cercaContrattoInizio(std::chrono::system_clock::time_point timeDate);
    std::list<contratto> cercaContrattoFine(std::chrono::system_clock::time_point timeDate);
    std::list<contratto> cercaContrattoCliente(int clientIndex); 

private:
    std::list<contratto> _lista_appuntamenti;
};

#endif // APPOINTMENTS_H