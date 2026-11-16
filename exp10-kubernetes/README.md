# Experiment 10 — Implementing Container Orchestration and Deployment using Kubernetes

**Aim:** To create a Kubernetes cluster, deploy a containerized application (Nginx) using a
Deployment, expose it with a Service, scale it, and verify it is running.

**Ready-made files:** `deployment.yaml`, `service.yaml`
(fixed — the handout's YAML has broken indentation and fails with `error converting YAML to JSON`).

**Needs:** Docker Desktop with **Kubernetes enabled** (includes `kubectl`), or minikube.
No Git needed — Download ZIP works.

---

## Theory (viva)

- **Kubernetes (K8s)** = open-source **container orchestration** platform — automates deploying,
  scaling, networking and managing containers.
- **Orchestration** = deploying, starting/stopping, scaling, load balancing, service discovery,
  health monitoring and **self-healing** (restarting failed containers).
- **Architecture:**
  - **Control Plane:** **API Server** (front door, `kubectl` talks to it) · **Scheduler** (decides which node
    runs a Pod) · **Controller Manager** (keeps desired state = actual state) · **etcd** (key-value store of cluster state)
  - **Worker Node:** **Kubelet** (agent that runs Pods) · **Container runtime** (containerd/Docker) · **Kube-proxy** (networking)
- **Pod** — smallest deployable unit; one or more containers sharing network + storage. Pods are temporary, IPs change.
- **ReplicaSet** — keeps N copies of a Pod running.
- **Deployment** — manages ReplicaSets; declarative updates, scaling, rollbacks.
- **Service** — stable IP/DNS name + load balancing to Pods chosen by **label selector**.
  Types: **ClusterIP** (internal, default), **NodePort** (port 30000–32767 on each node), **LoadBalancer** (cloud).
- **Declarative:** you describe the desired state in YAML; `kubectl apply` makes the cluster match it.

---

## Step 1 — Start the cluster
**Docker Desktop → Settings (gear) → Kubernetes → Enable Kubernetes → Apply & Restart.**
Wait until the bottom-left shows Kubernetes **running** (green), 3–5 min first time.

(minikube instead: `minikube start` — wait for *Done!*)

## Step 2 — Verify kubectl and the cluster
```
kubectl version --client
kubectl cluster-info
kubectl get nodes
```
Expected: `docker-desktop   Ready   control-plane ...` (or `minikube   Ready`). 📸 Screenshot

## Step 3 — Go to the folder with the YAML files
```
cd capstone-v2-arch\exp10-kubernetes
type deployment.yaml
type service.yaml
```
(Or create them yourself: `notepad deployment.yaml`, paste, save — **YAML uses spaces, never tabs**.)

`deployment.yaml` — Deployment `nginx-deployment`, **3 replicas** of `nginx:latest`, label `app: nginx`, port 80.
`service.yaml` — Service `nginx-service`, type **NodePort**, selects `app: nginx`, port 80 → nodePort **30080**.

## Step 4 — Create the Deployment
```
kubectl apply -f deployment.yaml
```
→ `deployment.apps/nginx-deployment created`
```
kubectl get deployments
kubectl get pods
```
Wait until `READY 3/3` and all 3 Pods show `Running` (first time pulls the nginx image, ~30 s).
Add `-w` to watch live: `kubectl get pods -w` (Ctrl+C to stop). 📸

## Step 5 — Create the Service
```
kubectl apply -f service.yaml
kubectl get services
```
```
NAME            TYPE       CLUSTER-IP     PORT(S)        AGE
nginx-service   NodePort   10.x.x.x       80:30080/TCP   5s
```
📸

## Step 6 — Access the application
- **Docker Desktop:** browser → **http://localhost:30080** → *"Welcome to nginx!"* 📸
- **minikube:** `minikube service nginx-service --url` → open the printed URL
- If neither works: `kubectl port-forward service/nginx-service 8080:80` → http://localhost:8080

## Step 7 — Verify everything
```
kubectl get all
kubectl describe deployment nginx-deployment
kubectl get pods -o wide
```
`get all` shows Pods, Service, Deployment and ReplicaSet. 📸

## Step 8 — Scale the application
```
kubectl scale deployment nginx-deployment --replicas=5
kubectl get pods
```
5 Pods running. Scale back:
```
kubectl scale deployment nginx-deployment --replicas=3
kubectl get pods
```

## Step 9 (optional, impressive) — Self-healing
```
kubectl get pods
kubectl delete pod <copy-one-pod-name>
kubectl get pods
```
A **new** Pod is created automatically (new name, small AGE) — the Deployment keeps 3 running.

## Step 10 (optional) — Rolling update and rollback
```
kubectl set image deployment/nginx-deployment nginx=nginx:1.25
kubectl rollout status deployment/nginx-deployment
kubectl rollout history deployment/nginx-deployment
kubectl rollout undo deployment/nginx-deployment
```

## Step 11 — Clean up
```
kubectl delete -f deployment.yaml
kubectl delete -f service.yaml
kubectl get all
```

---

## Common errors

| Error | Fix |
|---|---|
| `Unable to connect to the server` / `connection refused` | Kubernetes not running — enable it in Docker Desktop / `minikube start` |
| `error converting YAML to JSON` / `mapping values are not allowed` | Indentation broken or tabs used — use this folder's files |
| Pods `ImagePullBackOff` / `ErrImagePull` | No internet to pull nginx — check network; `kubectl describe pod <name>` |
| Pods stuck `Pending` | Cluster still starting / low resources — wait, `kubectl describe pod <name>` |
| `provided port is already allocated` (30080) | Change `nodePort` to 30081 or delete the old service |
| localhost:30080 not opening on minikube | Use `minikube service nginx-service --url` |
| `kubectl` points to a different cluster | `kubectl config get-contexts` → `kubectl config use-context docker-desktop` |

## Conclusion
We implemented container orchestration with Kubernetes: a Deployment ran 3 Nginx Pods, a NodePort
Service exposed them, and we scaled the application and observed self-healing — showing how
Kubernetes automates deployment, scaling and availability of containerized applications.
