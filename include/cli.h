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
    void showClientMenu(const client clnt);
    void showAppointments(const client clnt);
    void showContracts(const client clnt);
    void addAppointment(const client clnt);
    void addContract(const client clnt);
    void removeAppointment(const client clnt);
    void removeContract(const client clnt);
    void searchAppointments(const client clnt);
    void searchContracts(const client clnt);

    template<typename Container>
    void printElemList(const Container& elements);
    bool findSingleClient(client*& clnt, std::string searchTerm);
    void narrowSearchClient(std::list<client>& clients);
    bool validateTimeDateInput(std::string date, std::string time, std::time_t& asTimeT);

    appointmentList _appointments;
    clientList _clients;
    contractList _contracts;

};

#endif // CLI_H
