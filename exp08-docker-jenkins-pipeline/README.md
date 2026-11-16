# Experiment 8 — Building a CI/CD Pipeline using Docker and Jenkins

**Aim:** To design and implement an automated CI/CD pipeline with Jenkins and Docker:
checkout from GitHub → build a Docker image → test it → push to registry (optional) → deploy a container.

**Ready-made code:** `docker-cicd-app/`
- `Main.java` + `Dockerfile` — Java web app (same as Exp 7)
- `Jenkinsfile` — **use this one** (plain `docker` commands, works on Windows Jenkins + Docker Desktop)
- `Jenkinsfile.handout` — the handout's style (`docker.build` / `docker.withRegistry`), needs Docker Pipeline plugin + Docker Hub

**Needs:** Docker Desktop **running**, Java, Git, Jenkins → [../00-setup/SETUP.md](../00-setup/SETUP.md)

---

## Theory (viva)

- **CI** — every commit is automatically built and tested. **Continuous Delivery** — every good build
  is ready to release. **Continuous Deployment** — every good build is released automatically.
- **Docker in CI/CD** — the app + dependencies are packaged as an **immutable image**, tagged with the
  **build number**, pushed to a **registry** (Docker Hub), and run anywhere → no "works on my machine".
- **Flow:** developer pushes to GitHub → Jenkins detects commit (Poll SCM / webhook) → checkout →
  `docker build` → test → `docker push` → deploy (`docker run`).
- **Tagging with `BUILD_NUMBER`** → every build gets a unique version, easy rollback.
- Jenkins plugins: **Git**, **Pipeline**, **Docker Pipeline**; **Credentials** store Docker Hub login safely.

---

## Step 1 — Check Docker and Jenkins
```
docker ps
```
Start Jenkins **from the same Windows user** (so it can use Docker Desktop):
```
java -jar jenkins.war --httpPort=8080
```
→ http://localhost:8080 → log in.

> The handout runs Jenkins *inside* Docker (`docker run ... jenkins/jenkins:lts`). That container has no
> Docker CLI inside, so it can't build images without extra setup. On a lab PC, running `jenkins.war`
> directly is simpler and works with Docker Desktop. Mention this if asked.

Plugins: **Manage Jenkins → Plugins → Available** → make sure **Git**, **Pipeline**, and
**Docker Pipeline** are installed (Git + Pipeline come with suggested plugins).

## Step 2 — Push the app to GitHub
```bash
cp -r exp08-docker-jenkins-pipeline/docker-cicd-app ~/Desktop/docker-cicd-app
cd ~/Desktop/docker-cicd-app
git init
git add .
git commit -m "Add Java app, Dockerfile and Jenkinsfile"
git branch -M main
```
GitHub → New repository **`docker-cicd-app`** (Public, no README) →
```bash
git remote add origin https://github.com/atharvvs718/docker-cicd-app.git
git push -u origin main
```

## Step 3 — Create the Pipeline job
**New Item** → `Docker-CICD-Pipeline` → **Pipeline** → OK
- **Build Triggers:** **Poll SCM** → `H/2 * * * *`
- **Pipeline:** Definition **Pipeline script from SCM** → SCM **Git** →
  URL `https://github.com/atharvvs718/docker-cicd-app.git` → Branch **`*/main`** → Script Path `Jenkinsfile`
- **Save**

## Step 4 — Run it
**Build Now**. (First run only: after it finishes, the left menu shows **Build with Parameters**
because of the `PUSH_TO_DOCKERHUB` checkbox — that's normal.)

Console / Stage View shows:
1. **Checkout** — code pulled from GitHub
2. **Build Docker Image** — `docker build -t cicd-java-app:1 ...`
3. **Test** — runs a temporary container on port 9099 and `curl` checks the page responds
4. **Push to Docker Hub** — *skipped* (checkbox off)
5. **Deploy** — old container removed, new one started on port 8082

Browser → **http://localhost:8082** → *"Hello from the Jenkins + Docker CI/CD pipeline!"*
```
docker images cicd-java-app      # shows tags 1, latest
docker ps                        # cicd-java-app running
```

## Step 5 — Change code → automatic rebuild and redeploy
```bash
notepad Main.java      # change the <h1> text, e.g. "... pipeline! Version 2"
git add .
git commit -m "Update message to version 2"
git push
```
Within ~2 minutes build `#2` runs automatically → new image `cicd-java-app:2` → container replaced →
refresh http://localhost:8082 → new message ✅

## Step 6 (optional) — Push the image to Docker Hub
1. Create a free account at hub.docker.com → Account settings → **Personal access tokens** → generate one.
2. Jenkins → **Manage Jenkins → Credentials → System → Global credentials → Add Credentials**
   - Kind: **Username with password**
   - Username: your Docker Hub username · Password: the access token
   - ID: **`dockerhub-credentials`** (must match the Jenkinsfile) → Create
3. Job → **Build with Parameters** → tick **PUSH_TO_DOCKERHUB** → Build
4. Docker Hub → Repositories → `cicd-java-app` with tag = build number ✅

(Handout version: set Script Path to `Jenkinsfile.handout` and change `your-dockerhub-username` in it.)

---

## Common errors

| Error | Fix |
|---|---|
| `docker: not recognized` / `error during connect` in Jenkins | Docker Desktop not running, or Jenkins started as a different user/service — start Jenkins with `java -jar jenkins.war` from your own cmd |
| `Couldn't find any revision to build` | Branch `*/master` → `*/main` |
| Test stage fails at `curl` | App slow to start → increase `ping -n 6` to `ping -n 11`; check `docker logs` |
| `port is already allocated` | Change `APP_PORT` in Jenkinsfile, or `docker rm -f` the old container |
| `denied: requested access to the resource is denied` on push | Wrong Docker Hub username/token, or image not tagged with your username |
| `No such DSL method 'docker'` (handout file) | Install **Docker Pipeline** plugin and restart Jenkins |

## Conclusion
We built a CI/CD pipeline where Jenkins automatically checks out code from GitHub, builds a Docker
image tagged with the build number, tests the container, optionally pushes it to Docker Hub and
deploys the new version — achieving consistent, automated and repeatable delivery.
