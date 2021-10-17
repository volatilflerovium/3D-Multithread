#ifndef MASTER_SLAVE_H
#define MASTER_SLAVE_H
#include <thread>
#include <mutex>
#include <condition_variable>

#include"shape.h"

class Slave;

class Master
{
	public:
		static void registerSlave(Slave* slave);
		static void go();
		static void sleep();
		static void workDone(int id);
		static void wakeUpSlaves();
		static void waiting();
		static void stop();

	private:
		static mutex m_controlMutex;
		static mutex m_mtx;
		static unique_lock<mutex> m_ulock;
		static condition_variable m_cv;
		static std::vector<Slave*> m_slaves;
		static std::vector<std::thread*> m_threads;
		static std::vector<bool> m_slaveStatus;
		static bool m_ready;
};

//####################################################################
//####################################################################

class Slave
{
	public: 
		Slave();
		void addShape(Shape* shape);
		void setID(int id);
		void run();
		void notify();
		void stop();

	private:
		mutex m_mtx;
		unique_lock<mutex> m_ulock;
		condition_variable m_cv;
	
		std::vector<Shape*> m_shapes;
		int m_id;
		bool m_wait;
		bool m_running;
};

//======================================================================


inline Slave::Slave()
:m_ulock(unique_lock<mutex>(m_mtx)),
m_id(-1), m_wait(false), m_running(true)
{}

//======================================================================

inline void Slave::setID(int id){
	if(m_id<0){
		m_id=id;
	}
}

//======================================================================

inline void Slave::stop(){
	m_running=false;
	notify();
}

//======================================================================

inline void Slave::notify(){
	m_wait=true;
	m_cv.notify_one();
}

//======================================================================

inline void Slave::addShape(Shape* shape){
	m_shapes.push_back(shape);
}


#endif
