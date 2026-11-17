# Experiment 8 — Building a CI/CD Pipeline using Docker and Jenkins

**Aim:** To design and implement an automated CI/CD pipeline with Jenkins and Docker:
checkout code from GitHub → build a Docker image → test it → (push to Docker Hub) → deploy the container.



## Expected outcome
By the end of this experiment you will have:
- A Jenkins Pipeline job **Docker-CICD-Pipeline** with 4 green stages: **Checkout → Build Docker Image → Test → Deploy**.
- A Docker image **cicd-java-app** tagged with the build number (`cicd-java-app:1`, `cicd-java-app:latest`).
- The app running at **http://localhost:8082** showing *"Hello from the Jenkins + Docker CI/CD pipeline! Version 1"*.
- After pushing *Version 2*, Jenkins rebuilds and redeploys **automatically** → page shows *Version 2*, image `cicd-java-app:2` exists.
- (Optional) the image pushed to Docker Hub.

**You need:** Git, Java 21, Jenkins, Docker Desktop, GitHub account. Time: ~35 min (+ installs).

---

## Step 0 — Install everything (on a PC that has nothing)
Open **Command Prompt**: press `Win + R` → type `cmd` → Enter.
Do each part below. If the *Check* command already works, skip that part.

> Tip: if Docker is **not** installed, do **0.D (Docker) first** — its install may restart the PC, which would stop Jenkins.

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

### 0.D — Docker Desktop
Check in cmd: `docker --version` → if it prints a version, just start **Docker Desktop** from the Start menu and skip the rest.

> ⚠️ Installing Docker Desktop needs **admin rights**, **WSL2** and often a **restart**. If the lab PC doesn't allow
> that, ask the lab assistant for a PC that already has Docker — it cannot be installed without admin.

1. Browser → **https://www.docker.com/products/docker-desktop/** → **Download for Windows – AMD64**.
2. Open the installer → **Yes** → keep **Use WSL 2 instead of Hyper-V** ticked → **Ok** → wait → **Close and restart** (if asked).
3. If it says **WSL needs updating** / **WSL 2 is not installed**: open cmd **as administrator** and run
   `wsl --install` (or `wsl --update`) → restart the PC.
4. Start **Docker Desktop** from the Start menu → **Accept** the terms → you can **Skip** sign-in and the survey.
5. Wait until the bottom-left shows **Engine running** (green). Then in a new cmd:
```
docker --version
docker ps
```
An empty table (`CONTAINER ID   IMAGE ...`) means Docker works.

---

## Theory (short)
- **CI** = every commit is automatically built and tested. **Continuous Delivery** = every good build is ready
  to release. **Continuous Deployment** = every good build is released automatically.
- **Docker in CI/CD:** the app is packaged as an image, tagged with the **build number**, pushed to a
  **registry** (Docker Hub) and run anywhere → no "works on my machine" problem.
- **Flow:** developer pushes to GitHub → Jenkins detects the commit → checkout → `docker build` → test →
  `docker push` → deploy (`docker run`).
- Jenkins plugins used: **Git**, **Pipeline**, **Docker Pipeline**. Docker Hub login is stored in **Jenkins Credentials**.

---

## Step 1 — Start Docker and Jenkins
1. Start **Docker Desktop** → wait for **Engine running**. Check in cmd: `docker ps`
2. Start Jenkins **from cmd** (so Jenkins can use Docker) — skip if it's already running from Step 0.C:
```
cd /d %USERPROFILE%\Downloads
java -jar jenkins.war --httpPort=8080
```
Keep this window open.
3. Browser → **http://localhost:8080** → log in.

> The handout runs Jenkins *inside* a Docker container. That container has no Docker inside it, so it
> can't build images without extra setup. Running `jenkins.war` directly on the PC is simpler and works
> with Docker Desktop. (Say this if asked.)

