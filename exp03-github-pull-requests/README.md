# Experiment 3 — Collaborating on Projects using GitHub and Pull Requests

**Aim:** To understand working on a shared project hosted on GitHub — clone/fork, work on a
new branch, push it, and create a Pull Request (PR) that is reviewed and merged.

**Problem statement:** Create a simple starter project and host it on GitHub to fork and work on.

**Ready-made code:** `starter-project/` (HTML/CSS/JS calculator) and `feature-code/CHANGES.md`
(the change you make on the feature branch).

---

## Theory (viva)

- **Clone** = copy a repo to your PC. **Fork** = copy someone's repo into *your* GitHub account.
- **Branch** = separate line of development; `main` stays stable while you work on `feature/...`.
- **Pull Request (PR)** = request to merge your branch into another branch; teammates
  **review**, comment, approve, then **merge**.
- Flow: clone/fork → branch → change → add/commit → push branch → PR → review → merge → pull.

---

## Part A — Create and host the starter project (Problem statement)

### Step 1 — Copy the starter project out of this repo
```bash
cp -r exp03-github-pull-requests/starter-project ~/Desktop/team-starter-project
cd ~/Desktop/team-starter-project
```

### Step 2 — Create an empty repo on GitHub
github.com → **+** → **New repository** → name `team-starter-project` → Public →
**don't tick README** → Create.

### Step 3 — Push the starter project
```bash
git init
git add .
git commit -m "Initial commit: starter calculator project"
git branch -M main
git remote add origin https://github.com/atharvvs718/team-starter-project.git
git push -u origin main
```
The project is now hosted on GitHub and ready to be forked/cloned.

---

## Part B — Collaborate with a branch and Pull Request (Steps 1–7 of handout)

> Solo in the lab? Do this on your own repo — PR from `feature/...` into `main` works the same.
> With a teammate: they **Fork** your repo (Fork button, top right), clone *their* fork, and do the steps below.

### Step 1 — Clone the repository
(Already have it from Part A? Skip. Otherwise:)
```bash
git clone https://github.com/atharvvs718/team-starter-project.git
cd team-starter-project
```

### Step 2 — Create and switch to a new branch
```bash
git checkout -b feature/multiply-divide
git branch
```
`*` shows you're on `feature/multiply-divide`.

### Step 3 — Make code changes
```bash
code .        # opens VS Code (or: notepad index.html / notepad script.js)
```
Make the changes from `feature-code/CHANGES.md` — add Multiply and Divide buttons in
`index.html` and the two lines in `script.js`. Save. Open `index.html` in a browser to check.

### Step 4 — Add, commit and push the branch
```bash
git status
git add .
git commit -m "Add multiply and divide operations"
git push origin feature/multiply-divide
```

### Step 5 — Create the Pull Request on GitHub
1. Open the repo on GitHub → yellow banner **"feature/multiply-divide had recent pushes"** → **Compare & pull request**
   (or: **Pull requests** tab → **New pull request** → base: `main` ← compare: `feature/multiply-divide`)
2. Title: `Add multiply and divide operations`
3. Description: `Adds two new buttons and logic for * and /. Handles divide by zero.`
4. **Create pull request**

### Step 6 — Code review and merge
1. Open the PR → **Files changed** tab → hover a line → **+** → write a comment (e.g. "Looks good")
2. **Review changes** → *Comment* / *Approve* → Submit
   (GitHub doesn't let you *approve* your own PR — just comment; a teammate can approve.)
3. **Conversation** tab → **Merge pull request** → **Confirm merge**
4. Optional: **Delete branch**

### Step 7 — Pull the latest changes to your PC
```bash
git checkout main
git pull origin main
git log --oneline --graph
```
`main` now contains the multiply/divide feature.

---

## Common errors

| Error | Fix |
|---|---|
| No "Compare & pull request" banner | Pull requests tab → New pull request → choose branches manually |
| `error: pathspec 'main' did not match` | Your default branch is `master` → use `master` |
| Merge conflict in PR | Pull main into your branch: `git checkout feature/... && git pull origin main`, fix the file, commit, push |
| Permission denied when teammate pushes | They must fork, or you add them: Settings → Collaborators |

## Conclusion
We hosted a starter project on GitHub, created a feature branch, pushed changes and raised a
Pull Request which was reviewed and merged into `main`, then pulled the merged code locally —
demonstrating collaborative development using GitHub.
