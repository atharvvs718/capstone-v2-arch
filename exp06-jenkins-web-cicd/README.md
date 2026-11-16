# Experiment 6 — Applying CI/CD Principles to Web Development using Jenkins

**Aim:** To apply CI/CD by automating the checkout, build, test and deployment of a simple
HTML/CSS/JS web application using a Jenkins pipeline, triggered automatically on code changes.

**Ready-made code:** `web-app/` → `index.html`, `style.css`, `script.js`,
`Jenkinsfile` (Windows), `Jenkinsfile.linux` (Linux + tidy, matches the handout's `/var/www/html`)

**Needs:** Java, Git, Jenkins → [../00-setup/SETUP.md](../00-setup/SETUP.md). Python optional (to serve the page on a URL).

---

## Theory (viva)

- **CI (Continuous Integration):** every push is automatically built and tested → bugs caught early.
- **Continuous Delivery:** every good build is automatically made *ready* to release (manual approval to go live).
- **Continuous Deployment:** every good build is automatically deployed to production.
- **Jenkins Pipeline:** CI/CD process written as code in a **Jenkinsfile** (stored in Git with the app).
  - `pipeline` → `agent` (where to run) → `stages` → `stage` → `steps`; `post` runs after (success/failure).
- Our pipeline: **Checkout → Build → Test → Deploy**.

---

## Step 1 — Push the web app to GitHub
```bash
cp -r exp06-jenkins-web-cicd/web-app ~/Desktop/cicd-web-app
cd ~/Desktop/cicd-web-app
git init
git add .
git commit -m "Add web app and Jenkinsfile"
git branch -M main
```
GitHub → New repository **`cicd-web-app`** (Public, no README) →
```bash
git remote add origin https://github.com/atharvvs718/cicd-web-app.git
git push -u origin main
```
> If you name the repo differently, change the URL in the `Jenkinsfile` `git ...` line, commit and push.

## Step 2 — Start Jenkins
`java -jar jenkins.war --httpPort=8080` (or open http://localhost:8080 if already installed) → log in.

## Step 3 — Create a Pipeline job
**New Item** → name `WebApp-CICD` → **Pipeline** → OK

- **Build Triggers:** tick **Poll SCM** → `H/2 * * * *`
- **Pipeline** section:
  - Definition: **Pipeline script from SCM**
  - SCM: **Git** → Repository URL `https://github.com/atharvvs718/cicd-web-app.git`
  - Branch Specifier: **`*/main`**
  - Script Path: `Jenkinsfile`
- **Save**

(Quick alternative: Definition **Pipeline script** and paste the Jenkinsfile contents.)

## Step 4 — Run the pipeline
**Build Now** → open build `#1` → **Console Output** / **Stage View** (or *Pipeline Overview*). Verify:
- **Checkout** — "Cloning project from GitHub..."
- **Build** — `dir` lists files, `build-info.txt` created
- **Test** — `findstr` finds `<html`, `</html>`, `<title>` → "All tests passed"
- **Deploy** — files copied to `C:\deploy\web-app`
- `Finished: SUCCESS`

## Step 5 — View the deployed page
- Simple: File Explorer → `C:\deploy\web-app\index.html` → open in browser.
- On a URL (better for screenshot) — in a new cmd window:
  ```
  cd C:\deploy\web-app
  python -m http.server 8000
  ```
  Browser → http://localhost:8000 → page shows *"Welcome to my CI/CD Web App - Version 1"*.
  `build-info.txt` shows which build deployed it: http://localhost:8000/build-info.txt
- If IIS is installed: change `DEPLOY_DIR` to `C:\\inetpub\\wwwroot` → http://localhost/index.html

## Step 6 — Change code → automatic build and redeploy (Continuous Deployment)
Edit `index.html` heading to `Version 2`:
```bash
notepad index.html          # change "Version 1" to "Version 2", save
git add index.html
git commit -m "Update heading to Version 2"
git push
```
Wait ≤ 2 minutes **without clicking Build Now** → build `#2` starts automatically →
refresh http://localhost:8000 → heading now says **Version 2** ✅

## Step 7 — Show a failing test (optional, impressive)
Delete the `<title>` line from index.html, commit and push → build fails at **Test** stage →
**Deploy does not run**, so the broken page never goes live. Put the line back and push → green again.

## Screenshots to take
Pipeline configuration · Stage View with all 4 stages green · Console output · Deployed page in browser

---

## Linux version (handout's tidy + /var/www/html)
If Jenkins runs on Linux: use `Jenkinsfile.linux` (rename it to `Jenkinsfile` or set Script Path to `Jenkinsfile.linux`).
Needs `sudo apt install tidy apache2` and write permission on `/var/www/html` for the jenkins user.

## Common errors

| Error | Fix |
|---|---|
| `Couldn't find any revision to build` | Branch Specifier `*/master` → `*/main` |
| `Access is denied` on copy | Jenkins can't write to that folder — keep `C:\deploy\web-app` (not `C:\inetpub` without admin) |
| `bat` not found / `sh` not found | Windows Jenkins → `bat`; Linux Jenkins → `sh` / Jenkinsfile.linux |
| Test stage fails | `findstr` didn't find a tag in index.html — check the file |
| No automatic build | Poll SCM not ticked, or you pushed to a different branch/repo than Jenkins watches |

## Conclusion
We applied CI/CD principles using a Jenkins pipeline that automatically checks out a web app
from GitHub, builds, tests and deploys it on every change. Broken code is stopped at the test
stage, and good code reaches the server without manual work — enabling fast, reliable delivery.
