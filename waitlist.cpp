#include "waitlist.h"
#include <iostream>
 
Waitlist::Waitlist() {
    front = nullptr;
    rear = nullptr;
    size = 0;
}
 
Waitlist::~Waitlist() {
    WaitlistNode* current = front;
    while (current != nullptr) {
        WaitlistNode* toDelete = current;
        current = current->next;
        delete toDelete;
    }
}
 
void Waitlist::addToWaitlist(int resourceID, const std::string& studentName, int quantity) {
    WaitlistNode* newNode = new WaitlistNode;
    newNode->data.resourceID = resourceID;
    newNode->data.studentName = studentName;
    newNode->data.quantity = quantity;
    newNode->next = nullptr;
 
    if (rear == nullptr) {
        front = newNode;
        rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    size++;
}
 
bool Waitlist::removeFromWaitlist(WaitlistEntry& removedEntry) {
    if (front == nullptr) {
        return false; 
    }
 
    WaitlistNode* toRemove = front;
    removedEntry = toRemove->data;
 
    front = front->next;
    if (front == nullptr) {
        rear = nullptr; // queue is now empty
    }
 
    delete toRemove;
    size--;
    return true;
}
 
void Waitlist::displayWaitlist() const {
    if (front == nullptr) {
        std::cout << "Now showing Waitlist is empty.\n";
        return;
    }
 
    std::cout << "\n--- Waitlist (front to back) ---\n";
    WaitlistNode* current = front;
    int position = 1;
    while (current != nullptr) {
        std::cout << position << ". " << current->data.studentName << " | Resource ID: " << current->data.resourceID << " | Quantity: " << current->data.quantity << std::endl;
        current = current->next;
        position++;
    }
}
 
bool Waitlist::isEmpty() const {
    return front == nullptr;
}
 
int Waitlist::getSize() const {
    return size;
}
 