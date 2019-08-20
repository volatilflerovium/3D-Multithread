#include<iostream>
#include<cmath>
#include<cstdlib>
#include<ctime>
#include<SFML/Graphics.hpp>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<csignal>

#include "helper.h"
#include "base.h"
#include "framerate.h"
#include "noise.h"
#include "rspace.h"
#include "vector.h"
#include "shape.h"
#include "camera.h"
#include "platonic.h"

#include "mover.h"
#include "master.h"

using namespace std;

mutex gMtx;

//####################################################################
//####################################################################
//####################################################################

/*

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

mutex Master::mtx;
unique_lock<mutex> Master::ulock=unique_lock<mutex>(Master::mtx);
condition_variable Master::cv;
bool Master::wait=true;
bool Master::ready=false;
std::vector<bool> Master::AXD;
std::vector<std::thread> Master::Threads;
std::vector<Mover*> Master::Movers;

//####################################################################
//####################################################################

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


void Mover::notify(){
	ready=true;
	cv.notify_one();
}

void Mover::stopping(){
	stop=true;
	notify();
}

//####################################################################
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

/**/
//####################################################################
//####################################################################
//####################################################################
//####################################################################

int main(){
//	signal(SIGINT, &sigint_handler);

	condition_variable cv;
	mutex mtx;
	unique_lock<mutex> ulock;
	ulock=unique_lock<mutex>(mtx);

	Shape::registerShapeMaker('T', Tetra::mkTetra);
	Shape::registerShapeMaker('C', Cube::mkCube);
	Shape::registerShapeMaker('O', Octahedron::mkOcta);
	Shape::registerShapeMaker('D', Dodecahedron::mkDode);
	const int NP=4;
	char shp[NP]={'T', 'C', 'O', 'D'};	
	
	srand(time(0));
	sf::ContextSettings settings;
	settings.antialiasingLevel = 20;

	//cout<<"Display settings: "<< sf::VideoMode::getDesktopMode().width << ", " << sf::VideoMode::getDesktopMode().height<<endl;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window",sf::Style::Default, settings);
	ReferenceFrame RF(400, 400);
	Base::set_window(&window);
	Base::set_rf(&RF);

	std::shared_ptr<RSpace<3>> Global(RSpace<3>::maker({0, 0, 0}, {0, 0, 0}));

	Camera CameraView(Global->spawn({6080, 0, 0}, {0, 90, 0}), 1.0, 0.8);	
	Shape::setCamera(&CameraView);
	
	AxeSys XYZ(Global);	

	const int Nt=500;	
	Shape* Shps[Nt];
	
	Tesseract* C4=new Tesseract(Global->spawn({800, 800, 0}, {0, 0, 0}), sf::Color(104, 90, 202));
	Shps[0]=C4;
	
	for(int i=1; i<Nt; i++){
		Shps[i]=Shape::Mk_Poliedrom(shp[i%NP], Global->spawn({20, 50, 250}, {0, 0, 0}), sf::Color(rand()%256, rand()%256, rand()%256));		
	}
	int helpers=4, vt=Nt/helpers, t=Nt-vt*helpers, k=0, r;
	for(int i=0; i<helpers; i++){
		r=vt;
		if(t>0){
			r+=1;
			t--;
		}
		Master::registerMover(Shps+k, r);
		k+=r;
	}

	static double total=0;
	static double tt=1.0;
	
	bool a=false;
	FrameRate Framerate(50);

	while(window.isOpen()){
		sf::Event event;
		while(window.pollEvent(event))
		{
			if(event.type==sf::Event::Closed)
			{
				window.close();
			}
			else if(event.type == sf::Event::KeyPressed){
				if(event.key.code == sf::Keyboard::Q){
					// X up
					CameraView.updateAngle(0, -5.0);
				}
				else if(event.key.code == sf::Keyboard::W){
					// X down
					CameraView.updateAngle(0, 5.0);
				}
				else if(event.key.code == sf::Keyboard::S){
					// Y up
					CameraView.updateAngle(1, -5.0);
				}
				else if(event.key.code == sf::Keyboard::A){
					// Y down
					CameraView.updateAngle(1, 5.0);
				}
				else if(event.key.code == sf::Keyboard::X){
					//Z up
					CameraView.updateAngle(2, -5.0);
				}
				else if(event.key.code == sf::Keyboard::Z){
					//Z down
					CameraView.updateAngle(2, 5.0);
				}
				else if(event.key.code>70 && event.key.code<75){
					CameraView.lRuD(event.key.code);
				}
			}
		}

		if(Framerate()>=0){
			Framerate.reset();
			window.clear(sf::Color::White);

			//################################################################
			//draw things here ###############################################

			auto start = chrono::high_resolution_clock::now();

			Master::awake();

			Master::waiting();	
			
			// END of drawing ###############################################
			//###############################################################
			//###############################################################
			//t=0;
			Framerate.reset();
		}

		window.display();		
	}

	Master::stop();

	for(int i=0; i<Nt; i++){
		//cout<<Shps[i]<<endl;
		delete Shps[i];
	}

	return 0;
}


