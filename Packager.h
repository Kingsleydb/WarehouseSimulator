// Packager.h
// Kingsley bowen
//
// Packager's Design Purpose: The Packager is a class within the Warehouse 
// Class. The Packager accepts, packages, and updates the time stamps of the
// orders. 
#ifndef PACKAGER_H
#define PACKAGER_H

#include <iostream>
#include "Orderqueue.h"
#include "Order.h"
using namespace std;

class Packager{
public:
    Packager(); // Packager constructor 
    ~Packager(); // Packager destructor

    void acceptOrder(Order o); // Takes order puts on queue
	bool update(); // Does work on current order e.g. calculate and change
                     // timestamps
    Order dropOff(); // called when the currentOrder is done, removes and
                     // returns it
	void testPrintQueue();
    int numOrders();
    int totalTime(); //returns the sum of pack_time_left

private:
    OrderQueue *queue; // Instance of a pointer to an OrderQueue

    bool currentOrderDone(); // returns true if the Order's pack remaining is 
                             // is zero
};

#endif