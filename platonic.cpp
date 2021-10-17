#include "camera.h"
#include "platonic.h"

AxeSys::AxeSys(std::shared_ptr<RSpace<3>> _RS)
	: Shape(_RS, 3, sf::Color::Black, {1000,1000,1000})
{
	m_Vertex=new Vect<3>[4];
	m_Vertex[0]=Vect<3>{0,0,0};
	m_Vertex[1]=2000*Vect<3>(0);
	m_Vertex[2]=2000*Vect<3>(1);
	m_Vertex[3]=2000*Vect<3>(2);
	m_Edges=new sf::Vertex*[3];
	for(int i=0; i<m_numEdges; i++){
		m_Edges[i]=new sf::Vertex[2];
	}
}

//======================================================================

void AxeSys::updateEdges(){
	if(m_hasChanged || 1){
		for(int i=0; i<3; i++){
			m_Edges[i][0]=m_Cm->VtSFVx(m_RS.local2World(m_Vertex[0]));
			m_Edges[i][1]=m_Cm->VtSFVx(m_RS.local2World(m_Vertex[i+1]));
		}

		m_Edges[0][0].color=sf::Color::Blue;
		m_Edges[0][1].color=sf::Color::Blue;

		m_Edges[1][0].color=sf::Color::Green;
		m_Edges[1][1].color=sf::Color::Green;

		m_Edges[2][0].color=sf::Color::Yellow;
		m_Edges[2][1].color=sf::Color::Yellow;
		m_hasChanged=false;
	}
}

//======================================================================

void AxeSys::rotate(){
}

//======================================================================

void AxeSys::set_position(const Vect<3>& V){
	//m_RS.move(V);
	m_Cm->angCos(this);
	m_hasChanged=true;
}

//####################################################################
//####################################################################
//####################################################################


Cube::Cube(std::shared_ptr<RSpace<3>> _RS, sf::Color color)
	:Shape(_RS, 12, color, {SL/2.0, SL/2.0, SL/2.0})
{
	m_Vertex=new Vect<3>[8];
	m_Vertex[0]=Vect<3>{0,0,0};
	m_Vertex[1]=Vect<3>{SL, 0, 0};
	m_Vertex[2]=Vect<3>{SL, SL, 0};
	m_Vertex[3]=Vect<3>{0, SL, 0};
	m_Vertex[4]=Vect<3>{0, 0, SL};
	m_Vertex[5]=Vect<3>{SL, 0, SL};
	m_Vertex[6]=Vect<3>{SL, SL, SL};
	m_Vertex[7]=Vect<3>{0, SL, SL};
	m_Edges=new sf::Vertex*[12];

	for(int i=0; i<12; i++){
		m_Edges[i]=new sf::Vertex[2];
		m_Edges[i][0].color=m_Color;
		m_Edges[i][1].color=m_Color;
	}

	m_hasChanged=true;
	updateEdges();
};

//======================================================================

void Cube::updateEdges(){
	if(m_hasChanged){
		int j=0, r=0;
		
		for(int i=0; i<8; i++){
			j=4*(i/4)+(i+1)%4;
			m_Cm->updateVertex(m_Edges[i][0], m_RS.local2World(m_Vertex[i]));
			m_Cm->updateVertex(m_Edges[i][1], m_RS.local2World(m_Vertex[j]));
		}
		for(int i=8; i<m_numEdges; i++){
			j=4*(i/4)+(i+1)%4;
			m_Edges[i][0]=m_Edges[i-8][0];
			m_Edges[i][1]=m_Edges[i-4][0];
		}

		m_hasChanged=false;
	}
}

//======================================================================

void Cube::rotate(){
	static thread_local Rotation<3> Rt({1,1,1}, 2.0);
	Rt.rotate(m_Centroid);
	m_Cm->angCos(this);
	for(int i=0; i<8; i++){
		Rt.rotate(m_Vertex[i]);
	}
	m_hasChanged=true;
}

//======================================================================

void Cube::set_position(const Vect<3>& V){
	m_RS.move(V);
	m_Cm->angCos(this);
	m_hasChanged=true;
}

//####################################################################
//####################################################################
//####################################################################

