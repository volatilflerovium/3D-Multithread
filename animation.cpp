#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <csignal>

#include "helper.h"
#include "base.h"
#include "framerate.h"
#include "noise.h"
#include "rspace.h"
#include "vector.h"
#include "shape.h"
#include "camera.h"
#include "platonic.h"
#include "master_slave.h"

using namespace std;

//####################################################################
//####################################################################

int main(){
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
	settings.antialiasingLevel = 8;

	cout<<"Display settings: "<< sf::VideoMode::getDesktopMode().width << ", " << sf::VideoMode::getDesktopMode().height<<endl;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "My window",sf::Style::Default, settings);
	ReferenceFrame RF(400, 400);
	Base::set_window(&window);
	Base::set_rf(&RF);

	std::shared_ptr<RSpace<3>> Global(RSpace<3>::maker({0, 0, 0}, {0, 0, 0}));

	Camera CameraView(Global->spawn({6080, 0, 0}, {0, 90, 0}), 1.0, 0.8);	
	Shape::setCamera(&CameraView);

	Slave* slaves[6];
	slaves[0]=new Slave();
	slaves[1]=new Slave();
	slaves[2]=new Slave();
	slaves[3]=new Slave();
	slaves[4]=new Slave();
	slaves[5]=new Slave();
	Master::registerSlave(slaves[0]);
	Master::registerSlave(slaves[1]);
	Master::registerSlave(slaves[2]);
	Master::registerSlave(slaves[3]);
	Master::registerSlave(slaves[4]);
	Master::registerSlave(slaves[5]);

	AxeSys XYZ(Global);	
	Tesseract C4(Global->spawn({800, 800, 0}, {0, 0, 0}), sf::Color(104, 90, 202));	
	slaves[0]->addShape(&C4);
	slaves[0]->addShape(&XYZ);

	const int Nt=402;
	Shape* Shps[Nt];
	Shps[0]=&C4;
	Shps[1]=&XYZ;
	for(int i=2; i<Nt; i++){
		Shps[i]=Shape::Mk_Poliedrom(shp[i%NP], Global->spawn({20, 50, 250}, {0, 0, 0}), sf::Color(rand()%256, rand()%256, rand()%256));		
		slaves[i%6]->addShape(Shps[i]);
	}

	double total=0;
	double tt=1.0;
	
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

			Master::wakeUpSlaves();

			Master::waiting();

			for(int i=0; i<Nt; i++){
				Shps[i]->draw();
			}

			a=true;
			
			auto elapsed = std::chrono::high_resolution_clock::now() - start;
			long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
			//*
			cout<<"Total Elapsed time: "<<microseconds/1000000.0<<endl;
			total+=microseconds/1000000.0;
			cout<<tt<<"============================= "<<total/tt<<endl;
			tt+=1.0;

			// END of drawing ###############################################
			//###############################################################
			//###############################################################
			//t=0;
			Framerate.reset();
		}
		window.display();		
	}

	Master::stop();

	for(int i=2; i<Nt; i++){
		delete Shps[i];
	}

	return 0;
}

