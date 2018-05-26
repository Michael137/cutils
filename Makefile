all: clean install_containers

clean:
	rm -rf target

install_containers:
	$(shell mkdir -p target/containers)
	$(MAKE) -C src/containers all

install_utils:
	$(shell mkdir -p target/bin)
	$(MAKE) -C src/utils all
