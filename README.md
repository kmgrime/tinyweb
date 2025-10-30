# Tinyweb

A minimal HTTP server written in C.

## Features
- Single C file implementation
- Serves static index.html file
- Minimal error handling
- Container ready
- Kubernetes Helm chart included

## Building and Running

Build:
```bash
gcc server.c -o server
```

Run:
```bash
./server
curl http://localhost:8080
```

## Container

Build and run:
```bash
# Build image
podman build -t tinyweb .

# Run on default port 8080
podman run --rm -p 8080:8080 tinyweb

# Or map to port 443 (requires root)
sudo podman run --rm -p 443:8080 tinyweb
```

Test:
```bash
# For default port
curl http://localhost:8080

# For mapped 443 port
curl -k http://localhost:443
```

## Kubernetes

Install using Helm:
```bash
# Build and push your image
podman build -t tinyweb .
podman push tinyweb

# Install
helm install web helm/tinyweb
```

Configuration:
- `image.repository`: Container image location
- `image.tag`: Container image tag (default: latest)
- `replicas`: Number of pods (default: 1)

Notes:
- Server always runs on port 8080 internally
- Podman can map port 8080 to any port (443 requires root)
- Kubernetes service maps port 8080 to 443 externally