#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include <list>
#include <algorithm>

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
    virtual bool operator==(const Item& other) const = 0; // Pure virtual
    virtual bool operator<(const Item& other) const = 0; // Pure virtual
};

template<typename T>
class ItemList {
protected:
    std::list<T> _items;
    int _nextId = 1;
public:
    void add(T item);
    void remove(int id);
    void remove(Item obj);
    T* search(int id);
    T* ItemList<T>::search(Item obj);
    int size();
    std::list<T>::iterator begin() { return _items.begin(); }
    std::list<T>::iterator end() { return _items.end(); }
    std::list<T>::const_iterator begin() const { return _items.begin(); }
    std::list<T>::const_iterator end() const { return _items.end(); }
};

// Template implementations must be in header file
template<typename T>
void ItemList<T>::add(T item) {
    item.setId(_nextId);
    _nextId++;
    _items.push_back(item);
    _items.sort();
}

template<typename T>
void ItemList<T>::remove(int id) {
    _items.remove_if([id](const T& item) {
        return item.getId() == id;
    });
}

template<typename T>
void ItemList<T>::remove(Item obj) {
    _items.remove_if([obj](const T& item) {
        return item == obj;
    });
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
T* ItemList<T>::search(Item obj) {
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