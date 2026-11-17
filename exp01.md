# Experiment 1 — Introduction to DevOps: Culture, Principles and Benefits

**Aim:** To understand the culture, principles and benefits of DevOps.

**This is a theory experiment — no software, no commands.** Write/explain the points below.


## Expected outcome
By the end of this experiment you will have:
- A written answer / explanation covering: what DevOps is, the DevOps lifecycle diagram (Plan → … → Monitor), the CALMS principles, culture change table, metrics (DORA, MTTR, MTBF) and benefits.
- Ability to answer the viva questions at the bottom.

**You need:** Nothing — theory only.

---

## 1. What is DevOps?

- DevOps = **Dev**elopment + **Op**eration**s**.
- It is a **culture** where development and operations teams work together.
- One team handles the whole application lifecycle: development → testing → deployment → operations.
- It reduces the gap between **developers, QA (testers) and system administrators**.
- Goal: deliver code to production **faster**, in an **automated and repeatable** way.
- Helps organizations deliver applications faster, serve customers better and compete more strongly.

## 2. DevOps lifecycle (draw this as an infinity loop)

```
  PLAN → CODE → BUILD → TEST → PACKAGE → RELEASE → OPERATE → MONITOR
    ↑                                                          │
    └─────────────────────── feedback ─────────────────────────┘
```

| Stage | What happens | Tool example |
|---|---|---|
| Plan | Decide features and tasks | Jira |
| Code | Write code, version control | Git, GitHub |
| Build | Compile and package | Maven |
| Test | Automated tests | JUnit, Selenium |
| Release / Deploy | Ship to servers | Jenkins, Docker |
| Operate | Run and manage the app | Kubernetes |
| Monitor | Logs, metrics, alerts | Prometheus, Grafana |

## 3. Development vs Operations

```
          ┌──────────── Feedback loop ─────────────┐
          ↓                                         │
   [ Development ] ──── [ Technology ] ──── [ Operations ]
     - Design                                  - Manage servers
     - Code & develop                          - Check security
                                               - Scaling & backup
```

## 4. DevOps principles — CALMS

| Principle | Meaning | Examples |
|---|---|---|
| **C**ulture | Cross-functional, trusted, autonomous teams; failure = learning | Working out loud, screw-up nights, "tell it like it is" |
| **A**utomation | Automate testing, configuration, infrastructure, operations | Test automation, CI/CD pipelines, automated alert remediation, Kubernetes |
| **L**ean | Deliver fast in small chunks, remove waste, fail early, continuous improvement | Continuous Delivery, Agile |
| **M**easurement | "You can only improve what you measure" — data-driven decisions | DORA metrics, MTBF, MTTR |
| **S**haring | Break knowledge silos, share success and failure | Team celebrations, show & tell, pair programming |

### Culture change (From → To)

| From | To |
|---|---|
| Functional silos | Cross-functional teams |
| Heteronomy | Autonomy |
| Avoiding risk and failure | Seeing failure as a learning opportunity |
| "Never revise" policy | Continuous process review |
| Project thinking | Product mindset |

### Metrics to remember
- **DORA metrics:** deployment frequency, lead time for changes, change failure rate, time to restore service.
- **MTBF** — Mean Time Between Failures (higher is better).
- **MTTR** — Mean Time To Repair (lower is better).

## 5. Benefits of DevOps

- Faster, better product delivery
- Faster issue resolution and reduced complexity
- Greater scalability and availability
- More stable operating environments
- Better resource utilization
- Greater automation
- Greater visibility into system outcomes and greater innovation

## 6. Tools used in this lab
Git & GitHub (Exp 2–4) → Jenkins (Exp 5–6) → Docker (Exp 7–8) → Maven (Exp 9) → Kubernetes (Exp 10)

## Conclusion
DevOps is a culture that unites development and operations through collaboration, automation,
lean delivery, measurement and sharing, resulting in faster and more reliable software delivery.

---

## Viva questions
- **What is DevOps?** A culture and set of practices that combine development and operations to deliver software faster and more reliably using collaboration and automation.
- **Why DevOps?** Removes silos between teams, automates repetitive work, gives faster releases and quicker bug fixes.
- **Name the DevOps principles.** CALMS — Culture, Automation, Lean, Measurement, Sharing.
- **What is CI/CD?** Continuous Integration (auto build + test on every push) and Continuous Delivery/Deployment (auto release).
- **What is MTTR?** Mean Time To Repair — average time to recover from a failure.
- **DevOps vs Agile?** Agile improves development speed; DevOps extends it to deployment and operations.
