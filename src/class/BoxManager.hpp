/*
 *
 *
 */

#pragma once
#include <class/Box.hpp>

class BoxManager
{
	public:

		BoxManager();

		Box::BetErrorCode 	addBet(float value, int box);

		// Increment

		int				Next();
		int				nextActive();

		void setActive(int index);
		void Reset(); 

		// Access
		
		Box&			getBox(int index);
		Box&			getCurrentBox();
		int 			getActiveIndex();	

	protected:

		std::array<Box, 6> 	boxes;
		Box 				dealer;
		// Receives card at end of dealing phase
		// Always hits if below 17

		int current_box;

};
