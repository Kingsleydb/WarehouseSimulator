// Fetcher.h
// Kingsley Bowen
// 
// Fetcher's Design Purpose: The Fetcher is a class within the Warehouse
// class. It is the Fetcher's role to accepts packages as they arrive, fetch
// the orders in arrival order, and passes them back to the warehouse to
// choose the appropriate packager. 
// 

#ifndef FETCHER_H
#define FETCHER_H
#include <iostream>
#include "Order.h"
#include "Orderqueue.h"
using namespace std;

class Fetcher{
public:
	Fetcher(); // constructor of Fetcher
	~Fetcher(); // destructor of Fetcher

    void acceptOrder(Order o); // takes order puts on queue
	bool update(); // does work on current order e.g. calculate and change 
                     // time stamps
    Order dropOff(); // called when the currentOrder is done, removes and
                     // returns it
    int numOrders();


private:
	OrderQueue *queue; // Instance of OrderQueue
	bool currentOrderDone();

};

#endif