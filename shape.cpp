#include<SFML/Graphics.hpp>
#include "vector.h"
#include "noise.h"
#include "shape.h"
#include "rspace.h"

std::map<char, MkShape>Shape::m_Shapes;
Camera* Shape::m_Cm=nullptr;

//======================================================================

Shape::~Shape(){
	for(int i=0; i<m_numEdges; i++){
		delete[] m_Edges[i];
	}
	delete[] m_Vertex;
	delete[] m_Edges;
}

//======================================================================

Shape::Shape(std::shared_ptr<RSpace<3>> _RS, int nE, sf::Color color, std::initializer_list<double> l)
: m_Correction({1.0, 1.0, 1.0}), 
m_Ns{Noise(10),Noise(10),Noise(10)},
m_RS(*_RS),
m_Centroid(l), m_Color(color), 
__RS(_RS), 
m_numEdges(nE)
{
}

//======================================================================

Shape::Shape(std::shared_ptr<RSpace<3>> _RS, int nE, sf::Color color)
:
 m_Correction({1.0, 1.0, 1.0}), 
m_Ns{Noise(10),Noise(10),Noise(10)},
m_RS(*_RS),
m_Color(color), 
__RS(_RS), 
m_numEdges(nE)
{}

//======================================================================

void Shape::move(double t){
	Vect<3> Speed({m_Correction[0]*m_Ns[0].lerp(), 
						m_Correction[1]*m_Ns[1].lerp(), 
						m_Correction[2]*m_Ns[2].lerp()});
	Speed*=t;
	Vect<3> VT=m_RS.getPos()+Speed;
	for(int i=0; i<3; i++){
		if(abs(VT[i])>12000.0){
			m_Correction+=-2.0*m_Correction[i]*Vect<3>(i);
      	Speed+=-2.0* Speed[i]*Vect<3>(i);
   	}
   }
   set_position(Speed);   
}   

//====================================================================

void Shape::preDraw()
{
	if(!m_display){
		return;
	}

	updateEdges();
}


//====================================================================

void Shape::draw()
{
	if(!m_display){
		return;
	}

	for(int i=0; i<m_numEdges; i++){
		m_window->draw(m_Edges[i], 2, sf::Lines);
	}
}
//====================================================================

void Shape::registerShapeMaker(char c, MkShape mk_shape){
	m_Shapes[c]=mk_shape;
}

//====================================================================

Shape* Shape::Mk_Poliedrom(char c, std::shared_ptr<RSpace<3>> _RS, sf::Color color){
	return m_Shapes[c](_RS, color);
}

//====================================================================

