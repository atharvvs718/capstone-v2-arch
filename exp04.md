# Experiment 4 — Implementing GitFlow Workflow in a Team-Based Scenario

**Aim:** To simulate a team environment and implement the GitFlow branching model
(`main`, `develop`, `feature/*`, `release/*`, `hotfix/*`) to manage code contributions.



## Expected outcome
By the end of this experiment you will have:
- A GitHub repo **gitflow-demo** with branches **main, develop, feature/contact, release/v1.0, hotfix/bug-4**.
- **5 merged Pull Requests** (feature→develop, release→main, release→develop, hotfix→main, hotfix→develop).
- A published GitHub **Release v1.0** on `main`.
- Final `main` has the contact page, says *Version 1.0*, and the spelling bug "Wellcome" is fixed to "Welcome".
- `git log --oneline --graph --all` and GitHub *Insights → Network* show the GitFlow branch graph.

**You need:** Git + a GitHub account. Time: ~35 min (+5 min to install Git).

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

| Branch | Purpose | Created from | Merged into |
|---|---|---|---|
| `main` | Production-ready code, tagged releases | — | — |
| `develop` | Integration of finished features | `main` | `release/*` |
| `feature/*` | One new feature | `develop` | `develop` |
| `release/*` | Prepare a release (version number, final fixes) | `develop` | `main` and `develop` |
| `hotfix/*` | Urgent fix for a production bug | `main` | `main` and `develop` |

```
main     ●──────────────────────●────────────●  (v1.0)
          \                    /            / \
release    \          ●───────●            /   \
            \        /         \          /     \
develop      ●──●───●───────────●────────/───────●
                 \ /                    /
feature           ●  feature/contact   /
hotfix                         ●──────●  hotfix/bug-4
```

**Reading a PR on GitHub:** `base ← compare` means "merge **compare** INTO **base**".

**Story for this experiment:** our website has a spelling bug ("Wellcome"). We add a Contact page
(feature), release version 1.0 (release), then fix the spelling bug urgently (hotfix).

---

## Step 1 — Create the project on `main`
```
cd /d %USERPROFILE%
mkdir gitflow-demo
cd gitflow-demo
```
`notepad index.html` → Yes → paste → save (the spelling mistake is on purpose):
```html
<!DOCTYPE html>
<html>
<head>
  <title>GitFlow Demo</title>
</head>
<body>
  <h1>Wellcome to the GitFlow Demo Website</h1>
  <p>Version 0.1</p>
</body>
</html>
```
`notepad README.md` → paste → save:
```markdown
# GitFlow Demo

Demo website to practise the GitFlow branching model.

Branches: main, develop, feature/*, release/*, hotfix/*
```
Commit on main:
```
git init
git add .
git commit -m "Initial commit on main"
git branch -M main
```

## Step 2 — Push to GitHub
GitHub → **New repository** → `gitflow-demo` → Public → **don't tick README** → Create. Then:
```
git remote add origin https://github.com/atharvvs718/gitflow-demo.git
git push -u origin main
```

## Step 3 — Create the `develop` branch
```
git branch
git checkout -b develop
git branch
```
`notepad README.md` → **Ctrl+A** → paste → save:
```markdown
# GitFlow Demo

Demo website to practise the GitFlow branching model.

Branches: main, develop, feature/*, release/*, hotfix/*

Status: development started on develop branch.
```
```
git status
git add .
git commit -m "Set up develop branch"
git push origin develop
```

## Step 4 — Feature branch (from develop)
```
git checkout develop
git checkout -b feature/contact
```
`notepad contact.html` → Yes → paste → save:
```html
<!DOCTYPE html>
<html>
<head>
  <title>Contact Us</title>
</head>
<body>
  <h1>Contact Us</h1>
  <p>Email: team@gitflowdemo.com</p>
  <p><a href="index.html">Back to Home</a></p>
</body>
</html>
```
```
git add .
git commit -m "Add contact page feature"
git push origin feature/contact
```
**PR on GitHub:** **Pull requests** → **New pull request** →
base: **`develop`** ← compare: **`feature/contact`** → **Create pull request** → Create →
**Merge pull request** → **Confirm merge**.

