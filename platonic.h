/*********************************************************************
* implement Shape class as AxeSys, Cube, Tetra, Octahedron, Tesseract*
*                                                                    *
* Version: 1.5                                                       *
* Date:    25-07-2021                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#ifndef PLATONIC_H
#define PLATONIC_H

#include <SFML/Graphics.hpp>
#include "helper.h"
#include "base.h"
#include "vector.h"
#include "rspace.h"
#include "shape.h"

//####################################################################

class AxeSys : public Shape
{
	public:
		AxeSys(std::shared_ptr<RSpace<3>> _RS);
		void updateEdges();
		void set_position(const Vect<3>& V);
		void rotate();
};

//####################################################################
//###################################################################

class Cube : public Shape
{
	public:
		Cube(std::shared_ptr<RSpace<3>> _RS, sf::Color);
		void updateEdges();
		void rotate();
		void set_position(const Vect<3>& V);
		static Shape* mkCube(std::shared_ptr<RSpace<3>> _RS, sf::Color color);
		
};

//======================================================================

inline Shape* Cube::mkCube(std::shared_ptr<RSpace<3>> _RS, sf::Color color){
	return new Cube(_RS, color);
}

//###################################################################
//###################################################################

class Tetra : public Shape
{
	public:
		Tetra(std::shared_ptr<RSpace<3>> _RS, sf::Color color);
		void updateEdges();
		void rotate();
		void set_position(const Vect<3>& V);
		static Shape* mkTetra(std::shared_ptr<RSpace<3>> _RS, sf::Color color);
};

//======================================================================

inline Shape* Tetra::mkTetra(std::shared_ptr<RSpace<3>> _RS, sf::Color color){
	return new Tetra(_RS, color);
}

//###################################################################
//###################################################################
//###################################################################
//###################################################################

class Octahedron : public Shape
{
	public:
		Octahedron(std::shared_ptr<RSpace<3>> _RS, sf::Color color);
		void updateEdges();
		void rotate();
		void set_position(const Vect<3>& V);
		static Shape* mkOcta(std::shared_ptr<RSpace<3>> _RS, sf::Color color);
};

//======================================================================

inline Shape* Octahedron::mkOcta(std::shared_ptr<RSpace<3>> _RS, sf::Color color){
	return new Octahedron(_RS, color);
}

//###################################################################
//###################################################################

class Dodecahedron : public Shape
{
	public:
		Dodecahedron(std::shared_ptr<RSpace<3>> _RS, sf::Color color);
		void updateEdges();
		void rotate();
		void set_position(const Vect<3>& V);
		static Shape* mkDode(std::shared_ptr<RSpace<3>> _RS, sf::Color color);
};

//======================================================================

inline Shape* Dodecahedron::mkDode(std::shared_ptr<RSpace<3>> _RS, sf::Color color){
	return new Dodecahedron(_RS, color);
}

//###################################################################
//###################################################################


class Tesseract : public Shape
{
	public:
		~Tesseract();
		Tesseract(std::shared_ptr<RSpace<3>> _RS, sf::Color color);
		void updateEdges();
		void rotate();
		void set_position(const Vect<3>& V);

	private:
		Vect<4> m_Centroid2;
		Vect<4>* Vertex2;
};


//###################################################################
//###################################################################

#endif
