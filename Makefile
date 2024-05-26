# sfetch - suckless fetching utility

.POSIX:

include config.mk

all: sgpasswd

config.h:
	cp config.def.h config.h

sgpasswd: $(SRC)
	$(CC) $(SRC) -o sgpasswd
	
install: sgpasswd
	cp $(TARGETBIN) $(DESTDIR)

clean:
	rm -rf $(TARGETBIN)

uninstall:
	rm $(DESTDIR)/sgpasswd
