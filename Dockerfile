FROM ubuntu

RUN apt-get update -qq
RUN apt-get -qq install -y \
  cdecl \
  clang \
  clang-tools \
  lldb \
  make \
  perl \
  valgrind \
  vim \
  && rm -rf /var/lib/apt/lists/*
