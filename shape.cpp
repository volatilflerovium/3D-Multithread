#include<SFML/Graphics.hpp>
#include "vector.h"
#include "noise.h"
#include "shape.h"
#include "rspace.h"

std::map<char, MkShape>Shape::Shapes;
Camera* Shape::Cm=nullptr;


Shape::~Shape(){
	for(int i=0; i<numEdges; i++){
		delete[] Edges[i];
	}
	delete[] Vertex;
	delete[] Edges;
}


Shape::Shape(std::shared_ptr<RSpace<3>> _RS, int nE, sf::Color color)
	: __RS(_RS), RS(*_RS), numEdges(nE), Correction({1.0, 1.0, 1.0}),Color(color){
	Ns[0]=Noise(10);
	Ns[1]=Noise(10);
	Ns[2]=Noise(10);
}

void Shape::move(double t){
	//*
	rotate();
	Vect<3> Speed({Correction.coordinate(0)*Ns[0].lerp(), 
						Correction.coordinate(1)*Ns[1].lerp(), 
						Correction.coordinate(2)*Ns[2].lerp()});
	Speed*=t;
	Vect<3> VT=RS.getPos()+Speed;
	for(int i=0; i<3; i++){
		if(abs(VT.coordinate(i))>12000.0){
			Correction+=-2.0*Correction.coordinate(i)*Vect<3>(i+1);
      	Speed+=-2.0* Speed.coordinate(i)*Vect<3>(i+1);
   	}
   }
   set_position(Speed);   
   /**/
}   

//====================================================================

void Shape::registerShapeMaker(char c, MkShape mk_shape){
	Shapes[c]=mk_shape;
}

//====================================================================

Shape* Shape::Mk_Poliedrom(char c, std::shared_ptr<RSpace<3>> _RS, sf::Color color){
	return Shapes[c](_RS, color);
}

//====================================================================

