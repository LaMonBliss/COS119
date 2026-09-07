#include "Compound.h"

// default constructor.. nothing given yet, so everything starts empty
Compound::Compound()
{
    name = "";
    formula = "";
    fact = "";
}

// the real constructor, takes the name, formula, and fact and stores all three
Compound::Compound(const std::string& name, const std::string& formula, const std::string& fact)
{
    this->name = name;              // this-> since the parameters share the member names
    this->formula = formula;
    this->fact = fact;
}

// simple getters, each hands back one piece of the compound
std::string Compound::GetName() const { return name; }
std::string Compound::GetFormula() const { return formula; }
std::string Compound::GetFact() const { return fact; }
