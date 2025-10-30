FROM ubuntu:22.04

# Install build tools and debugging utilities
RUN apt-get update && \
    apt-get install -y \
    gcc \
    net-tools \
    iproute2 \
    curl \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Copy only necessary files
COPY server.c index.html ./

# Build the server
RUN gcc server.c -o server

# Expose the port
EXPOSE 8080

# Run with bash to allow debugging
CMD ["./server"]
