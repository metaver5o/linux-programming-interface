# Book source link
BOOK_SRC:=http://man7.org/tlpi/code/download/tlpi-190116-dist.tar.gz

### Uncomment this to run Clang's static analyzer while building; this makes the build slower.
ANALYZER:=scan-build --status-bugs

### Compiler settings
CC:=clang
CFLAGS :=-std=gnu11 -g -lm
WARNINGS :=-Weverything -Werror
INCLUDES :=-I common/include
LIBS := common/src/*.c
EXTRA_FLAGS:=-D TEST_OUTPUT
COMPILE:=$(ANALYZER) $(CC) $(CFLAGS) $(WARNINGS) $(EXTRA_FLAGS) $(INCLUDES) $(LIBS)

### Valgrind target for memory analysis
VALGRIND := valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42

### Update source from Kerrisk
update-source:
	rm -rf tlpi-dist/
	wget http://man7.org/tlpi/code/download/tlpi-190116-dist.tar.gz
	tar -xvzf tlpi-190116-dist.tar.gz
	rm tlpi-190116-dist.tar.gz


### Binary cleanup
setup:
	-mkdir bin

clean:
	-rm -r bin/*

CONTAINER_NAME:=lpi

### Dockerized Linux workspace for consistent environment
docker-clean:
	-docker stop $(CONTAINER_NAME)
	-docker rm $(CONTAINER_NAME)

docker: docker-clean
	docker pull $(CONTAINER_NAME)
	docker run \
	-dt \
	--name $(CONTAINER_NAME) \
	-v `pwd`:/$(CONTAINER_NAME) \
	$(CONTAINER_NAME)
	docker exec $(CONTAINER_NAME) apt-get update
	docker exec $(CONTAINER_NAME) apt-get install -y make valgrind clang clang-tools cdecl perl

shell:
	docker exec -it $(CONTAINER_NAME) /bin/bash

workspace: docker-clean docker shell


