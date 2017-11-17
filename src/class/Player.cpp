#include <class/Player.hpp>

Player::Player() : balance(100.0f), name("Null")
{
    
}
		
void Player::setBalance(float f)
{
	balance = f;
}

		
void Player::setName(const std::string& inString)
{
	name = inString;
}

float Player::getBalance() const
{
	return balance;
}
		
const std::string& Player::getName() const
{
	return name;
}
		
void Player::write_form(std::ostream& stream)
{
	stream << "<Name> " << name << '\n' << "<Balance> " << balance;
}
		
void Player::read_form(std::istream& stream)
{
    stream.ignore(256, ' ');
	stream >> name;
    stream.ignore(256, ' ');
	stream >> balance;
}
