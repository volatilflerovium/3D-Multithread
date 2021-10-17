/*********************************************************************
* vector and rotation classes                  								*
*                                                                    *
* Version: 1.5                                                       *
* Date:    24-07-2021                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/

#ifndef VECTOR_CLASS_H
#define VECTOR_CLASS_H

#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;

//README: for value of pi use M_PI which is part of cmath

//###################################################################
//###################################################################

template<int D>
class Vect
{
	public:
		Vect();

		explicit Vect(int i, double p=1.0);

		Vect(double (&arr)[D]);
		Vect(const Vect<D>& V);
		Vect(std::initializer_list<double> l);
		Vect<D>& operator=(const Vect<D>& V);
		int get_dimension() const;
		bool operator==(const Vect<D>& v);
		bool operator!=(const Vect<D>& v);
		Vect<D>& operator+=(const Vect<D>& w);
		Vect<D>& operator-=(const Vect<D>& w);
		Vect<D> operator+(const Vect<D>& W);
		Vect<D> operator-(const Vect<D>& W);
		Vect<D>& operator*=(double f);

		static Vect canonical(int i);

		double operator[](int i)const;

		// utilities
		double coordinate(int n) const;
		double norm() const;
		Vect<D>& canonical_reflexion(int p);
		Vect<D>& normalize();
		Vect<D-1> projection(int p);

		void fastOp(double f, const Vect<D>& W);

	private:
		unsigned const int m_dimension;		
		double m_V[D];
};

//===================================================================

template<int D>
Vect<D>::Vect()
:m_dimension(D)
{
	for(int i=0; i<D; i++){
		m_V[i]=1.0;
	}
}

//===================================================================

template<int D>
Vect<D>::Vect(int i, double p)
:m_dimension(D)
{
	for(int j=0; j<D; j++){
		m_V[j]=0;
	}
	if(i>=0 && i<D){
		m_V[i]=1*p;
	}
}

//===================================================================

template<int D>
Vect<D>::Vect(double (&arr)[D])
:m_dimension(D)
{
	std::memcpy(m_V, arr, m_dimension*sizeof(double));
}

//===================================================================

template<int D>
Vect<D> Vect<D>::canonical(int i)
{
	Vect<D> result;
	for(int j=0; j<D; j++){
		if(j!=i){
			result.m_V[i]=0;
		}
	}
	return result;
}

//===================================================================

template<int D>
Vect<D>::Vect(std::initializer_list<double> l)
:Vect()
{
	int i=0;
	for(double x : l){
		m_V[i++]=x;
		if(i==D){
			break;
		}
	}
}

//===================================================================

template<int D>
Vect<D>::Vect(const Vect<D>& W)
:m_dimension(D)
{
	std::memcpy(m_V, W.m_V, m_dimension*sizeof(double));
}

//===================================================================

template<int D>
int Vect<D>::get_dimension() const{
	return m_dimension;
}

//===================================================================

template<int D>
Vect<D>& Vect<D>::operator=(const Vect<D>& W){
	std::memcpy(m_V, W.m_V, m_dimension*sizeof(double));
	return *this;
}

//===================================================================

template<int D>
bool Vect<D>::operator==(const Vect<D>& W){
	if(this==&W){
		return true;
	}
	
	for(int i=0; i<m_dimension; i++){
		if(m_V[i]!=W.m_V[i]){
			return false;
		}
	}
	
	return true;
}
//===================================================================

template<int D>
bool Vect<D>::operator!=(const Vect<D>& W){
	return !(*this==W);
}

//===================================================================

template<int D>
Vect<D>& Vect<D>::operator+=(const Vect<D>& W){
	for(int i=0; i<m_dimension; i++){
		m_V[i]+=W.m_V[i];		
	}
	return *this;
}

//===================================================================

template<int D>
Vect<D>& Vect<D>::operator-=(const Vect<D>& W){
	for(int i=0; i<m_dimension; i++){
		m_V[i]-=W.m_V[i];		
	}
	return *this;
}

//===================================================================

template<int D>
Vect<D> Vect<D>::operator+(const Vect<D>& W){ 
	Vect<D> V(*this);
	V+=W;
	return V;
}

//===================================================================

template<int D>
Vect<D> Vect<D>::operator-(const Vect<D>& W){	
	Vect<D> V(*this);
	V-=W;
	return V;
}

//===================================================================

template<int D>
Vect<D>& Vect<D>::operator*=(double f){
	for(int i=0; i<D; i++){
		m_V[i]*=f;		
	}
	return *this;
}

//===================================================================

template<int D>
double Vect<D>::operator[](int i)const {
	return m_V[i];
}

//===================================================================

template<int D>
double Vect<D>::norm() const{
	double sum=0;
	for(int i=0; i<m_dimension; i++){
		sum+=m_V[i]*m_V[i];
	}
	return sqrt(sum);
}

//===================================================================

template<int D>
Vect<D>& Vect<D>::normalize(){
	(*this)*=1/norm();
	return *this;
}

//===================================================================

/*
This is a reflexion with respect to the hyperplane orthogonal to the p-th
element of the canonical base.
*/

