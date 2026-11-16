# Quick Viva Prep — DevOps Lab

## Exp 1 — DevOps intro
- **DevOps?** Culture + practices joining Development and Operations to deliver software faster and reliably through collaboration and automation.
- **Lifecycle:** Plan → Code → Build → Test → Release → Deploy → Operate → Monitor (continuous feedback loop).
- **Principles (CALMS):** Culture, Automation, Lean, Measurement, Sharing.
- **MTTR / MTBF:** mean time to repair (lower better) / mean time between failures (higher better).
- **DORA metrics:** deployment frequency, lead time for changes, change failure rate, time to restore service.

## Exp 2 — Git
- **Git vs GitHub:** Git = version control tool on your PC; GitHub = website hosting Git repos remotely.
- **Distributed VCS:** every developer has the full repo + history locally.
- **3 areas:** working directory → staging area (`git add`) → repository (`git commit`).
- **`git init`** creates a `.git` folder. **`origin`** = default name of the remote.
- **`git push -u`** sets upstream so later just `git push`.
- **`git pull` = `git fetch` + `git merge`.**
- **`.gitignore`** = files Git should not track (e.g. `.exe`, `target/`).
- **Undo:** `git restore <file>` (discard change), `git reset HEAD~1` (undo last commit), `git revert <id>` (new commit that undoes).

## Exp 3 — GitHub & PR
- **Fork vs clone:** fork = copy repo to your GitHub account; clone = copy repo to your PC.
- **Pull Request:** request to merge one branch into another, with review and discussion.
- **Why branches?** Work without breaking `main`; parallel development.
- **Merge conflict:** two changes to the same lines → fix manually, then add + commit.
- **Merge vs rebase:** merge keeps history + adds merge commit; rebase rewrites commits onto another branch (linear history).

## Exp 4 — GitFlow
- **Branches:** main (production), develop (integration), feature/* (from develop → develop), release/* (from develop → main + develop), hotfix/* (from main → main + develop).
- **Why hotfix from main?** Bug is in production code; fix must not include unfinished develop work.
- **Tag** = named pointer to a commit, used for versions (`v1.0`).

## Exp 5 — Jenkins
- **Jenkins:** open-source automation server for CI/CD, written in Java, default port 8080.
- **Controller/master vs agent:** controller schedules + UI; agents run builds.
- **Freestyle vs Pipeline:** UI-configured vs code (`Jenkinsfile`, versioned in Git).
- **Poll SCM vs Build periodically vs Webhook:** poll checks Git and builds only on changes; periodically always builds; webhook = GitHub pushes notification (instant, needs public URL).
- **Cron `H/5 * * * *`:** every 5 minutes; fields = minute hour day-of-month month day-of-week.
- **Initial password:** `.jenkins/secrets/initialAdminPassword`.

## Exp 6 — CI/CD
- **CI:** integrate + build + test automatically on every push.
- **Continuous Delivery vs Deployment:** delivery = always ready to release, manual approval; deployment = goes live automatically.
- **Jenkinsfile structure:** `pipeline { agent { } environment { } stages { stage { steps { } } } post { } }`.
- **Declarative vs Scripted pipeline:** declarative = `pipeline {}` structured syntax; scripted = `node {}` Groovy code.
- **`post` block:** runs after stages — `success`, `failure`, `always`.

## Exp 7 — Docker
- **Container vs VM:** container shares host kernel (light, seconds); VM has full guest OS (heavy, minutes).
- **Image vs container:** image = read-only template; container = running instance of an image.
- **Dockerfile:** FROM, WORKDIR, COPY, RUN (build time), EXPOSE, CMD (run time).
- **CMD vs ENTRYPOINT:** CMD = default command, easily overridden; ENTRYPOINT = fixed executable.
- **RUN vs CMD:** RUN executes while building the image; CMD when the container starts.
- **`-p 8081:8080`:** host port 8081 → container port 8080. **`-d`:** detached.
- **Layers:** each instruction = cached layer; copy `requirements.txt` first so dependencies are cached.
- **Docker Hub:** public image registry. **Volume:** persistent storage outside the container.

## Exp 8 — Docker + Jenkins
- **Why Docker in CI/CD?** Same image in test and production → consistency, easy rollback.
- **Tag with BUILD_NUMBER:** unique version per build, traceable, rollback to old tag.
- **Credentials:** stored in Jenkins Credentials, referenced by ID — never hard-coded.
- **Pipeline stages:** checkout → build image → test → push → deploy.

## Exp 9 — Maven
- **Maven:** Java build + dependency management tool; config in `pom.xml`.
- **POM:** Project Object Model. **GAV:** groupId, artifactId, version.
- **Lifecycles:** clean, default, site. **Default phases:** validate, compile, test, package, verify, install, deploy.
- **Running `package`** runs all earlier phases too.
- **Local repo:** `~/.m2/repository`; **central repo:** Maven Central.
- **`install` vs `deploy`:** install → local `.m2`; deploy → remote repository.
- **SNAPSHOT:** development (unstable) version. **Archetype:** project template (`maven-archetype-quickstart`).
- **Maven vs Gradle:** Gradle uses Groovy/Kotlin scripts, faster incremental builds; Maven uses XML convention.

## Exp 10 — Kubernetes
- **K8s:** container orchestration — deploy, scale, heal, load-balance containers.
- **Control plane:** API server, scheduler, controller manager, etcd. **Node:** kubelet, kube-proxy, container runtime.
- **Pod:** smallest unit, 1+ containers. **ReplicaSet:** keeps N Pods. **Deployment:** manages ReplicaSets, rolling updates, rollback.
- **Service types:** ClusterIP (internal), NodePort (30000–32767), LoadBalancer (cloud).
- **Why Service?** Pod IPs change; Service gives a stable endpoint + load balancing via labels.
- **Self-healing:** delete a Pod → Deployment recreates it.
- **`kubectl apply` vs `create`:** apply is declarative (create or update); create fails if it exists.
- **Docker vs Kubernetes:** Docker builds/runs containers; Kubernetes manages many containers across machines.
