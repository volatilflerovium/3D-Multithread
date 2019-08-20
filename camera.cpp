/*********************************************************************
* camera class                               								*
*                                                                    *
* Version: 1.0                                                       *
* Date:    21-03-2019                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#include<thread>
#include "camera.h"
using namespace std;

//====================================================================

Camera::Camera(std::shared_ptr<RSpace<3>> _RS, double _fD, double ap)
	:__RS(_RS), RS(*_RS), fD(_fD), app(ap)
{
	Ax=RS.getPos();
	Ax=Vect<3>({-1.0*Ax.coordinate(1), Ax.coordinate(0), 0});

	threshold=fD/sqrt(fD*fD+app*app);

	vertex[0]=Vect<3>({0,0,0});
	vertex[1]=Vect<3>(1);
	vertex[2]=Vect<3>(2);
	vertex[3]=Vect<3>(3);
}

//====================================================================

void Camera::updateVertex(sf::Vertex& V, const Vect<3>& W){	
	static thread_local Vect<3> Cv;
	Cv=RS.wtl(W);
	Cv*=fD/Cv.coordinate(2);
	V.position.x=RF->trans_x(ppWx(Cv.coordinate(0)));
	V.position.y=RF->trans_y(ppWy(Cv.coordinate(1)));

}

//====================================================================

sf::Vertex Camera::VtSFVx(const Vect<3>& V) const{
	static Vect<3> Cv;
	Cv=RS.wtl(V);
	Cv*=fD/Cv.coordinate(2);
	
	return sf::Vertex(sf::Vector2f(RF->trans_x(ppWx(Cv.coordinate(0))), RF->trans_y(ppWx(Cv.coordinate(1)))));
}

//====================================================================

void Camera::lRuD(int k){
	static Rotation<3> RT[4]={Rotation<3>({0,0,1}, 5.0), 
					Rotation<3>({0,0,1}, -5.0),
					Rotation<3>(Ax, 5.0),
					Rotation<3>(Ax, -5.0)};

	k-=71;
	if(hasChanged && k>1){
		RT[2]=Rotation<3>(Ax, 5.0);
		RT[3]=Rotation<3>(Ax, -5.0);
		hasChanged=false;
	}

	if(k<2){//left or right
		Ax=RT[k](Ax);
		hasChanged=true;
	}

	Vect<3> V(RS.getPos());
	RS.move(RT[k](RS.getPos())-V);	
}

//====================================================================

bool Camera::angCos(Shape* shp){	
	return (fast_cos(RS.wtl(shp->getCentroidW()))>=threshold);//ang_cos(RS.wtl(shp->getCentroidW()), vertex[3])>=threshold;
}

