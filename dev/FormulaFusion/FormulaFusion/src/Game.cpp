#include "Game.h"
#include <iostream>
#include <random>
#include <cctype>   // cctype gives me tolower, which i use to lowercase each character in Normalize
#include <fstream>  // fstream gives me ifstream and ofstream for reading and writing the high scores file
#include <cstdlib>  // cstdlib gives me system, which i use to clear the console screen

// constructor.. the moment a Game is made i load all the data and any saved high scores
Game::Game()
{
    LoadData();
    LoadHighScores();
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
    // greet the player and grab their name once, up front, so every high score they earn is saved under it
    ClearScreen();
    std::cout << "=====================================\n";
    std::cout << "        Welcome to Formula Fusion\n";
    std::cout << "=====================================\n";
    std::cout << "\nWhat is your player name? ";
    std::getline(std::cin, playerName);

    bool running = true;
    while (running)
    {
        ClearScreen();   // start every round on a fresh screen so the game does not scroll forever

        std::cout << "=====================================\n";
        std::cout << "        Welcome to Formula Fusion\n";
        std::cout << "=====================================\n";

        ShowMenu();
        int choice = GetChoice(1, 6);   // only 1 through 6 are real options

        switch (choice)
        {
        case 1: ViewElements(); break;
        case 2: ViewCompounds(); break;
        case 3: GuessItMode(); break;
        case 4: BuildItMode(); break;
        case 5: ViewHighScores(); break;
        case 6:
            // if the player scored anything this session, save it to the high scores before we leave
            if (currentScore > 0)
            {
                Highscore entry;          // record this run under the name we grabbed at the start
                entry.name = playerName;
                entry.score = currentScore;
                highScores.push_back(entry);

                SortAndCapHighScores();   // keep the leaderboard ranked best first and trimmed to the top 10
                SaveHighScores();         // write the updated list back to the file
            }
            std::cout << "\nThanks for playing, " << playerName << "! See ya!\n";
            running = false;   // flip the flag so the while loop ends cleanly
            break;
        }

        if (running)   // if they did not quit, hold the screen so they can read it before the next clear
        {
            PauseForEnter();
        }
    }
}

// clears the console so the game shows one clean screen at a time instead of one long scroll.
void Game::ClearScreen() const
{
    system("cls");   // cls is the windows command that wipes the console
}

// holds the screen until the player presses Enter, so they can actually read what just happened
// before the next clear wipes it away.
void Game::PauseForEnter() const
{
    std::cout << "\nPress Enter to continue...";
    std::string dummy;
    std::getline(std::cin, dummy);   // just wait here until they hit Enter
}

