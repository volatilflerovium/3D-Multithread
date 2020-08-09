#ifndef REF_FRAME_H
#define REF_FRAME_H
#include "helper.h"

class ReferenceFrame
{
   private:
      double ration=1.0;
      const double px_per_cm=PX_CM;//37.795238;
      float Origin_x;
      float Origin_y;
      
   public:
   
   	ReferenceFrame() = delete;
		ReferenceFrame& operator=(const ReferenceFrame& RF) = delete;

		ReferenceFrame(float x, float y, double size=0.0);// size in cm
      
      float trans_x(float x) const;
      float trans_y(float y) const;
      const double& rt() const;
      
};

//-------------------------------------------------------------------

inline ReferenceFrame::ReferenceFrame(float x, float y, double size) // size is metres to scale down to 1 cm
       :Origin_x(x), Origin_y(y)
{
   if(size>0)
   {
      ration=px_per_cm/(1.0*size);
   }
}

//-------------------------------------------------------------------

inline const double& ReferenceFrame::rt() const{
   return ration;
}

//-------------------------------------------------------------------

inline float ReferenceFrame::trans_x(float x) const{
	return x+Origin_x;
}

//-------------------------------------------------------------------

inline float ReferenceFrame::trans_y(float y) const{
	return Origin_y-y;
}

//-------------------------------------------------------------------

#endif