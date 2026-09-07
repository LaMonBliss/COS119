#pragma once
#include <string>

// this class is one known compound.. the everyday name, the chemical formula,
// and a quick fun fact i can show the player after they get it right.
class Compound
{
public:
    Compound();   // default constructor, empty placeholder
    Compound(const std::string& name, const std::string& formula, const std::string& fact);

    // getters, all const since reading a compound should never change it
    std::string GetName() const;
    std::string GetFormula() const;
    std::string GetFact() const;

private:
    std::string name;      // what people call it, like Water
    std::string formula;   // the chemical formula, like H2O
    std::string fact;      // a one liner about it
};
