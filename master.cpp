/*********************************************************************
* Master class                               								*
*                                                                    *
* Version: 1.0                                                       *
* Date:    20-08-2019                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#include "master.h"
#include "mover.h"

//####################################################################
//####################################################################

mutex Master::mtx;
unique_lock<mutex> Master::ulock=unique_lock<mutex>(Master::mtx);
condition_variable Master::cv;
bool Master::wait=true;
bool Master::ready=false;
std::vector<bool> Master::AXD;
std::vector<std::thread> Master::Threads;
std::vector<Mover*> Master::Movers;


//####################################################################

void Master::registerMover(Shape** _shp, int mx){
	Mover* tmp=new Mover(_shp, mx, Movers.size());
	AXD.push_back(false);
	Movers.push_back(tmp);
	Threads.push_back(std::thread(&Mover::runner, tmp));
}

void Master::wake(int id){
	mtx.lock();
	AXD[id]=true;
	ready=true;
	for(int i=0; i<AXD.size(); i++){
		ready=ready && AXD[i];
	}
	if(ready){
		cv.notify_one();
	}
	mtx.unlock();
}

void Master::awake(){
	for(int i=0; i<Movers.size(); i++){
		Movers[i]->notify();
	}
}

void Master::waiting(){
	while(!ready){
		cv.wait(ulock, []{
			return Master::ready;
		});
	}
	ready=false;
	for(int i=0; i<Movers.size(); i++){
		AXD[i]=false;
	}
}


void Master::stop(){
	for(int i=0; i<Movers.size(); i++){
		Movers[i]->stopping();
		if(Threads[i].joinable()){
			Threads[i].join();
		}
		delete Movers[i];
	}
}
