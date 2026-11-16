# Experiment 5 — Automating Builds and Jobs using Jenkins

**Aim:** To automate software builds and jobs using Jenkins — create a Freestyle job that pulls a
Java program from GitHub, compiles and runs it, and rebuilds automatically when code changes.

**Ready-made code:** `jenkins-demo/` → `HelloWorld.java`, `Jenkinsfile` (pipeline version), `.gitignore`

**Needs:** Java 17/21, Git, Jenkins → see [../00-setup/SETUP.md](../00-setup/SETUP.md)

---

## Theory (viva)

- **Jenkins** = open-source automation server for CI/CD (build, test, deploy automatically).
- **Architecture:** **Controller/Master** (schedules jobs, web UI) + **Agents/Nodes** (execute jobs) + **Plugins** (Git, Maven, Docker…).
- **Job types:** **Freestyle** (simple, configured in UI), **Pipeline** (written as code in a `Jenkinsfile`), **Multi-configuration**.
- **Build triggers:** *Build periodically* (cron, runs always), *Poll SCM* (checks Git; builds only if there are new commits), *GitHub webhook* (GitHub notifies Jenkins — needs a public URL, so not usable on a lab PC's localhost).
- **Cron `H/5 * * * *`** = every 5 minutes (`H` = hash, spreads load). Fields: minute hour day month weekday.

---

## Step 1 — Push the Java program to a GitHub repo
```bash
cp -r exp05-jenkins-build/jenkins-demo ~/Desktop/jenkins-demo
cd ~/Desktop/jenkins-demo
git init
git add .
git commit -m "Add HelloWorld Java program"
git branch -M main
```
GitHub → New repository `jenkins-demo` (Public, no README) →
```bash
git remote add origin https://github.com/atharvvs718/jenkins-demo.git
git push -u origin main
```
Keep the repo **Public** → Jenkins needs no credentials.

## Step 2 — Start Jenkins
If Jenkins is already installed as a service → just open http://localhost:8080.
Otherwise (no admin needed):
```
java -jar jenkins.war --httpPort=8080
```
First time: copy the admin password from the console → http://localhost:8080 → paste →
**Install suggested plugins** → create admin user → Save and Finish.

## Step 3 — Create a Freestyle project
**Dashboard → New Item** → name `HelloWorld-Build` → **Freestyle project** → OK

## Step 4 — Source Code Management
- Select **Git**
- Repository URL: `https://github.com/atharvvs718/jenkins-demo.git`
- Credentials: *none* (public repo)
- Branch Specifier: **`*/main`**  ← change from `*/master`, otherwise the build fails

## Step 5 — Build Triggers
Tick **Poll SCM** → Schedule:
```
H/2 * * * *
```
(Handout uses `H/5` — 2 minutes is quicker to demonstrate. Ignore the yellow "spread load" warning.)

## Step 6 — Build Steps
**Add build step → Execute Windows batch command:**
```
javac HelloWorld.java
java HelloWorld
```
(If Jenkins runs on Linux/Docker: use **Execute shell** with the same two lines.)

**Save.**

## Step 7 — Build manually and check output
- **Build Now** (left menu) → a build `#1` appears under *Build History*
- Click `#1` → **Console Output** → you should see:
  ```
  Hello, World from Jenkins!
  Build automated successfully.
  Sum of 10 and 20 = 30
  Finished: SUCCESS
  ```

## Step 8 — Change code on GitHub → automatic rebuild
1. GitHub → `HelloWorld.java` → pencil icon (Edit) → change the message, e.g.
   `System.out.println("Hello, World from Jenkins - updated!");` → **Commit changes**
2. Wait ≤ 2 minutes, **don't click Build Now** → build `#2` starts by itself.
3. Left menu **Git Polling Log** shows *"Changes found"*. Console output shows the new message.
→ Trigger works automatically ✅

## Step 9 — Pipeline version (handout step 8)
**New Item** → `HelloWorld-Pipeline` → **Pipeline** → OK → scroll to *Pipeline*:
- **Option A:** Definition **Pipeline script** → paste the contents of `jenkins-demo/Jenkinsfile`
- **Option B:** Definition **Pipeline script from SCM** → SCM **Git** → URL of your repo →
  Branch `*/main` → Script Path `Jenkinsfile`

Save → **Build Now** → see the *Checkout → Build → Run* stages (Stage View / console).

---

## Common errors

| Error | Fix |
|---|---|
| `Couldn't find any revision to build` | Branch Specifier is `*/master` → change to `*/main` |
| `'javac' is not recognized` | JDK not on PATH for Jenkins — start Jenkins from a cmd where `javac -version` works, or Manage Jenkins → Tools → add JDK |
| `Cannot run program "git"` | Install Git, or Manage Jenkins → Tools → Git → path `C:\Program Files\Git\bin\git.exe` |
| `bat` fails on Linux Jenkins | Replace `bat` with `sh` in Jenkinsfile / use *Execute shell* |
| Port 8080 busy | `java -jar jenkins.war --httpPort=9090` |
| Forgot admin password | `C:\Users\<you>\.jenkins\secrets\initialAdminPassword` |

## Conclusion
We installed Jenkins, created a Freestyle job connected to GitHub that compiles and runs a Java
program, configured Poll SCM to trigger builds automatically on code changes, and also created the
same job as a Pipeline — showing how Jenkins automates builds in a CI workflow.
