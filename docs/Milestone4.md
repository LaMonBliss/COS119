# Milestone 4 Changelog

## Project: Formula Fusion

This is the final week. This milestone was about turning Formula Fusion from a simple two mode
quiz into a full game with progression, difficulty, and a real content library, while keeping
the code clean.

## Features Added

**Player name and score in the header**
The player's name now shows at the top of every screen right next to their current score and
difficulty, so they always know who is playing and how they are doing.

**Points per question**
Correct answers are now worth real points instead of a flat one. Each question tells the player
what it is worth up front, and the result tells them how many points they earned.

**Difficulty selection**
Right after entering their name, the player picks Easy, Medium, or Hard. The difficulty sets how
many points each question is worth (10, 20, or 30) and which compounds can show up. Each compound
now carries a difficulty rating from 1 to 3, and the game only pulls compounds at or below the
chosen difficulty.

**Rounds with quick and endless options**
The game modes are no longer one question and back to the menu. When the player picks Guess It or
Build It, they choose a quick round of five questions or an endless run that keeps going until
they stop. Either way the questions are numbered, and each round ends with a summary of how many
they got right and their total score.

**ASCII molecule viewer**
View Compounds is now interactive. The player picks a compound from the list and the game draws
its molecule as an ASCII diagram, boxed atoms wired together with bonds. Molecules that are too
big to fit on one line show a note instead of a broken diagram.

**A full content library**
The game now loads all 118 elements of the periodic table and a library of 34 compounds spread
across the three difficulty levels, all with real formulas and fun facts.

## Updates to System Design

- Compound gained a difficulty field with a matching getter.
- Game gained new members: pointsPerQuestion, maxDifficulty, and difficultyName.
- Game gained new methods: PlayRound, AskGuessQuestion, AskBuildQuestion, and ParseFormula.

## Refactoring and Code Quality

**Shared round runner**
Rather than copy the whole round loop into both game modes, I split each mode into a single
question helper (AskGuessQuestion and AskBuildQuestion) and wrote one PlayRound method that both
modes call. PlayRound handles the quick or endless choice, the question numbering, and the
summary in one place, so the two modes share all of that instead of duplicating it.

**Formula parser**
The ASCII viewer needed a way to turn a formula string back into a list of atoms. I wrote a
ParseFormula helper that walks the formula, reads each symbol and its count, and builds the atom
list. This reuses the same DrawMolecule helper that Build It already uses.

## Testing and Debugging

I compiled and tested constantly. I confirmed the header shows the name, score, and difficulty,
that points scale with difficulty and the compound pool filters correctly, that quick rounds run
five numbered questions and endless runs stop on command, and that both modes still work through
the shared round runner. I tested the molecule viewer on small compounds like water and on big
ones like sucrose to confirm the width guard works, and I verified all 118 elements and 34
compounds load and that big formulas are still buildable after raising the count cap.

## Wrap Up

This was the last development milestone. Formula Fusion is now a complete game with two modes,
difficulty, scoring, a saved leaderboard, live molecule diagrams, and a full periodic table.
