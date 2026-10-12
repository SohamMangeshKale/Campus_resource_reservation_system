Campus Resource Reservation System

A menu-driven C++ console application for reserving shared campus resources such as study rooms, projectors, laptop carts and conference rooms. The project is built from scratch around core data structures and algorithms: linked lists, a queue, a stack, merge sort and binary search. It uses no STL containers for its main structures.

Features
View resources: list all resources with total and available units, or check availability of one resource
Create reservations: reserve a quantity of units for a student; availability is updated immediately
Waitlist: if there aren't enough units available, the student is added to a first-come-first-served waitlist instead
Cancel reservations: frees the units and saves the cancelled reservation to a history
Undo last cancellation: restores the most recently cancelled reservation
Cancellation history: view cancelled reservations, most recent first
Search: find a reservation by ID (linear search) or a resource by ID (binary search)
Sort: display resources alphabetically by name (merge sort)
Reports: resource utilization, most requested resources, and waitlist statistics
File loading: resources and existing reservations are loaded from text files at startup
Input validation: invalid menu input and invalid quantities or resource IDs are rejected
Data Structures and Algorithms Used
Feature	Data Structure / Algorithm	Complexity
Active reservations	Singly linked list (insert at head)	Insert O(1), find/cancel O(n)
Waitlist	Queue (linked list with front and rear pointers)	Enqueue/dequeue O(1)
Cancellation history / undo	Stack (linked list)	Push/pop O(1)
Resource storage	Fixed-size array (max 100 resources)	Lookup O(n)
Sort resources by name or ID	Merge sort	O(n log n)
Search resource by ID	Binary search on sorted array	O(log n)
Search reservation by ID	Linear search	O(n)
Most requested report	Selection sort on reservation counts	O(n²)
Project Structure
Campus_resource_reservation_system/
├── main.cpp                   # Menu and program entry point
├── structures.h               # Resource, Reservation, WaitlistEntry structs
├── resource_manager.h/.cpp    # Loads resources, tracks availability
├── reservation_manager.h/.cpp # Linked list of reservations (create/cancel/search)
├── waitlist.h/.cpp            # Queue for waitlisted requests
├── history_stack.h/.cpp       # Stack for cancelled reservations (undo)
├── sorter.h/.cpp              # Merge sort and binary search
├── report_manager.h/.cpp      # Utilization, popularity and waitlist reports
├── resources.txt              # Input: resources
├── reservations.txt           # Input: existing reservations
└── README.md
Requirements
A C++ compiler with C++11 support or later (g++, clang++, or MSVC)
Build and Run

Clone the repository:

bash
git clone https://github.com/SohamMangeshKale/Campus_resource_reservation_system.git
cd Campus_resource_reservation_system

Compile:

bash
g++ -std=c++11 -o campus *.cpp

Run (from the project folder, so the .txt files are found):

bash
./campus          # Linux / macOS
campus.exe        # Windows
Input File Formats

resources.txt: one resource per line: id,name,totalUnits

1,Study Room 111,3
2,Study Room 112,2
3,Projector B3,1
4,Laptop Cart,5
5,Conference Room B,1

reservations.txt: one reservation per line: resourceID,studentName,quantity

1,Rajiv,1
4,Soham,2

Each line in reservations.txt goes through the normal reservation flow at startup, so if a resource is full, the extra requests are placed on the waitlist.

Menu
==== Campus Resource Reservation System ===
1.  Display all resources
2.  Display availability for a resource
3.  Create a reservation
4.  Cancel a reservation
5.  Display active reservations
6.  Display waitlist
7.  Undo last cancellation
8.  Display cancellation history
9.  Search for a reservation by ID (Linear Search)
10. Sort and display resources by name (Merge Sort)
11. Search for a resource by ID (Binary Search)
12. Report: Resource utilization
13. Report: Most requested resources
14. Report: Waiting-list statistics
15. Exit
Example Session
Choose an option: 3
Enter resource ID: 1
Enter student name (no spaces): Amit
Enter quantity: 2
Reservation has been created, ID:3

Choose an option: 3
Enter resource ID: 1
Enter student name (no spaces): Bob
Enter quantity: 1
Not enough availability. Adding Bob to the waitlist for Study Room 111.
Known Limitations
Data is held in memory only. Reservations made while the program runs are not saved back to reservations.txt.
Student names must not contain spaces.
Waitlisted students are not automatically promoted when a reservation is cancelled.
Maximum of 100 resources.
Reservations have no date or time slot; they are quantity-based.
Future Improvements
Save reservations to file on exit
Automatically promote waitlisted students when units are freed
Support names with spaces
Add date and time slots to reservations
Add user roles (student / admin)
