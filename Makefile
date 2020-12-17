.PHONY: all install uninstall reinstall

all: install

install:
	@make -C libraries/libmx
	@make -C client/

uninstall:
	@make -C client/ uninstall

	@make -C libraries/libmx uninstall

reinstall: uninstall install
