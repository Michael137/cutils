all: clean setup install_core install_containers install_utils tags

clean:
	@rm -rf target
	@rm -f tags

setup:
	$(shell mkdir -p target/bin)

install_core:
	$(shell mkdir -p target/core)
	$(MAKE) -C src/core all

install_containers:
	$(shell mkdir -p target/containers)
	$(MAKE) -C src/containers all

install_utils:
	$(shell mkdir -p target/utils)
	$(MAKE) -C src/utils/ll_loop all
	$(MAKE) -C src/utils/lex all

prof_%:
	$(MAKE) -f profile.mk $(MAKECMDGOALS)

.PHONY:
tags:
	@ctags -R