Tetra::Tetra(std::shared_ptr<RSpace<3>> _RS, sf::Color color)
	: Shape(_RS, 6,color, {0,0,0})
{
	m_Vertex=new Vect<3>[4];
	m_Vertex[0]=SL*Vect<3>{sqrt(8/9.0), 0, -1/3.0};
	m_Vertex[1]=SL*Vect<3>{-sqrt(2/9.0), sqrt(2/3.0), -1/3.0};
	m_Vertex[2]=SL*Vect<3>{-sqrt(2/9.0), -sqrt(2/3.0), -1/3.0};
	m_Vertex[3]=SL*Vect<3>{0, 0, 1}; 

	m_Edges=new sf::Vertex*[m_numEdges];
	for(int i=0; i<m_numEdges; i++){
		m_Edges[i]=new sf::Vertex[2];

		m_Edges[i][0].color=m_Color;
		m_Edges[i][1].color=m_Color;
	}

	m_hasChanged=true;
	updateEdges();
}

//======================================================================

void Tetra::updateEdges(){
	if(m_hasChanged){
		int j, k;
		for(int i=0; i<3; i++){
			j=(i+1)%3;
			k=2*i;
			m_Cm->updateVertex(m_Edges[k][0], m_RS.local2World(m_Vertex[3]));
			m_Cm->updateVertex(m_Edges[k][1], m_RS.local2World(m_Vertex[i]));

			m_Cm->updateVertex(m_Edges[k+1][0], m_RS.local2World(m_Vertex[i]));
			m_Cm->updateVertex(m_Edges[k+1][1], m_RS.local2World(m_Vertex[j]));
		}
		m_hasChanged=false;
	}
}

//======================================================================

void Tetra::rotate(){
	static thread_local Rotation<3> Rt({0,0,1}, -2.0);
	Rt.rotate(m_Centroid);
	m_Cm->angCos(this);

	for(int i=0; i<4; i++){
		Rt.rotate(m_Vertex[i]);
	}
	m_hasChanged=true;
}

//======================================================================

void Tetra::set_position(const Vect<3>& V){
	m_RS.move(V);
	m_Cm->angCos(this);
	m_hasChanged=true;
}

//####################################################################
//####################################################################
//####################################################################

Octahedron::Octahedron(std::shared_ptr<RSpace<3>> _RS, sf::Color color)
	: Shape(_RS, 12, color, {0,0,0})
{
	m_Vertex=new Vect<3>[6];
	
	m_Vertex[0]=SL*Vect<3>(0);
	m_Vertex[1]=SL*Vect<3>(1);
	m_Vertex[2]=SL*-1.0*Vect<3>(0);
	m_Vertex[3]=SL*-1.0*Vect<3>(1);
	m_Vertex[4]=SL*Vect<3>(2);
	m_Vertex[5]=SL*-1.0*Vect<3>(2);

	m_Edges=new sf::Vertex*[m_numEdges];
	for(int i=0; i<m_numEdges; i++){
		m_Edges[i]=new sf::Vertex[2];
		m_Edges[i][0].color=m_Color;
		m_Edges[i][1].color=m_Color;
	}
	
	m_hasChanged=true;
	updateEdges();
}

//======================================================================

void Octahedron::updateEdges(){
	if(m_hasChanged){
		int j;
		for(int i=0; i<4; i++){
			j=(i+1)%4;
			m_Cm->updateVertex(m_Edges[i][0], m_RS.local2World(m_Vertex[i]));
			m_Cm->updateVertex(m_Edges[i][1], m_RS.local2World(m_Vertex[j]));
			
			m_Cm->updateVertex(m_Edges[i+4][0], m_RS.local2World(m_Vertex[4]));
			m_Cm->updateVertex(m_Edges[i+4][1], m_RS.local2World(m_Vertex[i]));
			
			m_Cm->updateVertex(m_Edges[i+8][0], m_RS.local2World(m_Vertex[5]));
			m_Cm->updateVertex(m_Edges[i+8][1], m_RS.local2World(m_Vertex[i]));			
		}
		m_hasChanged=false;
	}
}

//======================================================================

void Octahedron::rotate(){
	static thread_local Rotation<3> Rt({3,-1,1}, 2.0);
	Rt.rotate(m_Centroid);
	m_Cm->angCos(this);
	for(int i=0; i<6; i++){
		Rt.rotate(m_Vertex[i]);
	}
	m_hasChanged=true;
}

//======================================================================

