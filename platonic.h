#ifndef PLATONIC_H
#define PLATONIC_H

#include<memory>
#include<SFML/Graphics.hpp>
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
		bool updateEdges();
		void set_position(const Vect<3>& V);
		void rotate();
};

//####################################################################
//###################################################################

class Cube : public Shape
{
	public:
		Cube(std::shared_ptr<RSpace<3>> _RS, sf::Color);
		bool updateEdges();
		void rotate();
		void set_position(const Vect<3>& V);
		static Shape* mkCube(std::shared_ptr<RSpace<3>> _RS, sf::Color color);
		
};

inline Shape* Cube::mkCube(std::shared_ptr<RSpace<3>> _RS, sf::Color color){
	return new Cube(_RS, color);
}

//###################################################################
//###################################################################

class Tetra : public Shape
{
	public:
		Tetra(std::shared_ptr<RSpace<3>> _RS, sf::Color color);
		bool updateEdges();
		void rotate();
		void set_position(const Vect<3>& V);
		static Shape* mkTetra(std::shared_ptr<RSpace<3>> _RS, sf::Color color);
};

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
		bool updateEdges();
		void rotate();
		void set_position(const Vect<3>& V);
		static Shape* mkOcta(std::shared_ptr<RSpace<3>> _RS, sf::Color color);
};

inline Shape* Octahedron::mkOcta(std::shared_ptr<RSpace<3>> _RS, sf::Color color){
	return new Octahedron(_RS, color);
}

//###################################################################
//###################################################################

class Dodecahedron : public Shape
{
	public:
		Dodecahedron(std::shared_ptr<RSpace<3>> _RS, sf::Color color);
		bool updateEdges();
		void rotate();
		void set_position(const Vect<3>& V);
		static Shape* mkDode(std::shared_ptr<RSpace<3>> _RS, sf::Color color);
};

inline Shape* Dodecahedron::mkDode(std::shared_ptr<RSpace<3>> _RS, sf::Color color){
	return new Dodecahedron(_RS, color);
}

//###################################################################
//###################################################################


class Tesseract : public Shape
{
	private:
		Vect<4> Centroid2;
		Vect<4>* Vertex2;
	
	public:
		~Tesseract();
		Tesseract(std::shared_ptr<RSpace<3>> _RS, sf::Color color);
		bool updateEdges();
		void rotate();
		void draw();
		void set_position(const Vect<3>& V);
};


//###################################################################
//###################################################################

#endif
