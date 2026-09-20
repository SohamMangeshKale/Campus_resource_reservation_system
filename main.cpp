#include <iostream>
#include <string>
#include <limits>
#include "resource_manager.h"
#include "reservation_manager.h"
#include "waitlist.h"
#include "history_stack.h"
 
 
void printMenu() {
    std::cout << "\n----------- Campus Resource Reservation System -----------\n";
    std::cout << "1. Display all resources\n";
    std::cout << "2. Display availability for a resource\n";
    std::cout << "3. Create a reservation\n";
    std::cout << "4. Cancel a reservation\n";
    std::cout << "5. Display active reservation\n";
    std::cout << "6. Display waitlist\n";
    std::cout << "7. Undo last cancellation\n";
    std::cout << "8. Display cancellation history\n";
    std::cout << "9. Exit\n";
    std::cout << "Choose an option: ";
}
 
 
// clearing galat inputs
void clearInputError() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
 
int main() { //anshika start here
    ResourceManager reservationManager;
    ReservationManager reservationManager;
    Waitlist waitlist;
    HistoryStack historyStack;

    if(!resourceManager.loadFormFile("resouces.txt")) {
        std::count << "Warning: continuing with no resources loaded.\n";
    }   


    int choice = 0;
    bool running = true;
 
    while (running) {
        printMenu();
 
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number.\n";
            clearInputError();
            continue;
        }

        switch (choice) {
            case 1: {
                resourceManager.displayAllResources();
                break;
            }
            case 2: {
                int id;
                std::cout << "Enter resource ID: ";
                if (!(std::cin >> id)) { std::cout << "Invalid input.\n"; clearInputError(); break; }
                resourceManager.displayAvailability(id);
                break;
            }   
            case 3: {
                int id, qty;
                std::string name;
                std::cout << "Enter resource ID: ";
                if (!(std::cin >> id)) { std::cout << "Invalid input.\n"; clearInputError(); break; }
                std::cout << "Enter student name (no spaces): ";
                std::cin >> name;
                std::cout << "Enter quantity: ";
                if (!(std::cin >> qty)) { std::cout << "Invalid input.\n"; clearInputError(); break; }
 
                reservationManager.createReservation(id, name, qty, resourceManager, waitlist);
                break;
            }
            case 4: {
                int resID;
                std::cout << "Enter reservation ID to cancel: ";
                if (!(std::cin >> resID)) { std::cout << "Invalid input.\n"; clearInputError(); break; }
                reservationManager.cancelReservation(resID, resourceManager, historyStack);
                break;
            }
            case 5: {
                reservationManager.displayActiveReservations();
                break;
            }
            case 6: {
                waitlist.displayWaitlist();
                break;
            }
            case 7: {
                Reservation restored;
                if (historyStack.pop(restored)) {
                    std::cout << "Restoring reservation for " << restored.studentName
                              << " (Resource ID " << restored.resourceID << ", Qty "
                              << restored.quantity << ")...\n";
                    
                    
                    reservationManager.createReservation(restored.resourceID, restored.studentName,
                                                           restored.quantity, resourceManager, waitlist);
                } else {
                    std::cout << "Nothing to undo.\n";
                }
                break;
            }
            case 8: {
                historyStack.displayHistory();
                break;
            }
            case 9: {
                running = false;
                std::cout << "Exiting. Goodbye!\n";
                break;
            }
            default: {
                std::cout << "Invalid option. Please choose 1-9.\n";
                break;
            }
        }
    }
 
    return 0;
}
  