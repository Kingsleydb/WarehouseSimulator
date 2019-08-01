// OrderQueue.h
// Kingsley Bowen
// OrderQueues's Design Purpose: The OrderQueue is a queue of Order structs. 
// The OrderQueue is a class within the Warehouse class. The OrderQueue gets 
// passed between the fetcher, packager, and warehouse classes. 
#ifndef ORDERQUEUE_H
#define ORDERQUEUE_H
#include <iostream>
#include "Order.h"
using namespace std;

const int INIT_CAPACITY = 3;

class OrderQueue{
public:
	OrderQueue(); // constructor of Queue of struct Orders
	~OrderQueue(); // destructor of Queue of struct Orders

	void enqueue(Order o); // adds an order to the back of the queue
	Order dequeue(); // removes an order from the front of the queue
	Order first(); //returns but leaves in place the first order
	void updateFirstOrder(Order o); //replaces the first order with order o

	bool isEmpty(); // Returns true if number of Orders is zero
	int size(); //Returns numElements

	int totalPackTime(); //returns the sum of pack_times


private:
	// number of orders in a queue
	int numElements; 
	// capacity of array of orders
	int capacity; 
	// front of orders in a queue 
	int front; 
	// back of orders in a queue
	int back;
	// creates a bigger array with twice the capacity for order queue
	void resize(); 
	// Throws a runtime Exception if client tries to dequeue from an empty
	// order queue.
	void ensureNotEmpty(); 

	Order *orders; // declaration of a pointer to orders

};

#endif