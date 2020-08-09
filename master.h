/*********************************************************************
* Master class                               								*
*       		                                                         *
* Version: 1.0                                                       *
* Date:    20-08-2019                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#ifndef MASTER_H
#define MASTER_H

#include<thread>
#include<mutex>
#include<condition_variable>

#include "shape.h"

using namespace std;

class Mover;

class Master
{
	private:
		static mutex mtx;
		static unique_lock<mutex> ulock;
		static condition_variable cv;
		static bool wait;
		static bool ready;
		static std::vector<bool> AXD;
		static std::vector<std::thread> Threads;
		static std::vector<Mover*> Movers;

	public:
		static void registerMover(Shape** _shp, int mx);
		static void wake(int id);
		static void waiting();
		static void stop();
		static void awake();
};


//####################################################################
//####################################################################


#endif