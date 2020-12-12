.PHONY: all install uchat clean uninstall reinstall

dirs := src src/events src/configure src/tools src/create
SRCS := $(foreach dir, $(dirs), $(wildcard $(dir)/*.c))
HDRS := $(wildcard inc/*.h)

WFLGS := $(addprefix -W, all extra error pedantic) \
	-Wno-unused-command-line-argument -Wno-unused-variable \
    -Wno-unused-function -Wno-unused-parameter
GTK_LINK_FLAGS = `pkg-config --cflags  --libs gtk+-3.0`
GTK_INC_FLAGS = `pkg-config --cflags gtk+-3.0`

all: install

install: uchat

uchat:
	@clang -lsqlite3 -lpthread $(WFLGS) $(GTK_INC_FLAGS) $(SRCS) $(HDRS) $(GTK_LINK_FLAGS)
	@mv a.out ../$@

clean:
	@rm -rf inc/*.gch

uninstall: clean
	@rm -rf ../uchat

reinstall: uninstall install
