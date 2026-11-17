# Experiment 2 — Getting Started with Git and Version Control

**Aim:** To perform basic Git operations (init, add, commit, log) and push a local repository to GitHub.

**Problem statement:** Create a repository `C-Programs-Library` with at least 5 C programs and a README,
commit with meaningful messages, push it to GitHub, then add one more program and push the update.



## Expected outcome
By the end of this experiment you will have:
- A GitHub repo **github.com/atharvvs718/C-Programs-Library** containing 6 C programs + README.md.
- `git log --oneline` shows **5 commits** with meaningful messages.
- The 6th program (binary_search.c) appears as a later commit — showing an update pushed to GitHub.

**You need:** Git + a GitHub account. Time: ~20 min (+5 min to install Git).

---

## Step 0 — Install everything (on a PC that has nothing)
Open **Command Prompt**: press `Win + R` → type `cmd` → Enter.
Do each part below. If the *Check* command already works, skip that part.

### 0.0 — GitHub account
You need to be logged in at **github.com** in the browser (account `atharvvs718`).

### 0.A — Git
Check in cmd: `git --version` → if it prints a version, skip to the next part.

1. Browser → **https://git-scm.com/downloads/win** → click **Click here to download** (64-bit Git for Windows Setup).
2. Open the downloaded file → Windows asks *"Allow this app to make changes?"* → **Yes**.
3. Click **Next** on every screen, but change these two:
   - **Choosing the default editor** → select **Use Notepad as Git's default editor**
   - **Adjusting the name of the initial branch** → select **Override the default branch name** → type `main`
