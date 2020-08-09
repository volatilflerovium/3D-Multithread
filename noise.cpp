#include<ctime>
#include<cmath>
#include<cstdlib>

#include "noise.h"

using namespace std;

double Noise::IntegerNoise(){
   int n = (seed >> 13) ^ seed;
   n = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;
   return 1.0*factor*(1.0 - ((double)n / 1073741824.0));
}


double Noise::lerp(){
	if(local_stp==0){
		la=lb;
		lb=IntegerNoise();
		local_stp=20+rand()%100;
		seed++;
		r=1.0/local_stp;
		s=0;
	}
	s+=r;
	local_stp--;
   return interpolation(s);
}



