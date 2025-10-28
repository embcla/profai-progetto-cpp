#ifndef CONTRACTS_H
#define CONTRACTS_H

#include <chrono>
#include <list>
#include <string>

#include "items.h"

class contratto : public Item {
public:
    contratto() = delete;
    contratto(std::chrono::system_clock::time_point begin, std::chrono::system_clock::time_point end, int clientIndex);
    contratto(std::chrono::system_clock::time_point begin, std::chrono::system_clock::time_point end, int clientIndex, std::string note);

    std::string toStr() const override;
    // bool operator==(const Item& other) const override;
    // bool operator<(const Item& other) const override;
    bool operator==(const contratto& other) const;
    bool operator<(const contratto& other) const;

private:
    std::chrono::system_clock::time_point _begin;
    std::chrono::system_clock::time_point _end;
    int _clientIndex;
    std::string _note;
};

class contratti : public ItemList<contratto> {
public:
    // contratti();

    void aggiungiContratto(contratto elem);
    void rimuoviContratto(contratto elem);
    contratto cercaContrattoInizio(std::chrono::system_clock::time_point timeDate);
    contratto cercaContrattoFine(std::chrono::system_clock::time_point timeDate);
    contratto cercaContrattoCliente(int clientIndex); 

private:
    ItemList<contratto> _lista_contratti;
};

#endif // CONTRACTS_H