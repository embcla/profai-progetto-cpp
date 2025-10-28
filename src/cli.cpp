#include <iostream>
#include <string>
#include <csignal>
#include <cstdlib>

#include "cli.h"

#include "appointments.h"
#include "clients.h"
#include "contracts.h"

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

// CLI::CLI(const CLICallbacks& callbacks) {
//     // manager = clientsManager();  // To be implemented

//     // Register signal handlers
//     std::signal(SIGINT, signalHandler);   // Ctrl+C
//     std::signal(SIGTSTP, signalHandler);  // Ctrl+Z

//     // Validate that all required callbacks are provided
//     if (!callbacks.clientAdd) {
//         throw std::invalid_argument("clientAdd callback is required");
//     }
//     if (!callbacks.clientMod) {
//         throw std::invalid_argument("clientMod callback is required");
//     }
//     if (!callbacks.clientDel) {
//         throw std::invalid_argument("clientDel callback is required");
//     }
//     if (!callbacks.clientSearch) {
//         throw std::invalid_argument("clientSearch callback is required");
//     }
//     if (!callbacks.clientViewAll) {
//         throw std::invalid_argument("clientViewAll callback is required");
//     }
//     if (!callbacks.appointmentAdd) {
//         throw std::invalid_argument("appointmentAdd callback is required");
//     }
//     if (!callbacks.appointmentDel) {
//         throw std::invalid_argument("appointmentDel callback is required");
//     }
//     if (!callbacks.appointmentSearch) {
//         throw std::invalid_argument("appointmentSearch callback is required");
//     }
//     if (!callbacks.appointmentShow) {
//         throw std::invalid_argument("appointmentShow callback is required");
//     }    
//     if (!callbacks.appointmentSearch) {
//         throw std::invalid_argument("appointmentSearch callback is required");
//     }
//     if (!callbacks.contractAdd) {
//         throw std::invalid_argument("contractAdd callback is required");
//     }
//     if (!callbacks.contractDel) {
//         throw std::invalid_argument("contractDel callback is required");
//     }
//     if (!callbacks.contractSearch) {
//         throw std::invalid_argument("contractSearch callback is required");
//     }
//     if (!callbacks.contractShow) {
//         throw std::invalid_argument("contractShow callback is required");
//     }    
//     if (!callbacks.contractSearch) {
//         throw std::invalid_argument("contractSearch callback is required");
//     }

//     // If all valid, store them
//     _callbacks = callbacks;

// }

CLI::CLI(const appointmentList& apps, const clientList& clnts, const contractList& cntrs) {
    std::signal(SIGINT, signalHandler);   // Ctrl+C
    std::signal(SIGTSTP, signalHandler);  // Ctrl+Z

    _appointments = apps;
    _clients = clnts;
    _contracts = cntrs;

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

    if(_clients.add(nome, cognome) == false) {
        std::cout << "\tFailed to add client." << std::endl;
    } else {
        std::cout << "\tClient added successfully!" << std::endl;
    }

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
    std::list<client> clients = _clients.searchToItemList(searchTerm);
    if (clients.empty()) {
        std::cout << "\tClient not found." << std::endl;
        return;
    } 
    
    if (clients.size() != 1) {
        std::cout << "\tMultiple clients found. Please refine your search." << std::endl;
        narrowSearchClient(clients);
    }
    if (clients.empty()) {
        std::cout << "\tNo client selected for modification." << std::endl;
        return;
    }

    std::cout << "\nCurrent client details:" << std::endl;
    std::cout << clients.front().toStr() << std::endl;
    std::cout << "\nEnter new values (press Enter to keep current value):" << std::endl;

    // Get new values and update
    std::string nome, cognome;
    std::cout << "Nome [current]: ";
    std::getline(std::cin, nome);
    std::cout << "Cognome [current]: ";
    std::getline(std::cin, cognome);

    if (_clients.modify(clients.front(), nome, cognome)) {
        std::cout << "\tClient updated successfully!" << std::endl;
    } else {
        std::cout << "\tFailed to update client." << std::endl;
    }
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

    std::list<client> clients = _clients.searchToItemList(searchTerm);
    if (clients.empty()) {
        std::cout << "\tClient not found." << std::endl;
        return;
    }
    if (clients.size() != 1) {
        narrowSearchClient(clients);
    }
    if (clients.empty()) {
        std::cout << "\tNo client selected for deletion." << std::endl;
        return;
    }

    std::cout << "\nClient to delete:" << std::endl;
    std::cout << clients.front().toStr() << std::endl;

    std::string confirm;
    std::cout << "\nAre you sure you want to delete this client? (y/N): ";
    std::getline(std::cin, confirm);

    if (confirm == "y" || confirm == "Y" || confirm == "yes" || confirm == "Yes") {
        _clients.remove(clients.front());
        std::cout << "Client deleted successfully!" << std::endl;
    } else {
        std::cout << "Deletion cancelled." << std::endl;
    }
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

    std::list<std::string> ret = _clients.searchToString(query);
    if(ret.empty()) {
        std::cout << "\tClient not found." << std::endl;
        return;
    } else {
        for (const auto& clientStr : ret) {
            std::cout << clientStr << std::endl;
        }
        std::cout << "--------------------" << std::endl;
    }
    
}

void CLI::narrowSearchClient(std::list<client>& clients) {
    std::cout << "\n--- Narrow Search Results ---" << std::endl;
    for (const auto& clnt : clients) {
        std::cout << "[" << clnt.getId() << "]: " << clnt.toStr() << std::endl;
    }
    std::cout << "------------------------------" << std::endl;

    std::string idStr;
    std::cout << "Enter the ID of the client you want to select: ";
    std::getline(std::cin, idStr);
    int id = std::stoi(idStr);

    auto it = std::find_if(clients.begin(), clients.end(), [id](const client& c) {
        return c.getId() == id;
    });

    if (it != clients.end()) {
        clients = { *it }; // Keep only the selected client
    } else {
        std::cout << "Invalid ID selected." << std::endl;
        clients.clear();
    }
}

void CLI::viewAllClients() {
    std::cout << "\n--- All Clients ---" << std::endl;

    for(auto elem : _clients) {
        std::cout << "[" << elem.getId() << "]: " << elem.toStr() << std::endl;
    }
    std::cout << "--------------------" << std::endl << std::endl;
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

    // client client = manager.searchClient(searchTerm);
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

// bool CLI::checkClientExists(std::string query) {
//     std::list<std::string> ret = _clients.searchToString(query);
//     if(ret.empty()) {
//         std::cout << "\tClient not found." << std::endl;
//         return false;
//     }
//     return true;
// }
