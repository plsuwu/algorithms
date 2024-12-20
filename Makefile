run: compile
	printf "\nrunning binaries...\n"
	./target/bubble_sort && printf "\n"
	./target/queue && printf "\n"
	./target/stack && printf "\n"
	./target/quicksort && printf "\n"
	./target/double_linked_list && printf "\n"

compile: target_dir
	gcc src/bubble_sort.c utils/utils.c -o target/bubble_sort
	gcc src/queue.c utils/utils.c -o target/queue
	gcc src/stack.c utils/utils.c -o target/stack 
	gcc src/quicksort.c utils/utils.c -o target/quicksort
	gcc src/double_linked_list.c -o target/double_linked_list

target_dir:
	rm -r ./target
	mkdir ./target
