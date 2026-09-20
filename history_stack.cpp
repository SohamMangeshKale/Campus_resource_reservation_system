#include "history_stack.h"
#include <iostream>
 
HistoryStack::HistoryStack() {
    top = nullptr;
    size = 0;
}
 
HistoryStack::~HistoryStack() {
    HistoryNode* current = top;
    while (current != nullptr) {
        HistoryNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}
 
void HistoryStack::push(const Reservation& res) {
    HistoryNode* newNode = new HistoryNode;
    newNode->data = res;
    newNode->data.next = nullptr; 
    newNode->next = top;
    top = newNode;
    size++;
}
 
bool HistoryStack::pop(Reservation& restored) {
    if (top == nullptr) {
        return false; 
    }
 
    HistoryNode* toRemove = top;
    restored = toRemove->data;
 
    top = top->next;
    delete toRemove;
    size--;
    return true;
}
 
void HistoryStack::displayHistory() const {
    if (top == nullptr) {
        std::cout << "Cancellation history is empty.\n";
        return;
    }
 
    std::cout << "\n--- Cancellation History (most recent first) ---\n";
    HistoryNode* current = top;
    while (current != nullptr) {
        std::cout << "Reservation ID: " << current->data.reservationID << " | Resource ID: " << current->data.resourceID << " | Student: " << current->data.studentName << " | Quantity: " << current->data.quantity << std::endl;
        current = current->next;
    }
}
 
bool HistoryStack::isEmpty() const {
    return top == nullptr;
}
 
int HistoryStack::getSize() const {
    return size;
}
 