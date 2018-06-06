target= test
CC	= gcc
CXX	= g++
AS	= as
AR	= ar
LD	= ld

OBJDIR  = obj
SRC = src
OBJS_FILE = $(OBJDIR)/memory.o $(OBJDIR)/test.o 

CFLAGS	:= $(CFLAGS) -w

$(target): $(OBJS_FILE) 
	$(CC) $^ -o $@

$(OBJDIR)/memory.o: $(SRC)/memory.c
	@if [ ! -d $(OBJDIR) ]; then mkdir -p $(OBJDIR); fi;
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJDIR)/test.o: test.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -rf $(OBJDIR) $(target)
