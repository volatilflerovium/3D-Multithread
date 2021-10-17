/*********************************************************************
* Base class                                  								*
*                                                                    *
* Version: 1.5                                                       *
* Date:    25-07-2021                                                *
* Author:  Dan Machado                                               *                                         *
**********************************************************************/
#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics.hpp>
#include "reference_frame.h"

class Base{
	public:
		static void set_window(sf::RenderWindow* W);
		static void set_rf(ReferenceFrame* rf);
	
	protected:
		static ReferenceFrame* m_WorldFrame;
		static sf::RenderWindow* m_window; 
	
};

//======================================================================

inline void Base::set_window(sf::RenderWindow* W){
	if(!m_window){
		m_window=W;
	}
}

//======================================================================

inline void Base::set_rf(ReferenceFrame* rf){
	if(!m_WorldFrame){
		m_WorldFrame=rf;
	}
}

//======================================================================

#endif
