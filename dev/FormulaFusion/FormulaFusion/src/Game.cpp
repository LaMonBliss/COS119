#include "Game.h"
#include <iostream>
#include <random>
#include <cctype>   // cctype gives me tolower, which i use to lowercase each character in Normalize

// constructor.. the moment a Game is made i load all the data so everything is ready to play
Game::Game()
{
    LoadData();
}

// fill the element table and the compound list.. hardcoded for now, i can move this out to a file later
void Game::LoadData()
{
    // a small slice of the periodic table, enough to cover my starting compounds
    elements.push_back(Element("H", "Hydrogen", 1));
    elements.push_back(Element("C", "Carbon", 6));
    elements.push_back(Element("N", "Nitrogen", 7));
    elements.push_back(Element("O", "Oxygen", 8));
    elements.push_back(Element("Na", "Sodium", 11));
    elements.push_back(Element("Cl", "Chlorine", 17));

    // the compounds the player can view and guess.. name, formula, and a quick fact for each
    compounds.push_back(Compound("Water", "H2O", "Covers about 71 percent of the earth's surface."));
    compounds.push_back(Compound("Carbon Dioxide", "CO2", "What we breathe out and plants breathe in."));
    compounds.push_back(Compound("Table Salt", "NaCl", "The salt sitting on your kitchen table."));
    compounds.push_back(Compound("Ammonia", "NH3", "That sharp smell in a lot of cleaning products."));
    compounds.push_back(Compound("Methane", "CH4", "The main ingredient in natural gas."));
    compounds.push_back(Compound("Hydrogen Peroxide", "H2O2", "The stuff that bubbles up on a cut."));
}

// the main loop.. show the menu, grab a valid choice, do the thing, then repeat until they quit
void Game::Run()
{
    std::cout << "=====================================\n";
    std::cout << "        Welcome to Formula Fusion\n";
    std::cout << "=====================================\n";

    bool running = true;
    while (running)
    {
        ShowMenu();
        int choice = GetChoice(1, 5);   // only 1 through 5 are real options

        switch (choice)
        {
        case 1: ViewElements(); break;
        case 2: ViewCompounds(); break;
        case 3: GuessItMode(); break;
        case 4: BuildItMode(); break;
        case 5:
            std::cout << "\nThanks for playing Formula Fusion. See ya!\n";
            running = false;   // flip the flag so the while loop ends cleanly
            break;
        }
    }
}

// just prints the options.. const because printing a menu changes nothing about the game
void Game::ShowMenu() const
{
    std::cout << "\n------------ Main Menu ------------\n";
    std::cout << "1. View Elements\n";
    std::cout << "2. View Compounds\n";
    std::cout << "3. Guess It  (guess the compound from its formula)\n";
    std::cout << "4. Build It  (coming in the next milestone)\n";
    std::cout << "5. Quit\n";
}

// list out every element i loaded, lined up in a little table
void Game::ViewElements() const
{
    std::cout << "\n--- Element Table ---\n";
    for (const Element& e : elements)   // range based loop, one Element at a time by const reference so nothing copies needlessly
    {
        std::cout << e.GetAtomicNumber() << "\t" << e.GetSymbol() << "\t" << e.GetName() << "\n";
    }
}

// list out every compound with its formula so the player can study up before guessing
void Game::ViewCompounds() const
{
    std::cout << "\n--- Known Compounds ---\n";
    for (const Compound& c : compounds)
    {
        std::cout << c.GetFormula() << "\t" << c.GetName() << "\n";
    }
}

// Guess It.. pick a random compound, show its formula, and see if the player knows the name
void Game::GuessItMode()
{
    // one random engine seeded off the hardware, then a distribution spanning my compound indexes
    static std::mt19937 engine(std::random_device{}());
    std::uniform_int_distribution<int> pick(0, (int)compounds.size() - 1);
    const Compound& target = compounds[pick(engine)];

    std::cout << "\n--- Guess It ---\n";
    std::cout << "What compound has the formula " << target.GetFormula() << " ?\n";
    std::cout << "Your guess: ";

    // read the whole line since names can have spaces, like Carbon Dioxide
    std::string guess;
    std::getline(std::cin, guess);

    // run BOTH the guess and the real name through Normalize before comparing.. that way casing and
    // stray spaces do not matter, so water, WATER, and " Water " all count as a correct Water
    if (Normalize(guess) == Normalize(target.GetName()))
    {
        std::cout << "Correct! " << target.GetFact() << "\n";
    }
    else
    {
        std::cout << "Not quite. That formula is " << target.GetName() << ".\n";
        std::cout << target.GetFact() << "\n";
    }
}

// Build It is a next milestone feature.. for now it just says so, so the menu option stays honest
void Game::BuildItMode()
{
    std::cout << "\nBuild It mode is coming in the next milestone. Hang tight!\n";
}

// keeps asking until the player types a whole number inside the range i pass in
int Game::GetChoice(int min, int max) const
{
    int choice = 0;
    while (true)
    {
        std::cout << "\nEnter a number from " << min << " to " << max << ": ";
        std::cin >> choice;

        if (std::cin.fail() || choice < min || choice > max)  // not a number, or outside the range
        {
            std::cin.clear();               // clear the error flag so cin works again
            std::cin.ignore(10000, '\n');   // dump the bad input off the line
            std::cout << "That is not a valid option, try again.\n";
        }
        else
        {
            std::cin.ignore(10000, '\n');   // clear the rest of the line so a later getline starts clean
            return choice;                  // good input, hand it back and stop looping
        }
    }
}

// takes a string and hands back a cleaned up copy.. everything lowercase with no spaces on the ends.
// i run guesses and answers through this so the player does not get punished for casing or a stray space.
std::string Game::Normalize(const std::string& text) const
{
    std::string result = text;   // start with a copy so i never change the original the caller passed in

    // walk every character and lowercase it.. tolower wants an unsigned char, so i cast to be safe
    for (char& c : result)
    {
        c = (char)std::tolower((unsigned char)c);
    }

    // chop any spaces off the front, one at a time, until the first character is a real one
    while (!result.empty() && result.front() == ' ')
    {
        result.erase(result.begin());
    }

    // chop any spaces off the back the same way
    while (!result.empty() && result.back() == ' ')
    {
        result.pop_back();
    }

    return result;   // hand back the cleaned up version, ready to compare
}
