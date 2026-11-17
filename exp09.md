# Experiment 9 — Demonstrating Maven Build Lifecycle for Java Applications

**Aim:** To demonstrate the Maven build lifecycle by compiling, testing and packaging a Java application using Maven.


> **Note:** the handout's `pom.xml` doesn't set a main class, so its `java -jar` step fails with
> *"no main manifest attribute"*, and it runs `MyApp-1.0-SNAPSHOT.jar`, which doesn't exist.
> The `pom.xml` below fixes both. The real JAR is `demo-1.0-SNAPSHOT.jar`.


## Expected outcome
By the end of this experiment you will have:
- `mvn compile` → `BUILD SUCCESS` and `target\classes\com\example\App.class` created.
- `mvn test` → **`Tests run: 2, Failures: 0, Errors: 0, Skipped: 0`**.
- `mvn package` → **`target\demo-1.0-SNAPSHOT.jar`** created.
- `mvn install` → JAR copied into `C:\Users\<you>\.m2\repository\com\example\demo\1.0-SNAPSHOT\`.
- `java -jar target\demo-1.0-SNAPSHOT.jar` prints `Hello from Maven Project!` and `2 + 3 = 5`.

**You need:** Java 21, Maven, internet. Time: ~20 min (first build downloads plugins) (+10 min installs).

---

## Step 0 — Install everything (on a PC that has nothing)
Open **Command Prompt**: press `Win + R` → type `cmd` → Enter.
Do each part below. If the *Check* command already works, skip that part.

### 0.A — Java 21 (JDK)
Check in cmd: `java -version` and `javac -version` → if both show **17** or higher, skip.

1. Browser → **https://adoptium.net/temurin/releases/** → Operating System **Windows**, Architecture **x64**,
   Package Type **JDK**, Version **21 - LTS** → download the **.msi**.
2. Open it → **Next** → on the *Custom Setup* screen click **Set JAVA_HOME variable** → choose
   **Will be installed on local hard drive** (Add to PATH is already on) → **Next** → **Install** → **Yes** → **Finish**.
3. **Close cmd and open a new one**, then check:
```
java -version
javac -version
```
Both should say `21`.

**No admin rights?** On the same page download the **.zip** instead → right-click → **Extract All** → extract to
`C:\Users\YOUR-USERNAME\` → it makes a folder like `jdk-21.0.x+y`. In every new cmd window run (use the real folder name):
```
set JAVA_HOME=%USERPROFILE%\jdk-21.0.5+11
set PATH=%JAVA_HOME%\bin;%PATH%
java -version
```

### 0.B — Maven (no install needed — just a ZIP)
Check in cmd: `mvn -version` → if it prints `Apache Maven 3.x`, skip.

1. Browser → **https://maven.apache.org/download.cgi** → in the Files table click the **Binary zip archive** link
   (`apache-maven-3.9.x-bin.zip`).
2. Downloads → right-click the zip → **Extract All** → change the path to `C:\Users\YOUR-USERNAME\` → **Extract**.
   It makes a folder like `C:\Users\YOUR-USERNAME\apache-maven-3.9.11`.
3. In cmd, find the exact folder name, then add it to PATH (use your real version number):
```
dir %USERPROFILE%\apache-maven*
set PATH=%USERPROFILE%\apache-maven-3.9.11\bin;%PATH%
mvn -version
```
`mvn -version` must print **Apache Maven 3.9.x** and **Java version: 21** (or 17).
The `set PATH` only lasts for that cmd window — run it again if you open a new window.

If it says **JAVA_HOME environment variable is not defined correctly**:
```
dir "C:\Program Files\Eclipse Adoptium"
set JAVA_HOME=C:\Program Files\Eclipse Adoptium\jdk-21.0.5.11-hotspot
mvn -version
```
(use the real folder name shown by `dir` — the folder that contains `bin`)

---

## Theory (short)
- **Maven** = build automation and dependency management tool for Java. Everything is configured in **`pom.xml`** (Project Object Model).
- **Coordinates (GAV):** `groupId` (com.example) + `artifactId` (demo) + `version` (1.0-SNAPSHOT).
- Dependencies are downloaded from **Maven Central** into the local repository **`C:\Users\<you>\.m2\repository`**.
- **3 lifecycles:** **clean** (delete `target`), **default** (build), **site** (documentation).
- **Default lifecycle phases, in order:**

| Phase | What it does |
|---|---|
| validate | Checks the project structure and pom.xml |
| compile | Compiles `src/main/java` into `target/classes` |
| test | Runs JUnit tests from `src/test/java` |
| package | Creates `target/demo-1.0-SNAPSHOT.jar` |
| verify | Checks the package is valid |
| install | Copies the JAR into the local repo `.m2` |
| deploy | Uploads to a remote repository (not used in lab) |

- Running a phase also runs **all phases before it** (`mvn package` = validate + compile + test + package).

---

## Step 1 — Check Java and Maven (in the same cmd window where you ran `set PATH`)
```
java -version
mvn -version
```
Both must work. If `mvn` is not recognized → redo the `set PATH=...` line from Step 0.B in this window.

## Step 2 — Create the Maven project structure
```
cd /d %USERPROFILE%
mkdir demo
cd demo
mkdir src\main\java\com\example
mkdir src\test\java\com\example
```

## Step 3 — Create pom.xml
`notepad pom.xml` → Yes → paste → save:
```xml
<project xmlns="http://maven.apache.org/POM/4.0.0"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://maven.apache.org/POM/4.0.0 http://maven.apache.org/xsd/maven-4.0.0.xsd">
  <modelVersion>4.0.0</modelVersion>

  <groupId>com.example</groupId>
  <artifactId>demo</artifactId>
  <version>1.0-SNAPSHOT</version>
  <packaging>jar</packaging>

  <properties>
    <maven.compiler.source>17</maven.compiler.source>
    <maven.compiler.target>17</maven.compiler.target>
    <project.build.sourceEncoding>UTF-8</project.build.sourceEncoding>
  </properties>

  <dependencies>
    <dependency>
      <groupId>org.junit.jupiter</groupId>
      <artifactId>junit-jupiter-api</artifactId>
      <version>5.9.3</version>
      <scope>test</scope>
    </dependency>
    <dependency>
      <groupId>org.junit.jupiter</groupId>
      <artifactId>junit-jupiter-engine</artifactId>
      <version>5.9.3</version>
      <scope>test</scope>
    </dependency>
  </dependencies>

  <build>
    <plugins>
      <!-- Runs JUnit 5 tests in the test phase -->
      <plugin>
        <groupId>org.apache.maven.plugins</groupId>
        <artifactId>maven-surefire-plugin</artifactId>
        <version>3.2.5</version>
      </plugin>
      <!-- Adds Main-Class to the JAR so java -jar works -->
      <plugin>
        <groupId>org.apache.maven.plugins</groupId>
        <artifactId>maven-jar-plugin</artifactId>
        <version>3.3.0</version>
        <configuration>
          <archive>
            <manifest>
              <mainClass>com.example.App</mainClass>
            </manifest>
          </archive>
        </configuration>
      </plugin>
    </plugins>
  </build>
