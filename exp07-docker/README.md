# Experiment 7 — Introduction to Containerization and Application Deployment using Docker

**Aim:** To containerize an application with a Dockerfile, build a Docker image, run it as a
container and access it in the browser.

**Problem statement:** Deploy a **Java application** using Docker.

**Ready-made code:**
- `flask-docker-app/` — handout's Flask example (`app.py`, `requirements.txt`, `Dockerfile`)
- `java-docker-app/` — **problem statement**: Java web app (`Main.java`, `Dockerfile`)

**Needs:** Docker Desktop running (no Git needed — Download ZIP from GitHub is enough).

---

## Theory (viva)

- **Containerization** = lightweight virtualization; app + dependencies packaged in an isolated
  **container** that shares the host OS kernel.
- **Container vs VM:** VM includes a full guest OS (GBs, minutes to boot); container shares the
  kernel (MBs, starts in seconds).
- Features: lightweight, portable, fast startup, isolated, scalable.
- **Docker Engine** — runs containers. **Image** — read-only template (code + libraries).
  **Container** — running instance of an image. **Dockerfile** — instructions to build an image.
  **Docker Hub** — public registry of images.
- Dockerfile keywords: `FROM` base image · `WORKDIR` working dir · `COPY` files in · `RUN` command
  at build time · `EXPOSE` documents port · `CMD` command when container starts.
- `-p 5000:5000` = **host port : container port**. `-d` = detached (background).

---

## Step 1 — Check Docker
Start **Docker Desktop** and wait for *Engine running*. Then in cmd / PowerShell:
```
docker --version
docker ps
```
`docker ps` shows an empty table = Docker works.

## Part A — Flask app (handout example)

### Step 2 — Go to the app folder
```
cd capstone-v2-arch\exp07-docker\flask-docker-app
dir
```
Files: `app.py`, `requirements.txt`, `Dockerfile` (code explained in the files' comments).

### Step 3 — Build the image
```
docker build -t flask-docker-app:1.0 .
docker images
```
(the `.` at the end = build context = current folder — don't forget it)

### Step 4 — Run the container
```
docker run -d -p 5000:5000 --name flask-app flask-docker-app:1.0
docker ps
```

### Step 5 — Access the app
Browser → **http://localhost:5000** → *"Hello, Docker!"*

---

## Part B — Problem statement: Deploy a Java application using Docker

### Step 6 — Go to the Java app folder
```
cd ..\java-docker-app
dir
```
`Main.java` = small Java web server on port 8080. `Dockerfile` = uses the Java 17 image,
compiles `Main.java` inside the image, runs `java Main`.

### Step 7 — Build the image
```
docker build -t java-docker-app:1.0 .
docker images
```

### Step 8 — Run the container
```
docker run -d -p 8081:8080 --name java-app java-docker-app:1.0
docker ps
docker logs java-app
```
Logs show *"Java app running on port 8080"*.

### Step 9 — Access the app
Browser → **http://localhost:8081** → *"Hello from a Java app in Docker!"* + Java version
(proves it runs on the container's Java 17, not the PC's Java).

---

## Useful commands (show these too)
```
docker ps -a                     # all containers incl. stopped
docker logs <name>               # container output
docker exec -it java-app bash    # open a shell inside the container (type exit to leave)
docker stop java-app flask-app   # stop
docker start java-app            # start again
docker rm java-app flask-app     # remove containers (stop first)
docker rmi java-docker-app:1.0   # remove image
```

## Optional — push the image to Docker Hub
```
docker login
docker tag java-docker-app:1.0 <dockerhub-username>/java-docker-app:1.0
docker push <dockerhub-username>/java-docker-app:1.0
```

---

## Common errors

| Error | Fix |
|---|---|
| `error during connect ... pipe/docker_engine` | Docker Desktop is not running — start it, wait for *Engine running* |
| `port is already allocated` | Use another host port: `-p 5001:5000` / `-p 8082:8080` |
| `Conflict. The container name ... is already in use` | `docker rm -f java-app` then run again |
| `"docker build" requires exactly 1 argument` | You forgot the `.` at the end |
| Build fails downloading the base image | Needs internet; check proxy, retry |
| Page doesn't open | `docker ps` — is it running? `docker logs <name>` for errors |

## Conclusion
We containerized a Flask app and a Java application by writing Dockerfiles, built Docker images,
ran them as containers with port mapping, and accessed them in the browser — showing how Docker
packages applications to run consistently on any machine.
