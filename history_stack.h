#ifndef HISTORY_STACK_H
#define HISTORY_STACK_H
 
#include "structures.h"
 

struct HistoryNode {
    Reservation data;   
    HistoryNode* next;
};
 
class HistoryStack {
private:
    HistoryNode* top;
    int size;
 
public:
    HistoryStack();
    ~HistoryStack();
 
    
    void push(const Reservation& res);
 
    
    
    bool pop(Reservation& restored);
 
    
    void displayHistory() const;
 
    bool isEmpty() const;
    int getSize() const;
};


  
#endif