#ifndef SHAPE_H
#define SHAPE_H

#include<memory>
#include<SFML/Graphics.hpp>
#include "base.h"
#include "vector.h"
#include "noise.h"
#include "rspace.h"

using namespace std;

class Camera;

class Shape;
typedef Shape* (*MkShape)(std::shared_ptr<RSpace<3>>, sf::Color);

//####################################################################

class Shape : public Base
{
	private:
		static std::map<char, MkShape> Shapes;
	public:
		static void registerShapeMaker(char, MkShape);
		static Shape* Mk_Poliedrom(char c, std::shared_ptr<RSpace<3>> _RS, sf::Color color);

	private:
		int id=-1;
		Vect<3> Correction;
		Noise Ns[3];

	protected:
		Vect<3> Centroid;
		int numEdges;
		sf::Color Color;
		std::shared_ptr<RSpace<3>> __RS;
		RSpace<3>& RS;
		Vect<3>* Vertex;
		sf::Vertex** Edges;
		bool hasChanged=true;
		static Camera* Cm;

		virtual void set_position(const Vect<3>& V)=0;


	public:
		static void setCamera(Camera* cm);

		Shape(std::shared_ptr<RSpace<3>> __RS, int nE, sf::Color color);
		virtual ~Shape();

		void draw();
		virtual void rotate()=0;
		virtual bool updateEdges()=0;

		int getID();
		void setID(int _id);
		RSpace<3>& getLocalSpace();
		void move(double t); // this update the position of the underlying position vector of the local space
		
		Vect<3> getCentroidW() const; // return the centroid in world coordinates
};


inline void Shape::setCamera(Camera* cm){
	if(Cm==nullptr){
		Cm=cm;
	}
}

inline RSpace<3>& Shape::getLocalSpace(){
	return RS;
}

inline void Shape::setID(int _id){
	id=_id;
}

inline int Shape::getID(){
	return id;
}


inline void Shape::draw(){
	for(int i=0; i<numEdges; i++){
		Window->draw(Edges[i], 2, sf::Lines);
	}
}

inline Vect<3> Shape::getCentroidW() const{
	return RS.ltw(Centroid);
}

/*
inline double Shape::getCos()const{
	return cosZ;
}
/**/

//####################################################################
//####################################################################
//####################################################################



#endif