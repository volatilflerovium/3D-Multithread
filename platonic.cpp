#include "camera.h"
#include "platonic.h"

AxeSys::AxeSys(std::shared_ptr<RSpace<3>> _RS)
	: Shape(_RS, 3, sf::Color::Black)
{
	Centroid=1000*Vect<3>({1,1,1});
	Vertex=new Vect<3>[4];
	Vertex[0]=Vect<3>({0,0,0});
	Vertex[1]=2000*Vect<3>(1);
	Vertex[2]=2000*Vect<3>(2);
	Vertex[3]=2000*Vect<3>(3);
	Edges=new sf::Vertex*[3];
	for(int i=0; i<numEdges; i++){
		Edges[i]=new sf::Vertex[2];
	}
}

bool AxeSys::updateEdges(){
	if(hasChanged || 1){
		for(int i=0; i<3; i++){
			Edges[i][0]=Cm->VtSFVx(RS.ltw(Vertex[0]));
			Edges[i][1]=Cm->VtSFVx(RS.ltw(Vertex[i+1]));
		}

		Edges[0][0].color=sf::Color::Blue;
		Edges[0][1].color=sf::Color::Blue;

		Edges[1][0].color=sf::Color::Green;
		Edges[1][1].color=sf::Color::Green;

		Edges[2][0].color=sf::Color::Yellow;
		Edges[2][1].color=sf::Color::Yellow;
		hasChanged=false;
		return !hasChanged;
	}
	return hasChanged;
}


void AxeSys::rotate(){
}

void AxeSys::set_position(const Vect<3>& V){
	RS.move(V);
	hasChanged=Cm->angCos(this);
}

//####################################################################
//####################################################################
//####################################################################


Cube::Cube(std::shared_ptr<RSpace<3>> _RS, sf::Color color)
	:Shape(_RS, 12, color)
{
	
	Centroid=Vect<3>({SL/2.0, SL/2.0, SL/2.0});
	Vertex=new Vect<3>[8];
	Vertex[0]=Vect<3>({0,0,0});
	Vertex[1]=Vect<3>({SL, 0, 0});
	Vertex[2]=Vect<3>({SL, SL, 0});
	Vertex[3]=Vect<3>({0, SL, 0});
	Vertex[4]=Vect<3>({0, 0, SL});
	Vertex[5]=Vect<3>({SL, 0, SL});
	Vertex[6]=Vect<3>({SL, SL, SL});
	Vertex[7]=Vect<3>({0, SL, SL});
	Edges=new sf::Vertex*[12];
	//int j=0;
	for(int i=0; i<12; i++){
		//j=4*(i/4)+(i+1)%4;
		Edges[i]=new sf::Vertex[2];
	}
	
	//*
	int j;
		for(int i=0; i<8; i++){
			j=4*(i/4)+(i+1)%4;
			Edges[i][0]=Cm->VtSFVx(RS.ltw(Vertex[i]));
			Edges[i][1]=Cm->VtSFVx(RS.ltw(Vertex[j]));
			
			Edges[i][0].color=Color;
			Edges[i][1].color=Color;
		}
		for(int i=8; i<numEdges; i++){
			j=4*(i/4)+(i+1)%4;
			Edges[i][0]=Edges[i-8][0];
			Edges[i][1]=Edges[i-4][0];
		}
		/**/
	
};


bool Cube::updateEdges(){
	if(hasChanged){
		int j=0, r=0;
		for(int i=0; i<8; i++){
			j=4*(i/4)+(i+1)%4;
			Cm->updateVertex(Edges[i][0], RS.ltw(Vertex[i]));
			Cm->updateVertex(Edges[i][1], RS.ltw(Vertex[j]));
		}
		for(int i=8; i<numEdges; i++){
			j=4*(i/4)+(i+1)%4;
			Edges[i][0]=Edges[i-8][0];
			Edges[i][1]=Edges[i-4][0];
		}
		hasChanged=false;
		return !hasChanged;
	}
	return hasChanged;
}

void Cube::rotate(){
	static Rotation<3> Rt({1,1,1}, 2.0);
	Centroid=Rt(Centroid);
	//Cm->angCos(this);
	for(int i=0; i<8; i++){
		Vertex[i]=Rt(Vertex[i]);
	}
	//hasChanged=true;
}


