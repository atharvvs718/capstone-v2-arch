# Experiment 1 — Introduction to DevOps: Culture, Principles and Benefits

**Aim:** To understand the culture, principles and benefits of DevOps.

This is a **theory experiment** — no software needed. If you get it, you'll write/explain it
and probably be asked viva questions. Learn the points below.

---

## What is DevOps?

- DevOps = **Dev**elopment + **Op**eration**s**.
- A **culture** where development and operations teams work together across the whole
  application lifecycle — development, testing, deployment and operations.
- Removes the gap between developers, QA (testers) and system administrators.
- Goal: deliver code to production **faster**, in an **automated and repeatable** way.

## DevOps lifecycle (the infinity loop — draw this)

```
   PLAN → CODE → BUILD → TEST → RELEASE → DEPLOY → OPERATE → MONITOR
     ↑                                                        │
     └──────────────────── feedback ──────────────────────────┘
```
(Your lab handout's version: Plan → Code → Build → Test → Package → Release → Operate → Monitor)

| Stage | What happens | Tool example |
|---|---|---|
| Plan | Requirements, tasks | Jira |
| Code | Write code, version control | Git, GitHub |
| Build | Compile, package | Maven, Gradle |
| Test | Automated testing | JUnit, Selenium |
| Release/Deploy | Ship to servers | Jenkins, Docker |
| Operate | Run and manage | Kubernetes |
| Monitor | Logs, metrics, alerts | Prometheus, Grafana |

## Dev vs Ops

- **Development:** design, code and develop.
- **Operations:** manage servers, check security, scaling and backup.
- **Technology** connects them, with a **feedback loop** from Ops back to Dev.

## DevOps principles (CALMS)

| Principle | Meaning | Examples |
|---|---|---|
| **C**ulture | Cross-functional, autonomous teams; failure seen as learning | Working out loud, "tell it like it is" |
| **A**utomation | Automate testing, config, infrastructure, deployment | Test automation, CI/CD pipelines, Kubernetes |
| **L**ean | Deliver small chunks fast, remove waste, fail early | Continuous Delivery, Agile |
| **M**easurement | "You can only improve what you measure" | DORA metrics, MTBF, MTTR |
| **S**haring | Break knowledge silos, share success and failures | Show & tell, pair programming |

### Culture shift (from → to)

| From | To |
|---|---|
| Functional silos | Cross-functional teams |
| Heteronomy (told what to do) | Autonomy |
| Avoiding risk and failure | Failure as a learning opportunity |
| "Never revise" policy | Continuous process review |
| Project thinking | Product mindset |

### Key metrics

- **DORA metrics:** deployment frequency, lead time for changes, change failure rate, time to restore service
- **MTBF** — Mean Time Between Failures (higher = better)
- **MTTR** — Mean Time To Repair/Recover (lower = better)

## Benefits of DevOps

- Faster, better product delivery
- Faster issue resolution, reduced complexity
- Greater scalability and availability
- More stable operating environments
- Better resource utilization
- Greater automation
- Greater visibility into system outcomes, more innovation

## DevOps toolchain used in this lab

Git/GitHub (Exp 2–4) → Jenkins CI/CD (Exp 5–6) → Docker (Exp 7–8) → Maven (Exp 9) → Kubernetes (Exp 10)

## Conclusion

DevOps is a culture and set of practices that unites development and operations through
collaboration, automation, lean delivery, measurement and sharing — resulting in faster,
more reliable and more frequent software releases.
