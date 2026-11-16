# Installing tools on the lab PC (Windows)

Install only what your experiment needs. If the PC blocks installers (no admin password),
use the **ZIP / portable** option — it needs no admin rights.

---

## 1. Git (Exp 2, 3, 4, 5, 6, 8)

**Check:** `git --version`

**Install:** https://git-scm.com → Downloads → Windows
- Normal: *64-bit Git for Windows Setup* → Next through everything, but:
  - Default editor → **Use Notepad**
  - Initial branch name → **Override → `main`**
  - Credential helper → **Git Credential Manager** (keep default)
- No admin: *64-bit Git for Windows Portable* → extract to Desktop → run `git-bash.exe`

**Configure (once):**
```bash
git config --global user.name "atharvvs718"
git config --global user.email "<your GitHub email>"
git config --global init.defaultBranch main
git config --list
```

**Login:** first `git push` opens a GitHub login popup → *Sign in with your browser*.
If it asks for a password in the terminal → username `atharvvs718`, password = **Personal Access Token** (not your GitHub password).

---

## 2. Java JDK (Exp 5, 6, 9 — and Jenkins needs it)

**Check:** `java -version` and `javac -version` (need 17 or 21)

**Install:** https://adoptium.net → Temurin **21 (LTS)** → Windows x64
- Normal: `.msi` → tick **"Set JAVA_HOME"** and **"Add to PATH"** during install
- No admin: download the **`.zip`**, extract to `C:\Users\<you>\jdk-21`, then in every new cmd window:
  ```
  set JAVA_HOME=C:\Users\<you>\jdk-21
  set PATH=%JAVA_HOME%\bin;%PATH%
  ```
  (folder name inside the zip is like `jdk-21.0.x+y` — use the real name)

---

## 3. Maven (Exp 9)

**Check:** `mvn -version`

**Install (no admin needed):** https://maven.apache.org/download.cgi → **Binary zip archive**
1. Extract to `C:\Users\<you>\apache-maven-3.9.x`
2. In cmd:
   ```
   set PATH=C:\Users\<you>\apache-maven-3.9.x\bin;%PATH%
   mvn -version
   ```
Maven needs `JAVA_HOME` set (see Java above). First build downloads plugins → needs internet.

---

## 4. Jenkins (Exp 5, 6, 8)

**Easiest, no install, no admin — run the WAR file:**
1. Java 17/21 must work (`java -version`).
2. https://www.jenkins.io/download/ → **Generic Java package (.war)** → LTS
3. In cmd, in the folder where `jenkins.war` downloaded:
   ```
   java -jar jenkins.war --httpPort=8080
   ```
   Keep this window open — closing it stops Jenkins.
4. The console prints the **initial admin password** between `*****` lines.
   (Also saved at `C:\Users\<you>\.jenkins\secrets\initialAdminPassword`)
5. Browser → http://localhost:8080 → paste password → **Install suggested plugins** (takes 3–5 min)
6. Create admin user → Save and Finish → Start using Jenkins.

If port 8080 is busy: `java -jar jenkins.war --httpPort=9090` → open http://localhost:9090

**Tell Jenkins where Git is (if a job fails with "git not found"):**
Manage Jenkins → Tools → Git installations → Path to Git executable: `C:\Program Files\Git\bin\git.exe`

---

## 5. Docker (Exp 7, 8, 10)

**Check:** `docker --version` then `docker ps` (if `docker ps` errors → Docker Desktop isn't running)

**Install:** https://www.docker.com/products/docker-desktop → Windows (needs **admin + WSL2**, restart).
Realistically: if Docker is not already installed on the lab PC, ask the lab assistant — it can't be installed
without admin rights and a reboot.

Start **Docker Desktop** from the Start menu and wait until it says *Engine running*.

---

## 6. Kubernetes (Exp 10)

Easiest: **Docker Desktop → Settings (gear) → Kubernetes → Enable Kubernetes → Apply & Restart**.
Wait until the Kubernetes icon at the bottom turns green (3–5 min). `kubectl` comes with Docker Desktop.

**Check:**
```
kubectl version --client
kubectl get nodes
```
`docker-desktop   Ready` = good.

Alternative: **minikube** (https://minikube.sigs.k8s.io) → `minikube start` → `kubectl get nodes`.

---

## 7. VS Code (optional, nice for Exp 3, 9)

https://code.visualstudio.com → *User Installer* (no admin needed).
For Exp 9 install extensions: **Extension Pack for Java**, **Maven for Java**.
