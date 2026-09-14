> Use this worksheet to plan the next phase of your project **before you begin coding**
> Be clear, specific, and intentional—this will guide your development this week.

---
## 📌 Project Overview

**Project Name:**
→ Formula Fusion

**What does your program currently do? (1–3 sentences)**
→ Formula Fusion is a console chemistry game with two modes. In Guess It the game shows a formula and I name the compound, and in Build It the game names a compound and I assemble its formula element by element. It also lets me view the element table and the list of known compounds, and it checks my answers against a fixed set of compounds I defined.

---
## 🔍 Current Progress Check

**What is working right now?**
→ The main menu loop with validated input, View Elements, View Compounds, Guess It, and Build It are all working. Answer checking is forgiving now, so casing, extra spaces, and special characters do not get a correct answer marked wrong.

**What is NOT working or incomplete?**
→ There is no scoring yet, so a round just says correct or not quite and moves on. Nothing is saved between runs, so there are no high scores. Build It also expects the elements in the right order to match the real formula.

**What feels confusing or messy in your code?**
→ All my element and compound data is hardcoded inside LoadData, which is going to get long as I add more. Mixing full line input with number input in Build It also took some care to get right.

---
## 🚀 Feature Planning

List the features you plan to add or improve this week.

### Feature 1
**Name:**
→ Scoring System

**What does this feature do?**
→ It tracks how many compounds the player gets right during a session, so both game modes add to a running score instead of just saying correct and forgetting it.

**Why is this feature important?**
→ It gives the player a goal and a reason to keep playing, and it is the number my high scores feature will actually save.

---
### Feature 2
**Name:**
→ Save and Load High Scores to a File

**What does this feature do?**
→ When the game ends it writes the player name and score out to a file, and when the game starts it reads that file back in so past high scores show up again.

**Why is this feature important?**
→ It makes the game feel real by letting progress carry over between runs, and it is my main chance this week to practice file input and output in C++.

---

### Feature 3 (optional)
**Name:**
→ Clearer Prompts and a View High Scores Screen

**What does this feature do?**
→ It reworks my prompts so they say exactly what to type, and it adds a menu option to view the saved high scores at any time.

**Why is this feature important?**
→ It makes the program easier and more welcoming to use for someone who has never seen it before, which is the usability focus for this week.

---
## 🧩 System Design Updates

**Will you need to create any new classes? If so, which ones?**
→ Probably a small Highscore struct that just holds a player name and a score, to keep that data clean and easy to store in a list.

**Will you modify any existing classes? How?**
→ Game gets a score counter and a list of high scores as new members, plus new methods to save the scores to a file, load them on startup, and show the high scores screen. Guess It and Build It get a line that bumps the score up on a correct answer.

**What data structures will you use (vectors, 2D vectors, etc.)?**
→ I keep my existing vectors of Element and Compound, and I add a vector of Highscore for the leaderboard. File reading and writing will use ifstream and ofstream.

---
## 🔄 Program Flow

**Describe how a user interacts with your program:**

1. Program starts → Game loads the elements, the compounds, and any existing high scores from the file
2. User chooses → a numbered menu option like View, Guess It, Build It, View High Scores, or Quit
3. Program responds → it runs that mode, and a correct answer adds to the running score
4. Loop/next step → it returns to the main menu, and on Quit it saves the high scores back to the file before exiting

---
## 🎯 Usability Improvements

How will you make your program easier to use this week?

- Clearer prompts:
→ Reword vague prompts so each one says exactly what to enter, for example telling the player to type the compound name rather than just asking for input.

- Better error handling:
→ Extend the input checks I already have on the menu and element symbols so the high score name entry also handles empty or odd input gracefully.

- Improved menu/navigation:
→ Add a View High Scores option to the main menu and keep every screen returning cleanly to the menu so the player is never stuck.

---
## ⚠️ Potential Challenges

**What do you think will be the hardest part this week?**
→ The file input and output, especially handling the very first run when the high scores file does not exist yet so the game does not error out.

**What is your plan if you get stuck?**
→ Review the file I/O material from lecture and my past labs, test with a tiny sample file first, add one piece at a time, and stop by Discord office hours if I stay stuck.

---

## 📈 Level Up Goal

**What skill are you focusing on improving this week?**
→ File input and output in C++, reading from and writing to a file with ifstream and ofstream.

**What will you do to improve it?**
(e.g., tutorial, practice, debugging, office hours)
→ Rewatch the version control and file I/O lecture pieces, practice on a small throwaway file before touching the game, and build the save and load in small tested steps.

---
## 🗓️ Task Breakdown (GitHub Issues Planning)

List the tasks you plan to create as GitHub Issues:

- [ ] Add a scoring system that tracks correct answers in a session
- [ ] Create a Highscore struct that holds a name and a score
- [ ] Implement saving high scores to a file on quit
- [ ] Implement loading high scores from the file on startup
- [ ] Add a View High Scores menu option and clearer prompts

---

## 🔥 Final Check

Before you start coding, ask yourself:

- [x] Do I know what I’m building this week?
- [x] Do I know where to start?
- [x] Did I break my work into small tasks?

If yes → start coding 🚀
If no → refine your plan first

---
## 😈 Final Thought

> Plan it now… or debug it later.