void Octahedron::set_position(const Vect<3>& V){
	m_RS.move(V);
	m_Cm->angCos(this);
	m_hasChanged=true;
}

//####################################################################
//####################################################################
//####################################################################

Dodecahedron::Dodecahedron(std::shared_ptr<RSpace<3>> _RS, sf::Color color)
	: Shape(_RS, 30, color, {0,0,0})
{
	double tht=(1+sqrt(5))/2;

	m_Vertex=new Vect<3>[20];
	m_Vertex[0]=SL*Vect<3>{-1, -1, 1};
	m_Vertex[1]=SL*Vect<3>{1, -1, 1};
	m_Vertex[2]=SL*Vect<3>{1, 1, 1};
	m_Vertex[3]=SL*Vect<3>{-1, 1, 1};
		
	m_Vertex[4]=SL*Vect<3>{-1, -1, -1};
	m_Vertex[5]=SL*Vect<3>{1, -1, -1};
	m_Vertex[6]=SL*Vect<3>{1, 1, -1};
	m_Vertex[7]=SL*Vect<3>{-1, 1, -1};

	//top
	m_Vertex[8]=SL*Vect<3>{1.0/tht, 0, tht};
	m_Vertex[9]=SL*Vect<3>{-1.0/tht, 0, tht};
	
	//side A
	m_Vertex[10]=SL*Vect<3>{0, tht, 1.0/tht};
	m_Vertex[11]=SL*Vect<3>{0, tht, -1.0/tht};	

	//side B
	m_Vertex[12]=SL*Vect<3>{tht, 1.0/tht, 0};
	m_Vertex[13]=SL*Vect<3>{tht, -1.0/tht, 0};

	//Side -A
	m_Vertex[14]=SL*Vect<3>{0, -1.0*tht, 1.0/tht};
	m_Vertex[15]=SL*Vect<3>{0, -1.0*tht, -1.0/tht};

	//side -B
	m_Vertex[16]=SL*Vect<3>{-1.0*tht, 1.0/tht, 0};
	m_Vertex[17]=SL*Vect<3>{-1.0*tht, -1.0/tht, 0};

	//bottom
	m_Vertex[18]=SL*Vect<3>{1.0/tht, 0, -1.0*tht};
	m_Vertex[19]=SL*Vect<3>{-1.0/tht, 0, -1.0*tht};
	
	m_Edges=new sf::Vertex*[m_numEdges];
	for(int i=0; i<m_numEdges; i++){
		m_Edges[i]=new sf::Vertex[2];
		m_Edges[i][0].color=m_Color;
		m_Edges[i][1].color=m_Color;
	}
	
	m_hasChanged=true;
	updateEdges();
}

//======================================================================