void Cube::set_position(const Vect<3>& V){
	RS.move(V);
	hasChanged=Cm->angCos(this);
}


//####################################################################
//####################################################################
//####################################################################


Tetra::Tetra(std::shared_ptr<RSpace<3>> _RS, sf::Color color)
	: Shape(_RS, 6,color)
{
	Centroid=Vect<3>({0,0,0});
	Vertex=new Vect<3>[4];
	Vertex[0]=SL*Vect<3>({sqrt(8/9.0), 0, -1/3.0});
	Vertex[1]=SL*Vect<3>({-sqrt(2/9.0), sqrt(2/3.0), -1/3.0});
	Vertex[2]=SL*Vect<3>({-sqrt(2/9.0), -sqrt(2/3.0), -1/3.0});
	Vertex[3]=SL*Vect<3>({0, 0, 1}); 

	Edges=new sf::Vertex*[numEdges];
	for(int i=0; i<numEdges; i++){
		Edges[i]=new sf::Vertex[2];
	}
	int j, k;
		for(int i=0; i<3; i++){
			j=(i+1)%3;
			k=2*i;
			
			Edges[k][0]=Cm->VtSFVx(RS.ltw(Vertex[3]));
			Edges[k][1]=Cm->VtSFVx(RS.ltw(Vertex[i]));
			
			Edges[k][0].color=Color;
			Edges[k][1].color=Color;
			
			Edges[k+1][0]=Cm->VtSFVx(RS.ltw(Vertex[i]));
			Edges[k+1][1]=Cm->VtSFVx(RS.ltw(Vertex[j]));
			
			Edges[k+1][0].color=Color;
			Edges[k+1][1].color=Color;
		}
}

bool Tetra::updateEdges(){
	if(hasChanged){
		int j, k;
		for(int i=0; i<3; i++){
			j=(i+1)%3;
			k=2*i;
			Cm->updateVertex(Edges[k][0], RS.ltw(Vertex[3]));
			Cm->updateVertex(Edges[k][1], RS.ltw(Vertex[i]));
	
			Cm->updateVertex(Edges[k+1][0], RS.ltw(Vertex[i]));
			Cm->updateVertex(Edges[k+1][1], RS.ltw(Vertex[j]));
		}
		//cout<<"+++++++++++++++++++++++++++++++++++++++++"<<endl;
		hasChanged=false;
		return !hasChanged;
	}
	return hasChanged;
}

void Tetra::rotate(){
	static Rotation<3> Rt({0,0,1}, -2.0);
	Centroid=Rt(Centroid);
	for(int i=0; i<4; i++){
		Vertex[i]=Rt(Vertex[i]);
	}
	//hasChanged=true;
}


void Tetra::set_position(const Vect<3>& V){
	RS.move(V);	
	hasChanged=Cm->angCos(this);
}


//####################################################################
//####################################################################
//####################################################################

Octahedron::Octahedron(std::shared_ptr<RSpace<3>> _RS, sf::Color color)
	: Shape(_RS, 12, color)
{
	Centroid=Vect<3>({0,0,0});
	Vertex=new Vect<3>[6];
	
	Vertex[0]=SL*Vect<3>(1);
	Vertex[1]=SL*Vect<3>(2);
	Vertex[2]=SL*-1.0*Vect<3>(1);
	Vertex[3]=SL*-1.0*Vect<3>(2);
	Vertex[4]=SL*Vect<3>(3);
	Vertex[5]=SL*-1.0*Vect<3>(3);

	Edges=new sf::Vertex*[numEdges];
	for(int i=0; i<numEdges; i++){
		Edges[i]=new sf::Vertex[2];
	}
	int j;
		for(int i=0; i<4; i++){
			j=(i+1)%4;
			Edges[i][0]=Cm->VtSFVx(RS.ltw(Vertex[i]));
			Edges[i][1]=Cm->VtSFVx(RS.ltw(Vertex[j]));
			
			Edges[i][0].color=Color;
			Edges[i][1].color=Color;

			Edges[4+i][0]=Cm->VtSFVx(RS.ltw(Vertex[4]));
			Edges[4+i][1]=Cm->VtSFVx(RS.ltw(Vertex[i]));

			Edges[4+i][0].color=Color;
			Edges[4+i][1].color=Color;
			
			Edges[8+i][0]=Cm->VtSFVx(RS.ltw(Vertex[5]));
			Edges[8+i][1]=Cm->VtSFVx(RS.ltw(Vertex[i]));
			
			Edges[8+i][0].color=Color;
			Edges[8+i][1].color=Color;
		}
}


