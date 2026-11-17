# Experiment 6 — Applying CI/CD Principles to Web Development using Jenkins

**Aim:** To apply CI/CD by automating the checkout, build, test and deployment of a simple
HTML/CSS/JS web application using a Jenkins pipeline that runs automatically when code changes.



## Expected outcome
By the end of this experiment you will have:
- A Jenkins Pipeline job **WebApp-CICD** with 4 green stages: **Checkout → Build → Test → Deploy**.
- The website deployed to **C:\deploy\web-app** showing *"Welcome to my CI/CD Web App - Version 1"*.
- After changing the heading to *Version 2* and pushing, Jenkins builds **automatically** and the deployed page shows *Version 2*.
- (Optional) a broken page fails at **Test** and is **not deployed**.

**You need:** Git, Java 21, Jenkins, GitHub account. Time: ~30 min (+15–20 min installs).

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
- **CI (Continuous Integration):** every push is automatically built and tested → bugs caught early.
- **Continuous Delivery:** every good build is ready to release (a person approves going live).
- **Continuous Deployment:** every good build goes live automatically.
- **Jenkins Pipeline:** the CI/CD process written as code (**Jenkinsfile**):
  `pipeline → agent → stages → stage → steps`, and `post` runs after (success / failure).
- Our pipeline: **Checkout → Build → Test → Deploy**.

---

## Step 1 — Start Jenkins
If you just finished Step 0.C, Jenkins is already running. Otherwise, in a cmd window (keep it open):
```
cd /d %USERPROFILE%\Downloads
java -jar jenkins.war --httpPort=8080
```
Browser → **http://localhost:8080** → log in.

## Step 2 — Create the web app
Open a **new** cmd window:
```
cd /d %USERPROFILE%
mkdir cicd-web-app
cd cicd-web-app
```
`notepad index.html` → Yes → paste → save:
```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <title>CI/CD Web App</title>
  <link rel="stylesheet" href="style.css">
</head>
<body>
  <h1>Welcome to my CI/CD Web App - Version 1</h1>
  <p>This page is built, tested and deployed automatically by Jenkins.</p>
  <button onclick="showTime()">Check if page is live</button>
  <p id="output"></p>
  <script src="script.js"></script>
</body>
</html>
```
`notepad style.css`:
```css
body {
  font-family: Arial, sans-serif;
  background: #f4f6f8;
  text-align: center;
  margin-top: 60px;
}
h1 {
  color: #1f6feb;
}
button {
  padding: 10px 18px;
  font-size: 15px;
  cursor: pointer;
}
```
`notepad script.js`:
```javascript
function showTime() {
  document.getElementById('output').innerText =
    'Page is live! Current time: ' + new Date().toLocaleString();
}
```
Check: `start index.html` → page opens in browser.

## Step 3 — Push it to GitHub
GitHub → **New repository** → `cicd-web-app` → **Public** → don't tick README → Create. Then:
```
git init
git add .
git commit -m "Add web app"
git branch -M main
git remote add origin https://github.com/atharvvs718/cicd-web-app.git
git push -u origin main
```

## Step 4 — Create the Pipeline job
Jenkins → **+ New Item** → name `WebApp-CICD` → **Pipeline** → **OK** →
scroll to **Pipeline** → Definition: **Pipeline script** → paste → **Save**:
```groovy
pipeline {
    agent any

    environment {
        DEPLOY_DIR = 'C:\\deploy\\web-app'
    }

    triggers {
        pollSCM('H/2 * * * *')
    }

    stages {
        stage('Checkout') {
            steps {
                echo 'Cloning project from GitHub...'
                git branch: 'main', url: 'https://github.com/atharvvs718/cicd-web-app.git'
            }
        }
        stage('Build') {
            steps {
                echo 'Build step: static website, nothing to compile - listing files'
                bat 'dir'
                bat 'echo Build #%BUILD_NUMBER% deployed on %DATE% %TIME% > build-info.txt'
            }
        }
        stage('Test') {
            steps {
                echo 'Test step: checking files exist and HTML is complete'
                bat 'if not exist index.html exit /b 1'
                bat 'if not exist style.css exit /b 1'
                bat 'if not exist script.js exit /b 1'
                bat 'findstr /C:"<html" index.html'
                bat 'findstr /C:"<title>" index.html'
                bat 'findstr /C:"</html>" index.html'
                echo 'All tests passed'
            }
        }
        stage('Deploy') {
            steps {
                echo "Deploying to ${env.DEPLOY_DIR}"
                bat 'if not exist "%DEPLOY_DIR%" mkdir "%DEPLOY_DIR%"'
                bat 'copy /Y index.html "%DEPLOY_DIR%"'
                bat 'copy /Y style.css "%DEPLOY_DIR%"'
                bat 'copy /Y script.js "%DEPLOY_DIR%"'
                bat 'copy /Y build-info.txt "%DEPLOY_DIR%"'
                bat 'dir "%DEPLOY_DIR%"'
            }
        }
    }

    post {
        success { echo 'Pipeline finished successfully! Open C:\\deploy\\web-app\\index.html' }
        failure { echo 'Pipeline failed! Check the console output.' }
    }
}
```

