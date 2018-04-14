all: clean install_containers

clean:
	rm -rf target

install_containers:
	$(shell mkdir -p target/containers)
	$(MAKE) -C src/containers all
