#ifndef CLI_H
#define CLI_H

#include <ctime>
#include <functional>
#include <string>
#include <vector>

#include "appointments.h"
#include "clients.h"
#include "contracts.h"
// #include "cli-iFace.h"

class CLI {
public:
    // CLI() = delete;
    CLI(const appointmentList& apps, const clientList& clnts, const contractList& cntrs);
    // CLI(const CLICallbacks& callbacks);
    void run();

private:
    // clientsManager manager;  // To be implemented

    // CLICallbacks _callbacks;

    // Main menu functions
    void showMenu();
    void addClient();
    void modifyClient();
    void removeClient();
    void searchClient();
    void viewAllClients();
    void selectClient();

    // Client submenu functions
    void showClientMenu(const std::string& clientName);
    void showAppointments();
    void showContracts();
    void addAppointment();
    void addContract();
    void removeAppointment();
    void removeContract();
    void searchAppointments();
    void searchContracts();

    void narrowSearchClient(std::list<client>& clients);

    appointmentList _appointments;
    clientList _clients;
    contractList _contracts;

};

#endif // CLI_H
