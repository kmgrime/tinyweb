FROM alpine:latest
RUN apk add --no-cache gcc musl-dev
WORKDIR /app
COPY . .
RUN gcc server.c -o server
EXPOSE 8080
CMD ["./server"]
