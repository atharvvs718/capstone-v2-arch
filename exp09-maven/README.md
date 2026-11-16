# Experiment 9 — Demonstrating Maven Build Lifecycle for Java Applications

**Aim:** To demonstrate the Maven build lifecycle by compiling, testing and packaging a Java
application using Maven (in VS Code or the command line).

**Ready-made code:** `demo/` — complete Maven project (`pom.xml`, `App.java`, `AppTest.java`).

> **Fixed vs handout:** the handout's `pom.xml` has no `Main-Class`, so its `java -jar` step fails
> with *"no main manifest attribute"*. This `pom.xml` adds the **maven-jar-plugin** with `mainClass`
> and the **surefire 3.2.5** plugin so JUnit 5 tests are definitely run. The handout also runs
> `MyApp-1.0-SNAPSHOT.jar` — the real file name is **`demo-1.0-SNAPSHOT.jar`**.

**Needs:** JDK 17+, Maven, internet (first build downloads plugins). VS Code optional.
No Git needed — Download ZIP works.

---

## Theory (viva)

- **Maven** = build automation + dependency management tool for Java; all config in **`pom.xml`**
  (Project Object Model).
- **Coordinates:** `groupId` (organisation, `com.example`) + `artifactId` (project, `demo`) + `version` (`1.0-SNAPSHOT`).
- **Dependencies** are downloaded from **Maven Central** into the **local repository** `C:\Users\<you>\.m2\repository`.
  `scope test` = only used for tests.
- **3 lifecycles:** **clean** (delete `target/`), **default/build** (compile → package → install), **site** (docs).
- **Default lifecycle phases (in order):**

| Phase | What it does |
|---|---|
| validate | Checks project structure and `pom.xml` |
| compile | Compiles `src/main/java` → `target/classes` |
| test | Runs JUnit tests in `src/test/java` → `target/surefire-reports` |
| package | Creates `target/demo-1.0-SNAPSHOT.jar` |
| verify | Checks the package is valid |
| install | Copies the JAR into the local repo `~/.m2` |
| deploy | Uploads to a remote repository (not used in lab) |

- Running a phase **runs all earlier phases too** — `mvn package` = validate + compile + test + package.
- Each phase is done by a **plugin goal** (compiler plugin, surefire plugin, jar plugin…).
- **SNAPSHOT** = development version, not final release.

---

## Step 1 — Check tools
```
java -version
mvn -version
```
Not installed? → [../00-setup/SETUP.md](../00-setup/SETUP.md) (Maven is just a ZIP + PATH).
In VS Code: Extensions → install **Extension Pack for Java** and **Maven for Java**.

## Step 2 — Get the project

**Option A — use the ready project:** copy `exp09-maven/demo` to `Desktop\demo` and open it in VS Code
(*File → Open Folder*), or just `cd` into it in cmd.

**Option B — create it like the handout (VS Code):**
1. `Ctrl+Shift+P` → **Maven: Create Maven Project** → **maven-archetype-quickstart** → latest version
2. GroupId `com.example`, ArtifactId `demo` → choose folder → press Enter for the prompts in the terminal
3. Replace `pom.xml`, `App.java`, `AppTest.java` with the files from this folder.

(Command-line equivalent of Option B:
`mvn archetype:generate -DgroupId=com.example -DartifactId=demo -DarchetypeArtifactId=maven-archetype-quickstart -DinteractiveMode=false`)

Structure:
```
demo/
├── pom.xml
└── src/
    ├── main/java/com/example/App.java
    └── test/java/com/example/AppTest.java
```

## Step 3 — Understand the code (examiner may ask)
- `App.java` — prints a message and has `add(a, b)`.
- `AppTest.java` — two JUnit 5 tests: `testApp` and `testAdd` (checks `add(2,3) == 5`).
- `pom.xml` — coordinates, Java 17, JUnit 5 dependencies, surefire + jar plugins.

## Step 4 — Run lifecycle phases one by one (VS Code: Terminal → New Terminal, inside `demo`)
```
mvn clean
mvn validate
mvn compile
mvn test
mvn package
mvn install
```
What to point out after each:

| Command | Look for |
|---|---|
| `mvn clean` | `target` folder deleted · `BUILD SUCCESS` |
| `mvn validate` | `BUILD SUCCESS` (project is valid) |
| `mvn compile` | `Compiling 1 source file` · `target/classes/com/example/App.class` appears |
| `mvn test` | `Tests run: 2, Failures: 0, Errors: 0` · `target/surefire-reports` |
| `mvn package` | `Building jar: ...target\demo-1.0-SNAPSHOT.jar` |
| `mvn install` | `Installing ... to C:\Users\<you>\.m2\repository\com\example\demo\1.0-SNAPSHOT\` |

(First run takes 1–3 min — Maven downloads plugins. Later runs are fast.)

## Step 5 — Run the packaged application
```
java -jar target\demo-1.0-SNAPSHOT.jar
```
Output:
```
Hello from Maven Project!
2 + 3 = 5
```

## Step 6 — Observe the target folder
```
dir /s /b target
```
```
target/
├── classes/com/example/App.class
├── test-classes/com/example/AppTest.class
├── surefire-reports/
└── demo-1.0-SNAPSHOT.jar
```

## Step 7 (optional) — Show a failing test stops the build
In `AppTest.java` change `assertEquals(5, ...)` to `assertEquals(6, ...)` → `mvn package` →
`Tests run: 2, Failures: 1` · **BUILD FAILURE** · no new JAR. Change it back → BUILD SUCCESS.
This shows Maven won't package broken code.

## Screenshots for Moodle
Successful `compile`, `test` (Tests run: 2), `package` (Building jar) · `java -jar` output · `target` folder

---

## Common errors

| Error | Fix |
|---|---|
| `'mvn' is not recognized` | Add Maven `bin` to PATH (see SETUP.md) |
| `JAVA_HOME environment variable is not defined correctly` | `set JAVA_HOME=C:\path\to\jdk` (folder **above** `bin`) |
| `invalid target release: 17` | Your JDK is older than 17 → install JDK 17/21, or change 17 → your version in `pom.xml` |
| `Could not transfer artifact ... repo.maven.apache.org` | No internet / proxy on lab network |
| `no main manifest attribute` | You're using the handout's pom — use this folder's `pom.xml` |
| `Tests run: 0` | Using old surefire — this `pom.xml` already fixes it |

## Conclusion
We used Maven to automate the Java build: `pom.xml` managed dependencies (JUnit 5), and lifecycle
phases validated, compiled, tested, packaged and installed the application, producing an executable
JAR — showing how Maven standardizes builds in a DevOps pipeline.
