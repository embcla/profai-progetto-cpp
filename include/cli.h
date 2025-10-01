#ifndef CLI_H
#define CLI_H

#include <string>
#include "clients.h"
// #include "clients-manager.h"  // To be implemented

class CLI {
public:
    CLI();
    void run();

private:
    // clientsManager manager;  // To be implemented

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
};

#endif // CLI_H
