all: clean install_containers install_utils tags

clean:
	@rm -rf target
	@rm -f tags

install_containers:
	$(shell mkdir -p target/containers)
	$(MAKE) -C src/containers all

install_utils:
	$(shell mkdir -p target/bin)
	$(shell mkdir -p target/utils)
	$(MAKE) -C src/utils/ll_loop all
	$(MAKE) -C src/utils/lex all

.PHONY:
tags:
	@ctags -R
