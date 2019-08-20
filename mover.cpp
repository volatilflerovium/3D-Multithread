/*********************************************************************
* Mover class	                               								*
*                                                                    *
* Version: 1.0                                                       *
* Date:    20-08-2019                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/

#include "mover.h"
#include "master.h"

mutex Mover::dwmtx;

Mover::Mover(Shape** _shp, int mx, int _id)
	:shp(_shp), max(mx), id(_id)
{
	ulock=unique_lock<mutex>(mtx);
}

void Mover::runner(){
	while(running){
		while(!ready){
			cv.wait(ulock, [this]{
				return this->ready;
			});
		}

		if(stop){
			break;
		}

		for(int i=0; i<max; ++i){
			shp[i]->move(2.0);
			if(shp[i]->updateEdges()){
				dwmtx.lock();
				shp[i]->draw();
				dwmtx.unlock();
			}
		}
		Master::wake(id);
		ready=false;
	}
}

