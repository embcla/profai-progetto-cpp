#include <iostream>
#include <ranges>

#include "clients.h"
#include "cli.h"

using namespace std;

int main (void) {
    auto database = clienti();

    database.aggiungiCliente(cliente("Franco", "Papaleo"));
    database.aggiungiCliente(cliente("Gino", "Bramieri"));
    database.aggiungiCliente(cliente("Nicole", "Grimaudo"));
    database.aggiungiCliente(cliente("Paolo", "Beltramelli"));
    

    // cout << "Elementi nel db: " << database.dimensione() << endl;
    // int index = 0;
    // for(auto it : database) {
    //     cout << "[" << index << "]: " << it.toStr() << endl;
    //     index++;
    // }

    // cout << endl << endl;

    // cout << "Ricerca cliente \"Gino\"" << endl;
    // cout << database.cercaCliente("Gino").toStr() << endl;

    // cout << "Ricerca cliente \"gino\"" << endl;
    // cout << database.cercaCliente("gino").toStr() << endl;

    // cout << "Ricerca cliente \"fino\"" << endl;
    // cout << database.cercaCliente("fino").toStr() << endl;

    // cout << "Ricerca cliente \"papa\"" << endl;
    // cout << database.cercaCliente("papa").toStr() << endl;

    auto userIface = CLI();
    userIface.run();
}