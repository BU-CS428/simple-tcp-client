FROM debian:latest

USER root

ARG DEBIAN_FRONTEND=noninteractive

RUN apt upgrade && apt update
RUN apt install -y build-essential \
                       libssl-dev \
                       cmake \
                       wget \
                       clang-format \
                       gdb \
                       python3 \
                       python3-pip \
                       autotools-dev \
                       libicu-dev \
                       libbz2-dev \
                       tcpdump \
                       net-tools \
                       git

EXPOSE 8080