#ifndef CLIENTS_H
#define CLIENTS_H

#include <string>
#include <list>

class cliente {
public:
    cliente(std::string nome, std::string cognome);
    cliente(std::string nome, std::string cognome, int index);

    std::string toStr();
    std::string getNome();
    std::string getCognome();

    bool operator==(const cliente& other) const;
    bool operator<(const cliente& other) const;

private:
    void setId(int val);
    int getId();
    std::string _nome;
    std::string _cognome;
    int _id;

friend class clienti;

};


class clienti {
public:
    clienti();

    void aggiungiCliente(cliente clnt);
    void modificaCliente(cliente oldClnt, cliente newClnt);
    void eliminaCliente(cliente clnt);
    cliente cercaCliente(std::string val);
    int dimensione();
    std::list<cliente>::iterator begin() { return _lista_clienti.begin(); }
    std::list<cliente>::iterator end() { return _lista_clienti.end(); }
    std::list<cliente>::const_iterator begin() const { return _lista_clienti.begin(); }
    std::list<cliente>::const_iterator end() const { return _lista_clienti.end(); }

private:
    cliente notFound = cliente("Not", "Found");
    std::list<cliente> _lista_clienti;
    std::list<cliente>::iterator _fineLista;
    std::list<cliente>::iterator _inizioLista;
    std::string toLower (std::string val);
    int _lastIndex = 0;
};

#endif // CLIENTS_H
