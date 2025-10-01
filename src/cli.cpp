#include "../include/cli.h"
#include <iostream>
#include <string>
#include <csignal>
#include <cstdlib>

// Signal handler for SIGINT (Ctrl+C) and SIGTSTP (Ctrl+Z)
void signalHandler(int signal) {
    if (signal == SIGINT) {
        std::cout << "\n\nCtrl+C detected. Please use option 0 to exit properly." << std::endl;
        std::cout << "\nEnter your choice: ";
        std::cout.flush();
    } else if (signal == SIGTSTP) {
        std::cout << "\n\nCtrl+Z detected. Please use option 0 to exit properly." << std::endl;
        std::cout << "\nEnter your choice: ";
        std::cout.flush();
    }
}

CLI::CLI() {
    // manager = clientsManager();  // To be implemented

    // Register signal handlers
    std::signal(SIGINT, signalHandler);   // Ctrl+C
    std::signal(SIGTSTP, signalHandler);  // Ctrl+Z
}

void CLI::run() {
    std::cout << "=== InsuraPro Solutions CRM ===" << std::endl;
    std::cout << "Welcome to your client management system!" << std::endl;

    showMenu();

    while (true) {
        std::string choice;
        std::cout << "\nEnter your choice: ";
        std::getline(std::cin, choice);

        if (choice == "1") {
            addClient();
        } else if (choice == "2") {
            modifyClient();
        } else if (choice == "3") {
            removeClient();
        } else if (choice == "4") {
            searchClient();
        } else if (choice == "5") {
            viewAllClients();
        } else if (choice == "6") {
            selectClient();
        } else if (choice == "7") {
            showMenu();
        } else if (choice == "0") {
            std::cout << "Goodbye!" << std::endl;
            break;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

void CLI::showMenu() {
    std::cout << "\n==============================" << std::endl;
    std::cout << "1. Add Client" << std::endl;
    std::cout << "2. Modify Client" << std::endl;
    std::cout << "3. Remove Client" << std::endl;
    std::cout << "4. Search Client" << std::endl;
    std::cout << "5. View All Clients" << std::endl;
    std::cout << "6. Client Activity (Submenu)" << std::endl;
    std::cout << "7. Show Menu" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "==============================" << std::endl;
}

void CLI::addClient() {
    std::cout << "\n--- Add New Client ---" << std::endl;

    std::string nome, cognome;

    std::cout << "Nome: ";
    std::getline(std::cin, nome);
    if (nome.empty()) {
        std::cout << "Nome cannot be empty." << std::endl;
        return;
    }

    std::cout << "Cognome: ";
    std::getline(std::cin, cognome);
    if (cognome.empty()) {
        std::cout << "Cognome cannot be empty." << std::endl;
        return;
    }

    // cliente newClient(nome, cognome);
    // if (manager.addClient(newClient)) {
    //     std::cout << "Client added successfully!" << std::endl;
    // } else {
    //     std::cout << "Failed to add client." << std::endl;
    // }

    std::cout << "TO BE IMPLEMENTED" << std::endl;
}

void CLI::modifyClient() {
    std::cout << "\n--- Modify Client ---" << std::endl;

    std::string searchTerm;
    std::cout << "Enter client name or surname to modify: ";
    std::getline(std::cin, searchTerm);

    if (searchTerm.empty()) {
        std::cout << "Search term cannot be empty." << std::endl;
        return;
    }

    // cliente client = manager.searchClient(searchTerm);
    // if (client not found) {
    //     std::cout << "Client not found." << std::endl;
    //     return;
    // }

    // std::cout << "\nCurrent client details:" << std::endl;
    // std::cout << client.toStr() << std::endl;
    // std::cout << "\nEnter new values (press Enter to keep current value):" << std::endl;

    // Get new values and update
    // std::string nome, cognome;
    // std::cout << "Nome [current]: ";
    // std::getline(std::cin, nome);
    // std::cout << "Cognome [current]: ";
    // std::getline(std::cin, cognome);

    // if (manager.modifyClient(oldClient, newClient)) {
    //     std::cout << "Client updated successfully!" << std::endl;
    // } else {
    //     std::cout << "Failed to update client." << std::endl;
    // }

    std::cout << "TO BE IMPLEMENTED" << std::endl;
}

void CLI::removeClient() {
    std::cout << "\n--- Remove Client ---" << std::endl;

    std::string searchTerm;
    std::cout << "Enter client name or surname to remove: ";
    std::getline(std::cin, searchTerm);

    if (searchTerm.empty()) {
        std::cout << "Search term cannot be empty." << std::endl;
        return;
    }

    // cliente client = manager.searchClient(searchTerm);
    // if (client not found) {
    //     std::cout << "Client not found." << std::endl;
    //     return;
    // }

    // std::cout << "\nClient to delete:" << std::endl;
    // std::cout << client.toStr() << std::endl;

    // std::string confirm;
    // std::cout << "\nAre you sure you want to delete this client? (y/N): ";
    // std::getline(std::cin, confirm);

    // if (confirm == "y" || confirm == "Y" || confirm == "yes" || confirm == "Yes") {
    //     if (manager.removeClient(client)) {
    //         std::cout << "Client deleted successfully!" << std::endl;
    //     } else {
    //         std::cout << "Failed to delete client." << std::endl;
    //     }
    // } else {
    //     std::cout << "Deletion cancelled." << std::endl;
    // }

    std::cout << "TO BE IMPLEMENTED" << std::endl;
}

void CLI::searchClient() {
    std::cout << "\n--- Search Client ---" << std::endl;

    std::string query;
    std::cout << "Enter search term (name or surname): ";
    std::getline(std::cin, query);

    if (query.empty()) {
        std::cout << "Search term cannot be empty." << std::endl;
        return;
    }

    // std::vector<cliente> results = manager.searchClients(query);

    // if (results.empty()) {
    //     std::cout << "No clients found." << std::endl;
    //     return;
    // }

    // std::cout << "\nFound " << results.size() << " client(s):" << std::endl;
    // int index = 0;
    // for (const auto& client : results) {
    //     std::cout << "\n" << index++ << ". " << client.toStr() << std::endl;
    //     std::cout << "--------------------" << std::endl;
    // }

    std::cout << "TO BE IMPLEMENTED" << std::endl;
}

void CLI::viewAllClients() {
    std::cout << "\n--- All Clients ---" << std::endl;

    // std::vector<cliente> clients = manager.getAllClients();

    // if (clients.empty()) {
    //     std::cout << "No clients found." << std::endl;
    //     return;
    // }

    // int index = 0;
    // for (const auto& client : clients) {
    //     std::cout << "\n" << index++ << ". " << client.toStr() << std::endl;
    //     std::cout << "--------------------" << std::endl;
    // }

    std::cout << "TO BE IMPLEMENTED" << std::endl;
}

void CLI::selectClient() {
    std::cout << "\n--- Select Client ---" << std::endl;

    std::string searchTerm;
    std::cout << "Enter client name or surname: ";
    std::getline(std::cin, searchTerm);

    if (searchTerm.empty()) {
        std::cout << "Search term cannot be empty." << std::endl;
        return;
    }

    // cliente client = manager.searchClient(searchTerm);
    // if (client not found) {
    //     std::cout << "Client not found." << std::endl;
    //     return;
    // }

    // std::cout << "Selected client: " << client.toStr() << std::endl;
    // showClientMenu(client.toStr());

    std::cout << "TO BE IMPLEMENTED" << std::endl;
    // For demonstration, call submenu anyway
    showClientMenu(searchTerm);
}

void CLI::showClientMenu(const std::string& clientName) {
    std::cout << "\n=== Client Submenu: " << clientName << " ===" << std::endl;

    while (true) {
        std::cout << "\n------------------------------" << std::endl;
        std::cout << "1. Show Appointments" << std::endl;
        std::cout << "2. Show Contracts" << std::endl;
        std::cout << "3. Add Appointment" << std::endl;
        std::cout << "4. Add Contract" << std::endl;
        std::cout << "5. Remove Appointment" << std::endl;
        std::cout << "6. Remove Contract" << std::endl;
        std::cout << "7. Search Appointments" << std::endl;
        std::cout << "8. Search Contracts" << std::endl;
        std::cout << "0. Back to Main Menu" << std::endl;
        std::cout << "------------------------------" << std::endl;

        std::string choice;
        std::cout << "\nEnter your choice: ";
        std::getline(std::cin, choice);

        if (choice == "1") {
            showAppointments();
        } else if (choice == "2") {
            showContracts();
        } else if (choice == "3") {
            addAppointment();
        } else if (choice == "4") {
            addContract();
        } else if (choice == "5") {
            removeAppointment();
        } else if (choice == "6") {
            removeContract();
        } else if (choice == "7") {
            searchAppointments();
        } else if (choice == "8") {
            searchContracts();
        } else if (choice == "0") {
            std::cout << "Returning to main menu..." << std::endl;
            break;
        } else {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
    }
}

// Client submenu functions
void CLI::showAppointments() {
    std::cout << "\n--- Show Appointments ---" << std::endl;
    // Implementation for showing appointments
    std::cout << "TO BE IMPLEMENTED" << std::endl;
}

void CLI::showContracts() {
    std::cout << "\n--- Show Contracts ---" << std::endl;
    // Implementation for showing contracts
    std::cout << "TO BE IMPLEMENTED" << std::endl;
}

void CLI::addAppointment() {
    std::cout << "\n--- Add Appointment ---" << std::endl;
    // Implementation for adding appointment
    std::cout << "TO BE IMPLEMENTED" << std::endl;
}

void CLI::addContract() {
    std::cout << "\n--- Add Contract ---" << std::endl;
    // Implementation for adding contract
    std::cout << "TO BE IMPLEMENTED" << std::endl;
}

void CLI::removeAppointment() {
    std::cout << "\n--- Remove Appointment ---" << std::endl;
    // Implementation for removing appointment
    std::cout << "TO BE IMPLEMENTED" << std::endl;
}

void CLI::removeContract() {
    std::cout << "\n--- Remove Contract ---" << std::endl;
    // Implementation for removing contract
    std::cout << "TO BE IMPLEMENTED" << std::endl;
}

void CLI::searchAppointments() {
    std::cout << "\n--- Search Appointments ---" << std::endl;
    // Implementation for searching appointments
    std::cout << "TO BE IMPLEMENTED" << std::endl;
}

void CLI::searchContracts() {
    std::cout << "\n--- Search Contracts ---" << std::endl;
    // Implementation for searching contracts
    std::cout << "TO BE IMPLEMENTED" << std::endl;
}
