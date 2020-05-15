# defines guard-%

SUBDIRS := $(wildcard */.)

.PHONY: all clean


all clean: 
	for dir in $(SUBDIRS); do \
		export SYNTH_ROOT=dir;\
		$(MAKE) -C $$dir -f Makefile $@; \
	done
