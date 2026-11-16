# Use official Python image
FROM python:3.11-slim

# Set working directory inside the container
WORKDIR /app

# Install dependencies first (cached layer)
COPY requirements.txt requirements.txt
RUN pip install --no-cache-dir -r requirements.txt

# Copy the rest of the app
COPY . .

# Document the port the app listens on
EXPOSE 5000

# Run Flask app
CMD ["python", "app.py"]
