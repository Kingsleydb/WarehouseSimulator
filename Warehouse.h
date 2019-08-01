// Warehouse.h
// Kingsley Bowen
// Warehouse's Design Purpose: The Warehouse class holds instances of one 
// fetcher, some packagers, and four OrderQueues. Warehouse contains the main
// run loop. The warehouse also keeps track of time. The packager is given an
// OrderQueues, which is a queue of order structs. The packagers package the 
// orders by one of three methods: FEWEST_ITEMS, SHORTEST_TIME, or ROUND_ROBIN.
#ifndef WAREHOUSE_H
#define WAREHOUSE_H
#include <iostream>
#include "Orderqueue.h"
#include "Packager.h"
#include "Fetcher.h"
using namespace std;

class Warehouse {
public:
    Warehouse(); // Warehouse Constructor
    Warehouse(int numPackagers);
    ~Warehouse(); // Warehouse Destructor
    void run(string filename, string mode, int numPackagers); // run loop that
    // packages and 

    
private:
    Fetcher *fetcher; // instance of fetcher 
    Packager *packagers; // instance of packagers
    void read_file(string filename);
    int totalOrders;
    OrderQueue *ordersNotArrived;   // orders not arrived
    OrderQueue *ordersPackaged;     // orders fetched and packaged
    int leastRecentlyUsed;
    int pickPackager(string mode, int numPackagers);
    int fewestItemsPick(int numElements); // 
    int shortestTimePick(int numElements);
    int roundRobinPick(int numElements);

    void shipOrder(Order o, int time);

    int minElapsedTime;
    int maxElapsedTime;
    int sumElapsedTime;

    void finalReport();
};

#endif