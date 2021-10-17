/*********************************************************************
* ReferenceFrame class                                               *
*                                                                    *
* Version: 1.5                                                       *
* Date:    25-07-2021                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#ifndef REF_FRAME_H
#define REF_FRAME_H

#include "helper.h"

class ReferenceFrame
{
   public:   
   	ReferenceFrame() = delete;
		ReferenceFrame& operator=(const ReferenceFrame& RF) = delete;

		ReferenceFrame(double x, double y, double size=0.0);// size in cm
      
		double trans_x(double x) const;
		double trans_y(double y) const;
		const double& rt() const;

	private:
		double m_ration{1.0};
		const double c_px_per_cm{PX_CM};//37.795238;
		double m_originX;
		double m_originY;
};

//-------------------------------------------------------------------

inline ReferenceFrame::ReferenceFrame(double x, double y, double size) // size is metres to scale down to 1 cm
       :m_originX(x), m_originY(y)
{
   if(size>0){
      m_ration=c_px_per_cm/(1.0*size);
   }
}

//-------------------------------------------------------------------

inline const double& ReferenceFrame::rt() const{
   return m_ration;
}

//-------------------------------------------------------------------

inline double ReferenceFrame::trans_x(double x) const{
	return x+m_originX;
}

//-------------------------------------------------------------------

inline double ReferenceFrame::trans_y(double y) const{
	return m_originY-y;
}

//-------------------------------------------------------------------

#endif