void Dodecahedron::updateEdges(){
	static thread_local Vect<3> Vxt[20];
	
	if(m_hasChanged){
		for(int i=0; i<20; i++){
			Vxt[i]=m_RS.local2World(m_Vertex[i]);
		}
		m_Cm->updateVertex(m_Edges[0][0], Vxt[8]);
		m_Cm->updateVertex(m_Edges[0][1], Vxt[9]);
		
		m_Cm->updateVertex(m_Edges[1][0], Vxt[0]);
		m_Cm->updateVertex(m_Edges[1][1], Vxt[9]);

		m_Cm->updateVertex(m_Edges[2][0], Vxt[8]);
		m_Cm->updateVertex(m_Edges[2][1], Vxt[1]);

		m_Cm->updateVertex(m_Edges[3][0], Vxt[8]);
		m_Cm->updateVertex(m_Edges[3][1], Vxt[2]);
		
		m_Cm->updateVertex(m_Edges[4][0], Vxt[9]);
		m_Cm->updateVertex(m_Edges[4][1], Vxt[3]);

		//=============
		
		m_Cm->updateVertex(m_Edges[5][0], Vxt[0]);
		m_Cm->updateVertex(m_Edges[5][1], Vxt[14]);			

		m_Cm->updateVertex(m_Edges[6][0], Vxt[1]);
		m_Cm->updateVertex(m_Edges[6][1], Vxt[14]);

		m_Cm->updateVertex(m_Edges[7][0], Vxt[14]);
		m_Cm->updateVertex(m_Edges[7][1], Vxt[15]);
		
		m_Cm->updateVertex(m_Edges[8][0], Vxt[15]);
		m_Cm->updateVertex(m_Edges[8][1], Vxt[4]);
		
		m_Cm->updateVertex(m_Edges[9][0], Vxt[15]);
		m_Cm->updateVertex(m_Edges[9][1], Vxt[5]);

		//=============

		m_Cm->updateVertex(m_Edges[10][0], Vxt[1]);
		m_Cm->updateVertex(m_Edges[10][1], Vxt[13]);

		m_Cm->updateVertex(m_Edges[11][0], Vxt[2]);
		m_Cm->updateVertex(m_Edges[11][1], Vxt[12]);

		m_Cm->updateVertex(m_Edges[12][0], Vxt[13]);
		m_Cm->updateVertex(m_Edges[12][1], Vxt[12]);

		m_Cm->updateVertex(m_Edges[13][0], Vxt[13]);
		m_Cm->updateVertex(m_Edges[13][1], Vxt[5]);

		m_Cm->updateVertex(m_Edges[14][0], Vxt[12]);
		m_Cm->updateVertex(m_Edges[14][1], Vxt[6]);

		//====================

		m_Cm->updateVertex(m_Edges[15][0], Vxt[2]);
		m_Cm->updateVertex(m_Edges[15][1], Vxt[10]);			

		m_Cm->updateVertex(m_Edges[16][0], Vxt[3]);
		m_Cm->updateVertex(m_Edges[16][1], Vxt[10]);			
		
		m_Cm->updateVertex(m_Edges[17][0], Vxt[10]);
		m_Cm->updateVertex(m_Edges[17][1], Vxt[11]);			

		m_Cm->updateVertex(m_Edges[18][0], Vxt[11]);
		m_Cm->updateVertex(m_Edges[18][1], Vxt[6]);			

		m_Cm->updateVertex(m_Edges[19][0], Vxt[11]);
		m_Cm->updateVertex(m_Edges[19][1], Vxt[7]);			

		//============

		m_Cm->updateVertex(m_Edges[20][0], Vxt[3]);
		m_Cm->updateVertex(m_Edges[20][1], Vxt[16]);

		m_Cm->updateVertex(m_Edges[21][0], Vxt[0]);
		m_Cm->updateVertex(m_Edges[21][1], Vxt[17]);

		m_Cm->updateVertex(m_Edges[22][0], Vxt[16]);
		m_Cm->updateVertex(m_Edges[22][1], Vxt[17]);

		m_Cm->updateVertex(m_Edges[23][0], Vxt[16]);
		m_Cm->updateVertex(m_Edges[23][1], Vxt[7]);

		m_Cm->updateVertex(m_Edges[24][0], Vxt[17]);
		m_Cm->updateVertex(m_Edges[24][1], Vxt[4]);			
		
		//=============

		m_Cm->updateVertex(m_Edges[25][0], Vxt[4]);
		m_Cm->updateVertex(m_Edges[25][1], Vxt[19]);

		m_Cm->updateVertex(m_Edges[26][0], Vxt[18]);
		m_Cm->updateVertex(m_Edges[26][1], Vxt[19]);
		
		m_Cm->updateVertex(m_Edges[27][0], Vxt[19]);
		m_Cm->updateVertex(m_Edges[27][1], Vxt[7]);
		
		m_Cm->updateVertex(m_Edges[28][0], Vxt[5]);
		m_Cm->updateVertex(m_Edges[28][1], Vxt[18]);

		m_Cm->updateVertex(m_Edges[29][0], Vxt[18]);
		m_Cm->updateVertex(m_Edges[29][1], Vxt[6]);
		
		m_hasChanged=false;
	}
}

//======================================================================

void Dodecahedron::rotate(){
	static thread_local Rotation<3> Rt({1,3,1}, -3.0);
	Rt.rotate(m_Centroid);
	m_Cm->angCos(this);
	for(int i=0; i<20; i++){
		Rt.rotate(m_Vertex[i]);
	}
	m_hasChanged=true;
}

//======================================================================

void Dodecahedron::set_position(const Vect<3>& V){
	m_RS.move(V);
	m_Cm->angCos(this);
	m_hasChanged=true;
}

//####################################################################
//####################################################################
//####################################################################

