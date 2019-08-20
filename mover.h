/*********************************************************************
* Mover class    	                           								*
*                                                                    *
* Version: 1.0                                                       *
* Date:    20-08-2019                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/

#ifndef MOVER_H
#define MOVER_H

#include<mutex>
#include<condition_variable>

#include "shape.h"

class Mover
{
	private:
		static mutex dwmtx;
	private:
		mutex mtx;
		condition_variable cv;
		unique_lock<mutex> ulock;
		Shape** shp;
		int max;
		int id;
		bool running=true;
		bool ready=false;
		bool stop=false;

	public:
		Mover(Shape** _shp, int mx, int _id);
		void runner();
		void notify();
		void stopping();
};

inline void Mover::notify(){
	ready=true;
	cv.notify_one();
}

inline void Mover::stopping(){
	stop=true;
	notify();
}


#endif