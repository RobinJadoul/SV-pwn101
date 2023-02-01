ARG INNER
FROM $INNER as builder
ARG CHAL

RUN apt update -y \
    && apt dist-upgrade -y \
    && apt install -y \
        build-essential \
        python3 \
        python3-pip \
        zip \
        make \
        git \
        wget \
        autoconf \
    && rm -rf /var/lib/apt/lists/*

RUN git clone --depth 1 --branch 0.12 https://github.com/NixOS/patchelf \
    && cd patchelf \
    && ./bootstrap.sh \
    && ./configure \
    && make all install \
    && cd .. \
    && rm -rf patchelf

COPY $CHAL/ /mnt/
COPY util/ /util/
RUN /util/builder.sh && rm -rf /util

FROM ubuntu:latest
RUN apt-get -y update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    autoconf \
    bison \
    flex \
    gcc \
    g++ \
    git \
    libprotobuf-dev \
    libnl-route-3-dev \
    libtool \
    make \
    pkg-config \
    protobuf-compiler \
    && rm -rf /var/lib/apt/lists/*


RUN git clone https://github.com/google/nsjail /nsjail && cd /nsjail && make && mv /nsjail/nsjail /bin && rm -rf -- /nsjail

COPY --from=builder / /chroot

EXPOSE 5000
CMD nsjail -Ml --port 5000 --chroot /chroot/ --user 99999 --group 99999 --disable_proc -B /dev/urandom:/dev/urandom -B /dev/null:/dev/null -- /entry
