# Milestone 3 Changelog

## Project: Formula Fusion

This documents the changes I made during Milestone 3. This week was about expanding the
program with new features, finishing the ones I started, and improving the quality of the
code through refactoring.

## Features Added

**Scoring system**
The game now tracks how many compounds the player gets right in a session. Both Guess It and
Build It add to a running score on a correct answer, and the current score shows at the top of
the main menu so the player always sees how they are doing.

**High scores leaderboard**
This grew from a rough idea into a full leaderboard. The game asks the player for their name up
front, so every score they earn is saved under that name. When they quit after scoring at least
one point, the game records their run, ranks the whole list best score first, trims it to a top
ten, and writes it out to a text file. On startup it reads that file back in, so the leaderboard
carries over between runs. There is a View High Scores option on the menu that prints the list
as a numbered ranking. If the file does not exist yet, like on the very first run, the game just
starts with an empty list instead of erroring out.

**ASCII molecule diagram**
Build It now draws the compound as an ASCII diagram while the player assembles it. Each atom
shows up as a boxed node wired to the next with a bond line, and the diagram grows live as each
element is added, then shows once more at the reveal. It builds the picture from a list of the
atoms the player has added, so it works for any compound they put together.

**Cleaner console (usability)**
The game now clears the screen between menus instead of scrolling into one long wall of text.
After each action it holds the screen with a Press Enter to continue prompt so the player can
read the result, then wipes it and shows a fresh menu. This makes the whole thing much easier
to follow.

## Refactoring Improvements

**GetRandomCompound**
Both Guess It and Build It had the exact same few lines that set up a random engine and picked a
random compound. I pulled that into a single helper, GetRandomCompound, that both modes now call,
so if I ever change how a compound is chosen I only touch one place instead of two.

**ShowResult**
Both modes also ended the same way, bumping the score and printing the fact on a correct answer,
or printing a miss message and the fact on a wrong one. I extracted that shared ending into a
ShowResult helper that takes whether the answer was correct and the mode's own miss message. Now
the result logic lives in one spot and each mode only supplies its own wording.

## Updates to System Design

- New Highscore struct to hold a name and a score together.
- Game gained new members: currentScore, a vector of Highscore, the high scores file name, and
  the player name.
- Game gained new methods: GetRandomCompound, ShowResult, DrawMolecule, LoadHighScores,
  SaveHighScores, ViewHighScores, SortAndCapHighScores, ClearScreen, and PauseForEnter.
- The main menu grew from five options to six with the new View High Scores option.

## Testing and Debugging

I compiled and ran the program often while building. I tested that the score goes up only on
correct answers and shows in the menu, that high scores save on quit and load back on the next
run, that a name with a space reads back correctly, and that the first run with no file does not
crash. I tested the leaderboard by seeding an unsorted file and confirming it came back ranked
highest first, and by seeding twelve scores and confirming only the top ten showed. I also
tested that both game modes still print their own correct and miss messages after the ShowResult
refactor, and that the molecule diagram grows correctly for one and two letter symbols.

## Next Steps (Week 4)

- Maybe add a few more compounds for variety
- Keep looking for any other duplication to clean up
- Continue polishing the overall program flow