bool Octahedron::updateEdges(){
	if(hasChanged){
		int j;
		for(int i=0; i<4; i++){
			j=(i+1)%4;
			Cm->updateVertex(Edges[i][0], RS.ltw(Vertex[i]));
			Cm->updateVertex(Edges[i][1], RS.ltw(Vertex[j]));
			
			Cm->updateVertex(Edges[i+4][0], RS.ltw(Vertex[4]));
			Cm->updateVertex(Edges[i+4][1], RS.ltw(Vertex[i]));
			
			Cm->updateVertex(Edges[i+8][0], RS.ltw(Vertex[5]));
			Cm->updateVertex(Edges[i+8][1], RS.ltw(Vertex[i]));			
		}
		hasChanged=false;
		return !hasChanged;
	}
	return hasChanged;
}

void Octahedron::rotate(){
	static Rotation<3> Rt({3,-1,1}, 2.0);
	Centroid=Rt(Centroid);
	//Cm->angCos(this);
	for(int i=0; i<6; i++){
		Vertex[i]=Rt(Vertex[i]);
	}
	//hasChanged=true;
}


void Octahedron::set_position(const Vect<3>& V){
	RS.move(V);
	hasChanged=Cm->angCos(this);
}



//####################################################################
//####################################################################
//####################################################################

