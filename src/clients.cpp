#include "clients.h"

#include <algorithm>

using namespace std::literals;

// Client class implementation
client::client(std::string nome, std::string cognome) {
    _nome = nome;
    _cognome = cognome;
    _id = 0;
}

client::client(int index, std::string nome, std::string cognome) {
    _nome = nome;
    _cognome = cognome;
    _id = index;
}

std::string client::toStr() const {
    return _cognome + " " + _nome + " ";
}

std::string client::getNome() const {
    return _nome;
}

std::string client::getCognome() const {
    return _cognome;
}

void client::setNome(std::string val) {
    _nome = val;
}

void client::setCognome(std::string val) {
    _cognome = val;
}

bool client::operator==(const client& other) const {
    return _nome == other._nome && _cognome == other._cognome;
}

// bool client::operator==(const Item& other) const {
//     const client* c = dynamic_cast<const client*>(&other);
//     if (!c) return false;
//     return this == c;
//     // return _nome == c->_nome && _cognome == c->_cognome;
// }

bool client::operator<(const client& other) const {
    if (_cognome != other._cognome)
        return _cognome < other._cognome;
    return _nome < other._nome;
}

// bool client::operator<(const Item& other) const {
//     const client* c = dynamic_cast<const client*>(&other);
//     if (!c) return false; // or throw
//     return this < c;
//     // if (_cognome != c->_cognome)
//     //     return _cognome < c->_cognome;
//     // return _nome < c->_nome;
// }


bool clientList::add(client clnt) {
    ItemList<client>::add(clnt);
    return true;
}

bool clientList::add(std::string nome, std::string cognome) {
    client clnt(nome, cognome);
    ItemList<client>::add(clnt);
    return true;
}

bool clientList::modify(client &clnt, std::string nome, std::string cognome) {
    if(clientList::exists(clnt)) {
        auto item = ItemList<client>::search(clnt);
        if(!nome.empty())
            item->setNome(nome);
        if(!cognome.empty())
            item->setCognome(cognome);
        this->persist();
    return true;
    } else {
        return false;
    }
}

bool clientList::exists(client& clnt) {
    if(clientList::exists(clnt.getId())) return true;
    return false;
}

bool clientList::exists(int id) {
    if(ItemList<client>::search(id) != nullptr) return true;
    return false;
}

std::string clientList::toLower (std::string str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return str;
}

std::string clientList::itemToCSVLine(const client& item) const {
    return std::to_string(item.getId()) + "," + item.getNome() + "," + item.getCognome();
}

client clientList::csvLineToItem(const std::string& line) const {
    size_t pos1 = line.find(',');
    size_t pos2 = line.find(',', pos1 + 1);
    int id = std::stoi(line.substr(0, pos1));
    std::string nome = line.substr(pos1 + 1, pos2 - pos1 - 1);
    std::string cognome = line.substr(pos2 + 1);
    return client(id, nome, cognome);
}

std::list<std::string> clientList::searchToString(std::string val) {
    std::list<std::string> results;
    std::string val_lower = toLower(val);
    std::list<client> results_items = clientList::searchToItemList(val);
    for (auto& item : results_items) {
            results.push_back(item.getId() + " " + item.toStr());
        }
    return results;
}

std::list<client> clientList::searchToItemList(std::string val) {
    std::list<client> results;
    std::string val_lower = toLower(val);
    for (auto& c : *this) {
        if (toLower(c.getNome()).find(val_lower) != std::string::npos || toLower(c.getCognome()).find(val_lower) != std::string::npos) {
            results.push_back(c);
        }
    }
    return results;
}
