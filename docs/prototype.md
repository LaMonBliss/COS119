# Formula Fusion - Prototype and Blueprint

This is the design blueprint for Formula Fusion, my console chemistry game. It maps out
the classes, the data, the flow, and how the user interacts before and while I build it.
The design has grown since Milestone 1, so this reflects where the program actually is now.

## 1. Class Design

**Element**
Holds one element from the periodic table. It stores a symbol, a name, and an atomic
number, and it only has getters since an element never needs to change once it is made.

**Compound**
Holds one known compound. It stores the everyday name, the chemical formula, and a short
fun fact. Getters only, same reasoning as Element.

**Game**
The heart of the program. It owns all the data and runs the whole menu loop. Every action
the player takes lives here as a method, so `main` stays tiny. Its responsibilities:

- Load the starting data (`LoadData`)
- Show the menu and read a valid choice (`ShowMenu`, `GetChoice`)
- Show the element table and compound list (`ViewElements`, `ViewCompounds`)
- Run the two game modes (`GuessItMode`, `BuildItMode`)
- Clean up player input so it is forgiving (`Normalize`)
- Look up an element by symbol (`FindElement`)
- Read a validated count for Build It (`GetCount`)

## 2. Data Structures

- `std::vector<Element> elements` inside Game holds my slice of the periodic table.
- `std::vector<Compound> compounds` inside Game holds the compounds the player can view,
  guess, and build.
- Strings carry the names, symbols, formulas, and the player's typed input.

Vectors are the right fit because both lists grow easily as I add more elements and
compounds later, and I can walk them with simple range based loops.

## 3. Program Flow

**Start**
`main` creates a `Game` object. The Game constructor calls `LoadData`, which fills the two
vectors, so everything is ready before anything prints. Then `main` calls `Run`.

**Loop**
`Run` repeats until the player quits:

1. Print the main menu
2. Read a valid choice with `GetChoice`, which rejects anything that is not 1 through 5
3. Do the chosen action through a switch statement
4. Return to the menu

**End**
Choosing Quit prints a goodbye, flips the loop flag to false, the loop ends, and `main`
returns 0 to exit cleanly.

## 4. User Interaction

The player drives everything from a numbered menu:

1. View Elements - lists the element table
2. View Compounds - lists each compound with its formula
3. Guess It - the game shows a formula and the player types the compound name
4. Build It - the game names a compound and the player assembles the formula element by element
5. Quit

**How input affects the system**

- In Guess It, the typed name is run through `Normalize` (lowercase, no spaces, no special
  characters) and compared to the real name, so casing and punctuation do not matter.
- In Build It, the player enters an element symbol and a count over and over. `FindElement`
  rejects anything that is not a real element, `GetCount` rejects bad counts, and the game
  builds the formula from the proper element symbols, then compares it to the real formula.
- Every menu choice runs through `GetChoice`, so bad input never crashes the program, it
  just asks again.
- After any action the player lands back on the main menu, so there are no dead ends.

## Planned Next (not built yet)

- A scoring system so a round tracks how many the player gets right
- Saving and loading high scores to a file
- ASCII molecule diagrams for the compounds

## Will This Scale?

Yes. New elements and compounds are just more entries in the two vectors. New game modes
are just new methods on Game plus one more menu option. Keeping the data in Game and the
logic split into small helpers means each new feature is an addition, not a rewrite.
