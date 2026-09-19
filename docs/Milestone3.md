# Milestone 3 Changelog

## Project: Formula Fusion

This documents the changes I made during Milestone 3. This week was about expanding the
program with new features and improving the quality of the code through refactoring.

## Features Added

**Scoring system**
The game now tracks how many compounds the player gets right in a session. Both Guess It
and Build It add to a running score on a correct answer, and the current score shows at the
top of the main menu so the player always sees how they are doing.

**Save and load high scores**
Added a Highscore struct (a name and a score) and a list of them on the Game class. When the
player quits after scoring at least one point, the game asks for their name and writes the
high scores out to a text file. On startup the game reads that file back in, so scores carry
over between runs. I also added a View High Scores option to the main menu. If the file does
not exist yet, like on the very first run, the game just starts with an empty list instead of
erroring out.

## Refactoring Improvements

**GetRandomCompound**
Both Guess It and Build It had the exact same few lines that set up a random engine and picked
a random compound from my vector. I pulled that into a single helper, GetRandomCompound, that
both modes now call. This removes the duplication, so if I ever change how a compound is chosen
I only touch one place instead of two.

**ShowResult**
Both modes also ended the same way, bumping the score and printing the fun fact on a correct
answer, or printing a miss message and the fact on a wrong one. I extracted that shared ending
into a ShowResult helper that takes whether the answer was correct and the mode's own miss
message. Now the result logic lives in one spot, and each mode only supplies its own wording.

## Updates to System Design

- New Highscore struct to hold a name and a score together.
- Game gained new members: currentScore, a vector of Highscore, and the high scores file name.
- Game gained new methods: GetRandomCompound, ShowResult, LoadHighScores, SaveHighScores, and
  ViewHighScores.
- The main menu grew from five options to six with the new View High Scores option.

## Testing and Debugging

I compiled and ran the program often while building. I tested that the score goes up only on
correct answers and shows in the menu, that high scores save on quit and load back on the next
run, that a name with a space reads back correctly, that the first run with no file does not
crash, and that both game modes still print their own correct and miss messages after the
ShowResult refactor.

## Next Steps (Week 4)

- Possibly show ASCII molecule diagrams for the compounds
- Sort the high scores so the best score shows first
- Keep looking for any other duplication to clean up
