BOOK_SRC:=http://man7.org/tlpi/code/download/tlpi-190116-dist.tar.gz
CONTAINER_NAME:=lpi

### Uncomment this to run Clang's static analyzer while building; this makes the build slower.
ANALYZER:=scan-build --status-bugs

### Compiler settings
CC:=clang
CFLAGS :=-std=gnu11 -g -lm -pthread
WARNINGS :=-Weverything -Werror
INCLUDES :=-I common/include
LIBS := common/src/*.c
EXTRA_FLAGS:=-D TEST_OUTPUT
COMPILE:=$(ANALYZER) $(CC) $(CFLAGS) $(WARNINGS) $(EXTRA_FLAGS)

### Valgrind target for memory analysis
VALGRIND := valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42

### Binary cleanup
setup:
	-mkdir bin

clean:
	-rm -r bin/*

### Update source from Kerrisk
update-source:
	-rm -rf tlpi-dist/
	wget http://man7.org/tlpi/code/download/tlpi-190116-dist.tar.gz
	tar -xvzf tlpi-190116-dist.tar.gz
	rm tlpi-190116-dist.tar.gz

### Dockerized Linux workspace for consistent environment
docker-clean:
	-docker stop $(CONTAINER_NAME)
	-docker rm $(CONTAINER_NAME)

image:
	docker pull ubuntu
	docker build . -t $(CONTAINER_NAME)

docker:
	docker run \
	-dt \
	--name $(CONTAINER_NAME) \
	-v `pwd`:/$(CONTAINER_NAME) \
	$(CONTAINER_NAME)

shell:
	docker exec -it $(CONTAINER_NAME) /bin/bash

workspace: docker-clean docker shell


