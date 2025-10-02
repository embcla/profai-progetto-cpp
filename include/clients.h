#ifndef CLIENTS_H
#define CLIENTS_H

#include <string>
#include <list>

#include "items.h"

class cliente : public Item {
public:
    cliente(std::string nome, std::string cognome);
    cliente(std::string nome, std::string cognome, int index);

    std::string toStr() const override;
    std::string getNome() const;
    std::string getCognome() const;

    bool operator==(const Item& other) const override;
    bool operator<(const Item& other) const override;

private:
    std::string _nome;
    std::string _cognome;

friend class clienti;

};


class clienti : public ItemList<cliente> {
public:

    // void aggiungiCliente(cliente clnt);
    // void modificaCliente(cliente oldClnt, cliente newClnt);
    // void eliminaCliente(cliente clnt);
    cliente cercaCliente(std::string val);
    // int dimensione();
    // std::list<cliente>::iterator begin() { return _lista_clienti.begin(); }
    // std::list<cliente>::iterator end() { return _lista_clienti.end(); }
    // std::list<cliente>::const_iterator begin() const { return _lista_clienti.begin(); }
    // std::list<cliente>::const_iterator end() const { return _lista_clienti.end(); }

private:
    // cliente notFound = cliente("Not", "Found");
    // std::list<cliente> _lista_clienti;
    // std::list<cliente>::iterator _fineLista;
    // std::list<cliente>::iterator _inizioLista;
    std::string toLower (std::string val);
    // int _lastIndex = 0;
};

#endif // CLIENTS_H
