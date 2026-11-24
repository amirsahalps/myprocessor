mypreprocessor: main.o filutils.o comment_removal.o include_file.o macro_handler.o
	cc main.o filutils.o comment_removal.o include_file.o macro_handler.o -o mypreprocessor

main.o: main.c filutils.h comment_removal.h macro_handler.h
	cc -c main.c
filutils.o:filutils.c filutils.h
	cc -c filutils.c
comment_removal.o:comment_removal.c comment_removal.h
	cc -c comment_removal.c
include_file.o:include_file.c include_file.h filutils.h comment_removal.h
	cc -c include_file.c
macro_handler.o:macro_handler.c macro_handler.h
	cc -c macro_handler.c
clean:
	@rm -vf *.o mypreprocessor
