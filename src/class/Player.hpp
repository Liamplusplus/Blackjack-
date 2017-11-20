#pragma once
#include <string>
#include <iostream>

class Player
{

    public:

        Player();

		void setBalance(float f);
        void Pay(float value);
		void setName(const std::string& inString);

		float getBalance() const;
		const std::string& getName() const;

		void write_form(std::ostream& stream);
		void read_form(std::istream& stream);

        void write_binary(std::ostream& stream);
        void read_binary(std::istream& stream);

	protected:
    
		std::string name;
        float balance;
};
