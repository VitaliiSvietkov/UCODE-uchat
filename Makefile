.PHONY: all install uninstall reinstall

all: install

install:
	@$(MAKE) -C libraries/libmx
	@$(MAKE) -C client/

uninstall:
	@$(MAKE) -C client/ uninstall
	@$(MAKE) -C libraries/libmx uninstall

reinstall: uninstall install
