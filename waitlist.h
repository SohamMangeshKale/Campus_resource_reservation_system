#ifndef WAITLIST_H
#define WAITLIST_H
 
#include "structures.h"
#include <string>
 

struct WaitlistNode {
    WaitlistEntry data;
    WaitlistNode* next;
};
 

class Waitlist {
private:
    WaitlistNode* front;
    WaitlistNode* rear;
    int size;
 
public:
    Waitlist();
    ~Waitlist();
 
    
    void addToWaitlist(int resourceID, const std::string& studentName, int quantity);
 
    
    bool removeFromWaitlist(WaitlistEntry& removedEntry);
 
    
    void displayWaitlist() const;
 
    bool isEmpty() const;
    int getSize() const;
};
 
#endif
 