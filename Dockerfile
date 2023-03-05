FROM ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive

# For tzdata
ENV TZ=Europe/Madrid

RUN apt-get update && apt-get upgrade -y && apt-get install -y \
    apt-utils \
    gcc \
    g++ \
    cmake \
    git \
    subversion \
    build-essential \
    libc6-dev-i386


CMD ["/bin/bash"]
