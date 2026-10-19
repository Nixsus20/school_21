FROM debian:bookworm-slim

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    bash gcc make libc6-dev pkg-config check libsubunit-dev libncurses-dev \
    postgresql postgresql-client coreutils diffutils util-linux ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /work
COPY . /work

CMD ["bash", "scripts/in-container.sh"]
