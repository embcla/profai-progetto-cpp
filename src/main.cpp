#include <iostream>
#include <ranges>

#include "appointments.h"
#include "cli.h"
#include "clients.h"
#include "contracts.h"


using namespace std;

int main (void) {
    auto apnts = appuntamenti();
    auto clnts = clienti();
    auto cntrs = contratti();

    clnts.add(cliente("Franco", "Papaleo"));
    clnts.add(cliente("Gino", "Bramieri"));
    clnts.add(cliente("Nicole", "Grimaudo"));
    clnts.add(cliente("Paolo", "Beltramelli"));
    

    cout << "Elementi nel db: " << clnts.size() << endl;
    int index = 0;
    for(auto it : clnts) {
        cout << "[" << index << "]: " << it.toStr() << endl;
        index++;
    }

    cout << endl << endl;

    cout << "Ricerca cliente \"Gino\"" << endl;
    cout << "  --> " + clnts.search("Gino")->toStr() << endl;

    cout << "Ricerca cliente \"gino\"" << endl;
    cout << "  --> " + clnts.search("gino")->toStr() << endl;

    cout << "Ricerca cliente \"fino\"" << endl;
    if(auto res = clnts.search("fino"); res == nullptr)
        cout << "Cliente non trovato!" << endl;
    else
        cout << "  --> " + clnts.search("fino")->toStr() << endl;

    cout << "Ricerca cliente \"papa\"" << endl;
    cout << "  --> " + clnts.search("papa")->toStr() << endl;

    auto userIface = CLI(apnts, clnts, cntrs);
    userIface.run();
}