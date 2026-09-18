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
    std::cout << "4. Build It  (build the formula from elements)\n";
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

// picks one random compound from my list and hands back a reference to it.
// both game modes call this, so the random logic lives in one spot instead of being copied twice.
const Compound& Game::GetRandomCompound() const
{
    // one random engine, seeded once off the hardware, kept alive between calls with static
    static std::mt19937 engine(std::random_device{}());
    // the distribution covers every valid index into my compound list
    std::uniform_int_distribution<int> pick(0, (int)compounds.size() - 1);
    return compounds[pick(engine)];   // hand back a reference to the chosen compound
}

// Guess It.. pick a random compound, show its formula, and see if the player knows the name
void Game::GuessItMode()
{
    const Compound& target = GetRandomCompound();   // grab a random compound to quiz the player on

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

// Build It.. name a compound, then let the player assemble its formula one element at a time.
void Game::BuildItMode()
{
    const Compound& target = GetRandomCompound();   // grab a random compound for the player to build

    std::cout << "\n--- Build It ---\n";
    std::cout << "Build this compound: " << target.GetName() << "\n";

    // show the player which symbols they have to work with
    std::cout << "Available elements: ";
    for (size_t i = 0; i < elements.size(); i++)
    {
        std::cout << elements[i].GetSymbol();
        if (i < elements.size() - 1)   // comma between them, but not after the last one
        {
            std::cout << ", ";
        }
    }
    std::cout << "\n\n";
    std::cout << "Add elements to your formula, one at a time. Type 'done' when finished.\n";

    std::string built;   // the formula the player is assembling, starts empty

    while (true)
    {
        std::cout << "Element symbol (or done): ";
        std::string symbol;
        std::getline(std::cin, symbol);

        if (Normalize(symbol) == "done")   // the player is finished adding elements
        {
            break;
        }

        // make sure it is a real element from our list before we accept it
        const Element* found = FindElement(symbol);
        if (found == nullptr)   // FindElement handed back null, so this symbol is not one we have
        {
            std::cout << "  that is not one of the available elements, try again.\n";
            continue;   // skip the rest of the loop and ask again
        }

        int count = GetCount(1, 20);   // how many of this element, validated

        // add the element's REAL symbol (proper casing from our data), not whatever the player typed
        built += found->GetSymbol();
        if (count > 1)   // chemists write O, not O1, so only tack on the number when it is more than one
        {
            built += std::to_string(count);
        }

        std::cout << "  added " << found->GetSymbol();
        if (count > 1)
        {
            std::cout << count;
        }
        std::cout << "   ->  formula so far: " << built << "\n";
    }

    std::cout << "\nYou built: " << built << "\n";

    // compare what they built to the real formula.. since we assembled it from our own canonical
    // symbols, a straight comparison is safe and keeps element casing correct
    if (built == target.GetFormula())
    {
        std::cout << "Correct! " << target.GetFact() << "\n";
    }
    else
    {
        std::cout << "Not quite. " << target.GetName() << " is " << target.GetFormula() << ".\n";
        std::cout << target.GetFact() << "\n";
    }
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

// takes a string and hands back a cleaned up copy.. lowercase, with spaces and special characters stripped out.
// i run guesses and answers through this so the player is not punished for casing, spaces, or punctuation.
std::string Game::Normalize(const std::string& text) const
{
    std::string result;   // build up the cleaned copy one character at a time, starting empty

    for (char c : text)
    {
        unsigned char uc = (unsigned char)c;   // isalnum and tolower both want an unsigned char to be safe
        if (std::isalnum(uc))                  // keep the character only if it is a letter or a digit
        {
            result += (char)std::tolower(uc);  // lowercase it as we add it, so casing never matters
        }
        // anything else, spaces, punctuation, or symbols like ! ? and -, just gets skipped over
    }

    return result;   // lowercase, letters and digits only, so casing and special characters do not matter
}

// looks up an element by its symbol, ignoring case so h and H both work.
// returns a POINTER to the real element if we have it, or nullptr if we do not.
// a pointer is handy here because the caller can check it for null AND read the element's proper symbol.
const Element* Game::FindElement(const std::string& symbol) const
{
    std::string wanted = Normalize(symbol);   // clean up what the player typed first
    for (const Element& e : elements)         // walk every element we loaded
    {
        if (Normalize(e.GetSymbol()) == wanted)   // compare cleaned up to cleaned up
        {
            return &e;   // match found, hand back its address so the caller can use the real thing
        }
    }
    return nullptr;   // made it through the whole list with no match, so we do not have this element
}

// reads a whole number count for Build It and keeps asking until it gets a valid one in range.
// this one is line based (getline) so it plays nicely with the symbol reading in Build It.
int Game::GetCount(int min, int max) const
{
    while (true)
    {
        std::cout << "How many? ";
        std::string line;
        std::getline(std::cin, line);

        try
        {
            int value = std::stoi(line);          // stoi turns the text into an int, or throws if it is not a number
            if (value >= min && value <= max)
            {
                return value;                     // good number in range, hand it back
            }
        }
        catch (...) { }                           // stoi threw because it was not a number, fall through to the retry

        std::cout << "  please enter a number from " << min << " to " << max << ".\n";
    }
}
