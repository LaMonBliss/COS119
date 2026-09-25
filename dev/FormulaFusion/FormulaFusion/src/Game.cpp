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
    // the full periodic table, all 118 elements with their symbol, name, and atomic number
    elements.push_back(Element("H", "Hydrogen", 1));
    elements.push_back(Element("He", "Helium", 2));
    elements.push_back(Element("Li", "Lithium", 3));
    elements.push_back(Element("Be", "Beryllium", 4));
    elements.push_back(Element("B", "Boron", 5));
    elements.push_back(Element("C", "Carbon", 6));
    elements.push_back(Element("N", "Nitrogen", 7));
    elements.push_back(Element("O", "Oxygen", 8));
    elements.push_back(Element("F", "Fluorine", 9));
    elements.push_back(Element("Ne", "Neon", 10));
    elements.push_back(Element("Na", "Sodium", 11));
    elements.push_back(Element("Mg", "Magnesium", 12));
    elements.push_back(Element("Al", "Aluminum", 13));
    elements.push_back(Element("Si", "Silicon", 14));
    elements.push_back(Element("P", "Phosphorus", 15));
    elements.push_back(Element("S", "Sulfur", 16));
    elements.push_back(Element("Cl", "Chlorine", 17));
    elements.push_back(Element("Ar", "Argon", 18));
    elements.push_back(Element("K", "Potassium", 19));
    elements.push_back(Element("Ca", "Calcium", 20));
    elements.push_back(Element("Sc", "Scandium", 21));
    elements.push_back(Element("Ti", "Titanium", 22));
    elements.push_back(Element("V", "Vanadium", 23));
    elements.push_back(Element("Cr", "Chromium", 24));
    elements.push_back(Element("Mn", "Manganese", 25));
    elements.push_back(Element("Fe", "Iron", 26));
    elements.push_back(Element("Co", "Cobalt", 27));
    elements.push_back(Element("Ni", "Nickel", 28));
    elements.push_back(Element("Cu", "Copper", 29));
    elements.push_back(Element("Zn", "Zinc", 30));
    elements.push_back(Element("Ga", "Gallium", 31));
    elements.push_back(Element("Ge", "Germanium", 32));
    elements.push_back(Element("As", "Arsenic", 33));
    elements.push_back(Element("Se", "Selenium", 34));
    elements.push_back(Element("Br", "Bromine", 35));
    elements.push_back(Element("Kr", "Krypton", 36));
    elements.push_back(Element("Rb", "Rubidium", 37));
    elements.push_back(Element("Sr", "Strontium", 38));
    elements.push_back(Element("Y", "Yttrium", 39));
    elements.push_back(Element("Zr", "Zirconium", 40));
    elements.push_back(Element("Nb", "Niobium", 41));
    elements.push_back(Element("Mo", "Molybdenum", 42));
    elements.push_back(Element("Tc", "Technetium", 43));
    elements.push_back(Element("Ru", "Ruthenium", 44));
    elements.push_back(Element("Rh", "Rhodium", 45));
    elements.push_back(Element("Pd", "Palladium", 46));
    elements.push_back(Element("Ag", "Silver", 47));
    elements.push_back(Element("Cd", "Cadmium", 48));
    elements.push_back(Element("In", "Indium", 49));
    elements.push_back(Element("Sn", "Tin", 50));
    elements.push_back(Element("Sb", "Antimony", 51));
    elements.push_back(Element("Te", "Tellurium", 52));
    elements.push_back(Element("I", "Iodine", 53));
    elements.push_back(Element("Xe", "Xenon", 54));
    elements.push_back(Element("Cs", "Cesium", 55));
    elements.push_back(Element("Ba", "Barium", 56));
    elements.push_back(Element("La", "Lanthanum", 57));
    elements.push_back(Element("Ce", "Cerium", 58));
    elements.push_back(Element("Pr", "Praseodymium", 59));
    elements.push_back(Element("Nd", "Neodymium", 60));
    elements.push_back(Element("Pm", "Promethium", 61));
    elements.push_back(Element("Sm", "Samarium", 62));
    elements.push_back(Element("Eu", "Europium", 63));
    elements.push_back(Element("Gd", "Gadolinium", 64));
    elements.push_back(Element("Tb", "Terbium", 65));
    elements.push_back(Element("Dy", "Dysprosium", 66));
    elements.push_back(Element("Ho", "Holmium", 67));
    elements.push_back(Element("Er", "Erbium", 68));
    elements.push_back(Element("Tm", "Thulium", 69));
    elements.push_back(Element("Yb", "Ytterbium", 70));
    elements.push_back(Element("Lu", "Lutetium", 71));
    elements.push_back(Element("Hf", "Hafnium", 72));
    elements.push_back(Element("Ta", "Tantalum", 73));
    elements.push_back(Element("W", "Tungsten", 74));
    elements.push_back(Element("Re", "Rhenium", 75));
    elements.push_back(Element("Os", "Osmium", 76));
    elements.push_back(Element("Ir", "Iridium", 77));
    elements.push_back(Element("Pt", "Platinum", 78));
    elements.push_back(Element("Au", "Gold", 79));
    elements.push_back(Element("Hg", "Mercury", 80));
    elements.push_back(Element("Tl", "Thallium", 81));
    elements.push_back(Element("Pb", "Lead", 82));
    elements.push_back(Element("Bi", "Bismuth", 83));
    elements.push_back(Element("Po", "Polonium", 84));
    elements.push_back(Element("At", "Astatine", 85));
    elements.push_back(Element("Rn", "Radon", 86));
    elements.push_back(Element("Fr", "Francium", 87));
    elements.push_back(Element("Ra", "Radium", 88));
    elements.push_back(Element("Ac", "Actinium", 89));
    elements.push_back(Element("Th", "Thorium", 90));
    elements.push_back(Element("Pa", "Protactinium", 91));
    elements.push_back(Element("U", "Uranium", 92));
    elements.push_back(Element("Np", "Neptunium", 93));
    elements.push_back(Element("Pu", "Plutonium", 94));
    elements.push_back(Element("Am", "Americium", 95));
    elements.push_back(Element("Cm", "Curium", 96));
    elements.push_back(Element("Bk", "Berkelium", 97));
    elements.push_back(Element("Cf", "Californium", 98));
    elements.push_back(Element("Es", "Einsteinium", 99));
    elements.push_back(Element("Fm", "Fermium", 100));
    elements.push_back(Element("Md", "Mendelevium", 101));
    elements.push_back(Element("No", "Nobelium", 102));
    elements.push_back(Element("Lr", "Lawrencium", 103));
    elements.push_back(Element("Rf", "Rutherfordium", 104));
    elements.push_back(Element("Db", "Dubnium", 105));
    elements.push_back(Element("Sg", "Seaborgium", 106));
    elements.push_back(Element("Bh", "Bohrium", 107));
    elements.push_back(Element("Hs", "Hassium", 108));
    elements.push_back(Element("Mt", "Meitnerium", 109));
    elements.push_back(Element("Ds", "Darmstadtium", 110));
    elements.push_back(Element("Rg", "Roentgenium", 111));
    elements.push_back(Element("Cn", "Copernicium", 112));
    elements.push_back(Element("Nh", "Nihonium", 113));
    elements.push_back(Element("Fl", "Flerovium", 114));
    elements.push_back(Element("Mc", "Moscovium", 115));
    elements.push_back(Element("Lv", "Livermorium", 116));
    elements.push_back(Element("Ts", "Tennessine", 117));
    elements.push_back(Element("Og", "Oganesson", 118));

    // the compounds the player can view, guess, and build.. name, formula, a quick fact, and a difficulty (1 to 3)
    // difficulty 1 is easy and common with small formulas
    compounds.push_back(Compound("Water", "H2O", "Covers about 71 percent of the earth's surface.", 1));
    compounds.push_back(Compound("Carbon Dioxide", "CO2", "What we breathe out and plants breathe in.", 1));
    compounds.push_back(Compound("Table Salt", "NaCl", "The salt sitting on your kitchen table.", 1));
    compounds.push_back(Compound("Oxygen Gas", "O2", "The gas your lungs pull out of every breath.", 1));
    compounds.push_back(Compound("Hydrogen Gas", "H2", "The lightest and most common element in the universe.", 1));
    compounds.push_back(Compound("Nitrogen Gas", "N2", "Makes up about 78 percent of the air you breathe.", 1));
    compounds.push_back(Compound("Carbon Monoxide", "CO", "A silent, colorless gas that is dangerous to breathe.", 1));
    compounds.push_back(Compound("Methane", "CH4", "The main ingredient in natural gas.", 1));
    compounds.push_back(Compound("Ammonia", "NH3", "That sharp smell in a lot of cleaning products.", 1));

    // difficulty 2 is common but a step up
    compounds.push_back(Compound("Hydrochloric Acid", "HCl", "The strong acid your stomach uses to digest food.", 2));
    compounds.push_back(Compound("Sodium Hydroxide", "NaOH", "Also known as lye, used to make soap.", 2));
    compounds.push_back(Compound("Hydrogen Peroxide", "H2O2", "The stuff that bubbles up on a cut.", 2));
    compounds.push_back(Compound("Sulfuric Acid", "H2SO4", "A powerful acid used in car batteries.", 2));
    compounds.push_back(Compound("Calcium Carbonate", "CaCO3", "What chalk, limestone, and seashells are made of.", 2));
    compounds.push_back(Compound("Sodium Bicarbonate", "NaHCO3", "Baking soda, the stuff that makes cookies rise.", 2));
    compounds.push_back(Compound("Ozone", "O3", "The gas high up that shields us from the sun's rays.", 2));
    compounds.push_back(Compound("Sulfur Dioxide", "SO2", "A sharp smelling gas released by volcanoes.", 2));
    compounds.push_back(Compound("Nitrous Oxide", "N2O", "Also called laughing gas at the dentist.", 2));
    compounds.push_back(Compound("Potassium Chloride", "KCl", "A salt substitute and a source of potassium.", 2));
    compounds.push_back(Compound("Calcium Oxide", "CaO", "Called quicklime, used to make cement.", 2));
    compounds.push_back(Compound("Nitric Acid", "HNO3", "A strong acid used to make fertilizers.", 2));
    compounds.push_back(Compound("Methanol", "CH4O", "A simple alcohol, but very toxic to drink.", 2));

    // difficulty 3 is complex, organic, or less common
    compounds.push_back(Compound("Glucose", "C6H12O6", "The sugar your body burns for energy.", 3));
    compounds.push_back(Compound("Sucrose", "C12H22O11", "Regular table sugar.", 3));
    compounds.push_back(Compound("Ethanol", "C2H6O", "The alcohol found in beer and wine.", 3));
    compounds.push_back(Compound("Acetic Acid", "C2H4O2", "What gives vinegar its sour taste.", 3));
    compounds.push_back(Compound("Octane", "C8H18", "A big part of what fuels your car.", 3));
    compounds.push_back(Compound("Benzene", "C6H6", "A ring shaped molecule used to make plastics.", 3));
    compounds.push_back(Compound("Sodium Carbonate", "Na2CO3", "Washing soda, used in glass and detergents.", 3));
    compounds.push_back(Compound("Potassium Permanganate", "KMnO4", "A deep purple crystal used to treat water.", 3));
    compounds.push_back(Compound("Iron Oxide", "Fe2O3", "Just a fancy name for rust.", 3));
    compounds.push_back(Compound("Ammonium Chloride", "NH4Cl", "A salt used in some batteries and licorice candy.", 3));
    compounds.push_back(Compound("Silicon Dioxide", "SiO2", "What sand and quartz are made of.", 3));
    compounds.push_back(Compound("Phosphoric Acid", "H3PO4", "The tangy acid in a lot of sodas.", 3));
}

