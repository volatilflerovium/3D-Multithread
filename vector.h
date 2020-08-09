/*********************************************************************
* vector and rotation classes                  								*
*                                                                    *
* Version: 1.0                                                       *
* Date:    21-03-2019                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/

#ifndef VECTOR_CLASS_H
#define VECTOR_CLASS_H

#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>

using namespace std;

//README: for value of pi use M_PI which is part of cmath
//const double pi=3.1415926535897; 

//###################################################################
//###################################################################

template<int D>
class Vect
{
	private:
		unsigned short dimension;		
		double V[D];

	public:
		Vect();
		Vect(double* p);
		explicit Vect(int i);
		Vect(const Vect<D>& V);
		Vect(std::initializer_list<double> l);
		virtual Vect<D>& operator=(const Vect<D>& V);
		int get_dimension() const;
		bool operator!=(const Vect<D>& v);
		Vect<D>& operator+=(const Vect<D>& w);
		Vect<D> operator+(const Vect<D>& W);
		Vect<D> operator-(const Vect<D>& W);
		Vect<D>& operator*=(double f);
		Vect<D>& operator-=(const Vect<D>& w);

		// utilities
		double coordinate(int n) const;
		double norm() const;
		Vect<D>& canonical_reflexion(int p);
		Vect<D>& normalize();
		Vect<D-1> proj(int p);
};


//===================================================================

template<int D>
int Vect<D>::get_dimension() const{
	return this->dimension;
}

//===================================================================

template<int D>
Vect<D>::Vect(){
	this->dimension=D;
	for(int i=0; i<D; i++){
		this->V[i]=0;
	}
}
//===================================================================

template<int D>
Vect<D>::Vect(double* p){
	this->dimension=D;
	for(int i=0; i<D; i++){
		this->V[i]=*p;
		p++;
	}
}
//===================================================================

template<int D>
Vect<D>::Vect(int i){
	i--;
	this->dimension=D;
	for(int j=0; j<D; j++){
		this->V[j]=0;
	}
	if(i>=0 && i<D){
		this->V[i]=1;
	}
}


//===================================================================

template<int D>
Vect<D>::Vect(std::initializer_list<double> l){
	this->dimension=D;
	int i=0;
	for(double x : l){
		this->V[i++]=x;
		if(i==D){
			break;
		}
	}
}

//===================================================================

template<int D>
Vect<D>::Vect(const Vect<D>& W){
	this->dimension=W.get_dimension();
	for(int i=0; i<this->dimension; i++){
		this->V[i]=W.coordinate(i);
	}
}

//===================================================================

template<int D>
Vect<D>& Vect<D>::operator=(const Vect<D>& W){
	for(int i=0; i<this->dimension; i++){
		this->V[i]=W.coordinate(i);		
	}
	return *this;
}

//===================================================================

template<int D>
bool Vect<D>::operator!=(const Vect<D>& W){
	bool a=(this==&W);
	if(!a){
		for(int i=0; i<this->dimension; i++){
			if(this->V[i]!=W.coordinate(i)){
				a=true;
				break;	
			}
		}
	}
	return a;
}

//===================================================================

template<int D>
Vect<D>& Vect<D>::operator+=(const Vect<D>& v){
	for(int i=0; i<this->dimension; i++){
		this->V[i]+=v.coordinate(i);		
	}
	return *this;
}

//===================================================================

template<int D>
Vect<D>& Vect<D>::operator-=(const Vect<D>& v){
	for(int i=0; i<this->dimension; i++){
		this->V[i]-=v.coordinate(i);		
	}
	return *this;
}

//===================================================================
//*
template<int D>
Vect<D> Vect<D>::operator+(const Vect<D>& W){ 
	Vect<D> V(*this);
	V+=W;
	
	return V;
}
/**/
//===================================================================
//*
template<int D>
Vect<D> Vect<D>::operator-(const Vect<D>& W){	
	Vect<D> V(*this);
	V-=W;
	return V;
}
/**/
//===================================================================

template<int D>
Vect<D>& Vect<D>::operator*=(double f){
	for(int i=0; i<D; i++){
		this->V[i]*=f;		
	}
	return *this;
}

//===================================================================

template<int D>
double Vect<D>::norm() const{
	double sum=0;
	for(int i=0; i<this->dimension; i++){
		sum+=this->V[i]*this->V[i];
	}
	return sqrt(sum);
}

//===================================================================

template<int D>
double Vect<D>::coordinate(int n) const{
	if(n<this->dimension){
		return this->V[n];
	}
	else{
		cout<<"Throw an exception!\n";	
	}
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
	if(p<this->dimension){
		this->V[p]*=-1;
	}
	return *this;
}

//===================================================================

template<int D>
Vect<D-1> Vect<D>::proj(int p){
	Vect<D-1> W;
	p--;
	int j=1;
	for(int i=0; i<D; i++){
		if(i!=p){
			//cout<<this->V[i]<<" "<<Vect<D-1>(j)<<endl;
			W+=this->V[i]*Vect<D-1>(j++);
		}
	}
	return W;
}

//===================================================================
//###################################################################
//===================================================================

