#include <iostream>
#include <ranges>

#include "clients.h"
#include "cli.h"

using namespace std;

int main (void) {
    auto database = clienti();

    database.add(cliente("Franco", "Papaleo"));
    database.add(cliente("Gino", "Bramieri"));
    database.add(cliente("Nicole", "Grimaudo"));
    database.add(cliente("Paolo", "Beltramelli"));
    

    cout << "Elementi nel db: " << database.size() << endl;
    int index = 0;
    for(auto it : database) {
        cout << "[" << index << "]: " << it.toStr() << endl;
        index++;
    }

    cout << endl << endl;

    cout << "Ricerca cliente \"Gino\"" << endl;
    cout << "  --> " + database.search("Gino")->toStr() << endl;

    cout << "Ricerca cliente \"gino\"" << endl;
    cout << "  --> " + database.search("gino")->toStr() << endl;

    cout << "Ricerca cliente \"fino\"" << endl;
    if(auto res = database.search("fino"); res == nullptr)
        cout << "Cliente non trovato!" << endl;
    else
        cout << "  --> " + database.search("fino")->toStr() << endl;

    cout << "Ricerca cliente \"papa\"" << endl;
    cout << "  --> " + database.search("papa")->toStr() << endl;

    auto userIface = CLI();
    userIface.run();
}