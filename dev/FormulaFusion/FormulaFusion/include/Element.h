#pragma once
#include <string>

// this class is one single element off the periodic table.. i only keep the few facts
// the game actually needs, which is the symbol, the full name, and the atomic number.
class Element
{
public:
    Element();   // default constructor, makes an empty placeholder element
    Element(const std::string& symbol, const std::string& name, int atomicNumber);  // the real one i build with

    // getters, all const since reading an element should never change it
    std::string GetSymbol() const;
    std::string GetName() const;
    int GetAtomicNumber() const;

private:
    std::string symbol;    // the short code like H, O, or Na
    std::string name;      // the full name like Hydrogen
    int atomicNumber;      // its spot on the table like 1, 8, or 11
};
