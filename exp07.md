# Experiment 7 — Introduction to Containerization and Application Deployment using Docker

**Aim:** To containerize an application using a Dockerfile, build a Docker image, run it as a container
and access it in the browser.

**Problem statement:** Deploy a **Java application** using Docker. (Part B — do this one for sure.)



## Expected outcome
By the end of this experiment you will have:
- Two Docker images: **flask-docker-app:1.0** and **java-docker-app:1.0** (`docker images`).
- Two running containers (`docker ps`).
- **http://localhost:5000** shows *"Hello, Docker!"* (Flask).
- **http://localhost:8081** shows *"Hello from a Java app in Docker!"* and *Java version: 17…* (problem statement).

**You need:** Docker Desktop. Time: ~20 min (first build downloads base images) (+20–30 min if Docker must be installed).

---

## Step 0 — Install everything (on a PC that has nothing)
Open **Command Prompt**: press `Win + R` → type `cmd` → Enter.
Do each part below. If the *Check* command already works, skip that part.

### 0.A — Docker Desktop
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
- **Containerization** = lightweight virtualization; the app and its dependencies run in an isolated
  **container** that shares the host OS kernel.
- **Container vs VM:** a VM has a full OS (GBs, minutes to start); a container shares the kernel (MBs, seconds).
- Features: lightweight, portable, fast startup, isolated, scalable.
- **Docker Engine** runs containers · **Image** = read-only template · **Container** = running instance of an image ·
  **Dockerfile** = instructions to build an image · **Docker Hub** = public image registry.
- Dockerfile words: `FROM` base image · `WORKDIR` folder inside container · `COPY` files in ·
  `RUN` command at build time · `EXPOSE` port · `CMD` command when the container starts.
- `-p 8081:8080` = **PC port : container port**. `-d` = run in background.

---

## Step 1 — Start Docker
Start menu → **Docker Desktop** → wait until it shows **Engine running** (green). Then:
```
docker --version
docker ps
```
An empty table = Docker works.

---

## PART A — Flask app (handout example)

### Step 2 — Create the folder and files
```
cd /d %USERPROFILE%
mkdir flask-docker-app
cd flask-docker-app
```
`notepad app.py` → Yes → paste → save:
```python
from flask import Flask

app = Flask(__name__)


@app.route('/')
def home():
    return "<h1>Hello, Docker!</h1><p>This Flask app is running inside a container.</p>"


if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
```
`notepad requirements.txt` → paste → save:
```
flask==3.0.3
```
Create the Dockerfile (**first line makes the file without .txt**):
```
type nul > Dockerfile
notepad Dockerfile
```
Paste → save:
```dockerfile
# Use official Python image
FROM python:3.11-slim

# Set working directory inside the container
WORKDIR /app

# Install dependencies
COPY requirements.txt requirements.txt
RUN pip install --no-cache-dir -r requirements.txt

# Copy the app code
COPY . .

# The app listens on port 5000
EXPOSE 5000

# Run the Flask app
CMD ["python", "app.py"]
```
Check the files — you must see `Dockerfile` (not `Dockerfile.txt`):
```
dir
```

### Step 3 — Build the image
```
docker build -t flask-docker-app:1.0 .
docker images
```
(Don't forget the **dot** at the end — it means "this folder".)

### Step 4 — Run the container
```
docker run -d -p 5000:5000 --name flask-app flask-docker-app:1.0
docker ps
```

### Step 5 — Open the app
```
start http://localhost:5000
```
Page shows **"Hello, Docker!"** ✅

---

## PART B — Problem statement: Deploy a Java application using Docker

### Step 6 — Create the folder and files
```
cd /d %USERPROFILE%
mkdir java-docker-app
cd java-docker-app
```
`notepad Main.java` → Yes → paste → save:
```java
import com.sun.net.httpserver.HttpServer;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.nio.charset.StandardCharsets;

/* A small Java web application (no external libraries) deployed with Docker. */
public class Main {
    public static void main(String[] args) throws Exception {
        int port = 8080;
        HttpServer server = HttpServer.create(new InetSocketAddress(port), 0);

        server.createContext("/", exchange -> {
            String html = "<h1>Hello from a Java app in Docker!</h1>"
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
Create the Dockerfile:
```
type nul > Dockerfile
notepad Dockerfile
```
Paste → save:
```dockerfile
# Base image with Java 17
FROM eclipse-temurin:17-jdk

# Working directory inside the container
WORKDIR /app

# Copy the source code and compile it
COPY Main.java .
RUN javac Main.java

# The app listens on port 8080
EXPOSE 8080

# Start the Java application
CMD ["java", "Main"]
```
Check:
```
dir
```

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
Logs show **"Java app running on port 8080"**.

### Step 9 — Open the app
```
start http://localhost:8081
```
Page shows **"Hello from a Java app in Docker!"** and the Java version (17 — from the container,
not your PC's Java) ✅

---

## Step 10 — Useful commands to show the examiner
```
docker ps -a
docker logs java-app
docker exec -it java-app ls /app
docker stop java-app flask-app
docker ps -a
docker start java-app
```
Clean up at the end:
```
docker rm -f java-app flask-app
docker rmi java-docker-app:1.0 flask-docker-app:1.0
```

## Optional — Push the image to Docker Hub
```
docker login
docker tag java-docker-app:1.0 YOUR-DOCKERHUB-USERNAME/java-docker-app:1.0
docker push YOUR-DOCKERHUB-USERNAME/java-docker-app:1.0
```

---

## If something goes wrong

| Error | Fix |
|---|---|
| `error during connect` / `cannot find the file specified ... docker_engine` | Docker Desktop not running → start it, wait for *Engine running* |
| `failed to read dockerfile` / `Dockerfile: no such file` | It saved as `Dockerfile.txt` → `ren Dockerfile.txt Dockerfile` |
| `"docker build" requires exactly 1 argument` | You forgot the `.` at the end |
| `port is already allocated` | Use another PC port: `-p 5001:5000` or `-p 8082:8080` |
| `container name ... already in use` | `docker rm -f java-app` then run again |
| Build fails downloading `python` / `eclipse-temurin` | No internet / proxy → retry, check network |
| Page doesn't open | `docker ps` (is it running?) and `docker logs java-app` |

## Conclusion
We containerized a Flask app and a Java application using Dockerfiles, built Docker images, ran them as
containers with port mapping and accessed them in the browser — showing how Docker packages applications
to run the same way on any machine.

## Viva questions
- **Container vs VM?** Containers share the host kernel and are lightweight; VMs include a full guest OS.
- **Image vs container?** Image = read-only template; container = a running instance of an image.
- **RUN vs CMD?** RUN executes while building the image; CMD runs when the container starts.
- **CMD vs ENTRYPOINT?** CMD is a default command that can be overridden; ENTRYPOINT is the fixed executable.
- **What does `-p 8081:8080` mean?** Port 8081 on the PC forwards to port 8080 inside the container.
- **What is Docker Hub?** A public registry to store and share Docker images.
- **What are image layers?** Each Dockerfile instruction creates a cached layer, which makes rebuilds faster.
- **What is a volume?** Storage outside the container so data survives when the container is removed.
