.PHONY: all install uchat clean uninstall reinstall

SRCS := $(wildcard src/*.c)
HDRS := $(wildcard inc/*.h)

WFLGS := $(addprefix -W, all extra error pedantic) \
	-Wno-unused-command-line-argument -Wno-unused-variable \
    -Wno-unused-function -Wno-unused-parameter -g3 -fsanitize=address,undefined \
    -fno-omit-frame-pointer -O0

all: install

install: uchat_server

uchat_server:
	@clang -std=c11 $(WFLGS) $(SRCS) $(HDRS)
	@mv a.out ../$@

clean:
	@rm -rf inc/*.gch

uninstall: clean
	@rm -rf ../uchat_server

reinstall: uninstall install
