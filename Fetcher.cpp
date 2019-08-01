// Fetcher.cpp
// Kingsley Bowen

#include <iostream>
#include "Fetcher.h"
using namespace std;

Fetcher::Fetcher(){
    queue = new OrderQueue;
}

Fetcher::~Fetcher(){
    delete queue;
}

// fills the Fetcher queue with Order from Parser
void Fetcher::acceptOrder(Order o){
    queue->enqueue(o);
}

// decrements the fetch_time left, puts the updated Order into Fetcher queue
bool Fetcher::update(){
    //make sure we have an order to work on
    if(queue->size() <= 0){
        return false;
    }

    //update values of first order
    Order currentOrder = queue->first();
    currentOrder.fetch_time_left--;
    queue->updateFirstOrder(currentOrder);

    //return true if current order just finished
    if(currentOrderDone()){
        return true;
    }
    return false;
}

// returns true if the current Order's fetch time reaches 0
bool Fetcher::currentOrderDone(){
    Order currentOrder = queue->first();
    return currentOrder.fetch_time_left == 0;
}

// returns the first Order in the queue
Order Fetcher::dropOff(){
    return queue->dequeue();
}

// returns the size of the Orderqueue
int Fetcher::numOrders(){
    return queue->size();
}
