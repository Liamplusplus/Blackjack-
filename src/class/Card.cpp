#include <class/Card.hpp>


void Card::write_form(std::ostream& stream) const
{
    stream << "<Value> " << value << '\n' << "<Suit> " << suit_names[static_cast<int>(suit)] << std::endl;
}
void Card::read_form(std::istream& stream)
{
    stream.ignore(256, ' ');
    stream >> value;
    stream.ignore(256, ' ');
    
    int cast;
    stream >> cast;
    suit = static_cast<Suit>(cast);
}

void Card::write_dump(std::ostream& stream) const
{
    stream << value << " " << static_cast<int>(suit);
}
void Card::read_dump(std::istream& stream)
{
    int cast;
    stream >> value >> cast;
    suit = static_cast<Suit>(cast);
}
