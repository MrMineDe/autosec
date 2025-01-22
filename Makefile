install:
	cc -o autosec autosec.c -Wall -Wno-deprecated-declarations -L/home/mrmine/prg/autosec/lib/libical/lib -I/home/mrmine/prg/autosec/lib/libical/include/libical -lical -licalss -g
debug:
	cc -o autosec autosec.c -Wall -Wno-deprecated-declarations -L/home/mrmine/prg/autosec/lib/libical/lib -I/home/mrmine/prg/autosec/lib/libical/include/libical -lical -licalss -g -fsanitize=address 
clean:
	rm events_00.ics events_02.ics sessions.ics autosec
uninstall:
	rm autosec