## Step 5 — Release branch (from develop)
```
git checkout develop
git pull origin develop
git checkout -b release/v1.0
```
Update the version — `notepad index.html` → **Ctrl+A** → paste → save:
```html
<!DOCTYPE html>
<html>
<head>
  <title>GitFlow Demo</title>
</head>
<body>
  <h1>Wellcome to the GitFlow Demo Website</h1>
  <p>Version 1.0</p>
  <p><a href="contact.html">Contact Us</a></p>
</body>
</html>
```
```
git add .
git commit -m "Prepare release v1.0"
git push origin release/v1.0
```
**Two PRs on GitHub:**
1. base: **`main`** ← compare: **`release/v1.0`** → Create → **Merge** → Confirm
2. base: **`develop`** ← compare: **`release/v1.0`** → Create → **Merge** → Confirm

## Step 6 — Hotfix branch (from main)
The spelling bug "Wellcome" is now live on main → fix it urgently:
```
git checkout main
git pull origin main
git branch
git checkout -b hotfix/bug-4
```
`notepad index.html` → **Ctrl+A** → paste → save (spelling fixed):
```html
<!DOCTYPE html>
<html>
<head>
  <title>GitFlow Demo</title>
</head>
<body>
  <h1>Welcome to the GitFlow Demo Website</h1>
  <p>Version 1.0</p>
  <p><a href="contact.html">Contact Us</a></p>
</body>
</html>
```
```
git add .
git commit -m "Hotfix bug-4: fix spelling of Welcome"
git push origin hotfix/bug-4
git branch
```
**Two PRs on GitHub:**
1. base: **`main`** ← compare: **`hotfix/bug-4`** → Create → **Merge** → Confirm
2. base: **`develop`** ← compare: **`hotfix/bug-4`** → Create → **Merge** → Confirm

## Step 7 — Publish release v1.0
GitHub repo page → right side **Releases** → **Create a new release**
- **Choose a tag** → type `v1.0` → click **Create new tag: v1.0 on publish**
- **Target:** `main`
- **Release title:** `v1.0`
- Description: `First stable release: home page, contact page, and hotfix bug-4 (spelling).`
- **Publish release**

## Step 8 — Show the result
```
git checkout main
git pull origin main
git fetch --all
git branch -a
git log --oneline --graph --all
```
On GitHub, show: **Insights → Network** (branch graph), **Pull requests → Closed** (5 merged PRs), **Releases** (v1.0).

---

## If something goes wrong

| Error | Fix |
|---|---|
| `There isn't anything to compare` | Branches are the same → make a commit and push on the compare branch |
| PR shows merge conflict | Click **Resolve conflicts** → keep the correct lines, delete `<<<<` `====` `>>>>` lines → **Mark as resolved** → **Commit merge** |
| `a branch named 'develop' already exists` | `git checkout develop` (without `-b`) |
| `Your branch is behind` | `git pull origin <branch-name>` |
| `Authentication failed` | `cmdkey /delete:git:https://github.com` → push again → token as password |

## Conclusion
We implemented GitFlow: `develop` for integration, a `feature/contact` branch merged into develop through a PR,
`release/v1.0` merged into main and develop, `hotfix/bug-4` from main merged into main and develop,
and published release v1.0 — giving stable releases and organised team collaboration.

## Viva questions
- **What is GitFlow?** A branching model with main, develop, feature, release and hotfix branches for organised team development.
- **Why is hotfix created from main and not develop?** The bug is in production (main); develop may contain unfinished work.
- **Why merge release/hotfix into both main and develop?** So the fix/release changes are not lost in future development.
- **What is a tag?** A named pointer to a specific commit, used to mark versions like v1.0.
- **Where do feature branches start and end?** Start from develop, merge back into develop.
- **GitFlow vs trunk-based?** GitFlow uses long-lived branches; trunk-based commits small changes directly to main frequently.