Dodecahedron::Dodecahedron(std::shared_ptr<RSpace<3>> _RS, sf::Color color)
	: Shape(_RS, 30, color)
{
	Centroid=Vect<3>({0,0,0});
	double tht=(1+sqrt(5))/2;

	Vertex=new Vect<3>[20];
	Vertex[0]=SL*Vect<3>({-1, -1, 1});
	Vertex[1]=SL*Vect<3>({1, -1, 1});
	Vertex[2]=SL*Vect<3>({1, 1, 1});
	Vertex[3]=SL*Vect<3>({-1, 1, 1});	
		
	Vertex[4]=SL*Vect<3>({-1, -1, -1});
	Vertex[5]=SL*Vect<3>({1, -1, -1});
	Vertex[6]=SL*Vect<3>({1, 1, -1});
	Vertex[7]=SL*Vect<3>({-1, 1, -1});

	//top
	Vertex[8]=SL*Vect<3>({1.0/tht, 0, tht});
	Vertex[9]=SL*Vect<3>({-1.0/tht, 0, tht});
	
	//side A
	Vertex[10]=SL*Vect<3>({0, tht, 1.0/tht});
	Vertex[11]=SL*Vect<3>({0, tht, -1.0/tht});	

	//side B
	Vertex[12]=SL*Vect<3>({tht, 1.0/tht, 0});
	Vertex[13]=SL*Vect<3>({tht, -1.0/tht, 0});

	//Side -A
	Vertex[14]=SL*Vect<3>({0, -1.0*tht, 1.0/tht});
	Vertex[15]=SL*Vect<3>({0, -1.0*tht, -1.0/tht});

	//side -B
	Vertex[16]=SL*Vect<3>({-1.0*tht, 1.0/tht, 0});
	Vertex[17]=SL*Vect<3>({-1.0*tht, -1.0/tht, 0});

	//bottom
	Vertex[18]=SL*Vect<3>({1.0/tht, 0, -1.0*tht});
	Vertex[19]=SL*Vect<3>({-1.0/tht, 0, -1.0*tht});
	
	Edges=new sf::Vertex*[numEdges];
	for(int i=0; i<numEdges; i++){
		Edges[i]=new sf::Vertex[2];
	}
	
	Edges[0][0]=Cm->VtSFVx(RS.ltw(Vertex[8]));
	Edges[0][1]=Cm->VtSFVx(RS.ltw(Vertex[9]));

	Edges[1][0]=Cm->VtSFVx(RS.ltw(Vertex[0]));
	Edges[1][1]=Cm->VtSFVx(RS.ltw(Vertex[9]));

	Edges[2][0]=Cm->VtSFVx(RS.ltw(Vertex[8]));
	Edges[2][1]=Cm->VtSFVx(RS.ltw(Vertex[1]));

	Edges[3][0]=Cm->VtSFVx(RS.ltw(Vertex[8]));
	Edges[3][1]=Cm->VtSFVx(RS.ltw(Vertex[2]));
			
	Edges[4][0]=Cm->VtSFVx(RS.ltw(Vertex[9]));
	Edges[4][1]=Cm->VtSFVx(RS.ltw(Vertex[3]));

			//=============
			
	Edges[5][0]=Cm->VtSFVx(RS.ltw(Vertex[0]));
	Edges[5][1]=Cm->VtSFVx(RS.ltw(Vertex[14]));			

	Edges[6][0]=Cm->VtSFVx(RS.ltw(Vertex[1]));
	Edges[6][1]=Cm->VtSFVx(RS.ltw(Vertex[14]));

	Edges[7][0]=Cm->VtSFVx(RS.ltw(Vertex[14]));
	Edges[7][1]=Cm->VtSFVx(RS.ltw(Vertex[15]));

	Edges[8][0]=Cm->VtSFVx(RS.ltw(Vertex[15]));
	Edges[8][1]=Cm->VtSFVx(RS.ltw(Vertex[4]));

	Edges[9][0]=Cm->VtSFVx(RS.ltw(Vertex[15]));
	Edges[9][1]=Cm->VtSFVx(RS.ltw(Vertex[5]));

			//=============

	Edges[10][0]=Cm->VtSFVx(RS.ltw(Vertex[1]));
	Edges[10][1]=Cm->VtSFVx(RS.ltw(Vertex[13]));

	Edges[11][0]=Cm->VtSFVx(RS.ltw(Vertex[2]));
	Edges[11][1]=Cm->VtSFVx(RS.ltw(Vertex[12]));

	Edges[12][0]=Cm->VtSFVx(RS.ltw(Vertex[13]));
	Edges[12][1]=Cm->VtSFVx(RS.ltw(Vertex[12]));

	Edges[13][0]=Cm->VtSFVx(RS.ltw(Vertex[13]));
	Edges[13][1]=Cm->VtSFVx(RS.ltw(Vertex[5]));

	Edges[14][0]=Cm->VtSFVx(RS.ltw(Vertex[12]));
	Edges[14][1]=Cm->VtSFVx(RS.ltw(Vertex[6]));

			//====================

	Edges[15][0]=Cm->VtSFVx(RS.ltw(Vertex[2]));
	Edges[15][1]=Cm->VtSFVx(RS.ltw(Vertex[10]));
            
	Edges[16][0]=Cm->VtSFVx(RS.ltw(Vertex[3]));
			Edges[16][1]=Cm->VtSFVx(RS.ltw(Vertex[10]));

			Edges[17][0]=Cm->VtSFVx(RS.ltw(Vertex[10]));
			Edges[17][1]=Cm->VtSFVx(RS.ltw(Vertex[11]));

			Edges[18][0]=Cm->VtSFVx(RS.ltw(Vertex[11]));
			Edges[18][1]=Cm->VtSFVx(RS.ltw(Vertex[6]));

			Edges[19][0]=Cm->VtSFVx(RS.ltw(Vertex[11]));
			Edges[19][1]=Cm->VtSFVx(RS.ltw(Vertex[7]));

			//============

			Edges[20][0]=Cm->VtSFVx(RS.ltw(Vertex[3]));
			Edges[20][1]=Cm->VtSFVx(RS.ltw(Vertex[16]));

			Edges[21][0]=Cm->VtSFVx(RS.ltw(Vertex[0]));
			Edges[21][1]=Cm->VtSFVx(RS.ltw(Vertex[17]));
	
			Edges[22][0]=Cm->VtSFVx(RS.ltw(Vertex[16]));
			Edges[22][1]=Cm->VtSFVx(RS.ltw(Vertex[17]));

			Edges[23][0]=Cm->VtSFVx(RS.ltw(Vertex[16]));
			Edges[23][1]=Cm->VtSFVx(RS.ltw(Vertex[7]));

			Edges[24][0]=Cm->VtSFVx(RS.ltw(Vertex[17]));
			Edges[24][1]=Cm->VtSFVx(RS.ltw(Vertex[4]));

			//=============

			Edges[25][0]=Cm->VtSFVx(RS.ltw(Vertex[4]));
			Edges[25][1]=Cm->VtSFVx(RS.ltw(Vertex[19]));

			Edges[26][0]=Cm->VtSFVx(RS.ltw(Vertex[18]));
			Edges[26][1]=Cm->VtSFVx(RS.ltw(Vertex[19]));

			Edges[27][0]=Cm->VtSFVx(RS.ltw(Vertex[19]));
			Edges[27][1]=Cm->VtSFVx(RS.ltw(Vertex[7]));

			Edges[28][0]=Cm->VtSFVx(RS.ltw(Vertex[5]));
			Edges[28][1]=Cm->VtSFVx(RS.ltw(Vertex[18]));

			Edges[29][0]=Cm->VtSFVx(RS.ltw(Vertex[18]));
			Edges[29][1]=Cm->VtSFVx(RS.ltw(Vertex[6]));

		for(int i=0; i<30; i++){
			Edges[i][0].color=Color;
			Edges[i][1].color=Color;
		}
	
}

