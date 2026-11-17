# Experiment 5 — Automating Builds and Jobs using Jenkins

**Aim:** To automate software builds using Jenkins — create a job that pulls a Java program from GitHub,
compiles and runs it, and rebuilds automatically when the code changes.



## Expected outcome
By the end of this experiment you will have:
- Jenkins running at **http://localhost:8080**.
- A Freestyle job **HelloWorld-Build** whose Console Output shows `Hello, World from Jenkins!` … `Finished: SUCCESS`.
- After editing the code on GitHub, build **#2 starts by itself** (Poll SCM) and prints the new message.
- A Pipeline job **HelloWorld-Pipeline** with 3 green stages: Checkout → Build → Run.

**You need:** Git, Java 21, Jenkins, GitHub account. Time: ~30 min (+15–20 min installs, mostly Jenkins plugins).

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

### 0.B — Java 21 (JDK)
Check in cmd: `java -version` and `javac -version` → if both show **21** or higher, skip. (**Java 17 is NOT enough** — current Jenkins needs Java 21 or 25. If you see 17 or lower, install 21 below.)

1. Browser → **https://adoptium.net/temurin/releases/** → Operating System **Windows**, Architecture **x64**,
   Package Type **JDK**, Version **21 - LTS** → download the **.msi**.
2. Open it → **Next** → on the *Custom Setup* screen click **Set JAVA_HOME variable** → choose
   **Will be installed on local hard drive** (Add to PATH is already on) → **Next** → **Install** → **Yes** → **Finish**.
3. **Close cmd and open a new one**, then check:
```
java -version
javac -version
```
Both should say `21`.

**No admin rights?** On the same page download the **.zip** instead → right-click → **Extract All** → extract to
`C:\Users\YOUR-USERNAME\` → it makes a folder like `jdk-21.0.x+y`. In every new cmd window run (use the real folder name):
```
set JAVA_HOME=%USERPROFILE%\jdk-21.0.5+11
set PATH=%JAVA_HOME%\bin;%PATH%
java -version
```

### 0.C — Jenkins (no install needed — runs from one file)
1. Browser → **https://www.jenkins.io/download/** → under **Stable (LTS)** click **Generic Java package (.war)** →
   `jenkins.war` is saved in **Downloads**.
2. In cmd (Java must work in this window):
```
cd /d %USERPROFILE%\Downloads
java -jar jenkins.war --httpPort=8080
```

**Important:** start Jenkins from a cmd window where `java -version` shows 21 **and** `git --version` works —
Jenkins uses this window's Java and Git. If you used the **Java ZIP** or **Portable Git**, run your
`set JAVA_HOME=...`, `set PATH=...` lines in this window first, then start Jenkins.

3. **Leave this cmd window open the whole time** — closing it stops Jenkins. Wait for the line
   `Jenkins is fully up and running` (1–2 minutes).
4. Scroll up in that window: copy the long **password** printed between the lines of `*****`.
5. Browser → **http://localhost:8080** → paste the password → **Continue** → **Install suggested plugins**
   (wait 3–5 min) → fill **Create First Admin User** (remember the username/password) → **Save and Continue** →
   **Save and Finish** → **Start using Jenkins**.

Next time you start Jenkins, just run step 2 again and log in with your admin user.
(If Windows Firewall pops up → **Allow**. Port 8080 busy → use `--httpPort=9090` and http://localhost:9090.)

---

## Theory (short)
- **Jenkins** = open-source automation server for **CI/CD** (build, test, deploy automatically). Runs on port **8080**.
- **Architecture:** **Controller (master)** — schedules jobs, web UI · **Agent (node)** — runs jobs · **Plugins** — Git, Maven, Docker…
- **Job types:** **Freestyle** (configured with forms) · **Pipeline** (written as code — Jenkinsfile) · Multi-configuration.
- **Build triggers:** **Poll SCM** (checks GitHub on a schedule, builds only if code changed) · **Build periodically** (always builds on schedule) · **GitHub webhook** (GitHub notifies Jenkins — needs a public URL).
- **Cron `H/5 * * * *`** = every 5 minutes. Fields: minute, hour, day-of-month, month, day-of-week.

---

## Step 1 — Start Jenkins
If you just finished Step 0.C, Jenkins is already running — go to Step 2.
Otherwise, in a cmd window (keep it open):
```
cd /d %USERPROFILE%\Downloads
java -jar jenkins.war --httpPort=8080
```
Browser → **http://localhost:8080** → log in with your admin user.

## Step 2 — Put the Java program on GitHub
Open a **new** cmd window (leave Jenkins running in the first one):
```
cd /d %USERPROFILE%
mkdir jenkins-demo
cd jenkins-demo
```
`notepad HelloWorld.java` → Yes → paste → save:
```java
public class HelloWorld {
    public static void main(String[] args) {
        System.out.println("Hello, World from Jenkins!");
        System.out.println("Build automated successfully.");
        int a = 10, b = 20;
        System.out.println("Sum of " + a + " and " + b + " = " + (a + b));
    }
}
```
Test it locally:
```
javac HelloWorld.java
java HelloWorld
del HelloWorld.class
```
GitHub → **New repository** → `jenkins-demo` → **Public** → don't tick README → Create. Then:
```
git init
git add HelloWorld.java
git commit -m "Add HelloWorld Java program"
git branch -M main
git remote add origin https://github.com/atharvvs718/jenkins-demo.git
git push -u origin main
```

## Step 3 — Create a Freestyle job
Jenkins → **+ New Item** → name `HelloWorld-Build` → select **Freestyle project** → **OK**.

**Source Code Management:**
- Select **Git**
- Repository URL: `https://github.com/atharvvs718/jenkins-demo.git`
- Credentials: **- none -** (public repo)
- Branch Specifier: change `*/master` to **`*/main`**  ← important

