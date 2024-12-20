make: 
	gcc src/bubble_sort.c utils/utils.c -o target/bubble_sort
	gcc src/queue.c utils/utils.c -o target/queue.c

run: 
	make
	printf "\nrunning binaries...\n"
	./target/bubble_sort && printf "\n"
	./target/queue.c && printf "\n"
