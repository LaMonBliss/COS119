# Milestone 2 Changelog

## Project: Formula Fusion

This documents the changes I made during Milestone 2, the features I added, the updates to
my code structure, and the usability improvements, with the reasoning behind each one.

## Features Added

**Build It mode**
Added the second game mode. The game names a compound and the player assembles its formula
one element at a time by entering an element symbol and a count. The game builds the formula
from the proper element symbols and compares it to the real formula, then shows the result
and the fun fact. This turns the program from a one mode quiz into an actual two mode game.

## Updates to Code Structure

**New helper functions on the Game class**
- `FindElement` takes a symbol and returns a pointer to the matching element, or nullptr if
  it is not one we have. Using a pointer lets the caller both check for "not found" and read
  the element's real symbol. This is what Build It uses to reject invalid input.
- `GetCount` reads a whole number count for Build It. It is line based so it works cleanly
  next to the symbol reading, and it keeps asking until the input is a valid number in range.
- `Normalize` was expanded (see usability below).

Keeping these as small, single purpose helpers on Game means each game mode stays short and
readable, and the shared logic lives in one place instead of being copied around.

## Usability Improvements (what changed and why)

**Case insensitive answers**
Before, typing "water" when the answer was "Water" got marked wrong, which felt unfair. I
now run both the guess and the real answer through `Normalize`, which lowercases them first,
so capitalization no longer matters.

**Special character and space tolerance**
I expanded `Normalize` to keep only letters and digits, dropping spaces, punctuation, and
symbols. Now "water!", "carbon-dioxide", and "  Water  " all count as correct. This makes
the game far less frustrating and more forgiving for any user, which was the accessibility
focus for the week. Both game modes got this improvement from the single change.

**Accurate menu label**
The menu used to say Build It was "coming in the next milestone." Now that it works, the
option reads "Build It (build the formula from elements)" so the menu tells the truth.

**Stronger input validation in Build It**
`FindElement` rejects any symbol that is not a real element and `GetCount` rejects bad
counts, so the player gets a clear message and another try instead of a crash.

## Testing and Debugging

I compiled and ran the program frequently while building. I tested Guess It with lowercase,
spaced, and punctuated answers to confirm they all pass, tested Build It by assembling both
correct and incorrect formulas, and tested the validation by entering a fake element symbol
and bad counts to confirm the program asks again instead of breaking.

## Planned for Next (Week 3)

- A scoring system that tracks correct answers in a session
- Saving and loading high scores to a file
- A View High Scores screen and a clearer prompt pass