</project>
```

## Step 4 — Create the Java source file
`notepad src\main\java\com\example\App.java` → Yes → paste → save:
```java
package com.example;

public class App {

    public static int add(int a, int b) {
        return a + b;
    }

    public static void main(String[] args) {
        System.out.println("Hello from Maven Project!");
        System.out.println("2 + 3 = " + add(2, 3));
    }
}
```

## Step 5 — Create the test file
`notepad src\test\java\com\example\AppTest.java` → Yes → paste → save:
```java
package com.example;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

public class AppTest {

    @Test
    public void testApp() {
        assertTrue(true);
    }

    @Test
    public void testAdd() {
        assertEquals(5, App.add(2, 3));
    }
}
```
Check the structure:
```
tree /f
```
```
demo
│   pom.xml
└───src
    ├───main\java\com\example\App.java
    └───test\java\com\example\AppTest.java
```

## Step 6 — Run the lifecycle phases one by one
Run each, and take a screenshot of the important ones:
```
mvn clean
```
→ `BUILD SUCCESS` (deletes `target`). First run downloads plugins — takes 1–3 minutes.
```
mvn validate
```
→ `BUILD SUCCESS` (project structure is valid)
```
mvn compile
```
→ `Compiling 1 source file` · `BUILD SUCCESS` 📸
```
mvn test
```
→ `Tests run: 2, Failures: 0, Errors: 0, Skipped: 0` · `BUILD SUCCESS` 📸
```
mvn package
```
→ `Building jar: ...\target\demo-1.0-SNAPSHOT.jar` · `BUILD SUCCESS` 📸
```
mvn install
```
→ `Installing ... to C:\Users\...\.m2\repository\com\example\demo\1.0-SNAPSHOT\...` · `BUILD SUCCESS`

## Step 7 — Run the packaged JAR
```
java -jar target\demo-1.0-SNAPSHOT.jar
```
Output:
```
Hello from Maven Project!
2 + 3 = 5
```
📸

## Step 8 — Observe the target folder
```
tree /f target
```
You'll see `classes\com\example\App.class`, `test-classes\com\example\AppTest.class`,
`surefire-reports\` and `demo-1.0-SNAPSHOT.jar`. 📸

## Step 9 (optional) — Show that a failing test stops the build
`notepad src\test\java\com\example\AppTest.java` → change `assertEquals(5,` to `assertEquals(6,` → save →
```
mvn package
```
→ `Tests run: 2, Failures: 1` · **BUILD FAILURE** → no JAR is made. Change it back to 5 → `mvn package` → BUILD SUCCESS.

## Doing it in VS Code instead (if the examiner asks)
Open the `demo` folder: **File → Open Folder** → `C:\Users\<you>\demo`.
Install extensions **Extension Pack for Java** and **Maven for Java**.
**Terminal → New Terminal** → run the same `mvn` commands from Step 6.
(Creating the project the handout way: `Ctrl+Shift+P` → **Maven: Create Maven Project** → **maven-archetype-quickstart** →
GroupId `com.example`, ArtifactId `demo` → then replace the generated `pom.xml`, `App.java`, `AppTest.java` with the ones above.)

---

## If something goes wrong

| Error | Fix |
|---|---|
| `'mvn' is not recognized` | Do the Maven ZIP + `set PATH=...` from Step 1 |
| `JAVA_HOME environment variable is not defined correctly` | `set JAVA_HOME=<your JDK folder>` (the folder containing `bin`) |
| `invalid target release: 17` / `release version 17 not supported` | Java older than 17 → install Java 17/21 |
| `Could not transfer artifact ... repo.maven.apache.org` | No internet / proxy on the lab network |
| `no main manifest attribute` | You used the handout's pom → use the pom.xml above |
| `Tests run: 0` | Use the pom.xml above (it has the surefire plugin) |
| `package com.example does not exist` / file not found | File is in the wrong folder → check with `tree /f` |

## Conclusion
We used Maven to automate the Java build process: pom.xml managed the JUnit dependency, and the lifecycle
phases validated, compiled, tested, packaged and installed the application, producing a runnable JAR —
showing how Maven standardises and automates builds.

## Viva questions
- **What is Maven?** A build automation and dependency management tool for Java projects.
- **What is pom.xml?** Project Object Model — the configuration file with project info, dependencies and plugins.
- **What is GAV?** groupId, artifactId, version — uniquely identifies a project.
- **Name the default lifecycle phases.** validate, compile, test, package, verify, install, deploy.
- **What happens when you run `mvn package`?** All earlier phases (validate, compile, test) run first, then the JAR is made.
- **install vs deploy?** install copies the JAR to the local `.m2` repo; deploy uploads it to a remote repository.
- **What is SNAPSHOT?** A development (not final) version.
- **What is `<scope>test</scope>`?** The dependency is used only for compiling and running tests.
- **Maven vs Gradle?** Maven uses XML and fixed conventions; Gradle uses Groovy/Kotlin scripts and is faster for incremental builds.