## Step 2 — Create the app
Open a **new** cmd window:
```
cd /d %USERPROFILE%
mkdir docker-cicd-app
cd docker-cicd-app
```
`notepad Main.java` → Yes → paste → save:
```java
import com.sun.net.httpserver.HttpServer;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;

/* Java web app that is built, tested and deployed by a Jenkins + Docker pipeline. */
public class Main {
    public static void main(String[] args) throws Exception {
        int port = 8080;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);

        server.createContext("/", exchange -> {
            String html = "<h1>Hello from the Jenkins + Docker CI/CD pipeline! Version 1</h1>"
                    + "<p>Java version: " + System.getProperty("java.version") + "</p>";
            byte[] body = html.getBytes(StandardCharsets.UTF_8);
            exchange.getResponseHeaders().set("Content-Type", "text/html; charset=UTF-8");
            exchange.sendResponseHeaders(200, body.length);
            try (OutputStream os = exchange.getResponseBody()) {
                os.write(body);
            }
        });

        server.start();
        System.out.println("Java app running on port " + port);
    }
}
```
Dockerfile:
```
type nul > Dockerfile
notepad Dockerfile
```
Paste → save:
```dockerfile
FROM eclipse-temurin:17-jdk
WORKDIR /app
COPY Main.java .
RUN javac Main.java
EXPOSE 8080
CMD ["java", "Main"]
```
Check (must be `Dockerfile`, not `Dockerfile.txt`):
```
dir
```

## Step 3 — Push to GitHub
GitHub → **New repository** → `docker-cicd-app` → **Public** → don't tick README → Create. Then:
```
git init
git add .
git commit -m "Add Java app and Dockerfile"
git branch -M main
git remote add origin https://github.com/atharvvs718/docker-cicd-app.git
git push -u origin main
```

## Step 4 — Create the Pipeline job
Jenkins → **+ New Item** → name `Docker-CICD-Pipeline` → **Pipeline** → **OK** →
scroll to **Pipeline** → Definition: **Pipeline script** → paste → **Save**:
```groovy
pipeline {
    agent any

    environment {
        IMAGE_NAME = 'cicd-java-app'
        APP_PORT   = '8082'
    }

    triggers {
        pollSCM('H/2 * * * *')
    }

    stages {
        stage('Checkout') {
            steps {
                git branch: 'main', url: 'https://github.com/atharvvs718/docker-cicd-app.git'
            }
        }

        stage('Build Docker Image') {
            steps {
                bat 'docker build -t %IMAGE_NAME%:%BUILD_NUMBER% -t %IMAGE_NAME%:latest .'
                bat 'docker images %IMAGE_NAME%'
            }
        }

        stage('Test') {
            steps {
                bat 'docker rm -f %IMAGE_NAME%-test 2>nul || exit /b 0'
                bat 'docker run -d --name %IMAGE_NAME%-test -p 9099:8080 %IMAGE_NAME%:%BUILD_NUMBER%'
                bat 'ping -n 6 127.0.0.1 > nul'
                bat 'curl -s -f http://localhost:9099'
            }
            post {
                always {
                    bat 'docker rm -f %IMAGE_NAME%-test 2>nul || exit /b 0'
                }
            }
        }

        stage('Deploy') {
            steps {
                bat 'docker rm -f %IMAGE_NAME% 2>nul || exit /b 0'
                bat 'docker run -d --name %IMAGE_NAME% -p %APP_PORT%:8080 %IMAGE_NAME%:%BUILD_NUMBER%'
                bat 'docker ps --filter name=%IMAGE_NAME%'
            }
        }
    }

    post {
        success { echo "Deployed build #${env.BUILD_NUMBER} - open http://localhost:${env.APP_PORT}" }
        failure { echo 'Pipeline failed - check the console output.' }
    }
}
```
What each stage does:
- **Checkout** — pulls code from GitHub
- **Build Docker Image** — builds the image, tagged with the build number (`cicd-java-app:1`)
- **Test** — starts a temporary container, waits 5 seconds, `curl` checks the page responds, then removes it
- **Deploy** — removes the old container and runs the new version on port 8082

