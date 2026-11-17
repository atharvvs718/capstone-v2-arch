# Experiment 3 — Collaborating on Projects using GitHub and Pull Requests

**Aim:** To understand working on a shared GitHub project — clone/fork, make changes in a new branch,
push the branch, and create a Pull Request (PR) for review and merge.

**Problem statement:** Create a simple starter project and host it on GitHub to fork and work on.



## Expected outcome
By the end of this experiment you will have:
- A GitHub repo **team-starter-project** with a working calculator web page (Add, Subtract).
- A branch **feature/multiply-divide** with a commit that adds Multiply and Divide.
- One **Pull Request** on GitHub, commented and **merged** into `main`.
- After `git pull`, the local `main` has all 4 operations; `git log --oneline --graph` shows the branch merge.

**You need:** Git + a GitHub account. Time: ~25 min (+5 min to install Git).

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
- **Clone** = copy a repo to your PC. **Fork** = copy someone's repo into *your* GitHub account.
- **Branch** = separate line of work; `main` stays safe while you work on `feature/...`.
- **Pull Request** = request to merge your branch into `main`; teammates review, comment, approve, merge.
- Flow: fork/clone → branch → change → add/commit → push branch → PR → review → merge → pull.

---

## PART A — Create the starter project and host it on GitHub

### Step 1 — Create the folder
```
cd /d %USERPROFILE%
mkdir team-starter-project
cd team-starter-project
```

### Step 2 — Create the 4 files

`notepad index.html` → Yes → paste → Ctrl+S → close:
```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Team Starter Project</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
  <h1>Team Starter Project</h1>
  <p>A simple calculator used to practise GitHub forks, branches and pull requests.</p>

  <div class="calc">
    <input type="number" id="a" placeholder="First number">
    <input type="number" id="b" placeholder="Second number">
    <button onclick="calculate('+')">Add</button>
    <button onclick="calculate('-')">Subtract</button>
    <p id="result">Result: </p>
  </div>

  <script src="script.js"></script>
</body>
</html>
```

`notepad style.css`:
```css
body {
  font-family: Arial, sans-serif;
  max-width: 600px;
  margin: 40px auto;
  text-align: center;
}
.calc input, .calc button {
  padding: 8px;
  margin: 4px;
}
#result {
  font-weight: bold;
}
```

`notepad script.js`:
```javascript
function calculate(op) {
  const a = parseFloat(document.getElementById('a').value);
  const b = parseFloat(document.getElementById('b').value);
  if (isNaN(a) || isNaN(b)) {
    document.getElementById('result').innerText = 'Result: enter both numbers';
    return;
  }
  let result;
  if (op === '+') result = a + b;
  if (op === '-') result = a - b;
  document.getElementById('result').innerText = 'Result: ' + result;
}
```

`notepad README.md`:
```markdown
# Team Starter Project

A simple HTML/CSS/JS calculator used to practise collaboration on GitHub
(fork, branch, commit, push, pull request, review, merge).

## Run
Open index.html in any browser.

## Contributing
1. Fork or clone this repo
2. Create a branch: git checkout -b feature/your-feature
3. Commit and push your branch
4. Open a Pull Request into main
```

Check it works: `start index.html` → opens in browser → try Add/Subtract.

### Step 3 — Create an empty repo on GitHub
github.com → **+** → **New repository** → name `team-starter-project` → Public →
**don't tick README** → **Create repository**.

### Step 4 — Push the starter project
```
git init
git add .
git commit -m "Initial commit: starter calculator project"
git branch -M main
git remote add origin https://github.com/atharvvs718/team-starter-project.git
git push -u origin main
```
Refresh GitHub → project is hosted ✅ (others can now **Fork** it with the Fork button.)

---

## PART B — Work on a branch and create a Pull Request

> Working alone? Do it in your own repo — a PR from a branch into `main` works the same.
> With a teammate: they click **Fork** on your repo, then `git clone` *their* fork and do the same steps.

