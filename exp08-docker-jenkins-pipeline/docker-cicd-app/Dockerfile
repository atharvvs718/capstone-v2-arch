# Base image with Java 17 JDK
FROM eclipse-temurin:17-jdk

# Working directory inside the container
WORKDIR /app

# Copy source code and compile it
COPY Main.java .
RUN javac Main.java

# The app listens on port 8080
EXPOSE 8080

# Start the Java application
CMD ["java", "Main"]
