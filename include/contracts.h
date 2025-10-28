#ifndef CONTRACTS_H
#define CONTRACTS_H

#include <chrono>
#include <list>
#include <string>

#include "items.h"

class contract : public Item {
public:
    // contract() = delete;
    contract(std::chrono::system_clock::time_point being, std::chrono::system_clock::time_point end, int clientIndex);
    contract(std::chrono::system_clock::time_point being, std::chrono::system_clock::time_point end, int clientIndex, std::string note);

    std::string toStr() const override;
    bool operator==(const contract& other) const;
    bool operator<(const contract& other) const;

private:
    std::chrono::system_clock::time_point _begin;
    std::chrono::system_clock::time_point _end;
    int _clientIndex;
    std::string _note;

friend class contractList;
};

class contractList : public ItemList<contract> {
public:
    explicit contractList(std::string filename = "contracts.csv") : ItemList(std::move(filename)) {
        if (!fileExists(_filename)) {
            std::ofstream{_filename};
        }
        ItemList<contract>::readFromCSV(_filename);
    }

    void add(contract elem);
    void add(std::chrono::system_clock::time_point begin,  std::chrono::system_clock::time_point end, int clientIndex, std::string note = "");
    void remove(contract elem);
    void remove(std::chrono::system_clock::time_point begin,  std::chrono::system_clock::time_point end,  int clientIndex);
    std::list<contract> contractSearchFrom(std::chrono::system_clock::time_point timeDate);
    std::list<contract> contractSearchTo(std::chrono::system_clock::time_point timeDate);
    std::list<contract> contractSearchClient(int clientIndex);

private:
    std::string itemToCSVLine(const contract& item) const override;
    contract csvLineToItem(const std::string& line) const override;
};

#endif // CONTRACTS_H