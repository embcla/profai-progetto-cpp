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
    return _cognome + " " + _nome + " ";
}

std::string cliente::getNome() const {
    return _nome;
}

std::string cliente::getCognome() const {
    return _cognome;
}

void cliente::setNome(std::string val) {
    _nome = val;
}

void cliente::setCognome(std::string val) {
    _cognome = val;
}

bool cliente::operator==(const cliente& other) const {
    return _nome == other._nome && _cognome == other._cognome;
}

// bool cliente::operator==(const Item& other) const {
//     const cliente* c = dynamic_cast<const cliente*>(&other);
//     if (!c) return false;
//     return this == c;
//     // return _nome == c->_nome && _cognome == c->_cognome;
// }

bool cliente::operator<(const cliente& other) const {
    if (_cognome != other._cognome)
        return _cognome < other._cognome;
    return _nome < other._nome;
}

// bool cliente::operator<(const Item& other) const {
//     const cliente* c = dynamic_cast<const cliente*>(&other);
//     if (!c) return false; // or throw
//     return this < c;
//     // if (_cognome != c->_cognome)
//     //     return _cognome < c->_cognome;
//     // return _nome < c->_nome;
// }

bool clienti::add(cliente clnt) {
    ItemList<cliente>::add(clnt);
    return true;
}

bool clienti::add(std::string nome, std::string cognome) {
    cliente clnt(nome, cognome);
    ItemList<cliente>::add(clnt);
    return true;
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

std::string clienti::searchToString(std::string val) {
    auto ret = clienti::search(val);
    if(ret != nullptr) {
        return ret->toStr();
    } else {
        return "";
    }    
}

bool clienti::modify(cliente *clnt, std::string nome, std::string cognome) {
    if(clienti::exists(*clnt)) {
        auto item = ItemList<cliente>::search(*clnt);
        if(!nome.empty())
            item->setNome(nome);
        if(!cognome.empty())
            item->setCognome(cognome);
    return true;
    } else {
        return false;
    }
}

bool clienti::exists(cliente& clnt) {
    if(clienti::exists(clnt.getId())) return true;
    return false;
}

bool clienti::exists(int id) {
    if(ItemList<cliente>::search(id) != nullptr) return true;
    return false;
}

std::string clienti::toLower (std::string str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return str;
}
