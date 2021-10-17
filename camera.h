/*********************************************************************
* camera class                               								*
*                                                                    *
* Version: 1.5                                                       *
* Date:    25-07-2021                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include "helper.h"
#include "base.h"
#include "vector.h"
#include "rspace.h"
#include "shape.h"

using namespace std;

class Camera : public Base
{
	public:
		Camera(std::shared_ptr<RSpace<3>> _RS, double _fD, double ap);		
		void updateAngle(int i, double ang);
		void draw();
		sf::Vertex VtSFVx(const Vect<3>& V) const;
		void lRuD(int k);
		void angCos(Shape* shp);
		void updateVertex(sf::Vertex& V, const Vect<3>& W);
		double angCos(const Vect<3>& V) const; // V is in world coordinates		

	private:
		RSpace<3>& m_RS;
		Vect<3> m_Ax;
		Vect<3> m_vertex[4];
		std::shared_ptr<RSpace<3>> __RS;

		double m_fD;
		double m_app;
		double m_threshold{0};
		bool m_hasChanged{false};

		double ppWx(double d) const;
		double ppWy(double d) const;
};

//======================================================================

inline void Camera::updateAngle(int i, double ang){
	m_RS.updateTrans(i, ang);
}

//======================================================================

inline double Camera::ppWx(double d) const {
	return d*D_WINDOW_WIDTH*m_app;
}

//======================================================================

inline double Camera::ppWy(double d) const {
	return d*D_WINDOW_HEIGHT*m_app;
}

//======================================================================

inline void Camera::angCos(Shape* shp){	
	shp->setDisplay(fast_cos(m_RS.world2Local(shp->getCentroidW()))>=m_threshold);
}

//======================================================================

// V is in world coordinates
inline double Camera::angCos(const Vect<3>& V) const{
	return ang_cos(m_RS.world2Local(V), m_vertex[3]);
}

//======================================================================


#endif
