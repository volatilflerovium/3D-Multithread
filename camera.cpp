//#include <thread>
#include "camera.h"

using namespace std;

//====================================================================

Camera::Camera(std::shared_ptr<RSpace<3>> _RS, double _fD, double aperture)
	:__RS(_RS), m_RS(*_RS), m_Ax(m_RS.getPos()),
	m_vertex{Vect<3>{0,0,0}, Vect<3>(0), Vect<3>(1), Vect<3>(2)},
	m_fD(_fD), m_app(1.0/(2.0*aperture))
{
	m_Ax=Vect<3>{-1.0*m_Ax[1], m_Ax[0], 0};

	m_threshold=m_fD/sqrt(m_fD*m_fD+aperture*aperture);
}

//======================================================================

void Camera::updateVertex(sf::Vertex& V, const Vect<3>& W){	
	static thread_local Vect<3> Cv;
	Cv=m_RS.world2Local(W);

	V.position.x=m_WorldFrame->trans_x(ppWx(Cv[0]*(m_fD/Cv[2])));
	V.position.y=m_WorldFrame->trans_y(ppWy(Cv[1]*(m_fD/Cv[2])));
}

//======================================================================

sf::Vertex Camera::VtSFVx(const Vect<3>& V) const{
	static thread_local Vect<3> Cv;
	Cv=m_RS.world2Local(V);
	
	return sf::Vertex(sf::Vector2f(m_WorldFrame->trans_x(ppWx(Cv[0]*(m_fD/Cv[2]))), m_WorldFrame->trans_y(ppWx(Cv[1]*(m_fD/Cv[2])))));
}

//======================================================================

void Camera::lRuD(int k){
	static thread_local Rotation<3> RT[4]={Rotation<3>({0,0,1}, 5.0), 
					Rotation<3>({0,0,1}, -5.0),
					Rotation<3>(m_Ax, 5.0),
					Rotation<3>(m_Ax, -5.0)};

	k-=71;
	if(m_hasChanged && k>1){
		RT[2]=Rotation<3>(m_Ax, 5.0);
		RT[3]=Rotation<3>(m_Ax, -5.0);
		m_hasChanged=false;
	}

	if(k<2){//left or right
		RT[k].rotate(m_Ax);
		m_hasChanged=true;
	}

	Vect<3> V(m_RS.getPos());
	RT[k].rotate(V);
	V-=m_RS.getPos();
	m_RS.move(V);	
}

//======================================================================
