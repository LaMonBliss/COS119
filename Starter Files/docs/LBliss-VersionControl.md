# Version Control & Markdown Documentation

<br>

## Project and Portfolio I: Computer Science - Online

- **La'Mon Bliss**
- **09/06/26**

This paper addresses some of the topic matter covered in research and activity this week. Be sure to include reference links below to the research and information you used to complete this assignment.

## Topic: Terminal

Professional developers use Terminal daily. It's essential to understand some fundamental commands to use the application.

Update the information below to demonstrate your knowledge on this topic.

**1. Using Terminal, there are essential commands to know.**

List the correct Terminal commands to do the actions listed below. Replace **CMD** with the correct command sequence. You can keep or enhance the brief description.

**The last bullet provides an example**.

- `clear`: Clear the Screen
- `pwd`: Print the "Working Directory"
- `ls`: List files and folders
- `ls -a`: List files and folders, including invisible files
- `ls -alh`: List all files and folders, in human readable form
- `cd foldername`: Change directory
- `cd /`: Change directory, go to root directory
- `cd ~`: Change directory and go to user home directory
- `cd ..`: Change directory, go up one folder level
- `cd ../..`: Change directory, go up two folder levels
- `cd ~/Desktop`: Change directory to my desktop!

**2. Using Terminal...**

**Folder Drop:** Try typing "cd" followed by a space, and then drag a folder into terminal and press return. Test this out and describe your results below.

When I type `cd` and a space and then drag a folder onto the Terminal window, it automatically fills in the full path to that folder for me. Once I press return it drops me straight into that directory. It's a nice shortcut so I don't have to type out a long path by hand or worry about spelling a folder name wrong.

## Topic: Version Control & Git

Version control, also known as revision control, records changes to a file or set of files over time so that you can recall specific versions later. In this class, we are learning Git. Update the information below where indicated.

**1. There are three types of version control.**

Local version control keeps all the tracked versions on your own computer only. It usually works by saving snapshots of your files in a simple database on your local disk. It's easy to set up but it only helps one person and everything is lost if that machine fails.

Centralized version control uses a single central server that holds all the versioned files, and everyone checks files out from and commits back to that one server. Tools like Subversion and CVS work this way. It makes team collaboration possible, but the central server is a single point of failure, so if it goes down nobody can save new versions.

Distributed version control gives every user a full copy of the entire repository, including its complete history, not just the latest files. Git works this way. Because everyone has the whole history, you can work offline, there is no single point of failure, and if the server dies any full copy can restore it.

**2. Using Terminal, there are also essential Git commands to know.**

List the correct Git commands to do the actions listed below in Terminal. Replace CMD with the correct command and keep or enhance the brief description.

- `git clone <repo-url>`: Clone a repository
- `git config --global user.name "Your Name"`: Set-up a global user name
- `git config --global user.email "you@example.com"`: Set-up a global email address (to match my GitHub account email)
- `git status`: Shows the current state of your directory and staging area
- `git add <filename>`: Add modified files to the next commit
- `git commit -m "message"`: Make a commit with a new message
- `git log`: Show my commit history
- `git help`: Show Git's help screen

**3. Connecting to GitHub using Terminal.**
HTTPS is the the correct way to connect to GitHub in this course. Describe how you connect to GitHub from Terminal using this protocol. What steps do you take?

First I create the repository on GitHub and copy its HTTPS web address, which ends in .git. In Terminal I set my identity once with `git config --global user.name` and `git config --global user.email`, using the same email that is on my GitHub account. Then I run `git clone` followed by that HTTPS address to pull the repo down to my computer. From there I work normally with add, commit, and push. The first time I push, GitHub asks me to authenticate, and with HTTPS I sign in using my GitHub username and a Personal Access Token in place of a password, since GitHub no longer accepts account passwords over HTTPS.

**4. Using .gitignore and Why it's Important**  
Most repositories contain a .gitignore file.

- What is the purpose of this file?
  <br>
  The .gitignore file tells Git which files and folders it should not track or commit. It's how I keep junk out of the repository, like build output, temporary files, editor settings, and anything with private information, so the repo only holds the source files that actually matter.

- What is the "**.DS_Store**" file and why would you want to ignore it?
  <br>
  A .DS_Store file is a hidden file that macOS Finder drops into a folder to remember view settings like icon positions and window size. It has nothing to do with the project itself, so committing it just clutters the repo and causes pointless changes, which is why you ignore it.

- What other file or folder would you want to add to a .gitignore file and why?
  <br>
  For my C++ work in Visual Studio I ignore the build and IDE folders like `.vs/`, `x64/`, `Debug/`, and `Release/`. Those hold compiled output and machine specific settings that get regenerated every build, so they don't belong in source control and would only bloat the repo and cause merge headaches.

<br>

# Reference Links

The resource that helped me most this week was the Pro Git book's section on version control, because it laid out the local, centralized, and distributed types in plain language and made it clear why Git being distributed is such a big deal. The official GitHub docs were also great for the HTTPS and Personal Access Token side of connecting from Terminal.

**Terminal Commands**  
[The Linux command line for beginners](https://ubuntu.com/tutorials/command-line-for-beginners)

**Three Types of Version Control**  
[Pro Git: About Version Control](https://git-scm.com/book/en/v2/Getting-Started-About-Version-Control)

**Git Commands**  
[Git Reference Documentation](https://git-scm.com/docs)

**Connecting to GitHub using Terminal**  
[GitHub Docs: Cloning a repository](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository)

**Using .gitignore and Why it's Important**  
[Git Documentation: gitignore](https://git-scm.com/docs/gitignore)
