# DevOps Lab Practical — Copy-Paste Guides

One page per experiment. Every page has the steps, every file's code, and every command.
**Just open your experiment's page below and follow it top to bottom.**

| # | Experiment | Guide |
|---|---|---|
| 1 | Introduction to DevOps (theory) | [exp01.md](exp01.md) |
| 2 | Getting started with Git and version control | [exp02.md](exp02.md) |
| 3 | Collaborating using GitHub and Pull Requests | [exp03.md](exp03.md) |
| 4 | GitFlow workflow in a team scenario | [exp04.md](exp04.md) |
| 5 | Automating builds and jobs using Jenkins | [exp05.md](exp05.md) |
| 6 | CI/CD for web development using Jenkins | [exp06.md](exp06.md) |
| 7 | Containerization and deployment using Docker | [exp07.md](exp07.md) |
| 8 | CI/CD pipeline using Docker and Jenkins | [exp08.md](exp08.md) |
| 9 | Maven build lifecycle for Java | [exp09.md](exp09.md) |
| 10 | Container orchestration using Kubernetes | [exp10.md](exp10.md) |

---

## How to use these guides

- **Terminal:** use **Command Prompt (cmd)** for everything → press `Win + R`, type `cmd`, Enter.
- **Copy a command:** click the copy icon on the code block → in cmd, **right-click** to paste → Enter.
- **Create a file:** the guide says e.g. `notepad index.html` → Notepad asks *"Do you want to create a new file?"* → **Yes** → paste the code with **Ctrl+V** → **Ctrl+S** → close Notepad.
- **Files without an extension** (`Dockerfile`): the guide first runs `type nul > Dockerfile`, then `notepad Dockerfile`. Otherwise Notepad saves it as `Dockerfile.txt` and Docker can't find it.
- **See your files in Explorer:** run `explorer .` in cmd.
- **Paste replaces:** when the guide says *"replace everything"*, press **Ctrl+A** in Notepad first, then **Ctrl+V**.

---

## Step 0 — Check what is installed (do this first, any experiment)

```
git --version
java -version
mvn -version
docker --version
kubectl version --client
```
"is not recognized" = not installed. What each experiment needs:

| Exp | Needs |
|---|---|
| 1 | nothing |
| 2, 3, 4 | Git |
| 5, 6 | Git, **Java 21**, Jenkins |
| 7 | Docker Desktop |
| 8 | Git, **Java 21**, Jenkins, Docker Desktop |
| 9 | Java 21 (17 also works), Maven |
| 10 | Docker Desktop with Kubernetes enabled |

---

## Installing tools
Every guide starts with **Step 0 — Install everything (on a PC that has nothing)**: Git, Java, Jenkins, Docker,
Maven — whatever that experiment needs, with exact download links and clicks. Each guide also starts with the
**Expected outcome**, so you know what the finished result should look like.

## Before leaving the lab

```
cmdkey /delete:git:https://github.com
git config --global --unset user.name
git config --global --unset user.email
```
Then log out of GitHub (and Docker Hub) in the browser.
