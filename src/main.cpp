#include <filesystem>
#include <iostream>
#include <ranges>

#include "appointments.h"
#include "cli.h"
#include "clients.h"
#include "contracts.h"


using namespace std;

int main (void) {
    namespace fs = std::filesystem;
    fs::path storageDir = fs::current_path();

    auto apnts = appointmentList((storageDir / "appointments.csv").string());
    auto clnts = clientList((storageDir / "clients.csv").string());
    auto cntrs = contractList((storageDir / "contracts.csv").string());

    clnts.add(client("Franco", "Papaleo"));
    clnts.add(client("Gino", "Bramieri"));
    clnts.add(client("Nicole", "Grimaudo"));
    clnts.add(client("Paolo", "Beltramelli"));
    

    cout << "Elementi nel db: " << clnts.size() << endl;
    int index = 0;
    for(auto it : clnts) {
        cout << "[" << index << "]: " << it.toStr() << endl;
        index++;
    }

    cout << endl << endl;

    // cout << "Ricerca client \"Gino\"" << endl;
    // cout << "  --> " + clnts.search("Gino")->toStr() << endl;

    // cout << "Ricerca client \"gino\"" << endl;
    // cout << "  --> " + clnts.search("gino")->toStr() << endl;

    // cout << "Ricerca client \"fino\"" << endl;
    // if(auto res = clnts.search("fino"); res == nullptr)
    //     cout << "client non trovato!" << endl;
    // else
    //     cout << "  --> " + clnts.search("fino")->toStr() << endl;

    // cout << "Ricerca client \"papa\"" << endl;
    // cout << "  --> " + clnts.search("papa")->toStr() << endl;

    auto userIface = CLI(apnts, clnts, cntrs);
    userIface.run();
}