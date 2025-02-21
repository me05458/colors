LINK_TARGET = colors

OBJS = \
       screencolors.o\

REBUILDABLES = $(OBJS) $(LINK_TARGET)

all: $(LINK_TARGET)
	@echo "all done!"

$(LINK_TARGET): $(OBJS)
	gcc -o $@ $(OBJS) -lsodium -lm


%.o : %.c
	gcc -o $@ -c $<





clean:
	rm -f $(REBUILDABLES)
