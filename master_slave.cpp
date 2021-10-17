#include "master_slave.h"

//====================================================================

std::mutex Master::m_controlMutex;
std::mutex Master::m_mtx;
std::unique_lock<mutex> Master::m_ulock=unique_lock<mutex>(m_mtx);
std::condition_variable Master::m_cv;
std::vector<Slave*> Master::m_slaves;
std::vector<std::thread*> Master::m_threads;
std::vector<bool> Master::m_slaveStatus;
bool Master::m_ready(false);

//======================================================================

void Slave::run(){
	while(m_running){
		while(!m_wait){
			m_cv.wait(m_ulock, [this]{return this->m_wait;});
		}	

		if(!m_running){
			break;
		}
		
		for(int i=0; i<m_shapes.size(); i++){
			m_shapes[i]->rotate();
			m_shapes[i]->move(2.0);
			m_shapes[i]->preDraw();
		}

		m_wait=false;
		Master::workDone(m_id);
	}
}

//####################################################################
//####################################################################

void Master::registerSlave(Slave* tmp){
	m_slaveStatus.push_back(false);
	m_slaves.push_back(tmp);
	tmp->setID(m_slaves.size()-1);
	m_threads.push_back(new std::thread(&Slave::run, tmp));
}

//======================================================================

void Master::workDone(int id){
	m_mtx.lock();
	m_slaveStatus[id]=true;
	m_ready=true;
	for(int i=0; i<m_slaveStatus.size(); i++){
		m_ready=m_ready && m_slaveStatus[i];
	}
	if(m_ready){
		m_cv.notify_one();
	}
	m_mtx.unlock();
}

//======================================================================

void Master::wakeUpSlaves(){
	for(int i=0; i<m_slaves.size(); i++){
		m_slaves[i]->notify();
	}
}

//======================================================================

void Master::waiting(){
	while(!m_ready){
		m_cv.wait(m_ulock, []{
			return Master::m_ready;
		});
	}
	m_ready=false;
	for(int i=0; i<m_slaves.size(); i++){
		m_slaveStatus[i]=false;
	}
}

//======================================================================

void Master::stop(){
	for(int i=0; i<m_slaves.size(); i++){
		m_slaves[i]->stop();
		if(m_threads[i]->joinable()){
			m_threads[i]->join();
		}
		delete m_slaves[i];
		delete m_threads[i];
	}
}

//======================================================================
