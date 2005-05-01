SUBDIRS:= `ls | egrep -v '^(CVS)$$'`
all:
	@for i in $(SUBDIRS); do if test -d $$i; then make -s -C $$i; fi; done;
clean:
	@for i in $(SUBDIRS); do if test -d $$i; then make -s -C $$i clean; fi; done;