// just prints the options.. const because printing a menu changes nothing about the game
void Game::ShowMenu() const
{
    std::cout << "\n------------ Main Menu ------------\n";
    std::cout << "Player: " << playerName << "     Score: " << currentScore << "\n";
    std::cout << "1. View Elements\n";
    std::cout << "2. View Compounds\n";
    std::cout << "3. Guess It  (guess the compound from its formula)\n";
    std::cout << "4. Build It  (build the formula from elements)\n";
    std::cout << "5. View High Scores\n";
    std::cout << "6. Quit\n";
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

// the shared ending both game modes use once they know if the player was right.
// on a correct answer it bumps the score and shows the fact, otherwise it prints the miss
// message the mode passed in, then the fact. keeping it here means the result logic lives in one spot.
void Game::ShowResult(bool correct, const Compound& target, const std::string& missMessage)
{
    if (correct)
    {
        currentScore += pointsPerQuestion;   // award the points this question was worth
        std::cout << "Correct! You earned " << pointsPerQuestion << " points. " << target.GetFact() << "\n";
    }
    else
    {
        std::cout << missMessage << "\n";                                   // the mode's own wording for a wrong answer
        std::cout << "No points that time. " << target.GetFact() << "\n";   // no points, but still share the fun fact
    }
}

// draws the atoms the player has added so far as a little ascii molecule diagram.
// each atom becomes a boxed node, and the boxes get wired together with bond lines,
// so the player watches their compound take shape one element at a time.
void Game::DrawMolecule(const std::vector<std::string>& atoms) const
{
    if (atoms.size() == 0)   // nothing added yet, so there is nothing to draw
    {
        return;
    }

    std::string top;      // the top edges of every box
    std::string middle;   // the row that holds the symbols and the bonds between boxes
    std::string bottom;   // the bottom edges of every box

    for (size_t i = 0; i < atoms.size(); i++)
    {
        if (i > 0)   // this is not the first atom, so wire it to the one before with a bond
        {
            top += "   ";      // blank space above the bond so the boxes still line up
            middle += "---";   // the bond line itself sits on the middle row
            bottom += "   ";   // blank space below the bond
        }

        std::string symbol = atoms[i];   // the element symbol that goes inside this box
        if (symbol.size() == 1)          // pad a one letter symbol so every box is the same width
        {
            symbol += " ";
        }

        top += "+----+";                 // one box top
        middle += "| " + symbol + " |";  // the symbol boxed on the middle row
        bottom += "+----+";              // one box bottom
    }

    std::cout << top << "\n" << middle << "\n" << bottom << "\n";
}

// Guess It.. pick a random compound, show its formula, and see if the player knows the name
void Game::GuessItMode()
{
    const Compound& target = GetRandomCompound();   // grab a random compound to quiz the player on

    std::cout << "\n--- Guess It ---\n";
    std::cout << "This one is worth " << pointsPerQuestion << " points.\n";
    std::cout << "What compound has the formula " << target.GetFormula() << " ?\n";
    std::cout << "Your guess: ";

    // read the whole line since names can have spaces, like Carbon Dioxide
    std::string guess;
    std::getline(std::cin, guess);

    // run BOTH the guess and the real name through Normalize before comparing.. that way casing and
    // stray spaces do not matter, so water, WATER, and " Water " all count as a correct Water
    // did they get it? then hand the result off to the shared ending, with my own miss message
    bool correct = (Normalize(guess) == Normalize(target.GetName()));
    ShowResult(correct, target, "Not quite. That formula is " + target.GetName() + ".");
}

// Build It.. name a compound, then let the player assemble its formula one element at a time.
void Game::BuildItMode()
{
    const Compound& target = GetRandomCompound();   // grab a random compound for the player to build

    std::cout << "\n--- Build It ---\n";
    std::cout << "This one is worth " << pointsPerQuestion << " points.\n";
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

    std::string built;                  // the formula the player is assembling, starts empty
    std::vector<std::string> atoms;     // every atom added in order, so i can draw the molecule as it grows

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

        // also record each atom on its own so the molecule diagram can show every node
        for (int k = 0; k < count; k++)
        {
            atoms.push_back(found->GetSymbol());
        }

        std::cout << "  added " << found->GetSymbol();
        if (count > 1)
        {
            std::cout << count;
        }
        std::cout << "   ->  formula so far: " << built << "\n";
        DrawMolecule(atoms);   // draw the molecule taking shape as it grows
    }

    std::cout << "\nYou built: " << built << "\n";
    DrawMolecule(atoms);   // one last look at the finished molecule

    // compare what they built to the real formula.. since we assembled it from our own canonical
    // symbols, a straight comparison is safe and keeps element casing correct
    // check what they built against the real formula, then use the shared ending with my own miss message
    bool correct = (built == target.GetFormula());
    ShowResult(correct, target, "Not quite. " + target.GetName() + " is " + target.GetFormula() + ".");
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

// reads the saved high scores from the file when the game starts up.
// if the file does not exist yet, like on the very first run, i just skip it and start empty.
void Game::LoadHighScores()
{
    std::ifstream inFile(highScoreFile);   // try to open the high scores file for reading
    if (!inFile)   // the file is not there yet, so there is nothing to load
    {
        return;
    }

    int score;
    while (inFile >> score)   // read a score.. the loop ends when there are no more numbers to read
    {
        inFile.ignore();      // skip the newline sitting right after the number

        Highscore entry;      // build one entry from the score and the name on the next line
        entry.score = score;
        std::getline(inFile, entry.name);   // read the whole name line, spaces and all
        highScores.push_back(entry);
    }

    inFile.close();
    SortAndCapHighScores();   // make sure the loaded list is ranked and trimmed before anyone views it
}

// writes the whole high scores list back out to the file, replacing whatever was there before.
void Game::SaveHighScores() const
{
    std::ofstream outFile(highScoreFile);   // open for writing, this overwrites the file's contents
    for (const Highscore& h : highScores)
    {
        // score on one line, then the name on the next.. that way names with spaces still read back cleanly
        outFile << h.score << "\n" << h.name << "\n";
    }
    outFile.close();
}

// prints the saved high scores, or a friendly note if there are not any yet.
void Game::ViewHighScores() const
{
    std::cout << "\n--- High Scores ---\n";
    if (highScores.size() == 0)   // nothing has been saved yet
    {
        std::cout << "No high scores yet. Go earn one!\n";
        return;
    }

    // the list is already ranked best first, so i just number them off as i print
    for (size_t i = 0; i < highScores.size(); i++)
    {
        std::cout << (i + 1) << ". " << highScores[i].name << "\t" << highScores[i].score << "\n";
    }
}

// ranks the high scores so the biggest score is first, then trims the list down to the top 10.
void Game::SortAndCapHighScores()
{
    // a simple bubble sort.. i keep sweeping through and swapping any pair that is out of order,
    // pushing the bigger scores toward the front, until the whole list is ranked highest first.
    for (size_t pass = 0; pass < highScores.size(); pass++)
    {
        for (size_t j = 0; j + 1 < highScores.size(); j++)
        {
            if (highScores[j].score < highScores[j + 1].score)   // the later one is bigger, so they are out of order
            {
                Highscore temp = highScores[j];       // stash the smaller one
                highScores[j] = highScores[j + 1];    // move the bigger one up
                highScores[j + 1] = temp;             // drop the stashed one into the open spot
            }
        }
    }

    // now that the best scores are up front, drop anything past the tenth spot so the list stays a top 10
    while (highScores.size() > 10)
    {
        highScores.pop_back();
    }
}
