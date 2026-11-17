# Experiment 10 — Implementing Container Orchestration and Deployment using Kubernetes

**Aim:** To create a Kubernetes cluster, deploy a containerized application (Nginx) using a Deployment,
expose it with a Service, scale it, and verify that it runs.

> **Note:** the YAML in the handout has broken indentation and fails with *"error converting YAML to JSON"*.
> The YAML below is fixed and tested.


## Expected outcome
By the end of this experiment you will have:
- `kubectl get nodes` → **docker-desktop  Ready**.
- `kubectl get pods` → **3 nginx Pods Running** (then 5 after scaling, then back to 3).
- `kubectl get services` → **nginx-service  NodePort  80:30080/TCP**.
- **http://localhost:30080** shows *"Welcome to nginx!"*.
- (Optional) deleting a Pod → Kubernetes recreates it automatically (self-healing).

**You need:** Docker Desktop with Kubernetes enabled. Time: ~25 min (+5 min to enable Kubernetes, + Docker install if missing).

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
- **Kubernetes (K8s)** = open-source **container orchestration** platform: automates deploying, scaling,
  networking and managing containers.
- **Orchestration** = deploying, starting/stopping, scaling, load balancing, service discovery,
  health monitoring and **self-healing** (restarting failed containers).
- **Control Plane:** **API Server** (kubectl talks to it) · **Scheduler** (picks a node for each Pod) ·
  **Controller Manager** (keeps actual state = desired state) · **etcd** (database of cluster state).
- **Worker Node:** **Kubelet** (runs Pods) · **Container runtime** · **Kube-proxy** (networking).
- **Pod** = smallest unit, one or more containers. Pods are temporary; their IPs change.
- **ReplicaSet** keeps N copies of a Pod. **Deployment** manages ReplicaSets (scaling, updates, rollback).
- **Service** = stable address + load balancing to Pods selected by **labels**.
  Types: **ClusterIP** (internal), **NodePort** (port 30000–32767 on the node), **LoadBalancer** (cloud).

---

## Step 1 — Enable Kubernetes
1. Start **Docker Desktop** → wait for **Engine running**.
2. Click the **gear icon (Settings)** → **Kubernetes** → tick **Enable Kubernetes**.
   (If it asks for a cluster type, choose **Kubeadm**.)
3. **Apply & Restart** → **Install** → wait 3–5 minutes until Kubernetes shows **running** (green) at the bottom left.

## Step 2 — Check the cluster
```
kubectl version --client
kubectl config use-context docker-desktop
kubectl cluster-info
kubectl get nodes
```
Expected:
```
NAME             STATUS   ROLES           AGE   VERSION
docker-desktop   Ready    control-plane   2m    v1.3x.x
```
📸

## Step 3 — Create the folder
```
cd /d %USERPROFILE%
mkdir k8s-demo
cd k8s-demo
```

## Step 4 — Create deployment.yaml
`notepad deployment.yaml` → Yes → paste → save:
```yaml
apiVersion: apps/v1
kind: Deployment
metadata:
  name: nginx-deployment
  labels:
    app: nginx
spec:
  replicas: 3
  selector:
    matchLabels:
      app: nginx
  template:
    metadata:
      labels:
        app: nginx
    spec:
      containers:
        - name: nginx
          image: nginx:latest
          ports:
            - containerPort: 80
```
Meaning: run **3 Pods** of `nginx:latest`, each labelled `app: nginx`, listening on port 80.

## Step 5 — Create the Deployment
```
kubectl apply -f deployment.yaml
```
Expected: `deployment.apps/nginx-deployment created`
```
kubectl get deployments
kubectl get pods
```
Wait ~30 seconds (it downloads nginx) and run `kubectl get pods` again until all 3 show **Running**:
```
NAME                                READY   STATUS    RESTARTS   AGE
nginx-deployment-xxxxxxxxx-aaaaa    1/1     Running   0          40s
nginx-deployment-xxxxxxxxx-bbbbb    1/1     Running   0          40s
nginx-deployment-xxxxxxxxx-ccccc    1/1     Running   0          40s
```
📸

