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
 
int main() {}  //anshika start here