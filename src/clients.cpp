#include "../include/clients.h"

#include <algorithm>

using namespace std::literals;

// Cliente class implementation
cliente::cliente(std::string nome, std::string cognome) {
    _nome = nome;
    _cognome = cognome;
    _id = 0;
}

cliente::cliente(std::string nome, std::string cognome, int index) {
    _nome = nome;
    _cognome = cognome;
    _id = index;
}

std::string cliente::toStr() {
    std::string val = _nome + " " + _cognome + " ";
    return val;
}

std::string cliente::getNome() {
    return _nome;
}

std::string cliente::getCognome() {
    return _cognome;
}

bool cliente::operator==(const cliente& other) const {
    return _nome == other._nome && _cognome == other._cognome;
}

bool cliente::operator<(const cliente& other) const {
    if (_cognome != other._cognome)
        return _cognome < other._cognome;
    return _nome < other._nome;
}

void cliente::setId(int val) {
    _id = val;
}

int cliente::getId() {
    return _id;
}

// Clienti class implementation
clienti::clienti() {

}

void clienti::aggiungiCliente(cliente clnt) {
    clnt.setId(_lastIndex);
    _lastIndex++;
    _lista_clienti.push_back(clnt);
    _lista_clienti.sort();
    _fineLista = _lista_clienti.end();
    _inizioLista = _lista_clienti.begin();
}

void clienti::modificaCliente(cliente oldClnt, cliente newClnt) {
    eliminaCliente(oldClnt);
    aggiungiCliente(newClnt);
}

void clienti::eliminaCliente(cliente clnt) {
    _lista_clienti.remove(clnt);
}

cliente clienti::cercaCliente(std::string val) {
    std::string val_lower = toLower(val);
    auto it = std::find_if(_inizioLista, _fineLista, [this, &val_lower](cliente& c) {
        return (toLower(c.getNome()).find(val_lower) != std::string::npos || toLower(c.getCognome()).find(val_lower) != std::string::npos);
    });
    if (it != _fineLista)
        return *it;
    else
        return notFound;
}

int clienti::dimensione() {
    return _lista_clienti.size();
}

std::string clienti::toLower (std::string str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return str;
}
