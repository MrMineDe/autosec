install:
	cc -o autosec autosec.c -Wall -L/home/mrmine/prg/autosec/lib/libical/lib -I/home/mrmine/prg/autosec/lib/libical/include/libical -lical -licalss -g
uninstall:
	rm autosec
