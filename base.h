#ifndef BASE_H
#define BASE_H

#include <SFML/Graphics.hpp>
#include "reference_frame.h"

class ReferenceFrame;

class Base{

	private:
		static bool is_window_set;
		static bool is_rf_set;	
		
	protected:
		static ReferenceFrame* RF;
		static sf::RenderWindow* Window; 

	public:
		static void set_window(sf::RenderWindow* W);
		static void set_rf(ReferenceFrame* rf);
};



#endif