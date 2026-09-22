#include "Compound.h"

// default constructor.. nothing given yet, so everything starts empty and easy
Compound::Compound()
{
    name = "";
    formula = "";
    fact = "";
    difficulty = 1;
}

// the real constructor, takes the name, formula, fact, and difficulty and stores them all
Compound::Compound(const std::string& name, const std::string& formula, const std::string& fact, int difficulty)
{
    this->name = name;              // this-> since the parameters share the member names
    this->formula = formula;
    this->fact = fact;
    this->difficulty = difficulty;
}

// simple getters, each hands back one piece of the compound
std::string Compound::GetName() const { return name; }
std::string Compound::GetFormula() const { return formula; }
std::string Compound::GetFact() const { return fact; }
int Compound::GetDifficulty() const { return difficulty; }
