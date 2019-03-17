FROM ubuntu

RUN apt-get update -qq
RUN apt-get -qq install -y \
  cdecl \
  clang \
  clang-tools \
  lldb \
  make \
  manpages \
  manpages-dev \
  manpages-posix \
  manpages-posix-dev \
  perl \
  valgrind \
  vim \
  && rm -rf /var/lib/apt/lists/*
