# DevOps Lab Practical — CS447 (RIT)

All 10 experiments with step-by-step guides and ready-to-run code.
Open the folder of the experiment you get and follow its `README.md` from top to bottom.

| # | Experiment | Folder | Tools needed |
|---|---|---|---|
| 1 | Introduction to DevOps: culture, principles, benefits | [exp01-devops-intro](exp01-devops-intro) | None (theory) |
| 2 | Getting started with Git and version control | [exp02-git-basics](exp02-git-basics) | Git, GitHub, (gcc optional) |
| 3 | Collaborating using GitHub and pull requests | [exp03-github-pull-requests](exp03-github-pull-requests) | Git, GitHub |
| 4 | GitFlow workflow in a team scenario | [exp04-gitflow](exp04-gitflow) | Git, GitHub |
| 5 | Automating builds and jobs using Jenkins | [exp05-jenkins-build](exp05-jenkins-build) | Java, Jenkins, Git |
| 6 | CI/CD for web development using Jenkins | [exp06-jenkins-web-cicd](exp06-jenkins-web-cicd) | Java, Jenkins, Git, (Python) |
| 7 | Containerization and deployment using Docker | [exp07-docker](exp07-docker) | Docker |
| 8 | CI/CD pipeline using Docker and Jenkins | [exp08-docker-jenkins-pipeline](exp08-docker-jenkins-pipeline) | Docker, Jenkins, Git |
| 9 | Maven build lifecycle for Java | [exp09-maven](exp09-maven) | Java 17+, Maven |
| 10 | Container orchestration using Kubernetes | [exp10-kubernetes](exp10-kubernetes) | Docker Desktop + Kubernetes, kubectl |

## First 5 minutes in the lab (any experiment)

1. Check what is already installed — open **Command Prompt** and run [`00-setup/check-tools.bat`](00-setup/check-tools.bat), or type:
   ```
   git --version
   java -version
   mvn -version
   docker --version
   kubectl version --client
   ```
2. Install only what is missing for **your** experiment → [00-setup/SETUP.md](00-setup/SETUP.md).
3. Clone this repo:
   ```bash
   cd Desktop
   git clone https://github.com/atharvvs718/capstone-v2-arch.git
   cd capstone-v2-arch
   ```
4. Open your experiment folder's `README.md` and follow it.

> Many experiments ask you to **create a new GitHub repo** and push code to it.
> Copy the experiment's code folder out of this repo first (instructions in each guide),
> so you don't push it inside this repo by mistake.

## Before leaving the lab

- `cmdkey /delete:git:https://github.com` (in cmd) — removes your saved GitHub login
- `git config --global --unset user.name` and `git config --global --unset user.email`
- Log out of GitHub (and Docker Hub) in the browser
- Stop things you started: `docker stop` containers, close Jenkins window (Ctrl+C)

Quick viva prep for all experiments: [VIVA.md](VIVA.md)
"# capstone-v2-arch" 
