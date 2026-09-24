# Formula Fusion

A console chemistry game built in C++ for COS119. You fuse elements to build known
compounds, and you can flip to a detective mode and guess a compound from its formula.
The game checks your answers against a fixed set of compounds I define myself, so it
stays fun and focused instead of trying to simulate real chemistry.

## Project Structure

- `dev/` holds the C++ project, with headers in `include/` and sources in `src/`
- `docs/` holds documentation, progress notes, and testing evidence
- `img/` holds screenshots and other images

## Classes

- `Element` holds one element's symbol, name, and atomic number
- `Compound` holds one compound's name, formula, and a quick fun fact
- `Game` owns all the data and runs the main menu loop

## How to Run

Open `dev/FormulaFusion/FormulaFusion.sln` in Visual Studio, then build and run it.
You can also compile the sources under `dev/FormulaFusion/FormulaFusion/src` with any
C++20 compiler.

## Weekly Stand Up

### Milestone 1

**Overview**

This week I set up my whole project and built the core of Formula Fusion. I got my
repository organized with a dev folder for code, a docs folder for documentation, and
an img folder for screenshots. From there I built the starting version of the game with
three classes, a working menu loop, input validation, and a playable Guess It mode.

**Challenges**

The newer part for me was the Git workflow, working across a dev branch and a main
branch and keeping them in sync before opening a pull request. My other honest challenge
is staying consistent instead of letting work pile up, and I'm handling that by
committing in smaller chunks as I finish each piece.

**Accomplishments**

I leveled up the most on version control. Getting comfortable with branches, commits,
and syncing dev into main before a pull request made the whole workflow finally click.
I also kept my code cleanly separated across files instead of dumping everything into main.

**Next Steps**

Before the next milestone I want to finish Build It mode so the player can assemble a
formula, add case insensitive guessing, start a scoring system, and eventually save
high scores out to a file.

### Milestone 2

**Overview**

This week I turned the structure into a game that actually plays. I finished Build It mode,
where the game names a compound and I assemble its formula element by element, and I made
both game modes a lot more forgiving so casing, extra spaces, and special characters no
longer get a correct answer marked wrong. I also wrote a prototype blueprint and a
Milestone 2 planning worksheet for my docs folder.

**Challenges**

My main obstacle was Git. I got turned around between my dev and main branches and briefly
thought I lost my work, but it was safe and I was just on the wrong branch. I am handling
that by checking which branch I am on before I commit. Reading a symbol and then a number
in Build It also got finicky, so I wrote a dedicated line based input helper to keep it clean.

**Accomplishments**

I leveled up on writing reusable code. One cleanup helper is shared by both game modes, so a
single change made the whole game more forgiving at once. I also used a helper that hands back
a pointer to look up an element by its symbol, which is what finally made pointers click for me.

**Next Steps**

Before Week 3 I want to add a scoring system, then build saving and loading high scores to a
file, which will be my main chance to practice file input and output.

### Milestone 3

**Overview**

This week I expanded Formula Fusion with real progress features and spent time cleaning up the
code I already had. The game went from a two mode quiz to something that actually tracks how
you do and remembers it between runs.

**Improvements**

I added a scoring system that tracks correct answers and shows the current score in the menu. I
turned my high scores into a real leaderboard that asks the player for their name up front, ranks
the scores best first, keeps a top ten, and saves and loads them from a file so they carry over
between runs. I added an ASCII molecule diagram to Build It that draws the compound as boxed atoms
wired together, growing live as the player adds each element. I also cleaned up the console so it
clears between menus instead of scrolling forever. On the code quality side I did two refactors,
pulling the duplicated random compound pick into a shared GetRandomCompound helper, and pulling the
shared correct or miss ending out of both modes into a ShowResult helper.

**Challenges**

The honest one was staying on pace after a lighter week, which I handled by breaking the work
into small commits and knocking them out one at a time. On the code side, getting the high
scores file to read names with spaces and to not crash on the very first run when the file does
not exist yet took a little care.

**Accomplishments**

I leveled up on file input and output, actually reading from and writing to a file for the first
time in this project. I also got better at spotting duplicated code and pulling it into shared
helpers instead of leaving it copy pasted.

**Next Steps**

Before Week 4 I want to keep refining, sort the high scores so the best one shows first, and
maybe add a few more compounds so there is more variety to play with.

### Milestone 4

**Overview**

This was the final week, and I went big. I turned Formula Fusion from a simple quiz into a full
game with progression, difficulty, and a real content library, while keeping the code clean as it
grew.

**Improvements**

I added the player name and score to the header, a real points per question system, and a
difficulty select that changes both the points and which compounds show up. I gave both game modes
quick and endless rounds with numbered questions and a round summary, so it is no longer one
question and back to the menu. I made both view screens interactive so you can
pick a compound and see its molecule, or pick an element and see it drawn as a single atom. And I loaded the whole content library, all 118 elements of
the periodic table and 34 compounds across the difficulty levels. On the code side I split each
mode into a single question helper and wrote one shared round runner they both call, and I added a
formula parser so the molecule viewer could reuse my existing drawing helper.

**Challenges**

The main challenge was adding a lot of features fast without turning the Game class into a mess. I
kept it under control by pulling shared logic into helpers like the round runner and the formula
parser. Some smaller puzzles came up too, like raising the build count cap so big molecules like
sucrose could still be built, and guarding the molecule drawing so huge molecules do not spill off
the screen.

**Accomplishments**

I leveled up on structuring a program as it grows. Splitting the modes into small helpers and
sharing one round runner made adding features feel clean instead of chaotic, and writing my own
formula parser with plain character math was a good exercise in breaking a problem down.

I also finished the polish this week. The game opens on an ASCII title screen, and the long lists
are now paged, View Elements shows twenty at a time and View Compounds pages through with next and
previous navigation, so nothing runs off the screen.

**Next Steps**

The core game is complete and polished. My last step is putting together the showcase presentation
to demo everything the game can do, then the final submission.