**Triggers (Build Triggers):**
- Tick **Poll SCM** → Schedule:
```
H/2 * * * *
```
(checks GitHub every ~2 minutes. Ignore the yellow warning.)

**Build Steps:**
- **Add build step** → **Execute Windows batch command** → paste:
```
javac HelloWorld.java
java HelloWorld
```
Click **Save**.

## Step 4 — Build manually
Click **Build Now** (left menu) → build **#1** appears under Build History → click **#1** → **Console Output**:
```
Hello, World from Jenkins!
Build automated successfully.
Sum of 10 and 20 = 30
Finished: SUCCESS
```

## Step 5 — Change code on GitHub → automatic build
1. GitHub → `jenkins-demo` → click `HelloWorld.java` → **pencil icon (Edit)**
2. Change the first message to: `Hello, World from Jenkins - code updated!`
3. **Commit changes** → **Commit changes**
4. Go back to Jenkins and **wait up to 2 minutes — don't click Build Now.**
5. Build **#2** starts automatically → Console Output shows the new message ✅
6. Left menu **Git Polling Log** shows *Changes found*.

## Step 6 — Same job as a Pipeline (Jenkinsfile)
Jenkins → **+ New Item** → name `HelloWorld-Pipeline` → **Pipeline** → **OK** →
scroll to **Pipeline** → Definition: **Pipeline script** → paste → **Save**:
```groovy
pipeline {
    agent any

    triggers {
        pollSCM('H/2 * * * *')
    }

    stages {
        stage('Checkout') {
            steps {
                git branch: 'main', url: 'https://github.com/atharvvs718/jenkins-demo.git'
            }
        }
        stage('Build') {
            steps {
                echo 'Compiling HelloWorld.java ...'
                bat 'javac HelloWorld.java'
            }
        }
        stage('Run') {
            steps {
                echo 'Running HelloWorld ...'
                bat 'java HelloWorld'
            }
        }
    }

    post {
        success { echo 'Build and run successful!' }
        failure { echo 'Build failed - check the console output.' }
    }
}
```
**Build Now** → you see the 3 stages **Checkout → Build → Run** (stage view) → Console Output shows the program output.

## Screenshots to take
Job configuration (SCM, trigger, build step) · Console Output of #1 · Automatic build #2 · Pipeline stages

---

## If something goes wrong

| Error | Fix |
|---|---|
| `Couldn't find any revision to build` | Branch Specifier is `*/master` → change to `*/main` |
| `'javac' is not recognized` (in Jenkins) | Close Jenkins (Ctrl+C), make sure `javac -version` works in that cmd, start Jenkins again |
| `Cannot run program "git"` | Install Git, or Manage Jenkins → Tools → Git → Path: `C:\Program Files\Git\bin\git.exe` |
| `Jenkins requires Java 21` / `UnsupportedClassVersionError` | Your Java is too old → install Temurin 21 |
| No automatic build after 2 min | Poll SCM not ticked / wrong repo URL → check **Git Polling Log** |
| `Address already in use` | Port taken → `java -jar jenkins.war --httpPort=9090` |
| Forgot the first password | Open `C:\Users\<you>\.jenkins\secrets\initialAdminPassword` in Notepad |

## Conclusion
We set up Jenkins, created a Freestyle job connected to GitHub that compiles and runs a Java program,
configured Poll SCM so builds run automatically on code changes, and created the same job as a Pipeline —
showing how Jenkins automates builds in CI.

## Viva questions
- **What is Jenkins?** An open-source automation server written in Java used for CI/CD.
- **Freestyle vs Pipeline?** Freestyle is configured in the UI; Pipeline is written as code (Jenkinsfile) and can be stored in Git.
- **Poll SCM vs Build periodically?** Poll SCM builds only when the code changed; Build periodically builds every time.
- **What does `H/5 * * * *` mean?** Run every 5 minutes (H spreads load across the hour).
- **Master vs agent?** Master schedules jobs and serves the UI; agents execute the builds.
- **What is a plugin?** An add-on that extends Jenkins (Git, Maven, Docker plugins).
- **What is a webhook?** GitHub sending an HTTP request to Jenkins on every push, so builds start instantly.
