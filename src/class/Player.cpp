#include <class/Player.hpp>
#include <class/Config.hpp>

Player::Player() : balance(100.0f), name("Null")
{
    
}
		
void Player::setBalance(float f)
{
	balance = f;
}

void Player::Pay(float value)
{
    balance += value;
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
        
void Player::write_binary(std::ostream& stream)
{
    game::write_binary(stream, name);
	stream.write((char*)&balance, sizeof(float)); //Save size to file

}
        
void Player::read_binary(std::istream& stream)
{
    game::read_binary(stream, name);
	stream.read((char*)&balance, sizeof(float)); //Save size to file
}
