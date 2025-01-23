install:
	cc -o autosec autosec.c \
		-Wall -Wno-deprecated-declarations \
		-L/home/sergey/stuff/archive/code/autosec/lib/libical/lib \
		-I/home/sergey/stuff/archive/code/autosec/lib/libical/include/libical \
		-lical -licalss

debug:
	cc -o autosec autosec.c \
		-Wall -Wno-deprecated-declarations \
		-L/home/mrmine/prg/autosec/lib/libical/lib \
		-I/home/mrmine/prg/autosec/lib/libical/include/libical \
		-lical -licalss -g -fsanitize=address 

clean:
	rm -v events_00.ics events_02.ics sessions.ics autosec

uninstall:
	rm -v autosec
