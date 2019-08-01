// Packager.cpp
// Kingsley Bowen

#include <iostream>
#include "Packager.h"
using namespace std;

// Packager constructor
Packager::Packager(){
    queue = new OrderQueue;
}

// Packager destructor
Packager::~Packager(){
    delete queue;
}

// takes in Order from Fetcher queue
void Packager::acceptOrder(Order o){ // not done
    queue->enqueue(o);
}

// returns true if there is an order that is packed
bool Packager::update(){
	//make sure we have an order to work on
	if(queue->size() <= 0){
		return false;
	}

	//update values of first order
	Order currentOrder = queue->first();
	currentOrder.pack_time_left--;
	queue->updateFirstOrder(currentOrder);

	//return true if current order just finished
	if(currentOrderDone()){
		return true;
	}
	return false;
}

// returns true if the current Order's pack time remaining is zero
bool Packager::currentOrderDone(){
	Order currentOrder = queue->first();
	return currentOrder.pack_time_left == 0;
}

// returns the Order at the front of the Orderqueue
Order Packager::dropOff(){
	return queue->dequeue();
}

// return the number of elements in the Orderqueue
int Packager::numOrders(){
    return queue->size();
}

// calculates the total time it takes per order
int Packager::totalTime(){
	return queue->totalPackTime();
}
