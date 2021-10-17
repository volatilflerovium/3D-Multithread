/*********************************************************************
* Shape class                                                        *
*                                                                    *
* Version: 1.5                                                       *
* Date:    25-07-2021                                                *
* Author:  Dan Machado                                               *
**********************************************************************/
#ifndef SHAPE_H
#define SHAPE_H

#include <memory>
#include <SFML/Graphics.hpp>
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
	public:
		static void registerShapeMaker(char, MkShape);
		static Shape* Mk_Poliedrom(char c, std::shared_ptr<RSpace<3>> _RS, sf::Color color);
		static void setCamera(Camera* cm);

		Shape(std::shared_ptr<RSpace<3>> __RS, int nE, sf::Color color, std::initializer_list<double> l);
		Shape(std::shared_ptr<RSpace<3>> __RS, int nE, sf::Color color);
		virtual ~Shape();

		void preDraw();
		void draw();
		virtual void rotate()=0;
		virtual void updateEdges()=0;

		int getID();
		void setID(int _id);
		RSpace<3>& getLocalSpace();
		void move(double t); // this update the position of the underlying position vector of the local space
		virtual void set_position(const Vect<3>& V)=0;

		Vect<3> getCentroidW() const; // return the centroid in world coordinates

		bool display() const;
		void setDisplay(bool view);

	private:
		static std::map<char, MkShape> m_Shapes;
		Vect<3> m_Correction;
		Noise m_Ns[3];
		int m_id{-1};

	protected:
		RSpace<3>& m_RS;
		Vect<3> m_Centroid;
		sf::Color m_Color;

		Vect<3>* m_Vertex{nullptr};
		sf::Vertex** m_Edges{nullptr};
		static Camera* m_Cm;
		
		std::shared_ptr<RSpace<3>> __RS{nullptr};
		int m_numEdges;
		bool m_hasChanged{true};
		bool m_display{true};
};

//======================================================================

inline void Shape::setCamera(Camera* cm){
	if(m_Cm==nullptr){
		m_Cm=cm;
	}
}

//======================================================================

inline bool Shape::display() const{
	return m_display;
}

//======================================================================

inline void Shape::setDisplay(bool display){
	m_display=display;
}

//======================================================================

inline RSpace<3>& Shape::getLocalSpace(){
	return m_RS;
}

//======================================================================

inline void Shape::setID(int _id){
	m_id=_id;
}

//======================================================================

inline int Shape::getID(){
	return m_id;
}

//======================================================================

inline Vect<3> Shape::getCentroidW() const{
	return m_RS.local2World(m_Centroid);
}

//####################################################################
//####################################################################
//####################################################################



#endif