template<int D>
inline Vect<D> operator*(double f, const Vect<D>& V){
	Vect<D> W(V);
	return W*=f;
}

//===================================================================

template<int D>
inline Vect<D> operator*(const Vect<D>& V, double f){
	return f*V;
} 

//===================================================================

template<int D>
inline Vect<D> operator/(const Vect<D>& V, double f){
	return (1.0/f)*V;
}
 
//===================================================================


template<int D>
inline Vect<D> operator+(const Vect<D>& U, const Vect<D>& V){
	Vect<D> W(U);
	return W+=V;
}

//===================================================================

template<int D>
inline Vect<D> operator-(const Vect<D>& U, const Vect<D>& V){
	return U+(-1)*V;
}

//===================================================================

template<int D>
ostream& operator<<(ostream& out, const Vect<D>& v){
	int d=v.get_dimension();
	out<<'(';
	for(int i=0; i<d; i++){
		out<<v.coordinate(i);
		if(i<d-1){
			out<<", ";
		}
	}
	out<<')';
	return out;
}

//===================================================================

template<int D>
double inner_prod(const Vect<D>& V, const Vect<D>& W){
	double dprod=0;
	for(int i=0; i<D; i++){
		dprod+=V.coordinate(i)*W.coordinate(i);
	}
	return dprod;
}

//===================================================================

template<int D>
inline double ang_cos(const Vect<D>& V, const Vect<D>& W){
	return inner_prod(V, W)/(V.norm()*W.norm());
}

//===================================================================

template<int D>
inline double fast_cos(const Vect<D>& V){
	//return inner_prod(V, W)/(V.norm()*W.norm());
	return V.coordinate(D-1)/V.norm();
}
//===================================================================

template<int D>
double distance(const Vect<D>& V, const Vect<D>& W){
	double sum=0;
	for(int i=0; i<V.get_dimension; i++){
		sum+=pow(V.coordinate(i)-W.coordinate(i), 2);
	}
	return sqrt(sum);
}


//===================================================================
//################################################################### 
//################################################################### 
//################################################################### 
//################################################################### 
//################################################################### 
//###################################################################
/*
Implement a builder rotation
*/
template<int D>
class Rotation
{
	private:
		double rad;
		Vect<D> P1;
		Vect<D> P2;
		Vect<D> Q;
		Vect<D> Offset;
		void setup(Vect<D> rotation_axe);
		void set_angle(double angle);
		Vect<D> rtd(const Vect<D>& V) const;
		Vect<D> rtd(const Vect<D>& V, const Vect<D>& OffV) const;
		Vect<D> rtd_reverse(const Vect<D>& V) const;

	public:
		//center of rotation is the line through origin 
		//determined by the vector V, angle
		Rotation();
		Rotation(Vect<D> V, double angle);
		Rotation(std::initializer_list<double> l, double angle);
		// center of rotation is the line determined by the vectors 
		// vector V and W, angle
		Rotation(Vect<D> V, Vect<D> W, double angle);
		Rotation(const Rotation<D>& Rt);
		double getAngle() const;
		Vect<D> getV(int i) const;

		Rotation(std::initializer_list<double> lp, std::initializer_list<double> lq, double angle);
		Vect<D> operator()(const Vect<D>& v);
		//Vect<D> operator()(double ang, const Vect<D>& V);
		Vect<D> operator()(const Vect<D>& relative_offset, const Vect<D>& V);
		Vect<D> operator()(std::initializer_list<double> r_offset, const Vect<D>& V);
		Vect<D> reverse(const Vect<D>& V);
};


//===================================================================

template<int D>
inline double Rotation<D>::getAngle() const{
	return rad;
}

template<int D>
Vect<D> Rotation<D>::getV(int i) const{
	if(i==0){
		return Offset;
	}
	else if(i==1){
		return P1;
	}
	else if(i==2){
		return P2;
	}
	else if(i==3){
		return Q;
	}
}

template<int D>
Rotation<D>::Rotation()
	:rad(0), P1(), P2(), Q(), Offset()
{}


template<int D>
Rotation<D>::Rotation(const Rotation<D>& Rt)
	:rad(Rt.getAngle()), P1(Rt.getV(1)), P2(Rt.getV(2)), Q(Rt.getV(3)), Offset(Rt.getV(0))
{}

template<int D>
Rotation<D>::Rotation(Vect<D> rotation_axe, double angle)
				:Offset()
{
	//Vect<D> O;
	//Offset=O;
	set_angle(angle);
	setup(rotation_axe);
}


template<int D>
Rotation<D>::Rotation(std::initializer_list<double> l, double angle)
				:Offset()
{
	//Vect<D> O;
	//Offset=O;
	set_angle(angle);
	Vect<D> V(l);
	setup(V);
}

template<int D>
Rotation<D>::Rotation(std::initializer_list<double> lp, std::initializer_list<double> lq, double angle)
			:Offset(lq)
{
	set_angle(angle);
	Vect<D> V(lp);
	//Vect<D> U(lq);
	//Offset=U;
	//setup(V-U);
	setup(V-Offset);
}

