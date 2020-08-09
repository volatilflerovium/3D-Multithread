#ifndef NOISE_H
#define NOISE_H


using namespace std;

class Noise
{
	private:
		//static bool nx;
		int step;
		double r, s, la, lb;
		int seed, local_stp;
		double factor; // how much we want to stretch the result
		double interpolation(double w);

	public:
		//Noise();
		Noise(double _factor=3.0);
		double IntegerNoise();
		double lerp();
		//void move();
};

//bool Noise::nx=true;
//int Noise::step=0;

//--------------------------------------------------------------------
/*
inline Noise::Noise()
	: seed(105+rand()%10000), local_stp(0), factor(3){}
/**/
//--------------------------------------------------------------------

inline Noise::Noise(double _factor)
	: seed(105+rand()%10000), local_stp(0), factor(_factor){
	lb=IntegerNoise();
	seed++;
}

//--------------------------------------------------------------------

inline double Noise::interpolation(double w){
//	cout<<la<<" "<<lb<<" "<<w<<"+++++++++++++"<<endl;
	
	w=w*(w*(w*(6.0*pow(w,2)-15.0*w + 10.0)));
   return la*(1 - w)+lb*w;
}

//--------------------------------------------------------------------
/*
inline void Noise::move(){
  if(nx){
  	step=20+rand()%100;
  	nx=false;
  }
}
/**/
//--------------------------------------------------------------------

#endif