## Step 5 — Run the pipeline
**Build Now** → click build **#1** → **Console Output** (or the stage view). Verify:
- **Checkout** — "Cloning project from GitHub..."
- **Build** — file list shown
- **Test** — the `findstr` lines print the matching HTML lines → "All tests passed"
- **Deploy** — files copied to `C:\deploy\web-app`
- `Finished: SUCCESS`

## Step 6 — Open the deployed website
In cmd:
```
start C:\deploy\web-app\index.html
```
The page shows **"Welcome to my CI/CD Web App - Version 1"**.

(Optional, to show it on a URL — only if `python --version` works:)
```
cd /d C:\deploy\web-app
python -m http.server 8000
```
Browser → **http://localhost:8000** (Ctrl+C to stop). `http://localhost:8000/build-info.txt` shows which build deployed it.

## Step 7 — Change code → automatic build and redeploy
Back in the `cicd-web-app` cmd window:
```
cd /d %USERPROFILE%\cicd-web-app
notepad index.html
```
Change `Version 1` to `Version 2` in the `<h1>` line → save → then:
```
git add index.html
git commit -m "Update heading to Version 2"
git push
```
**Wait up to 2 minutes — don't click Build Now.** Build **#2** starts automatically →
refresh the deployed page (`start C:\deploy\web-app\index.html`) → it now says **Version 2** ✅

## Step 8 (optional) — Show that a failing test stops deployment
`notepad index.html` → delete the `<title>CI/CD Web App</title>` line → save →
```
git add index.html
git commit -m "Break the title on purpose"
git push
```
Build #3 fails at **Test** → **Deploy is skipped**, so the broken page never goes live.
Put the line back, commit and push → green again.

## Screenshots to take
Pipeline script config · Stage view (4 green stages) · Console output · Deployed page · Automatic build #2

---

## If something goes wrong

| Error | Fix |
|---|---|
| `Couldn't find any revision to build` / branch error | Repo branch must be `main`; check the URL in the `git` line |
| `Access is denied` while copying | Change `DEPLOY_DIR` to `'C:\\Users\\<your-user>\\deploy\\web-app'` |
| Test stage fails | `findstr` didn't find a tag → check index.html has `<html`, `<title>`, `</html>` |
| No automatic build | Build #1 must run once manually first (that registers Poll SCM); then wait 2 min |
| `bat: not found` | Jenkins is on Linux → replace every `bat` with `sh` and use Linux commands |

## Conclusion
We applied CI/CD using a Jenkins pipeline that automatically checks out a web application from GitHub,
builds, tests and deploys it whenever code changes. A failed test stops deployment, so only working code goes live.

## Viva questions
- **CI vs CD?** CI = automatically build and test every change; CD = automatically deliver/deploy every good build.
- **Continuous Delivery vs Continuous Deployment?** Delivery needs manual approval to go live; deployment is fully automatic.
- **What is a Jenkinsfile?** A text file containing the pipeline as code, usually stored in the repository.
- **What is `agent any`?** Run the pipeline on any available Jenkins node.
- **What is the `post` block?** Steps that run after the stages — e.g. on `success` or `failure`.
- **Declarative vs Scripted pipeline?** Declarative uses the structured `pipeline {}` syntax; scripted uses Groovy `node {}` code.
- **Why is the Test stage before Deploy?** So broken code is caught and never deployed.
