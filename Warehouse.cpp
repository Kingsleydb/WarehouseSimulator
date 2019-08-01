// Warehouse.cpp
// Kingsley Bowen

#include <iostream>
#include "Warehouse.h"
#include "Parser.h"
#include "string2int.h"

using namespace std;

void testReadFile();

// Warehouse constructor
Warehouse::Warehouse(){		
	fetcher = new Fetcher;
	packagers = NULL;
    ordersNotArrived = new OrderQueue;
	ordersPackaged = new OrderQueue;
	leastRecentlyUsed = 0;
	sumElapsedTime = 0;
	// minElapsedTime = 9999; // initialized in readfile
	maxElapsedTime = 0;
}

// Warehouse constructor with a specified number of packagers
Warehouse::Warehouse(int numPackagers){		
	fetcher = new Fetcher;
	packagers = new Packager[numPackagers];
    ordersNotArrived = new OrderQueue;
	ordersPackaged = new OrderQueue;
	leastRecentlyUsed = 0;
	// minElapsedTime = 9999; // initialized in readfile
	maxElapsedTime = 0;
}

// Warehouse destructor
Warehouse::~Warehouse(){
	delete fetcher;
	delete [] packagers;
	delete ordersNotArrived;
	delete ordersPackaged;
}

// main loop that fetches and packages orders
void Warehouse::run(string filename, string mode, int numPackagers){
	int	currentTime = 0;
	read_file(filename);	//fills ordersNotArrived OrderQueue
	//warehouse operation loop
	while(ordersPackaged->size() < totalOrders){ 
		//check if the packager finished		
		for (int i = 0; i < numPackagers; i++){
			if(packagers[i].update()){
				Order packagedOrder = packagers[i].dropOff();
				ordersPackaged->enqueue(packagedOrder);
				shipOrder(packagedOrder, currentTime);
			}
		}

		//check if the fetcher is finished fetching
		if(fetcher->update()){
			Order fetchedOrder = fetcher->dropOff();
			int index = pickPackager(mode, numPackagers);
			packagers[index].acceptOrder(fetchedOrder);
		}
		
		if(!ordersNotArrived->isEmpty()){ // checks if package has arrived
			Order nextToArrive = ordersNotArrived->first();
			while(currentTime == nextToArrive.arrival_timestamp){
				//move order to fetcher and look at next order
				fetcher->acceptOrder(ordersNotArrived->dequeue());
				nextToArrive = ordersNotArrived->first();
			}
		}
		currentTime++;
	}	
	finalReport();
}

// takes in Order information and fills in ordersNotArrived Orderqueue
void Warehouse::read_file(string filename){
	string f = filename;
	Parser p(f);

	int numOrders = 0;
	while(!p.is_done()){
		Order nextOrder = p.read_order();
		ordersNotArrived->enqueue(nextOrder);
		if(numOrders == 0){
			//initialize minElapsedTime
			minElapsedTime = nextOrder.fetch_duration + 
			nextOrder.pack_duration + 50; // worried about picking too low not
										  // too high
		}
		numOrders++;
	}
	totalOrders = numOrders;
}

// Decides which packager to use depending on client choice
// returns the index of the packager to use
int Warehouse::pickPackager(string mode, int numPackagers){
	if(mode == "FEWEST_ITEMS"){
		return fewestItemsPick(numPackagers);
	}
	else if(mode == "SHORTEST_TIME"){
		return shortestTimePick(numPackagers);
	}
	else if (mode == "ROUND_ROBIN"){
		return roundRobinPick(numPackagers);
	}
	else return 0; 
}

// reads in command line input
int main(int argc, char* argv[]){
	Warehouse w(string2int(argv[2]));
	w.run(argv[1], argv[3], string2int(argv[2]));
}

// determines and returns index of the packager that has the index with the
// fewest items in its queue
int Warehouse::fewestItemsPick(int numPackagers){
	int index = 0;
	int fewestItems = packagers[0].numOrders();

	for(int i=1; i<numPackagers; i++){
		if(packagers[i].numOrders() < fewestItems){
			fewestItems = packagers[i].numOrders();
			index = i;
		}
	}
	return index;
}

// determines and returns the index of the packager with the shortest 
// packing time in its queue 
int Warehouse::shortestTimePick(int numPackagers){
	int index = 0;
	int shortestTime = packagers[0].totalTime();

	for(int i=1; i<numPackagers; i++){
		if(packagers[i].totalTime() < shortestTime){
			shortestTime = packagers[i].totalTime();
			index = i;
		}
	}
	return index;
}

// returns the index of the packager that has least recently been used
int Warehouse::roundRobinPick(int numPackagers){
	int index = leastRecentlyUsed;
	leastRecentlyUsed = (leastRecentlyUsed + 1) % numPackagers;
	return index;
}

// print out order in expected format
void Warehouse::shipOrder(Order o, int time){
	int elapsed_time = time - o.arrival_timestamp;

	cout << "<Order(" << o.id << ") " << " arrival_timestamp = "
	<< o.arrival_timestamp << " fetch_duration = " << o.fetch_duration
	<< " pack_duration = " << o.pack_duration << " total_time = "
	<< elapsed_time << ">" << endl;

	
	sumElapsedTime += elapsed_time;
	if (elapsed_time > maxElapsedTime) maxElapsedTime = elapsed_time;
	if (elapsed_time < minElapsedTime) minElapsedTime = elapsed_time;

}

// prints out final calculations of orders
void Warehouse::finalReport(){
	cout << "min elapsed time " << minElapsedTime << " minutes" << endl;
	cout << "max elapsed time " << maxElapsedTime << " minutes" << endl;
	cout << "mean elapsed_time " << sumElapsedTime/totalOrders << " minutes"
	<< endl;
	cout << totalOrders << " orders processed" << endl;
}