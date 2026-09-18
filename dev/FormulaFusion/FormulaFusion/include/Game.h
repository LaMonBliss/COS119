#pragma once
#include <string>
#include <vector>
#include "Element.h"
#include "Compound.h"

// the Game class is the heart of Formula Fusion.. it owns all the data and runs the
// whole menu loop. main stays tiny and just tells this class to go.
class Game
{
public:
    Game();       // sets the game up by loading all the starting data
    void Run();   // the main menu loop, keeps going until the player quits

private:
    std::vector<Element> elements;     // my subset of the periodic table
    std::vector<Compound> compounds;   // the compounds the player can learn and guess
    int currentScore = 0;              // how many the player has gotten right this session

    void LoadData();                        // fills the two vectors above with the starting set
    void ShowMenu() const;                  // prints the main menu options
    void ViewElements() const;              // lists every element i loaded
    void ViewCompounds() const;             // lists every compound with its formula
    void GuessItMode();                     // show a formula, let the player guess the name
    void BuildItMode();                     // placeholder for the next milestone
    int GetChoice(int min, int max) const;  // safe menu input, keeps asking until it is valid
    int GetCount(int min, int max) const;   // reads a whole number count for Build It, line based
    std::string Normalize(const std::string& text) const;  // lowercases and strips spaces/special chars so guesses are forgiving
    const Element* FindElement(const std::string& symbol) const;  // looks up an element by symbol, or nullptr if we do not have it
    const Compound& GetRandomCompound() const;  // picks one random compound, shared by both game modes
};
