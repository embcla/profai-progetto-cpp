#ifndef CLI_H
#define CLI_H

#include <ctime>
#include <functional>
#include <string>
#include <vector>
#include "clients.h"

// #include "clients-manager.h"  // To be implemented

struct CLICallbacks {
    // 1. Add Client           
    std::function<bool(std::string name, std::string surname)> clientAdd;
    // 2. Modify Client    
    std::function<bool(std::string searchStr, std::string name, std::string surname)> clientMod;
    // 3. Remove Client    
    std::function<bool(std::string searchStr)> clientDel;
    // 4. Search Client    
    std::function<std::string(std::string searchStr)> clientSearch;
    // 5. View All Clients 
    std::function<std::vector<std::string>()> clientViewAll;
    // 6.1 Show Appointment
    std::function<void(std::string searchStr)> appointmentShow;
    // 6.2 Show Contracts  
    std::function<void(std::string searchStr)> contractShow;
    // 6.3 Add Appointment 
    std::function<bool(std::string searchStr, std::time_t date, std::string note)> appointmentAdd;
    // 6.4 Add Contract    
    std::function<bool(std::string searchStr, std::time_t dateStart, std::time_t dateEnd, std::string note)> contractAdd;
    // 6.5 Remove appointment  
    std::function<bool(std::string searchStr, std::time_t date)> appointmentDel;
    // 6.6 Remove Contract 
    std::function<bool(std::string searchStr, std::time_t dateStart, std::time_t dateEnd)> contractDel;
    // 6.7 Search Appointments 
    std::function<std::vector<std::string>(std::string searchStr, std::time_t from, std::time_t to)> appointmentSearch;
    // 6.8 Search Contracts
    std::function<std::vector<std::string>(std::string searchStr, std::time_t from, std::time_t to)> contractSearch;
};

class CLI {
public:
    CLI() = delete;
    CLI(const CLICallbacks& callbacks);
    void run();

private:
    // clientsManager manager;  // To be implemented

    CLICallbacks _callbacks;

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

    bool checkClientExists(std::string query);
};

#endif // CLI_H
