// OrderQueue.cpp
// Kingsley Bowen

#include <iostream>
#include "Orderqueue.h"
using namespace std;

// OrderQueue constructor
OrderQueue::OrderQueue(){
	numElements = 0;
	capacity = INIT_CAPACITY;
	front = 0; 
	back = 0;

	orders = new Order[INIT_CAPACITY];
}

// OrderQueue destructor
OrderQueue::~OrderQueue(){
	delete [] orders;
}

// adds an order to the back of the queue, expanding if necessary
void OrderQueue::enqueue(Order o){
	if (back >= capacity) resize();
	orders[back] = o;
	back++;
	numElements++;
}

// removes an order from the front of the queue and returns the order
// Throws an exception if the queue is empty
Order OrderQueue::dequeue(){
	ensureNotEmpty();
	Order returnValue = orders[front];
	front++;	
	if (front == back){
		front = 0;
		back = 0;
	}

	numElements--;
	return returnValue;
}

// returns true if the number of orders is empty
bool OrderQueue::isEmpty(){
	return numElements == 0;
}

// Throws a runtime exception if client tries to dequeue from an empty
// order queue.
void OrderQueue::ensureNotEmpty(){
	if (isEmpty()){
		throw runtime_error ("Empty Queue!");
	}
}

// creates a bigger array with twice the capacity for order queue
void OrderQueue::resize(){
	Order* newArray = new Order[numElements*2];
	for (int i = 0; i < numElements; i++){
		newArray[i] = orders[i + front];
	}
	delete [] orders;
	orders = newArray;
	capacity = numElements*2;

	front = 0;
	back = numElements;
}

// returns but leaves in place the first order
Order OrderQueue::first(){
	return orders[front];
}

// fills in the queue
// throws an exception if there is no order to update
void OrderQueue::updateFirstOrder(Order o){
	ensureNotEmpty();
	orders[front] = o;
}

// returns the number of queue elements
int OrderQueue::size(){
	return numElements;
}

// calculates and returns the total pack time
int OrderQueue::totalPackTime(){
	int sumPackTime = 0;
	for(int i=front; i<back; i++){
		sumPackTime += orders[i].pack_duration;
	}
	return sumPackTime;
}