/*
bool Dodecahedron::updateEdges(){
	if(hasChanged){

			Cm->updateVertex(Edges[0][0], RS.ltw(Vertex[8]));
			Cm->updateVertex(Edges[0][1], RS.ltw(Vertex[9]));
			
			Cm->updateVertex(Edges[1][0], RS.ltw(Vertex[0]));
			Cm->updateVertex(Edges[1][1], RS.ltw(Vertex[9]));

			Cm->updateVertex(Edges[2][0], RS.ltw(Vertex[8]));
			Cm->updateVertex(Edges[2][1], RS.ltw(Vertex[1]));

			Cm->updateVertex(Edges[3][0], RS.ltw(Vertex[8]));
			Cm->updateVertex(Edges[3][1], RS.ltw(Vertex[2]));
			
			Cm->updateVertex(Edges[4][0], RS.ltw(Vertex[9]));
			Cm->updateVertex(Edges[4][1], RS.ltw(Vertex[3]));

			//=============
			
			Cm->updateVertex(Edges[5][0], RS.ltw(Vertex[0]));
			Cm->updateVertex(Edges[5][1], RS.ltw(Vertex[14]));			

			Cm->updateVertex(Edges[6][0], RS.ltw(Vertex[1]));
			Cm->updateVertex(Edges[6][1], RS.ltw(Vertex[14]));

			Cm->updateVertex(Edges[7][0], RS.ltw(Vertex[14]));
			Cm->updateVertex(Edges[7][1], RS.ltw(Vertex[15]));
			
			Cm->updateVertex(Edges[8][0], RS.ltw(Vertex[15]));
			Cm->updateVertex(Edges[8][1], RS.ltw(Vertex[4]));
			
			Cm->updateVertex(Edges[9][0], RS.ltw(Vertex[15]));
			Cm->updateVertex(Edges[9][1], RS.ltw(Vertex[5]));

			//=============

			Cm->updateVertex(Edges[10][0], RS.ltw(Vertex[1]));
			Cm->updateVertex(Edges[10][1], RS.ltw(Vertex[13]));

			Cm->updateVertex(Edges[11][0], RS.ltw(Vertex[2]));
			Cm->updateVertex(Edges[11][1], RS.ltw(Vertex[12]));

			Cm->updateVertex(Edges[12][0], RS.ltw(Vertex[13]));
			Cm->updateVertex(Edges[12][1], RS.ltw(Vertex[12]));

			Cm->updateVertex(Edges[13][0], RS.ltw(Vertex[13]));
			Cm->updateVertex(Edges[13][1], RS.ltw(Vertex[5]));

			Cm->updateVertex(Edges[14][0], RS.ltw(Vertex[12]));
			Cm->updateVertex(Edges[14][1], RS.ltw(Vertex[6]));

			//====================

			Cm->updateVertex(Edges[15][0], RS.ltw(Vertex[2]));
			Cm->updateVertex(Edges[15][1], RS.ltw(Vertex[10]));			

			Cm->updateVertex(Edges[16][0], RS.ltw(Vertex[3]));
			Cm->updateVertex(Edges[16][1], RS.ltw(Vertex[10]));			
			
			Cm->updateVertex(Edges[17][0], RS.ltw(Vertex[10]));
			Cm->updateVertex(Edges[17][1], RS.ltw(Vertex[11]));			

			Cm->updateVertex(Edges[18][0], RS.ltw(Vertex[11]));
			Cm->updateVertex(Edges[18][1], RS.ltw(Vertex[6]));			

			Cm->updateVertex(Edges[19][0], RS.ltw(Vertex[11]));
			Cm->updateVertex(Edges[19][1], RS.ltw(Vertex[7]));			

			//============

			Cm->updateVertex(Edges[20][0], RS.ltw(Vertex[3]));
			Cm->updateVertex(Edges[20][1], RS.ltw(Vertex[16]));

			Cm->updateVertex(Edges[21][0], RS.ltw(Vertex[0]));
			Cm->updateVertex(Edges[21][1], RS.ltw(Vertex[17]));

			Cm->updateVertex(Edges[22][0], RS.ltw(Vertex[16]));
			Cm->updateVertex(Edges[22][1], RS.ltw(Vertex[17]));

			Cm->updateVertex(Edges[23][0], RS.ltw(Vertex[16]));
			Cm->updateVertex(Edges[23][1], RS.ltw(Vertex[7]));

			Cm->updateVertex(Edges[24][0], RS.ltw(Vertex[17]));
			Cm->updateVertex(Edges[24][1], RS.ltw(Vertex[4]));			
			
			//=============

			Cm->updateVertex(Edges[25][0], RS.ltw(Vertex[4]));
			Cm->updateVertex(Edges[25][1], RS.ltw(Vertex[19]));

			Cm->updateVertex(Edges[26][0], RS.ltw(Vertex[18]));
			Cm->updateVertex(Edges[26][1], RS.ltw(Vertex[19]));
			
			Cm->updateVertex(Edges[27][0], RS.ltw(Vertex[19]));
			Cm->updateVertex(Edges[27][1], RS.ltw(Vertex[7]));
			
			Cm->updateVertex(Edges[28][0], RS.ltw(Vertex[5]));
			Cm->updateVertex(Edges[28][1], RS.ltw(Vertex[18]));

			Cm->updateVertex(Edges[29][0], RS.ltw(Vertex[18]));
			Cm->updateVertex(Edges[29][1], RS.ltw(Vertex[6]));
			
		hasChanged=false;
		return !hasChanged;
	}
	return hasChanged;
}
/**/
//*
bool Dodecahedron::updateEdges(){
	if(hasChanged){
			Vect<3> W=RS.ltw(Vertex[8]);

			Cm->updateVertex(Edges[0][0], W);
			Cm->updateVertex(Edges[2][0], W);
			Cm->updateVertex(Edges[3][0], W);
			
			W=RS.ltw(Vertex[9]);
			Cm->updateVertex(Edges[0][1], W);
			Cm->updateVertex(Edges[1][1], W);
			Cm->updateVertex(Edges[4][0], W);			
			
			W=RS.ltw(Vertex[0]);
			Cm->updateVertex(Edges[1][0], W);
			Cm->updateVertex(Edges[5][0], W);
			Cm->updateVertex(Edges[21][0], W);

			W=RS.ltw(Vertex[1]);
			Cm->updateVertex(Edges[2][1], W);
			Cm->updateVertex(Edges[6][0], W);
			Cm->updateVertex(Edges[10][0], W);

			W=RS.ltw(Vertex[2]);
			Cm->updateVertex(Edges[11][0], W);
			Cm->updateVertex(Edges[3][1], W);			
			Cm->updateVertex(Edges[15][0], W);

			W=RS.ltw(Vertex[3]);
			Cm->updateVertex(Edges[16][0], W);			
			Cm->updateVertex(Edges[4][1], W);
			Cm->updateVertex(Edges[20][0], W);
			
			W=RS.ltw(Vertex[4]);			
			Cm->updateVertex(Edges[8][1], W);
			Cm->updateVertex(Edges[24][1], W);
			Cm->updateVertex(Edges[25][0], W);	
			
			W=RS.ltw(Vertex[5]);
			Cm->updateVertex(Edges[9][1], W);
			Cm->updateVertex(Edges[13][1], W);
			Cm->updateVertex(Edges[28][0], W);

			W=RS.ltw(Vertex[6]);
			Cm->updateVertex(Edges[14][1], W);
			Cm->updateVertex(Edges[18][1], W);	
			Cm->updateVertex(Edges[29][1], W);

			W=RS.ltw(Vertex[7]);
			Cm->updateVertex(Edges[27][1], W);
			Cm->updateVertex(Edges[19][1], W);
			Cm->updateVertex(Edges[23][1], W);
			//=============
			
			W=RS.ltw(Vertex[14]);
			Cm->updateVertex(Edges[5][1], W);			
			Cm->updateVertex(Edges[6][1], W);
			Cm->updateVertex(Edges[7][0], W);

			W=RS.ltw(Vertex[15]);
			Cm->updateVertex(Edges[7][1], W);			
			Cm->updateVertex(Edges[8][0], W);
			Cm->updateVertex(Edges[9][0], W);
						
			//=============
			W=RS.ltw(Vertex[13]);
			Cm->updateVertex(Edges[10][1], W);
			Cm->updateVertex(Edges[12][0], W);
			Cm->updateVertex(Edges[13][0], W);
			
			W=RS.ltw(Vertex[12]);
			Cm->updateVertex(Edges[11][1], W);			
			Cm->updateVertex(Edges[12][1], W);
			Cm->updateVertex(Edges[14][0], W);
			
			//====================
			W=RS.ltw(Vertex[10]);
			Cm->updateVertex(Edges[15][1], W);
			Cm->updateVertex(Edges[16][1], W);
			Cm->updateVertex(Edges[17][0], W);			
			
			W=RS.ltw(Vertex[11]);
			Cm->updateVertex(Edges[17][1], W);			
			Cm->updateVertex(Edges[18][0], W);
			Cm->updateVertex(Edges[19][0], W);
			
			//============
			W=RS.ltw(Vertex[16]);			
			Cm->updateVertex(Edges[20][1], W);
			Cm->updateVertex(Edges[22][0], W);
			Cm->updateVertex(Edges[23][0], W);

			W=RS.ltw(Vertex[17]);
			Cm->updateVertex(Edges[21][1], W);
			Cm->updateVertex(Edges[22][1], W);
			Cm->updateVertex(Edges[24][0], W);		
			
			//=============			
			W=RS.ltw(Vertex[18]);
			Cm->updateVertex(Edges[26][0], W);
			Cm->updateVertex(Edges[28][1], W);
			Cm->updateVertex(Edges[29][0], W);

			W=RS.ltw(Vertex[19]);
			Cm->updateVertex(Edges[25][1], W);
			Cm->updateVertex(Edges[26][1], W);
			Cm->updateVertex(Edges[27][0], W);
			
		hasChanged=false;
		return !hasChanged;
	}
	return hasChanged;
}
/**/
void Dodecahedron::rotate(){
	static Rotation<3> Rt({1,3,1}, -3.0);
	Centroid=Rt(Centroid);
	//Cm->angCos(this);
	for(int i=0; i<20; i++){
		Vertex[i]=Rt(Vertex[i]);
	}
	//hasChanged=true;
}


