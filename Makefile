.PHONY: all uchat uninstall clean reinstall

SRCS := $(wildcard src/*.c)
HDRS := $(wildcard inc/*.h)

all: uchat

uchat:
	@clang -std=c11 -Wall -Wextra -Werror -Wpedantic ${SRCS} ${HDRS}
	@mv a.out uchat

uninstall: clean
	@rm -rdf inc/*.gch

clean:
	@rm -rdf uchat

reinstall: uninstall uchat
