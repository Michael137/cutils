define PROF_FN
	@$(1) && \
	if [[ ! -f "gmon.out" ]]; then \\
		echo "gmon.out does not exist. Were the sources compiled with the -pg flag?" \\
		echo "Try: PROFILE=1 make clean all" \\
	fi && \
	gprof $(1) gmon.out
endef

.PHONY:
prof_test_hashmap:
	$(call PROF_FN, target/containers/test_hashmap)

.PHONY:
prof_test_linkedlist:
	$(call PROF_FN, target/containers/test_linked_list)

.PHONY:
prof_utils_ll_loop:
	$(call PROF_FN, target/bin/test_ll_loop)

.PHONY:
prof_utils_lex:
	$(call PROF_FN, target/bin/test_fa)

.PHONY:
prof_core_hash:
	$(call PROF_FN, target/core/test_hash)
