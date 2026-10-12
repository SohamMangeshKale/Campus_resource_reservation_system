#include <iostream>
#include <string>
#include <limits>
#include "resource_manager.h"
#include "reservation_manager.h"
#include "waitlist.h"
#include "history_stack.h"
#include "sorter.h"
#include "report_manager.h"

void printMenu() {
    std::cout << "\n==== Campus Resource Reservation System ===\n";
    std::cout << "1. Display all resources\n";
    std::cout << "2. Display availability for a resource\n";
    std::cout << "3. Create a reservation\n";
    std::cout << "4. Cancel a reservation\n";
    std::cout << "5. Display active reservations\n";
    std::cout << "6. Display waitlist\n";
    std::cout << "7. Undo last cancellation\n";
    std::cout << "8. Display cancellation history\n";
    std::cout << "9. Search for a reservation by ID (Linear Search)\n";
    std::cout << "10. Sort and display resources by name (Merge Sort)\n";
    std::cout << "11. Search for a resource by ID (Binary Search)\n";
    std::cout << "12. Report: Resource utilization\n";
    std::cout << "13. Report: Most requested resources\n";
    std::cout << "14. Report: Waiting-list statistics\n";
    std::cout << "15. Exit\n";
    std::cout << "Choose an option: ";
}

// Clear bad input 
void clearInputError() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    ResourceManager resourceManager;
    ReservationManager reservationManager;
    Waitlist waitlist;
    HistoryStack historyStack;
    ReportManager reportManager;

    if (!resourceManager.loadFromFile("resources.txt")) {
        std::cout << "Warning: continuing with no resources loaded.\n";
    }

    // Load any existng reservations
    reservationManager.loadReservationsFromFile("reservations.txt", resourceManager, waitlist);

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
                if (!(std::cin >> id)) { 
                std::cout << "Invalid input.\n"; 
                clearInputError();
                break; 
                }
                resourceManager.displayAvailability(id);
                break;
            }

            case 3: {
                int id, qty;
                std::string name;
                std::cout << "Enter resource ID: ";
                if (!(std::cin >> id)) {
                    std::cout << "Invalid input.\n";
                    clearInputError();
                    break; }
                std::cout << "Enter student name (no spaces): ";
                std::cin >> name;
                std::cout << "Enter quantity: ";
                if (!(std::cin >> qty)) {
                    std::cout << "Invalid input.\n";
                    clearInputError();
                    break; 
                }

                reservationManager.createReservation(id, name, qty, resourceManager, waitlist);
                break;
            }

            case 4: {
                int resID;
                std::cout << "Enter reservation ID to cancel: ";
                if (!(std::cin >> resID)) {
                    std::cout << "Invalid input.\n";
                    clearInputError();
                    break; 
                }
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
                    std::cout << "Restoring reservation for " << restored.studentName << " (Resource ID " << restored.resourceID << ", Qty " << restored.quantity << ")...\n";
                    reservationManager.createReservation(restored.resourceID, restored.studentName, restored.quantity, resourceManager, waitlist);
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
                
                int resID;
                std::cout << "Enter reservation ID to search for: ";
                if (!(std::cin >> resID)) { 
                    std::cout << "Invalid input.\n";
                    clearInputError(); 
                    break; 
                }

                Reservation* found = reservationManager.findReservation(resID);
                if (found != nullptr) {
                    std::cout << "Found - Reservation ID: " << found->reservationID<< " | Resource ID: " << found->resourceID<< " | Student: " << found->studentName << " | Quantity: " << found->quantity << std::endl;
                } else {
                    std::cout << "No reservation found with ID " << resID << ".\n";
                }
                break;
            }
            case 10: {
               
                int total = resourceManager.getCount();
                if (total == 0) {
                    std::cout << "No resources loaded.\n";
                    break;
                }
                Resource* sorted = new Resource[total];
                for (int i = 0; i < total; i++) {
                    sorted[i] = resourceManager.getResourceAt(i);
                }
                mergeSortByName(sorted, total);

                std::cout << "\n--- Resources sorted by name ---\n";
                for (int i = 0; i < total; i++) {
                    std::cout << sorted[i].name << " (ID " << sorted[i].id << ", Available " << sorted[i].availableUnits<< "/" << sorted[i].totalUnits << ")\n";
                }
                delete[] sorted;
                break;
            }
            case 11: {

                int total = resourceManager.getCount();
                if (total == 0) {
                    std::cout << "No resources loaded.\n";
                    break;
                }


                int targetID;
                std::cout << "Enter resource ID to search for: ";

                if (!(std::cin >> targetID)) {
                    std::cout << "Invalid input.\n";
                    clearInputError();
                    break;
                }

                Resource* sorted = new Resource[total];
                for (int i = 0; i < total; i++) {
                    sorted[i] = resourceManager.getResourceAt(i);
                }
                mergeSortByID(sorted, total);

                int index = binarySearchByID(sorted, total, targetID);
                if (index != -1) {
                    std::cout << "Found - " << sorted[index].name<< " (Available " << sorted[index].availableUnits << "/" << sorted[index].totalUnits << ")\n";
                } else {
                    std::cout << "No resource found with ID " << targetID << ".\n";
                }
                delete[] sorted;
                break;
            }

            case 12: {
                reportManager.reportResourceUtilization(resourceManager, reservationManager);
                break;
            }

            case 13: {
                reportManager.reportMostRequestedResources(resourceManager, reservationManager);
                break;
            }

            case 14: {
                reportManager.reportWaitlistStatistics(resourceManager, waitlist);
                break;
            }

            case 15: {
                running = false;
                std::cout << "Exiting. Goodbye!\n";
                break;
            }

            default: {
                std::cout << "Invalid option. Please choose 1-15.\n";
                break;
            }

        }

    }


    return 0;
}