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
    void setNome(std::string val);
    void setCognome(std::string val);

    // bool operator==(const Item& other) const override;
    // bool operator<(const Item& other) const override;
    bool operator==(const cliente& other) const;
    bool operator<(const cliente& other) const;

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
    bool add(std::string nome, std::string cognome);
    bool add(cliente clnt);
    cliente* search(std::string val);
    std::string searchToString(std::string val);
    bool modify(cliente *cnt, std::string nome, std::string cognome);
    // int dimensione();
    // std::list<cliente>::iterator begin() { return _lista_clienti.begin(); }
    // std::list<cliente>::iterator end() { return _lista_clienti.end(); }
    // std::list<cliente>::const_iterator begin() const { return _lista_clienti.begin(); }
    // std::list<cliente>::const_iterator end() const { return _lista_clienti.end(); }

private:
    // cliente notFound = cliente("Not", "Found");
    // ItemList<cliente> _lista_clienti;
    // std::list<cliente>::iterator _fineLista;
    // std::list<cliente>::iterator _inizioLista;
    std::string toLower (std::string val);
    bool exists(cliente &clnt);
    bool exists(int id);
    // int _lastIndex = 0;
};

#endif // CLIENTS_H