void Dodecahedron::set_position(const Vect<3>& V){
	RS.move(V);
	hasChanged=Cm->angCos(this);
}



//####################################################################
//####################################################################
//####################################################################


Tesseract::Tesseract(std::shared_ptr<RSpace<3>> _RS, sf::Color color)
	: Shape(_RS, 32, color)
{
	Vertex=new Vect<3>[1];// README: this is just a place holder to avoid conflict with the destructor
	Vertex2=new Vect<4>[16];
	Vertex2[0]=Vect<4>({0, 0, 0, 0});
	Vertex2[1]=Vect<4>({SL, 0, 0, 0});
	Vertex2[2]=Vect<4>({SL, SL, 0,0});
	Vertex2[3]=Vect<4>({0, SL, 0, 0});
	Vertex2[4]=Vect<4>({0, 0, SL, 0});
	Vertex2[5]=Vect<4>({SL, 0, SL, 0});
	Vertex2[6]=Vect<4>({SL, SL, SL, 0});
	Vertex2[7]=Vect<4>({0, SL, SL, 0});

	Vertex2[8]=Vect<4>({0, 0, 0, SL});	
	Vertex2[9]=Vect<4>({SL, 0, 0, SL});
	Vertex2[10]=Vect<4>({SL, SL, 0, SL});
	Vertex2[11]=Vect<4>({0, SL, 0, SL});
	Vertex2[12]=Vect<4>({0, 0, SL, SL});
	Vertex2[13]=Vect<4>({SL, 0, SL, SL});
	Vertex2[14]=Vect<4>({SL, SL, SL, SL});
	Vertex2[15]=Vect<4>({0, SL, SL, SL});

	Edges=new sf::Vertex*[numEdges];
	for(int i=0; i<numEdges; i++){
		Edges[i]=new sf::Vertex[2];
	}
};