4. **Install** → untick *View Release Notes* → **Finish**.
5. **Close cmd and open a new cmd window** (otherwise it won't find git).

**If step 2 asks for an admin password you don't have** → use Portable Git instead:
1. Same page → click **64-bit Git for Windows Portable** → run it → in the box type `C:\Users\YOUR-USERNAME\PortableGit` → **OK**.
2. In every new cmd window run this once (it makes `git` work in cmd):
```
set PATH=%USERPROFILE%\PortableGit\cmd;%PATH%
```

Then set your name and email (once per PC):
```
git --version
git config --global user.name "atharvvs718"
git config --global user.email "your-github-email@example.com"
git config --global init.defaultBranch main
```
(Your email: GitHub → avatar → Settings → Emails.)

**GitHub login on first push:** a window opens → **Sign in with your browser** → **Authorize**.
If cmd instead asks *Username* → type `atharvvs718`; *Password* → paste a **Personal Access Token**, not your
GitHub password (GitHub → Settings → Developer settings → Personal access tokens → Tokens (classic) →
Generate new token (classic) → tick **repo** → Generate → copy `ghp_...`). Nothing shows while pasting — normal.

---

## Theory (short)
- **Git** = distributed version control system; tracks every change to your code.
- **Repository** = folder tracked by Git (has a hidden `.git` folder).
- **Working directory → `git add` → Staging area → `git commit` → Local repo → `git push` → GitHub (remote)**
- **Commit** = saved snapshot with a message. **origin** = name of the GitHub remote.

---

## Step 1 — Check and configure Git
```
git --version
git config --global user.name "atharvvs718"
git config --global user.email "your-github-email@example.com"
git config --list
```

## Step 2 — Create the project folder
```
cd /d %USERPROFILE%
mkdir C-Programs-Library
cd C-Programs-Library
```

## Step 3 — Initialize the repository
```
git init
git status
```

## Step 4 — Create the 5 C programs

**Program 1** — run `notepad bubble_sort.c` → Yes → paste → Ctrl+S → close:
```c
/* Bubble Sort - sorts an array in ascending order */
#include <stdio.h>

int main(void) {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i, j, temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    printf("Sorted array: ");
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
    return 0;
}
```

**Program 2** — `notepad linear_search.c`:
```c
/* Linear Search - finds the position of a key in an array */
#include <stdio.h>

int main(void) {
    int arr[] = {10, 23, 45, 70, 11, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 70, i, found = -1;

    for (i = 0; i < n; i++) {
        if (arr[i] == key) {
            found = i;
            break;
        }
    }

    if (found != -1)
        printf("Element %d found at index %d\n", key, found);
    else
        printf("Element %d not found\n", key);
    return 0;
}
```

**Program 3** — `notepad factorial_recursion.c`:
```c
/* Factorial using recursion */
#include <stdio.h>

long long factorial(int n) {
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}

int main(void) {
    int n = 5;
    printf("Factorial of %d = %lld\n", n, factorial(n));
    return 0;
}
```

**Program 4** — `notepad file_io.c`:
```c
/* File I/O - writes text to a file and reads it back */
#include <stdio.h>

int main(void) {
    FILE *fp;
    char line[100];

    fp = fopen("sample.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for writing\n");
        return 1;
    }
    fprintf(fp, "Hello from File I/O in C!\n");
    fprintf(fp, "This line was written by the program.\n");
    fclose(fp);

    fp = fopen("sample.txt", "r");
    if (fp == NULL) {
        printf("Error opening file for reading\n");
        return 1;
    }
    printf("Contents of sample.txt:\n");
    while (fgets(line, sizeof(line), fp) != NULL)
        printf("%s", line);
    fclose(fp);
    return 0;
}
```

**Program 5** — `notepad matrix_multiplication.c`:
```c
/* Matrix Multiplication of two 2x2 matrices */
#include <stdio.h>

int main(void) {
    int a[2][2] = {{1, 2}, {3, 4}};
    int b[2][2] = {{5, 6}, {7, 8}};
    int c[2][2] = {{0, 0}, {0, 0}};
    int i, j, k;

    for (i = 0; i < 2; i++)
        for (j = 0; j < 2; j++)
            for (k = 0; k < 2; k++)
                c[i][j] += a[i][k] * b[k][j];

    printf("Result matrix:\n");
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++)
            printf("%d ", c[i][j]);
        printf("\n");
    }
    return 0;
}
```

## Step 5 — Create the README
`notepad README.md` → paste → **put your roll number** → save:
```markdown
# C-Programs-Library

A version-controlled library of frequently used C programs, managed with Git and GitHub.

**Name:** Atharv Vitthal Shivankar
**Roll No:** YOUR-ROLL-NUMBER

## Programs

| File | Description |
|---|---|
| bubble_sort.c | Sorts an array in ascending order using Bubble Sort |
| linear_search.c | Searches an element in an array one by one |
| factorial_recursion.c | Finds factorial of a number using recursion |
| file_io.c | Writes text to a file and reads it back |
| matrix_multiplication.c | Multiplies two 2x2 matrices |

## How to compile and run

gcc bubble_sort.c -o bubble_sort
bubble_sort.exe

Replace bubble_sort with any program name.
```

## Step 6 — Check status, then commit in meaningful steps
```
git status
```
All files show in red (untracked). Now commit:
```
git add README.md
git commit -m "Add README with program list and run instructions"

git add bubble_sort.c linear_search.c
git commit -m "Add Bubble Sort and Linear Search programs"

git add factorial_recursion.c
git commit -m "Add recursive factorial program"

git add file_io.c matrix_multiplication.c
git commit -m "Add File I/O and Matrix Multiplication programs"
```
Check:
```
git status
git log --oneline
```
`working tree clean` + 4 commits = correct.

## Step 7 — Create the repo on GitHub
github.com → **+** → **New repository** → name `C-Programs-Library` → Public →
**don't tick README** → **Create repository**.

## Step 8 — Link and push
```
git remote add origin https://github.com/atharvvs718/C-Programs-Library.git
git remote -v
git branch -M main
git push -u origin main
```
Log in when asked (browser popup, or username + token). Refresh GitHub → all files are there.

## Step 9 — Add one more program later and push the update
`notepad binary_search.c` → paste → save:
```c
/* Binary Search - searches a sorted array */
#include <stdio.h>

int main(void) {
    int arr[] = {2, 5, 8, 12, 16, 23, 38, 56, 72, 91};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key = 23, low = 0, high = n - 1, mid;

    while (low <= high) {
        mid = (low + high) / 2;
        if (arr[mid] == key) {
            printf("Element %d found at index %d\n", key, mid);
            return 0;
        } else if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    printf("Element %d not found\n", key);
    return 0;
}
```
`notepad README.md` → add this line at the end of the table (after matrix_multiplication) → save:
```
| binary_search.c | Searches a sorted array using Binary Search |
```
Then:
```
git status
git diff
git add binary_search.c README.md
git commit -m "Add Binary Search program and update README"
git push
git log --oneline
```
Refresh GitHub → new file + 5 commits ✅

## Step 10 (optional) — Compile and run a program
Only if `gcc --version` works on the lab PC:
```
gcc bubble_sort.c -o bubble_sort
bubble_sort.exe
```
(Don't `git add` the `.exe` files.)

---

## If something goes wrong

| Error | Fix |
|---|---|
| `'git' is not recognized` | Git not installed, or cmd opened before install → open a new cmd |
| `fatal: not a git repository` | You're in the wrong folder → `cd /d %USERPROFILE%\C-Programs-Library` |
| `Author identity unknown` | Run the two `git config --global` lines from Step 1 |
| `remote origin already exists` | `git remote set-url origin https://github.com/atharvvs718/C-Programs-Library.git` |
| `src refspec main does not match any` | Run `git branch -M main` (needs at least one commit) |
| `rejected ... fetch first` | You ticked README on GitHub → `git pull origin main --allow-unrelated-histories --no-edit` then `git push` |
| `Authentication failed` | `cmdkey /delete:git:https://github.com` → push again → use token as password |

## Conclusion
We created a local Git repository, committed C programs with meaningful messages, linked it to GitHub,
pushed it, and pushed a later update — demonstrating version control with Git and GitHub.

## Viva questions
- **Git vs GitHub?** Git is the version control tool on your PC; GitHub is a website that hosts Git repositories.
- **What does `git add` do?** Moves changes to the staging area. **`git commit`?** Saves a snapshot of staged changes.
- **What is `origin`?** The default name for the remote (GitHub) repository.
- **What does `-u` in `git push -u origin main` do?** Sets upstream, so next time just `git push` works.
- **`git pull` = ?** `git fetch` + `git merge`.
- **What is a distributed VCS?** Every developer has a full copy of the repository and its history.
- **How to see history?** `git log` / `git log --oneline`.
