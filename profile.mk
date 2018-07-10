.PHONY:
prof_test_hashmap:
	./target/containers/test_hashmap
	gprof ./target/containers/test_hashmap gmon.out

.PHONY:
prof_test_linkedlist:
	./target/containers/test_linked_list
	gprof ./target/containers/test_linked_list gmon.out

.PHONY:
prof_utils_ll_loop:
	./target/bin/test_ll_loop
	gprof ./target/bin/test_ll_loop gmon.out

.PHONY:
prof_utils_lex:
	./target/bin/test_fa
	gprof ./target/bin/test_fa gmon.out

.PHONY:
prof_core_hash:
	./target/core/test_hash
	gprof ./target/core/test_hash gmon.out
