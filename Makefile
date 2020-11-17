.PHONY: all install uninstall reinstall

all: install

install:
	@make -C client/

uninstall:
	@make -C client/ uninstall

retinstall: uninstall install
