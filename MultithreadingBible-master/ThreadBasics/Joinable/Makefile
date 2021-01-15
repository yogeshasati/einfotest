joinablethread:joinable_example.o
	gcc -g  joinable_example.o -o joinablethread -lpthread
joinable_example.o:joinable_example.c
	@gcc -g -c joinable_example.c -o joinable_example.o
clean:
	@rm -f joinable_example.o
	rm joinablethread
