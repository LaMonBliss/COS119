#pragma once
#include <string>
#include <vector>
#include "Element.h"
#include "Compound.h"

// one high score entry.. just a player name and the score they earned that session
struct Highscore
{
    std::string name;
    int score;
};

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
    int currentScore = 0;              // the player's running points this session
    int pointsPerQuestion = 10;        // how many points a correct answer is worth, set by the difficulty
    int maxDifficulty = 3;             // the hardest compound level allowed, set by the difficulty
    std::string difficultyName = "Hard";  // the chosen difficulty name, shown in the header
    std::vector<Highscore> highScores; // the saved leaderboard, loaded from and written back to a file
    std::string highScoreFile = "highscores.txt";  // the file the high scores live in
    std::string playerName;            // the name the player gives at the start, used when saving their score

    void LoadData();                        // fills the two vectors above with the starting set
    void ClearScreen() const;               // wipes the console so each screen starts fresh instead of scrolling
    void ShowTitleScreen() const;           // prints the ascii title screen when the game first starts
    void PauseForEnter() const;             // waits for Enter so the player can read the screen before it clears
    void ShowMenu() const;                  // prints the main menu options
    void ViewElements() const;              // lists every element i loaded
    void ViewCompounds() const;             // lists every compound with its formula
    void GuessItMode();                     // runs a Guess It round (wrapper around PlayRound)
    void BuildItMode();                     // runs a Build It round (wrapper around PlayRound)
    void PlayRound(bool guessMode);         // plays a round of questions, either a set length or endless
    bool AskGuessQuestion();                // asks one Guess It question, returns whether it was right
    bool AskBuildQuestion();                // asks one Build It question, returns whether it was right
    void ShowResult(bool correct, const Compound& target, const std::string& missMessage);  // shared correct or miss ending for both modes
    void DrawMolecule(const std::vector<std::string>& atoms) const;  // draws the assembled atoms as an ascii molecule diagram
    std::vector<std::string> ParseFormula(const std::string& formula) const;  // breaks a formula string into a list of atoms to draw
    int GetChoice(int min, int max) const;  // safe menu input, keeps asking until it is valid
    int GetCount(int min, int max) const;   // reads a whole number count for Build It, line based
    std::string Normalize(const std::string& text) const;  // lowercases and strips spaces/special chars so guesses are forgiving
    const Element* FindElement(const std::string& symbol) const;  // looks up an element by symbol, or nullptr if we do not have it
    const Compound& GetRandomCompound() const;  // picks one random compound, shared by both game modes
    void LoadHighScores();                      // reads saved high scores from the file on startup
    void SaveHighScores() const;                // writes the high scores back out to the file
    void ViewHighScores() const;                // prints the saved high scores
    void SortAndCapHighScores();                // ranks the high scores best first and keeps only the top 10
};