Tesseract::Tesseract(std::shared_ptr<RSpace<3>> _RS, sf::Color color)
	: Shape(_RS, 32, color)
{
	m_Vertex=new Vect<3>[1];// README: this is just a place holder to avoid conflict with the destructor
	Vertex2=new Vect<4>[16];
	Vertex2[0]=Vect<4>{0, 0, 0, 0};
	Vertex2[1]=Vect<4>{SL, 0, 0, 0};
	Vertex2[2]=Vect<4>{SL, SL, 0,0};
	Vertex2[3]=Vect<4>{0, SL, 0, 0};
	Vertex2[4]=Vect<4>{0, 0, SL, 0};
	Vertex2[5]=Vect<4>{SL, 0, SL, 0};
	Vertex2[6]=Vect<4>{SL, SL, SL, 0};
	Vertex2[7]=Vect<4>{0, SL, SL, 0};

	Vertex2[8]=Vect<4>{0, 0, 0, SL};	
	Vertex2[9]=Vect<4>{SL, 0, 0, SL};
	Vertex2[10]=Vect<4>{SL, SL, 0, SL};
	Vertex2[11]=Vect<4>{0, SL, 0, SL};
	Vertex2[12]=Vect<4>{0, 0, SL, SL};
	Vertex2[13]=Vect<4>{SL, 0, SL, SL};
	Vertex2[14]=Vect<4>{SL, SL, SL, SL};
	Vertex2[15]=Vect<4>{0, SL, SL, SL};

	m_Edges=new sf::Vertex*[m_numEdges];
	for(int i=0; i<m_numEdges; i++){
		m_Edges[i]=new sf::Vertex[2];
	}

	for(int i=0; i<8; i++){
		m_Edges[i][0].color=sf::Color::Blue;
		m_Edges[i][1].color=sf::Color::Blue;
	}

	for(int i=12; i<20; i++){
		m_Edges[i][0].color=m_Color;
		m_Edges[i][1].color=m_Color;
	}

	for(int i=24; i<m_numEdges; i++){			
		m_Edges[i][0].color=sf::Color::Green;
		m_Edges[i][1].color=sf::Color::Green;
	}

};

//======================================================================

Tesseract::~Tesseract(){
	delete[] Vertex2;
}

//======================================================================

Vect<3> proj(Vect<4>& V){
	return V.projection(4);
}

//======================================================================

void Tesseract::updateEdges(){
	if(1){
		int j, k, t;
		for(int i=0; i<8; i++){
			j=4*(i/4)+(i+1)%4;
			m_Cm->updateVertex(m_Edges[i][0], m_RS.local2World(proj(Vertex2[i])));			
			m_Cm->updateVertex(m_Edges[i][1], m_RS.local2World(proj(Vertex2[j])));			
		}
		for(int i=8; i<12; i++){
			m_Edges[i][0]=m_Edges[i-8][0];
			m_Edges[i][1]=m_Edges[i-4][0];
		}
		
		for(int i=12; i<20; i++){
			k=i-4;
			j=4*(k/4)+(k+1)%4;
			m_Cm->updateVertex(m_Edges[i][0], m_RS.local2World(proj(Vertex2[k])));			
			m_Cm->updateVertex(m_Edges[i][1], m_RS.local2World(proj(Vertex2[j])));		
		}
		for(int i=20; i<24; i++){
			m_Edges[i][0]=m_Edges[i-8][0];
			m_Edges[i][1]=m_Edges[i-4][0];
		}
		for(int i=24; i<m_numEdges; i++){
			m_Cm->updateVertex(m_Edges[i][0], m_RS.local2World(proj(Vertex2[i-24])));			
			m_Cm->updateVertex(m_Edges[i][1], m_RS.local2World(proj(Vertex2[i-16])));
		}
		m_hasChanged=false;
	}
}

//======================================================================

void Tesseract::rotate(){
	static thread_local Rotation<4> Rt({1,1,1,1}, 2.0);

	Rt.rotate(m_Centroid2);
	m_Centroid=proj(m_Centroid2);
	m_Cm->angCos(this);
	for(int i=0; i<16; i++){
		Rt.rotate(Vertex2[i]);
	}
	m_hasChanged=true;
	
}

//======================================================================

void Tesseract::set_position(const Vect<3>& V){
	m_RS.move(V);
	m_Cm->angCos(this);
	m_hasChanged=true;
	m_display=true;
}

//####################################################################
//####################################################################