template<int D>
Vect<D>& Vect<D>::canonical_reflexion(int p){
	if(p<m_dimension){
		m_V[p]*=-1;
	}
	return *this;
}

//===================================================================

template<int D>
Vect<D-1> Vect<D>::projection(int p){
	Vect<D-1> W(0);
	int j=0;
	for(int i=0; i<D; i++){
		if(i!=p){
			W+=m_V[i]*Vect<D-1>(j++);
		}
	}
	return W;
}

//===================================================================

template<int D>
void Vect<D>::fastOp(double f, const Vect<D>& W){
	for(int i=0; i<D; i++){
		m_V[i]+=f*W.m_V[i];
	}	
}

//===================================================================
//###################################################################
//===================================================================

template<int D>
Vect<D> operator*(double f, const Vect<D>& V){
	Vect<D> W(V);
	return W*=f;
}

//===================================================================

template<int D>
Vect<D> operator*(const Vect<D>& V, double f){
	return f*V;
} 

//===================================================================

template<int D>
Vect<D> operator/(const Vect<D>& V, double f){
	return (1.0/f)*V;
}
 
//===================================================================


template<int D>
Vect<D> operator+(const Vect<D>& U, const Vect<D>& V){
	Vect<D> W(U);
	W+=V;
	return W;
}

//===================================================================

template<int D>
Vect<D> operator-(const Vect<D>& U, const Vect<D>& V){
	Vect<D> W(U);
	W-=V;
	return W;
}

//===================================================================

template<int D>
ostream& operator<<(ostream& out, const Vect<D>& v){
	out<<'(';
	for(int i=0; i<D; i++){
		out<<v[i];
		if(i<D-1){
			out<<", ";
		}
	}
	out<<')';
	return out;
}

//===================================================================

template<int D>
double innerProduct(const Vect<D>& V, const Vect<D>& W){
	double dprod=0;
	for(int i=0; i<D; i++){
		dprod+=V[i]*W[i];
	}
	return dprod;
}

//===================================================================

template<int D>
double ang_cos(const Vect<D>& V, const Vect<D>& W){
	return innerProduct(V, W)/(V.norm()*W.norm());
}

//===================================================================

template<int D>
double fast_cos(const Vect<D>& V){
	return V[D-1]/V.norm();
}

//===================================================================

template<int D>
double distance(const Vect<D>& V, const Vect<D>& W){
	double sum=0;
	for(int i=0; i<V.get_dimension; i++){
		sum+=pow(V[i]-W[i], 2);
	}
	return sqrt(sum);
}


//===================================================================
//################################################################### 
//################################################################### 

template<int D>
class Rotation
{
	public:		
		Rotation()=delete;

		//line of rotation is the line through origin 
		//determined by the vector V, angle
		Rotation(Vect<D> V, double angle);

		// line of rotation is the line determined by the vectors 
		// vector V and W, angle
		Rotation(Vect<D> V, Vect<D> W, double angle);
		Rotation(const Rotation<D>& Rt);
		double getRotationAngle() const;
		
		void rotate(Vect<D>& V, const Vect<D>& OffV);
		void rotate(Vect<D>& V);
		void revRotate(Vect<D>& V, const Vect<D>& OffV);
		void revRotate(Vect<D>& V);
		Vect<D> reverse(const Vect<D>& V);

	private:
		Vect<D> m_p1;
		Vect<D> m_p2;
		Vect<D> m_offset;
		double m_rad;
		double m_COS;
		double m_t;

		void setup(Vect<D> rotation_axe);
		double set_angle(double angle);
};

//======================================================================

template<int D>
Rotation<D>::Rotation(const Rotation<D>& Rt)
:m_p1(Rt.m_p1), 
m_p2(Rt.m_p2),
m_offset(Rt.m_offset),
m_rad(Rt.m_rad), m_COS(Rt.m_COS)
{}

