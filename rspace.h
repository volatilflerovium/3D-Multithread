/*********************************************************************
* rspace class                               								*
*                                                                    *
* Version: 1.0                                                       *
* Date:    21-03-2019                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#ifndef RSPACE_H
#define RSPACE_H
#include<memory>
#include"vector.h"

using namespace std;

template<int D>
class RSpace
{	
	private:
		Vect<D> relPosition; // the position of the origin of the space relatively to the reference space
		Rotation<D> Transf[D]; // rotations always at (0,0,0)
      RSpace* RF=NULL;
      double angles[D];
		void setRef(RSpace<D>* _RF);
		RSpace() = delete;
		RSpace(Vect<D> initialPosition, std::initializer_list<double> _angles);

	public:
		~RSpace();
		RSpace(const RSpace<D>& RS);
		Vect<D> getPos() const;
		Vect<D> ltw(const Vect<D>& VTX);
		Vect<D> wtl(const Vect<D>& VTX);

		static std::shared_ptr<RSpace<D>> maker(Vect<D> initialPosition, std::initializer_list<double> angles);
		std::shared_ptr<RSpace<D>> spawn(Vect<D> initialPosition, std::initializer_list<double> angles);

		void updateTrans(int i, double ang);
		void move(const Vect<D>& V);// set relPosition+=V
};


//-------------------------------------------------------------------

template<int D>
RSpace<D>::~RSpace(){
	/*	/**/
}

//-------------------------------------------------------------------

template<int D>
inline Vect<D> RSpace<D>::getPos() const{
	return relPosition;
}

//-------------------------------------------------------------------

template<int D>
inline std::shared_ptr<RSpace<D>> RSpace<D>::maker(Vect<D> initialPosition, std::initializer_list<double> angles){
	shared_ptr<RSpace<D>> tmp(new RSpace<D>(initialPosition, angles));
	return tmp;
}
//-------------------------------------------------------------------

template<int D>
inline std::shared_ptr<RSpace<D>> RSpace<D>::spawn(Vect<D> initialPosition, std::initializer_list<double> angles){
	shared_ptr<RSpace<D>> tmp(new RSpace<D>(initialPosition, angles));
	tmp->setRef(this);
	return tmp;
}

//-------------------------------------------------------------------

template<int D>
inline void RSpace<D>::setRef(RSpace<D>* _RF){
	if(!RF){
		RF=_RF;
	}
}

//-------------------------------------------------------------------

template<int D>
inline RSpace<D>::RSpace(Vect<D> initialPosition, std::initializer_list<double> _angles)
	:relPosition(initialPosition){
	int i=0;
	for(double ang : _angles){
		angles[i]=ang;
		Transf[i]=Rotation<D>(Vect<D>(i+1), ang);
		i++;
	}
}

//-------------------------------------------------------------------

template<int D>
inline void RSpace<D>::updateTrans(int i, double ang){
	angles[i]+=ang;
	Transf[i]=Rotation<D>(Vect<D>(i+1), angles[i]);
}

//-------------------------------------------------------------------

template<int D>
inline Vect<D> RSpace<D>::ltw(const Vect<D>& VRX){
	Vect<D> V(VRX);
	for(int i=0; i<D; i++){
		V=Transf[i](V);
	}

	if(RF){
		return RF->ltw(relPosition+V);
	}

	return relPosition+V;
}

//-------------------------------------------------------------------
//*
template<int D>
inline Vect<D> RSpace<D>::wtl(const Vect<D>& VRX){

	Vect<D> V(VRX-relPosition);
	for(int i=0; i<D; i++){
		V=Transf[i].reverse(V);
	}

	if(RF){
		return RF->wtl(V);
	}

	return V;
}

//-------------------------------------------------------------------

template<int D>
void RSpace<D>::move(const Vect<D>& V){
	relPosition+=V;
}

//-------------------------------------------------------------------


#endif