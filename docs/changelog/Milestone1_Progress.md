# Milestone 1 Progress Notes

## Project: Formula Fusion

A console chemistry game. You fuse elements to build known compounds, and you flip
to a detective mode to guess a compound from its formula. The game does not simulate
real chemistry rules. It checks answers against a fixed set of compounds I define
myself, which keeps it fun and finishable.

## Project Plan (Step 2 answers)

**What problem or system does it model?**
It models a small, self contained chemistry quiz. It holds a slice of the periodic
table and a set of known compounds, and turns that data into a guessing game.

**What classes will I need?**
- `Element` — one element, holding a symbol, a name, and an atomic number
- `Compound` — one compound, holding a name, a formula, and a fun fact
- `Game` — owns the data and runs the whole menu loop

**What data structures will I use?**
`std::vector<Element>` for the element table and `std::vector<Compound>` for the
compound list, both held inside the `Game` class.

**How will the user interact with the program?**
A numbered console menu. The player types a number to pick an option, and all input
runs through a validation helper that rejects anything that is not a valid choice.

**What is the minimum version that must work first?**
A running menu loop, the data loading in, the ability to view the elements and
compounds, and one working game mode. That is the foundation everything else builds on.

## What is done in Milestone 1

- Clean project structure with headers in `include/` and sources in `src/`
- Three classes, each in its own header and source file
- `main` is tiny and only starts the game, no logic living in it
- A working main menu loop with five options
- Input validation that rejects non numbers and out of range choices
- View Elements and View Compounds fully working
- Guess It mode working start to finish, picks a random compound and checks the guess
- Compiles clean with no warnings and runs correctly

## What is next

- Build It mode, where the player assembles a formula from elements (currently a placeholder)
- Case insensitive guessing so small typos do not count against the player
- A scoring system across a round
- ASCII molecule diagrams for the compounds
- Saving high scores to a file

## Changelog

- Created Element, Compound, and Game classes with header and source separation
- Loaded a starting set of 6 elements and 6 compounds
- Built the menu loop, input validation, and the two view screens
- Implemented Guess It mode with random compound selection
- Verified the whole thing compiles and runs