// the main loop.. show the menu, grab a valid choice, do the thing, then repeat until they quit
void Game::Run()
{
    // show the title screen, then grab the player's name once up front so every high score saves under it
    ShowTitleScreen();
    std::cout << "What is your player name? ";
    std::getline(std::cin, playerName);

    // let the player pick a difficulty, which sets both the points per question and how tough the compounds get
    std::cout << "\nPick a difficulty:\n";
    std::cout << "1. Easy    (10 points, simple compounds)\n";
    std::cout << "2. Medium  (20 points, tougher compounds)\n";
    std::cout << "3. Hard    (30 points, anything goes)\n";
    int diff = GetChoice(1, 3);
    if (diff == 1)
    {
        pointsPerQuestion = 10;
        maxDifficulty = 1;
        difficultyName = "Easy";
    }
    else if (diff == 2)
    {
        pointsPerQuestion = 20;
        maxDifficulty = 2;
        difficultyName = "Medium";
    }
    else
    {
        pointsPerQuestion = 30;
        maxDifficulty = 3;
        difficultyName = "Hard";
    }

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

// prints the title screen with a little ascii banner and a water molecule when the game first starts.
void Game::ShowTitleScreen() const
{
    ClearScreen();
    std::cout << "================================================\n";
    std::cout << "         F O R M U L A   F U S I O N\n";
    std::cout << "================================================\n\n";
    std::cout << "        +----+     +----+     +----+\n";
    std::cout << "        | H  |-----| O  |-----| H  |\n";
    std::cout << "        +----+     +----+     +----+\n\n";
    std::cout << "           a console chemistry game\n\n";
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
    std::cout << "Player: " << playerName << "     Score: " << currentScore << "     Difficulty: " << difficultyName << "\n";
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
    const int perPage = 20;   // how many elements to show on one page
    int totalPages = ((int)elements.size() + perPage - 1) / perPage;   // round up so the last few still get a page
    int page = 0;             // which page we are on, starting at the first

    bool viewing = true;
    while (viewing)
    {
        ClearScreen();

        // work out the slice of elements this page covers
        int start = page * perPage;
        int end = start + perPage;
        if (end > (int)elements.size())
        {
            end = (int)elements.size();
        }

        std::cout << "--- Element Table (page " << (page + 1) << " of " << totalPages << ") ---\n";
        for (int i = start; i < end; i++)
        {
            std::cout << elements[i].GetAtomicNumber() << "\t" << elements[i].GetSymbol() << "\t" << elements[i].GetName() << "\n";
        }

        // show the options.. next and previous only appear when there is actually a page to go to
        std::cout << "\nEnter an element number to see it drawn as an atom.\n";
        if (page < totalPages - 1)
        {
            std::cout << "Enter n for the next page.\n";
        }
        if (page > 0)
        {
            std::cout << "Enter p for the previous page.\n";
        }
        std::cout << "Enter 0 to go back.\n";
        std::cout << "Choice: ";

        std::string input;
        std::getline(std::cin, input);
        std::string choice = Normalize(input);   // clean it up so n, N, and stray spaces all behave

        if (choice == "0")   // done browsing
        {
            viewing = false;
        }
        else if (choice == "n" && page < totalPages - 1)   // flip to the next page
        {
            page++;
        }
        else if (choice == "p" && page > 0)   // flip to the previous page
        {
            page--;
        }
        else
        {
            // otherwise try to read it as an element number, building the number up from its digits
            int number = 0;
            bool allDigits = (choice.size() > 0);
            for (char ch : choice)
            {
                if (isdigit((unsigned char)ch))
                {
                    number = number * 10 + (ch - '0');
                }
                else
                {
                    allDigits = false;
                }
            }

            if (allDigits && number >= 1 && number <= (int)elements.size())
            {
                const Element& e = elements[number - 1];   // the elements are in order, so number lines up with index plus one
                std::cout << "\n" << e.GetName() << " (atomic number " << e.GetAtomicNumber() << ")\n";

                // draw the single element as one boxed atom, reusing the molecule drawer with a list of one
                std::vector<std::string> atom;
                atom.push_back(e.GetSymbol());
                DrawMolecule(atom);
                PauseForEnter();
            }
            else
            {
                std::cout << "That is not a valid choice.\n";
                PauseForEnter();
            }
        }
    }
}

// lists the compounds a page at a time and lets the player pick one to see its molecule.
void Game::ViewCompounds() const
{
    const int perPage = 12;   // how many compounds to show on one page
    int totalPages = ((int)compounds.size() + perPage - 1) / perPage;   // round up so the last few still get a page
    int page = 0;             // which page we are on, starting at the first

    bool viewing = true;
    while (viewing)
    {
        ClearScreen();

        // work out the slice of compounds this page covers
        int start = page * perPage;
        int end = start + perPage;
        if (end > (int)compounds.size())
        {
            end = (int)compounds.size();
        }

        std::cout << "--- Known Compounds (page " << (page + 1) << " of " << totalPages << ") ---\n";
        for (int i = start; i < end; i++)
        {
            std::cout << (i + 1) << ". " << compounds[i].GetFormula() << "\t" << compounds[i].GetName() << "\n";
        }

        // show the options.. next and previous only appear when there is actually a page to go to
        std::cout << "\nEnter a compound number to see its molecule.\n";
        if (page < totalPages - 1)
        {
            std::cout << "Enter n for the next page.\n";
        }
        if (page > 0)
        {
            std::cout << "Enter p for the previous page.\n";
        }
        std::cout << "Enter 0 to go back.\n";
        std::cout << "Choice: ";

        std::string input;
        std::getline(std::cin, input);
        std::string choice = Normalize(input);   // clean it up so n, N, and stray spaces all behave

        if (choice == "0")   // done browsing
        {
            viewing = false;
        }
        else if (choice == "n" && page < totalPages - 1)   // flip to the next page
        {
            page++;
        }
        else if (choice == "p" && page > 0)   // flip to the previous page
        {
            page--;
        }
        else
        {
            // otherwise try to read it as a compound number, building the number up from its digits
            int number = 0;
            bool allDigits = (choice.size() > 0);
            for (char ch : choice)
            {
                if (isdigit((unsigned char)ch))
                {
                    number = number * 10 + (ch - '0');
                }
                else
                {
                    allDigits = false;
                }
            }

            if (allDigits && number >= 1 && number <= (int)compounds.size())
            {
                const Compound& c = compounds[number - 1];   // the list is 1 based, the vector is 0 based
                std::cout << "\n" << c.GetName() << "  (" << c.GetFormula() << ")\n";

                std::vector<std::string> atoms = ParseFormula(c.GetFormula());
                if (atoms.size() <= 10)   // small enough to draw neatly on one line
                {
                    DrawMolecule(atoms);
                }
                else
                {
                    std::cout << "This molecule has too many atoms to draw on one line.\n";
                }
                PauseForEnter();
            }
            else
            {
                std::cout << "That is not a valid choice.\n";
                PauseForEnter();
            }
        }
    }
}

// picks one random compound from my list and hands back a reference to it.
// both game modes call this, so the random logic lives in one spot instead of being copied twice.
const Compound& Game::GetRandomCompound() const
{
    // first gather the indexes of every compound that fits the chosen difficulty ceiling
    std::vector<int> eligible;
    for (int i = 0; i < (int)compounds.size(); i++)
    {
        if (compounds[i].GetDifficulty() <= maxDifficulty)
        {
            eligible.push_back(i);
        }
    }

    // one random engine, seeded once off the hardware, kept alive between calls with static
    static std::mt19937 engine(std::random_device{}());
    // pick a random spot in the eligible list, then return that compound
    std::uniform_int_distribution<int> pick(0, (int)eligible.size() - 1);
    return compounds[eligible[pick(engine)]];
}

// the shared ending both game modes use once they know if the player was right.
// on a correct answer it bumps the score and shows the fact, otherwise it prints the miss
// message the mode passed in, then the fact. keeping it here means the result logic lives in one spot.
void Game::ShowResult(bool correct, const Compound& target, const std::string& missMessage)
{
    if (correct)
    {
        currentScore += pointsPerQuestion;   // award the points this question was worth
        std::cout << "Correct! You earned " << pointsPerQuestion << " points.\n";
    }
    else
    {
        std::cout << missMessage << "\n";        // the mode's own wording for a wrong answer
        std::cout << "No points that time.\n";
    }

    std::cout << target.GetFact() << "\n";   // the fun fact is always the last thing shown, on its own line
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

// turns a formula string like H2O or C6H12O6 into a list of individual atoms so it can be drawn.
// it walks the string reading a symbol (an uppercase letter plus an optional lowercase one),
// then any digits after it as the count, and adds that symbol to the list that many times.
std::vector<std::string> Game::ParseFormula(const std::string& formula) const
{
    std::vector<std::string> atoms;

    size_t i = 0;
    while (i < formula.size())
    {
        // a symbol always starts with the current character, an uppercase letter
        std::string symbol;
        symbol += formula[i];
        i++;

        // a lowercase letter right after belongs to the same symbol, like the l in Cl
        if (i < formula.size() && islower((unsigned char)formula[i]))
        {
            symbol += formula[i];
            i++;
        }

        // read any digits right after the symbol and build them into the count
        int count = 0;
        bool hasDigits = false;
        while (i < formula.size() && isdigit((unsigned char)formula[i]))
        {
            count = count * 10 + (formula[i] - '0');   // shift the running number over and add the new digit
            hasDigits = true;
            i++;
        }
        if (!hasDigits)   // no number written means there is just one of this element
        {
            count = 1;
        }

        // add this symbol once for each atom it represents
        for (int k = 0; k < count; k++)
        {
            atoms.push_back(symbol);
        }
    }

    return atoms;
}

// Guess It.. runs a whole round of guessing the compound from its formula
void Game::GuessItMode()
{
    PlayRound(true);
}

// Build It.. runs a whole round of assembling the formula from elements
void Game::BuildItMode()
{
    PlayRound(false);
}

// plays a round of one of the game modes. the player picks a quick five question round or an endless run,
// and either way the questions are numbered and the round finishes with a little summary.
// guessMode true means play Guess It, false means play Build It.
void Game::PlayRound(bool guessMode)
{
    // ask how they want to play this round
    std::cout << "\nHow do you want to play?\n";
    std::cout << "1. Quick round (5 questions)\n";
    std::cout << "2. Endless (until you stop)\n";
    int choice = GetChoice(1, 2);

    bool endless = (choice == 2);   // endless keeps going until the player chooses to stop
    int total = 5;                  // how many questions a quick round runs

    int questionNumber = 0;   // which question we are on
    int gotRight = 0;         // how many they have gotten right this round
    bool playing = true;

    while (playing)
    {
        questionNumber++;

        ClearScreen();
        // show which question this is.. endless just counts up since there is no end total
        if (endless)
        {
            std::cout << "Question " << questionNumber << "\n";
        }
        else
        {
            std::cout << "Question " << questionNumber << " of " << total << "\n";
        }

        // ask one question of whichever mode, and remember whether they nailed it
        bool correct;
        if (guessMode)
        {
            correct = AskGuessQuestion();
        }
        else
        {
            correct = AskBuildQuestion();
        }
        if (correct)
        {
            gotRight++;
        }

        // now decide whether the round keeps going
        if (endless)
        {
            std::cout << "\nPress Enter for another question, or type q to stop: ";
            std::string answer;
            std::getline(std::cin, answer);
            if (Normalize(answer) == "q")   // they want to head back to the menu
            {
                playing = false;
            }
        }
        else
        {
            if (questionNumber >= total)   // finished the whole set round
            {
                playing = false;
            }
            else
            {
                PauseForEnter();   // let them read the result before the next question clears the screen
            }
        }
    }

    // wrap the round up with a quick summary
    std::cout << "\nRound over! You got " << gotRight << " right. Total score: " << currentScore << ".\n";
}

// asks one Guess It question.. pick a random compound, show its formula, and see if the player knows the name.
// returns whether they got it right so the round can keep a tally.
bool Game::AskGuessQuestion()
{
    const Compound& target = GetRandomCompound();   // grab a random compound to quiz the player on

    std::cout << "\n--- Guess It ---\n";
    std::cout << pointsPerQuestion << " points\n";
    std::cout << "What compound has the formula " << target.GetFormula() << " ?\n";

    // keep reading until the player gives a real guess.. typing hint just shows a clue and asks again
    std::string guess;
    while (true)
    {
        std::cout << "Your guess (or type hint): ";
        std::getline(std::cin, guess);   // whole line since names can have spaces, like Carbon Dioxide

        if (Normalize(guess) == "hint")
        {
            // the clue is the first letter of the name.. enough to point them at it without giving it away
            std::cout << "  Hint: the name starts with the letter " << target.GetName()[0] << ".\n";
            continue;   // loop back and ask for the guess again
        }
        break;   // a real guess, move on
    }

    // run BOTH the guess and the real name through Normalize before comparing.. that way casing and
    // stray spaces do not matter, so water, WATER, and " Water " all count as a correct Water
    bool correct = (Normalize(guess) == Normalize(target.GetName()));
    ShowResult(correct, target, "Not quite. That formula is " + target.GetName() + ".");
    return correct;
}

// asks one Build It question.. name a compound, then let the player assemble its formula one element at a time.
// returns whether the formula they built matched, so the round can keep a tally.
bool Game::AskBuildQuestion()
{
    const Compound& target = GetRandomCompound();   // grab a random compound for the player to build

    std::cout << "\n--- Build It ---\n";
    std::cout << pointsPerQuestion << " points\n";
    std::cout << "Build this compound: " << target.GetName() << "\n\n";
    // with the full periodic table loaded there are too many symbols to list, so i just explain how to enter them
    std::cout << "Add elements one at a time using their symbols, like H or Na.\n";
    std::cout << "Type done when you are finished.\n";

    std::string built;                  // the formula the player is assembling, starts empty
    std::vector<std::string> atoms;     // every atom added in order, so i can draw the molecule as it grows

    while (true)
    {
        std::cout << "Element symbol (done, or hint): ";
        std::string symbol;
        std::getline(std::cin, symbol);

        if (Normalize(symbol) == "done")   // the player is finished adding elements
        {
            break;
        }

        if (Normalize(symbol) == "hint")   // give a clue about the size of the formula, then ask again
        {
            // the clue is how many atoms the real formula has.. helps without spelling it out
            std::vector<std::string> hintAtoms = ParseFormula(target.GetFormula());
            std::cout << "  Hint: this formula has " << hintAtoms.size() << " atoms in total.\n";
            continue;   // loop back and ask for a symbol again
        }

        // make sure it is a real element from our list before we accept it
        const Element* found = FindElement(symbol);
        if (found == nullptr)   // FindElement handed back null, so this symbol is not one we have
        {
            std::cout << "  that is not one of the available elements, try again.\n";
            continue;   // skip the rest of the loop and ask again
        }

        int count = GetCount(1, 30);   // how many of this element, validated (30 covers even big molecules)

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
    return correct;
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
