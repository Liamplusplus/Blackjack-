#pragma once
#include <class/State.hpp>


class InitialDeal : public State
{
	public:

		enum class _State { FIRST_ROUND = 0, SECOND_ROUND };

		void 	Setup();
		void 	Advance();
	
};
