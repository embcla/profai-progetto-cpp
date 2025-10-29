#ifndef ITEMS_H
#define ITEMS_H

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <list>
#include <string>

class Item {
protected:
    int _id = 0;
public:
    Item();
    Item(int id) : _id(id) {}
    virtual ~Item() = default;
    int getId() const { return _id; }
    void setId(int val) { _id = val; }
    virtual std::string toStr() const = 0;  // Pure virtual
    bool operator==(const Item& other) const; // Pure virtual
    bool operator<(const Item& other) const; // Pure virtual
};

template<typename T>
class ItemList {
protected:
    explicit ItemList(std::string filename) : _filename(std::move(filename)) {};
    std::string _filename;
    std::list<T> _items;
    int _nextId = 1;
    // Pure virtual methods for subclasses to implement
    virtual std::string itemToCSVLine(const T& item) const = 0;
    virtual T csvLineToItem(const std::string& line) const = 0;
    static bool fileExists(const std::string& filename) {
       return std::filesystem::exists(filename);
    }

    void persist() {
        writeToCSV(_filename);
    }

    bool itemExists(const T& item) const {
        return std::find(_items.begin(), _items.end(), item) != _items.end();
    }

public:
    bool add(T item);
    void remove(int id);
    void remove(const T& obj);
    T* search(int id);
    T* search(const T& obj);
    int size();
    typename std::list<T>::iterator begin() { return _items.begin(); }
    typename std::list<T>::iterator end() { return _items.end(); }
    typename std::list<T>::const_iterator begin() const { return _items.begin(); }
    typename std::list<T>::const_iterator end() const { return _items.end(); }
    void writeToCSV(const std::string& filename) const {
        std::ofstream file(filename);
        for (const auto& item : _items) {
            file << itemToCSVLine(item) << "\n";
        }
    }
    void readFromCSV(const std::string& filename) {
        if(!fileExists(filename))
            return;
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            if(itemExists(csvLineToItem(line))) {
                continue; // Skip duplicates
            } else {
                _items.push_back(csvLineToItem(line));
                _nextId = std::max(_nextId, _items.back().getId() + 1);
            }
        }
    }
};

// Template implementations must be in header file
template<typename T>
bool ItemList<T>::add(T item) {
    if(itemExists(item)) {
        return false; // Do not add duplicates
    }
    item.setId(_nextId);
    _nextId++;
    _items.push_back(item);
    _items.sort();
    persist();
    return true;
}

template<typename T>
void ItemList<T>::remove(int id) {
    _items.remove_if([id](const T& item) {
        return item.getId() == id;
    });
    persist();
}

template<typename T>
void ItemList<T>::remove(const T& obj) {
    _items.remove_if([&obj](const T& item) {
        return item == obj;
    });
    persist();
}

template<typename T>
T* ItemList<T>::search(int id) {
    auto it = std::find_if(_items.begin(), _items.end(), [id](const T& item) {
        return item.getId() == id;
    });

    if (it != _items.end()) {
        return &(*it);
    }
    return nullptr;
}

template<typename T>
T* ItemList<T>::search(const T& obj) {
    auto it = std::find_if(_items.begin(), _items.end(), [obj](const T& item) {
        return item == obj;
    });

    if (it != _items.end()) {
        return &(*it);
    }
    return nullptr;
}

template<typename T>
int ItemList<T>::size() {
    return _items.size();
}

#endif // ITEMS_H