## Step 5 — Run it
**Build Now** → open build **#1** → **Console Output** / stage view → all stages green, `Finished: SUCCESS`.
```
start http://localhost:8082
```
Page shows **"Hello from the Jenkins + Docker CI/CD pipeline! Version 1"** ✅

In cmd:
```
docker images cicd-java-app
docker ps
```

## Step 6 — Change code → automatic rebuild and redeploy
```
cd /d %USERPROFILE%\docker-cicd-app
notepad Main.java
```
Change `Version 1` to `Version 2` → save →
```
git add .
git commit -m "Update message to Version 2"
git push
```
**Wait up to 2 minutes — don't click Build Now.** Build **#2** runs by itself → new image `cicd-java-app:2`
→ container replaced → refresh **http://localhost:8082** → **Version 2** ✅

## Step 7 (optional) — Push the image to Docker Hub
1. Make a free account on **hub.docker.com** → Account settings → **Personal access tokens** → Generate → copy.
2. Jenkins → **Manage Jenkins** → **Credentials** → **System** → **Global credentials** → **Add Credentials**:
   - Kind: **Username with password**
   - Username: your Docker Hub username · Password: the token
   - ID: `dockerhub-credentials` → **Create**
3. Open the job → **Configure** → in the pipeline script, paste this stage **between the `Test` and `Deploy` stages** → Save:
```groovy
        stage('Push to Docker Hub') {
            steps {
                withCredentials([usernamePassword(credentialsId: 'dockerhub-credentials',
                                                  usernameVariable: 'DH_USER',
                                                  passwordVariable: 'DH_PASS')]) {
                    bat 'echo %DH_PASS%| docker login -u %DH_USER% --password-stdin'
                    bat 'docker tag %IMAGE_NAME%:%BUILD_NUMBER% %DH_USER%/%IMAGE_NAME%:%BUILD_NUMBER%'
                    bat 'docker push %DH_USER%/%IMAGE_NAME%:%BUILD_NUMBER%'
                    bat 'docker logout'
                }
            }
        }
```
4. **Build Now** → Docker Hub → Repositories → `cicd-java-app` with the build number tag ✅

## Screenshots to take
Pipeline script · Stage view (all green) · Console output · `docker images` · App in browser · Automatic build #2

---

## If something goes wrong

| Error | Fix |
|---|---|
| `docker` errors inside Jenkins / `error during connect` | Docker Desktop not running, or Jenkins installed as a Windows service → start Jenkins with `java -jar jenkins.war` from your own cmd |
| `failed to read dockerfile` | File is `Dockerfile.txt` → `ren Dockerfile.txt Dockerfile`, commit, push |
| Test stage fails at `curl` | App slow to start → change `ping -n 6` to `ping -n 11` |
| `port is already allocated` | Change `APP_PORT` to `'8083'` |
| `Couldn't find any revision` | Repo branch must be `main` |
| `denied: requested access` on push | Wrong Docker Hub username/token in credentials |
| No automatic build | Run build #1 manually first, then wait 2 minutes |

## Conclusion
We built a CI/CD pipeline where Jenkins automatically checks out code from GitHub, builds a Docker image tagged
with the build number, tests the container, (pushes it to Docker Hub) and deploys the new version — giving
consistent, automated and repeatable delivery.

## Viva questions
- **Why use Docker in CI/CD?** The same image runs in test and production → consistency and easy rollback.
- **Why tag images with BUILD_NUMBER?** Every build gets a unique version; you can roll back to an older tag.
- **What is a Docker registry?** A storage for images, e.g. Docker Hub.
- **Why store passwords in Jenkins Credentials?** So secrets are not written in the pipeline code.
- **What are the stages of this pipeline?** Checkout → Build image → Test → Push → Deploy.
- **What triggers the pipeline?** Poll SCM checks GitHub every 2 minutes (a webhook could trigger it instantly).
