.PHONY: all install uchat clean uninstall reinstall

SRCS := $(wildcard src/*.c)
HDRS := $(wildcard inc/*.h)

WFLGS := $(addprefix -W, all extra error pedantic)
GTK_LINK_FLAGS = `pkg-config --cflags  --libs gtk+-3.0`
GTK_INC_FLAGS = `pkg-config --cflags gtk+-3.0`

all: install

install: uchat

uchat:
	@clang -std=c11 $(WFLGS) $(GTK_INC_FLAGS) $(SRCS) $(HDRS) $(GTK_LINK_FLAGS)
	@mv a.out ../$@

clean:
	@rm -rf inc/*.gch

uninstall: clean
	@rm -rf ../uchat

reinstall: uninstall install
