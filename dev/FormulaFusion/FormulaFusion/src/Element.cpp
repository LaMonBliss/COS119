#include "Element.h"

// default constructor.. nothing handed in yet, so i start it blank and zeroed out
Element::Element()
{
    symbol = "";
    name = "";
    atomicNumber = 0;
}

// the constructor i actually build with, it takes all three facts and stores them
Element::Element(const std::string& symbol, const std::string& name, int atomicNumber)
{
    this->symbol = symbol;              // this-> because the parameter shares the member's name
    this->name = name;
    this->atomicNumber = atomicNumber;
}

// simple getters, each just hands back one piece of the element
std::string Element::GetSymbol() const { return symbol; }
std::string Element::GetName() const { return name; }
int Element::GetAtomicNumber() const { return atomicNumber; }
