# Experiment 4 — Implementing GitFlow Workflow in a Team-Based Scenario

**Aim:** To simulate a team environment and implement the GitFlow branching model
(`main`, `develop`, `feature/*`, `release/*`, `hotfix/*`) to manage code contributions.

**Code:** reuse `../exp03-github-pull-requests/starter-project` (or any small project).

---

## Theory (viva)

| Branch | Purpose | Created from | Merged into |
|---|---|---|---|
| `main` | Production-ready code, tagged releases | — | — |
| `develop` | Integration branch for the next release | `main` | `release/*` |
| `feature/*` | One new feature each | `develop` | `develop` |
| `release/*` | Prepare a release (version bump, final fixes) | `develop` | `main` **and** `develop` |
| `hotfix/*` | Urgent fix for a bug in production | `main` | `main` **and** `develop` |

```
main     ●─────────────────────●(v1.0)──────●(v1.0.1)
          \                   /             / \
release    \           ●─────●             /   \
            \         /       \           /     \
develop      ●───●───●─────────●─────────/───────●
                  \ /                   /
feature            ●  feature/login    /
hotfix                        ●───────●  hotfix/bug-4
```
Benefits: parallel development, stable `main`, clean releases, quick hotfixes.

**Reading a GitHub PR:** `base ← compare` means *merge compare INTO base*.
E.g. `base: develop ← compare: feature/login` merges the feature into develop.

---

## Steps

### Step 1 — Create the project and push `main` (handout steps 1, 5)
```bash
cp -r exp03-github-pull-requests/starter-project ~/Desktop/gitflow-demo
cd ~/Desktop/gitflow-demo
git init
git add .
git commit -m "Initial commit on main"
git branch -M main
```
GitHub → New repository `gitflow-demo` (no README) → then:
```bash
git remote add origin https://github.com/atharvvs718/gitflow-demo.git
git push -u origin main
```
(If the examiner gives you a repo: `git clone <url>` and `cd` into it instead.)

### Step 2 — Create the `develop` branch (handout steps 2–4, 6–9)
```bash
git branch                      # shows: * main
git checkout -b develop
git branch                      # shows: * develop
```
Make a small change (e.g. add a line to README.md: `Version: 0.1 (develop)`), then:
```bash
git status
git add .
git commit -m "Set up develop branch"
git push origin develop
```

### Step 3 — Feature branch from `develop` (handout step 10)
```bash
git checkout develop
git checkout -b feature/multiply
```
Make the change (add a Multiply button — see `../exp03-github-pull-requests/feature-code/CHANGES.md`):
```bash
git add .
git commit -m "Add multiply feature"
git push origin feature/multiply
```
**PR on GitHub:** Pull requests → New → `base: develop ← compare: feature/multiply` →
Create → **Merge pull request** → Confirm.

### Step 4 — Release branch (handout step 11)
Create `release/v1.0` from `develop`:
```bash
git checkout develop
git pull origin develop          # get the merged feature
git checkout -b release/v1.0
```
Bump the version (edit README.md: `Version: 1.0`):
```bash
git add .
git commit -m "Prepare release v1.0"
git push origin release/v1.0
```
(Handout way: GitHub → branch dropdown → type `release/v1.0` → *Create branch from develop*.)

**PRs:**
1. `base: main ← compare: release/v1.0` → Create → Merge   (release goes to production)
2. `base: develop ← compare: release/v1.0` → Create → Merge (keep develop in sync)

### Step 5 — Hotfix branch (handout steps 12–15)
A bug is found in production → branch from `main`:
```bash
git checkout main
git pull origin main
git branch
git checkout -b hotfix/bug-4
```
Fix something (e.g. in `script.js` change the empty-input message, or fix a typo in README):
```bash
git add .
git commit -m "Hotfix bug-4: fix empty input message"
git push origin hotfix/bug-4
git branch
```
**PRs:**
1. `base: main ← compare: hotfix/bug-4` → Create → Merge
2. `base: develop ← compare: hotfix/bug-4` → Create → Merge

### Step 6 — Publish the release (handout step 16)
GitHub repo page → right side **Releases** → **Create a new release**
- **Choose a tag** → type `v1.0` → *Create new tag*
- **Target:** `main`
- **Title:** `v1.0`
- Description: `First stable release: calculator with add, subtract, multiply. Includes hotfix bug-4.`
- **Publish release**

Or via command line:
```bash
git checkout main
git pull origin main
git tag -a v1.0 -m "Release v1.0"
git push origin v1.0
```

### Step 7 — Show the result (screenshots)
```bash
git fetch --all
git branch -a
git log --oneline --graph --all
```
On GitHub: **Insights → Network** shows the branch graph; **Pull requests → Closed** shows all merged PRs.

---

## Common errors

| Error | Fix |
|---|---|
| PR says "There isn't anything to compare" | The branches are identical — make a commit on the compare branch first |
| PR has merge conflicts | GitHub → *Resolve conflicts* → keep the right lines → *Mark as resolved* → Commit |
| `fatal: a branch named 'develop' already exists` | `git checkout develop` (without `-b`) |
| Local branch outdated after PR merge | `git checkout <branch> && git pull origin <branch>` |

## Conclusion
We implemented the GitFlow workflow: `develop` for integration, `feature/*` merged into develop
via PRs, `release/v1.0` merged into main and develop, a `hotfix/bug-4` from main merged back to
both, and published the `v1.0` release — ensuring stable releases and clean team collaboration.