## Step 6 — Create service.yaml
`notepad service.yaml` → Yes → paste → save:
```yaml
apiVersion: v1
kind: Service
metadata:
  name: nginx-service
spec:
  type: NodePort
  selector:
    app: nginx
  ports:
    - protocol: TCP
      port: 80
      targetPort: 80
      nodePort: 30080
```
Meaning: send traffic to Pods labelled `app: nginx`, and open it on port **30080** of your PC.

## Step 7 — Create the Service
```
kubectl apply -f service.yaml
kubectl get services
```
Expected:
```
NAME            TYPE        CLUSTER-IP      EXTERNAL-IP   PORT(S)        AGE
kubernetes      ClusterIP   10.96.0.1       <none>        443/TCP        10m
nginx-service   NodePort    10.x.x.x        <none>        80:30080/TCP   5s
```
📸

## Step 8 — Open the application
```
start http://localhost:30080
```
Page shows **"Welcome to nginx!"** ✅ 📸

If it doesn't open, use port-forward instead (keep that cmd window open):
```
kubectl port-forward service/nginx-service 8085:80
```
→ open **http://localhost:8085**

## Step 9 — Verify everything
```
kubectl get all
kubectl describe deployment nginx-deployment
kubectl get pods -o wide
```
`get all` shows the **Pods, Service, Deployment and ReplicaSet**. 📸

## Step 10 — Scale the application
```
kubectl scale deployment nginx-deployment --replicas=5
kubectl get pods
```
5 Pods running. Scale back:
```
kubectl scale deployment nginx-deployment --replicas=3
kubectl get pods
```

## Step 11 (optional, impressive) — Self-healing
```
kubectl get pods
```
Copy one Pod name, then:
```
kubectl delete pod PASTE-POD-NAME-HERE
kubectl get pods
```
A **new Pod** appears automatically (new name, AGE a few seconds) — Kubernetes keeps 3 running.

## Step 12 — Clean up
```
kubectl delete -f service.yaml
kubectl delete -f deployment.yaml
kubectl get all
```

## Screenshots to take
`kubectl get nodes` · `get deployments` · `get pods` · `get services` · nginx page in browser · `get all` · YAML files

---

## If something goes wrong

| Error | Fix |
|---|---|
| `'kubectl' is not recognized` | Docker Desktop not installed, or open a new cmd after installing |
| `Unable to connect to the server` / `connection refused` | Kubernetes not enabled/started → Step 1, wait for green |
| `context "docker-desktop" does not exist` | Kubernetes not enabled in Docker Desktop yet |
| `error converting YAML to JSON` / `mapping values are not allowed` | Indentation broken → copy the YAML again exactly (spaces only, no tabs) |
| Pods `ImagePullBackOff` / `ErrImagePull` | No internet to download nginx → check network → `kubectl describe pod <name>` |
| Pods stuck `Pending` / `ContainerCreating` | Still starting → wait 1 minute |
| `provided port is already allocated` | Change `nodePort: 30080` to `30081` and open that port |
| localhost:30080 not opening | Use the `kubectl port-forward` command in Step 8 |

## Conclusion
We implemented container orchestration with Kubernetes: a Deployment created 3 Nginx Pods, a NodePort Service
exposed them on the PC, and we scaled the application and saw self-healing — showing how Kubernetes automates
deployment, scaling and availability of containers.

## Viva questions
- **What is Kubernetes?** An open-source platform that automates deployment, scaling and management of containers.
- **What is a Pod?** The smallest deployable unit; one or more containers sharing network and storage.
- **Deployment vs ReplicaSet?** ReplicaSet keeps N Pods running; Deployment manages ReplicaSets and adds rolling updates and rollback.
- **Why do we need a Service?** Pod IPs change; a Service gives a stable address and load-balances across Pods.
- **Service types?** ClusterIP (internal), NodePort (30000–32767 on the node), LoadBalancer (cloud).
- **What is etcd?** A key-value database that stores the whole cluster state.
- **What is kubelet?** The agent on each node that starts and monitors Pods.
- **`kubectl apply` vs `create`?** apply creates or updates (declarative); create fails if the object already exists.
- **Docker vs Kubernetes?** Docker builds and runs containers; Kubernetes manages many containers across machines.
