# Experiment 2 — Getting Started with Git and Version Control

**Aim:** To perform basic Git operations (init, stage, commit, history) and push a local repository to GitHub.

**Problem statement:** Create a repo named `C-Programs-Library` with at least 5 C programs + README,
commit with meaningful messages, push to GitHub, then add one more program later and push the update.

**Ready-made code:** `C-Programs-Library/` (5 programs + README + .gitignore) and `add-later/binary_search.c` (the 6th program).

---

## Theory (say this in viva)

- **Git** = distributed version control system — tracks changes to code over time.
- **Repository** = project folder tracked by Git (has a hidden `.git` folder).
- **Working directory** → `git add` → **Staging area** → `git commit` → **Local repo** → `git push` → **Remote (GitHub)**
- **Commit** = snapshot of the project at a point in time, with a message.
- **Remote** = copy of the repo on a server (GitHub). `origin` = default name for it.

---

## Steps

### Step 1 — Check Git and configure it
```bash
git --version
git config --global user.name "atharvvs718"
git config --global user.email "<your GitHub email>"
git config --list
```

### Step 2 — Create the project folder (copy the ready programs out of this repo)
In Git Bash, from inside the cloned `capstone-v2-arch` folder:
```bash
cp -r exp02-git-basics/C-Programs-Library ~/Desktop/
cd ~/Desktop/C-Programs-Library
ls
```
(Or in File Explorer: copy the `C-Programs-Library` folder to the Desktop, then right-click inside it → *Open Git Bash here*.)

> If the examiner wants to see you **create** it: `mkdir C-Programs-Library && cd C-Programs-Library`,
> then create each `.c` file with `notepad bubble_sort.c` and paste the code.

Open `README.md` and fill in your **roll number**.

### Step 3 — Initialize the repository
```bash
git init
git status
```
`git status` shows all files in red = **untracked**.

### Step 4 — Stage and commit in small, meaningful commits
```bash
git add README.md .gitignore
git commit -m "Add README with program list and run instructions"

git add bubble_sort.c linear_search.c
git commit -m "Add Bubble Sort and Linear Search programs"

git add factorial_recursion.c
git commit -m "Add recursive factorial program"

git add file_io.c matrix_multiplication.c
git commit -m "Add File I/O and Matrix Multiplication programs"

git status
git log --oneline
```
`git status` should say *nothing to commit, working tree clean*. `git log --oneline` shows 4 commits.

### Step 5 — (Optional) Compile and run a program to show it works
```bash
gcc bubble_sort.c -o bubble_sort
./bubble_sort
```
(If gcc is not installed on the lab PC, skip — it isn't the point of the experiment. `.exe` files are ignored by `.gitignore`.)

### Step 6 — Create the repo on GitHub
1. github.com → **+** (top right) → **New repository**
2. Name: `C-Programs-Library`, **Public**
3. **Do NOT tick** "Add a README", ".gitignore" or "license"
4. **Create repository** → copy the HTTPS URL

### Step 7 — Link local repo to GitHub and push
```bash
git remote add origin https://github.com/atharvvs718/C-Programs-Library.git
git remote -v
git branch -M main
git push -u origin main
```
Login popup → *Sign in with your browser* (or paste the Personal Access Token if it asks for a password).
Refresh GitHub → all files and commits are visible.

### Step 8 — Add one more program later and push the update
```bash
cp ../capstone-v2-arch/exp02-git-basics/add-later/binary_search.c .
```
(adjust the path to wherever you cloned the repo — or create it with `notepad binary_search.c` and paste)

Add a line to the README table: `| binary_search.c | Searches a sorted array using Binary Search |`
```bash
git status
git diff README.md
git add .
git commit -m "Add Binary Search program and update README"
git push
```
Refresh GitHub → new file + 5 commits in history.

### Step 9 — Show history (good for screenshots)
```bash
git log --oneline
git log --stat -1
```

---

## Common errors

| Error | Fix |
|---|---|
| `fatal: not a git repository` | You're in the wrong folder → `cd` into `C-Programs-Library` |
| `remote origin already exists` | `git remote set-url origin <correct-url>` |
| `src refspec main does not match any` | Run `git branch -M main` (and make sure you have at least 1 commit) |
| `rejected ... fetch first` | You ticked README on GitHub → `git pull origin main --allow-unrelated-histories --no-edit` then `git push` |
| `Author identity unknown` | Run the two `git config --global` lines |

## Conclusion
We created a local Git repository, tracked and committed C programs with meaningful messages,
linked it to a remote GitHub repository, pushed it, and pushed a later update — demonstrating
basic version control and remote collaboration with Git and GitHub.
