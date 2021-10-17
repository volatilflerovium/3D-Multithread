#include <ctime>
#include <cmath>
#include <cstdlib>

#include "noise.h"

using namespace std;

//======================================================================

double Noise::IntegerNoise(){
   int n = (m_seed >> 13) ^ m_seed;
   n = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
   return 1.0*m_factor*(1.0 - ((double)n / 1073741824.0));
}

//======================================================================

double Noise::lerp(){
	if(m_localStp==0){
		m_la=m_lb;
		m_lb=IntegerNoise();
		m_localStp=20+rand()%100;
		m_seed++;
		m_r=1.0/m_localStp;
		m_s=0;
	}
	m_s+=m_r;
	m_localStp--;
   return interpolation(m_s);
}

//======================================================================