template<int D>
Rotation<D>::Rotation(Vect<D> V, Vect<D> W, double angle)
				:Offset(W)
{
	set_angle(angle);
	setup(V-Offset);
}

template<int D>
void Rotation<D>::set_angle(double angle){
	if(fabs(angle)>=360.0){
		angle=(fabs(angle)/angle)*(fabs(angle)-360.0);
	}
	rad=-1.0*((angle/2)*M_PI)/180;
}


template<int D>
void Rotation<D>::setup(Vect<D> rotation_axe){

	/*
	First we get a canonical solution to the equation axe dot v=0.
	This is everything zero except 2 for example
	axe =(a,b,c,d);
	v=(0,c,-b,0); where b!=0 || c!=0
	*/
	double a[D];
	a[0]=0;
	a[1]=0;
	double b[D];
	b[0]=1;
	b[1]=1;
	double s[D];
	s[0]=1;
	s[1]=1;
	int P[2]={0,1};
	// we get two non zero values
	if(D>2){
		for(int i=2; i<D; i++){
			a[i]=0;
			b[i]=1;
			s[i]=1;
			if(fabs(rotation_axe.coordinate(P[0]))+fabs(rotation_axe.coordinate(P[1]))==0){
				if(rotation_axe.coordinate(i)>0.0){
					P[0]=i-1;
					P[1]=i;
				}
			}
		}
		
		//cout<<P[0]<<" "<<P[1]<<endl;
		
		a[P[0]]=rotation_axe.coordinate(P[1]);
		a[P[1]]=-1.0*rotation_axe.coordinate(P[0]);
		Vect<D> p(a);
		
		b[P[0]]=0;
		b[P[1]]=0;
		Vect<D> B(b);
	  
	  // cout<<"B: "<<B<<" "<<endl;
	   /*
		 Now, we use p to construct an orthogonal vector W 
		 WE CAN USE the cross product!! 
		 NOOO, of course NOT!!! 
		 we need something easy and fast
		*/
		double r=0;
		r=rotation_axe.coordinate(P[0])*p.coordinate(P[1]);
		r-=rotation_axe.coordinate(P[1])*p.coordinate(P[0]);
		s[P[0]]=(-1.0*inner_prod(B, rotation_axe)*p.coordinate(P[1]))/r;
		s[P[1]]=(inner_prod(B, rotation_axe)*p.coordinate(P[0]))/r;
		//cout<<"S: "<<s[2]<<endl;
		Vect<D> W(s);
		/*
		cout<<"DDDD"<<inner_prod(W, p)<<endl;
		cout<<"p: "<<p<<endl;
		cout<<"W: "<<W<<endl;
		*/

		//cout<<"W: "<<W<<endl;
		P1=p.normalize();
		P2=W.normalize();
		Q=sin(rad)*P2+cos(rad)*P1;
		//cout<<"P1: "<<P1<<endl;
		//cout<<"P2: "<<P2<<endl;
	}
	else{
		Vect<D> v({1, 0});
		P1=v;
		Vect<D> w({0, 1});
		P2=w;
		Q=sin(rad)*P2+cos(rad)*P1;
	}
}

//===================================================================

template<int D>
Vect<D> Rotation<D>::rtd(const Vect<D>& V) const {
	Vect<D> W(V-Offset);
	double t=2.0*inner_prod(W, Q);
	return V-t*Q+(t*2.0*cos(rad)-2.0*inner_prod(W, P1))*P1;
}

//===================================================================

template<int D>
Vect<D> Rotation<D>::rtd(const Vect<D>& V, const Vect<D>& OffV) const{
	Vect<D> W(V-OffV);
	double t=2.0*inner_prod(W, Q);
	return V-t*Q+(t*2.0*cos(rad)-2.0*inner_prod(W, P1))*P1;
}

//===================================================================

template<int D>
Vect<D> Rotation<D>::rtd_reverse(const Vect<D>& V) const {
	Vect<D> W(V-Offset);
	double t=2.0*inner_prod(W, P1);
	return V-t*P1+(t*2.0*cos(rad)-2.0*inner_prod(W, Q))*Q;
}

//===================================================================

template<int D>
Vect<D> Rotation<D>::operator()(const Vect<D>& V){
	return rtd(V);
}

//===================================================================

template<int D>
Vect<D> Rotation<D>::reverse(const Vect<D>& V){
	/*
	static Vect<D> QR;
	QR=sin(-1.0*rad)*P2+cos(-1.0*rad)*P1;	
	double t=2.0*inner_prod(V-Offset, QR);
	return V-t*QR+(t*2.0*cos(-1.0*rad)-2.0*inner_prod(V-Offset, P1))*P1;
	/**/
	return rtd_reverse(V);
}
/**/
//===================================================================

template<int D>
Vect<D> Rotation<D>::operator()(const Vect<D>& newOffset, const Vect<D>& V){
	return rtd(V, newOffset);
}

//===================================================================

template<int D>
Vect<D> Rotation<D>::operator()(std::initializer_list<double> r_offset, const Vect<D>& V){
	return rtd(V, r_offset);
}

#endif