Tesseract::~Tesseract(){
	delete[] Vertex2;
}

inline void Tesseract::draw(){
	for(int i=0; i<numEdges; i++){
		Window->draw(Edges[i], 2, sf::Lines);
	}
}

Vect<3> proj(Vect<4>& V){
	//cout<<V.proj(3)<<endl;
	return V.proj(4);
}
bool Tesseract::updateEdges(){
	if(1){//hasChanged){
		int j, k, t;
		for(int i=0; i<8; i++){
			j=4*(i/4)+(i+1)%4;
			Edges[i][0]=Cm->VtSFVx(RS.ltw(proj(Vertex2[i])));
			Edges[i][1]=Cm->VtSFVx(RS.ltw(proj(Vertex2[j])));
			
			Edges[i][0].color=sf::Color::Blue;
			Edges[i][1].color=sf::Color::Blue;
		}
		for(int i=8; i<12; i++){
			Edges[i][0]=Edges[i-8][0];
			Edges[i][1]=Edges[i-4][0];
		}
		
		for(int i=12; i<20; i++){
			k=i-4;
			j=4*(k/4)+(k+1)%4;
			Edges[i][0]=Cm->VtSFVx(RS.ltw(proj(Vertex2[k])));
			Edges[i][1]=Cm->VtSFVx(RS.ltw(proj(Vertex2[j])));
			
			Edges[i][0].color=Color;
			Edges[i][1].color=Color;
		}
		for(int i=20; i<24; i++){
			Edges[i][0]=Edges[i-8][0];
			Edges[i][1]=Edges[i-4][0];
		}
		for(int i=24; i<numEdges; i++){
			Edges[i][0]=Cm->VtSFVx(RS.ltw(proj(Vertex2[i-24])));
			Edges[i][1]=Cm->VtSFVx(RS.ltw(proj(Vertex2[i-16])));
			Edges[i][0].color=sf::Color::Green;
			Edges[i][1].color=sf::Color::Green;
		}
		hasChanged=false;
		return !hasChanged;
	}
	return hasChanged;
}

void Tesseract::rotate(){
	static Rotation<4> Rt({1,1,1,1}, 2.0);

	Centroid2=Rt(Centroid2);
	Centroid=proj(Centroid2);

	for(int i=0; i<16; i++){
		Vertex2[i]=Rt(Vertex2[i]);
	}
	hasChanged=Cm->angCos(this);;
	
	
}

void Tesseract::set_position(const Vect<3>& V){
	RS.move(V);
	hasChanged=Cm->angCos(this);
}


//####################################################################
//####################################################################