### Step 5 — Create and switch to a new branch
```
git checkout -b feature/multiply-divide
git branch
```
The `*` shows you're on `feature/multiply-divide`.

### Step 6 — Make code changes

`notepad index.html` → **Ctrl+A** (select all) → paste this → save:
```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>Team Starter Project</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
  <h1>Team Starter Project</h1>
  <p>A simple calculator used to practise GitHub forks, branches and pull requests.</p>

  <div class="calc">
    <input type="number" id="a" placeholder="First number">
    <input type="number" id="b" placeholder="Second number">
    <button onclick="calculate('+')">Add</button>
    <button onclick="calculate('-')">Subtract</button>
    <button onclick="calculate('*')">Multiply</button>
    <button onclick="calculate('/')">Divide</button>
    <p id="result">Result: </p>
  </div>

  <script src="script.js"></script>
</body>
</html>
```

`notepad script.js` → **Ctrl+A** → paste → save:
```javascript
function calculate(op) {
  const a = parseFloat(document.getElementById('a').value);
  const b = parseFloat(document.getElementById('b').value);
  if (isNaN(a) || isNaN(b)) {
    document.getElementById('result').innerText = 'Result: enter both numbers';
    return;
  }
  let result;
  if (op === '+') result = a + b;
  if (op === '-') result = a - b;
  if (op === '*') result = a * b;
  if (op === '/') result = b !== 0 ? a / b : 'cannot divide by zero';
  document.getElementById('result').innerText = 'Result: ' + result;
}
```
Check: `start index.html` → Multiply and Divide buttons work.

### Step 7 — Add, commit and push the branch
```
git status
git add .
git commit -m "Add multiply and divide operations"
git push origin feature/multiply-divide
```

### Step 8 — Create the Pull Request on GitHub
1. Open `github.com/atharvvs718/team-starter-project`
2. Yellow banner → **Compare & pull request**
   (no banner? **Pull requests** tab → **New pull request** → base: `main` ← compare: `feature/multiply-divide`)
3. Title: `Add multiply and divide operations`
4. Description: `Adds Multiply and Divide buttons with their logic. Handles divide by zero.`
5. **Create pull request**

### Step 9 — Review and merge
1. In the PR → **Files changed** tab → hover a line → click **+** → write `Looks good` → **Add single comment**
2. Go to **Conversation** tab → **Merge pull request** → **Confirm merge**
3. (Optional) **Delete branch**

(GitHub doesn't let you *approve* your own PR — a teammate can click Review changes → Approve.)

### Step 10 — Pull the merged code to your PC
```
git checkout main
git pull origin main
git log --oneline --graph
```
`main` now has the multiply/divide feature ✅

---

## If something goes wrong

| Error | Fix |
|---|---|
| No "Compare & pull request" banner | Pull requests tab → New pull request → pick branches |
| `There isn't anything to compare` | You didn't commit/push on the branch — redo Step 7 |
| `src refspec feature/multiply-divide does not match` | Branch name typo — check `git branch` |
| `Authentication failed` | `cmdkey /delete:git:https://github.com` → push again → token as password |
| Teammate can't push to your repo | They must Fork, or add them: repo Settings → Collaborators |

## Conclusion
We hosted a starter project on GitHub, created a feature branch, pushed changes and raised a Pull Request
that was reviewed and merged into `main`, then pulled the merged code — demonstrating collaboration on GitHub.

## Viva questions
- **Fork vs clone?** Fork copies a repo to your GitHub account; clone copies a repo to your computer.
- **What is a Pull Request?** A request to merge changes from one branch into another, with code review.
- **Why use branches?** To work on features without breaking the stable `main` branch.
- **What is a merge conflict?** When two branches change the same lines — fixed manually, then committed.
- **`git checkout -b name`?** Creates a new branch and switches to it.
- **Merge vs rebase?** Merge joins histories with a merge commit; rebase replays commits for a straight history.