//======================================================================

template<int D>
Rotation<D>::Rotation(Vect<D> rotation_axe, double angle)
:m_offset(0, 0), m_rad(set_angle(angle)), m_COS(cos(m_rad))
{
	setup(rotation_axe);
}

//======================================================================

template<int D>
Rotation<D>::Rotation(Vect<D> V, Vect<D> W, double angle)
:m_offset(W), m_rad(set_angle(angle)), m_COS(cos(m_rad))
{
	setup(V-m_offset);
}

//======================================================================

template<int D>
double Rotation<D>::set_angle(double angle){
	if(fabs(angle)>=360.0){
		angle=(fabs(angle)/angle)*(fabs(angle)-360.0);
	}
	return -1.0*((angle/2)*M_PI)/180;
}


//======================================================================

template<int D>
inline double Rotation<D>::getRotationAngle() const{
	return m_rad;
}

//======================================================================

template<int D>
void Rotation<D>::setup(Vect<D> rotationAxe){
	/*
	First we get a canonical solution to the equation axe dot v=0.
	This is everything zero except 2 for example
	axe =(a,b,c,d);
	v=(0,c,-b,0); where b!=0 || c!=0
	*/
	double a[D]={0, 0};
	double b[D]={1, 1};
	double s[D]={1, 1};
	int P[2]={0,1};
	// we get two non zero values
	if(D>2){
		for(int i=2; i<D; i++){
			a[i]=0;
			b[i]=1;
			s[i]=1;
			if(fabs(rotationAxe[P[0]])+fabs(rotationAxe[P[1]])==0){
				if(rotationAxe[i]>0.0){
					P[0]=i-1;
					P[1]=i;
				}
			}
		}
		
		a[P[0]]=rotationAxe[P[1]];
		a[P[1]]=-1.0*rotationAxe[P[0]];
		Vect<D> p(a);

		b[P[0]]=0;
		b[P[1]]=0;
		Vect<D> B(b);

	   /*
		Now, we use p to construct an orthogonal vector W 
		WE CAN USE the cross product!! 
		NOOO, of course NOT!!! 
		we need something easier... and fast!
		*/
		double r=rotationAxe[P[0]]*p[P[1]]-rotationAxe[P[1]]*p[P[0]];
		s[P[0]]=(-1.0*innerProduct(B, rotationAxe)*p[P[1]])/r;
		s[P[1]]=(innerProduct(B, rotationAxe)*p[P[0]])/r;
		Vect<D> W(s);
		m_p1=p.normalize();
		Vect<D> vp=W.normalize();
		m_p2=sin(m_rad)*vp+cos(m_rad)*m_p1;
		//Let's be honest... you do not understand this.... :-D
	}
	else{		
		m_p1=Vect<D>{1, 0};
		Vect<D> w{0, 1};
		m_p2=sin(m_rad)*w+cos(m_rad)*m_p1;
	}
}

//===================================================================

template<int D>
Vect<D> Rotation<D>::reverse(const Vect<D>& V){
	Vect<D> W(V);
	W-=m_offset;
	double t=2.0*innerProduct(W, m_p1);
	return V-t*m_p1+(t*2.0*m_COS-2.0*innerProduct(W, m_p2))*m_p2;
}

//======================================================================

//*
template<int D>
void Rotation<D>::rotate(Vect<D>& V, const Vect<D>& OffV){
	Vect<D> W(V);
	W-=OffV;
	double t=2.0*innerProduct(W, m_p2);

	V.fastOp(-1.0*t, m_p2);
	V.fastOp(2.0*(t*m_COS-innerProduct(W, m_p1)), m_p1);
}


//===================================================================

template<int D>
void Rotation<D>::rotate(Vect<D>& V){
	rotate(V, m_offset);
}

//===================================================================

template<int D>
void Rotation<D>::revRotate(Vect<D>& V, const Vect<D>& OffV){
	Vect<D> W(V);
	W-=OffV;
	double t=2.0*innerProduct(W, m_p1);
	V.fastOp(-1.0*t, m_p1);
	V.fastOp(2.0*(t*m_COS-innerProduct(W, m_p2)), m_p2);
}

//===================================================================

template<int D>
void Rotation<D>::revRotate(Vect<D>& V){
	revRotate(V, m_offset);
}

//======================================================================

#endif
