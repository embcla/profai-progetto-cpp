#ifndef CLIENTS_H
#define CLIENTS_H

#include <string>
#include <list>

#include "items.h"

class client : public Item {
public:
    client(std::string nome, std::string cognome);
    client(int index, std::string nome, std::string cognome);

    std::string toStr() const override;
    std::string getNome() const;
    std::string getCognome() const;
    void setNome(std::string val);
    void setCognome(std::string val);

    // bool operator==(const Item& other) const override;
    // bool operator<(const Item& other) const override;
    bool operator==(const client& other) const;
    bool operator<(const client& other) const;

private:
    std::string _nome;
    std::string _cognome;

friend class clientList;

};


class clientList : public ItemList<client> {
public:

    explicit clientList(std::string filename = "clients.csv") : ItemList(std::move(filename)) {
        if (!fileExists(_filename)) {
            std::ofstream{_filename};
        }
        ItemList<client>::readFromCSV(_filename);
    }
    // void aggiungiCliente(cliente clnt);
    // void modificaCliente(cliente oldClnt, cliente newClnt);
    // void eliminaCliente(cliente clnt);
    bool add(std::string nome, std::string cognome);
    bool add(client clnt);
    std::list<client> searchToItemList(std::string val);
    std::list<std::string> searchToString(std::string val);
    
    bool modify(client &cnt, std::string nome, std::string cognome);
    // clientList() = delete;
    // int dimensione();
    // std::list<client>::iterator begin() { return _lista_clientList.begin(); }
    // std::list<client>::iterator end() { return _lista_clientList.end(); }
    // std::list<client>::const_iterator begin() const { return _lista_clientList.begin(); }
    // std::list<client>::const_iterator end() const { return _lista_clientList.end(); }

private:
    // cliente notFound = cliente("Not", "Found");
    // ItemList<cliente> _lista_clienti;
    // std::list<cliente>::iterator _fineLista;
    // std::list<cliente>::iterator _inizioLista;
    // client notFound = client("Not", "Found");
    std::string toLower (std::string val);
    bool exists(client &clnt);
    bool exists(int id);
    // int _lastIndex = 0;
    std::string itemToCSVLine(const client& item) const override;
    client csvLineToItem(const std::string& line) const override;
};

#endif // CLIENTS_H
