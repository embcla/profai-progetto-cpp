#include "clients.h"

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

std::string cliente::toStr() const {
    return _nome + " " + _cognome + " ";
}

std::string cliente::getNome() const {
    return _nome;
}

std::string cliente::getCognome() const {
    return _cognome;
}

bool cliente::operator==(const cliente& other) const {
    return _nome == other._nome && _cognome == other._cognome;
}

bool cliente::operator==(const Item& other) const {
    const cliente* c = dynamic_cast<const cliente*>(&other);
    if (!c) return false;
    return this == c;
    // return _nome == c->_nome && _cognome == c->_cognome;
}

bool cliente::operator<(const cliente& other) const {
    if (_cognome != other._cognome)
        return _cognome < other._cognome;
    return _nome < other._nome;
}

bool cliente::operator<(const Item& other) const {
    const cliente* c = dynamic_cast<const cliente*>(&other);
    if (!c) return false; // or throw
    return this < c;
    // if (_cognome != c->_cognome)
    //     return _cognome < c->_cognome;
    // return _nome < c->_nome;
}

cliente* clienti::search(std::string val) {
    std::string val_lower = toLower(val);
    auto it = std::find_if(this->begin(), this->end(), [this, &val_lower](cliente& c) {
        return (toLower(c.getNome()).find(val_lower) != std::string::npos || toLower(c.getCognome()).find(val_lower) != std::string::npos);
    });
    if (it != this->end())
        return &(*it);
    else
        return nullptr;
}

std::string clienti::toLower (std::string str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return str;
}
