# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
#               # 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
# #
#

CFLAGS:=$(CFLAGS) -fpic
INCLUDES:= $(INCLUDES)
LDFLAGS := $(LDFLAGS) -shared 
SRCS = ipc.cpp

OBJS = $(SRCS:.c=.o)
NAME = ipc
.PHONY: depend clean

lib: lib$(NAME).so

lib$(NAME).so: $(OBJ)
	 $(CC) $(CFLAGS) $(INCLUDES) -o lib$(NAME).so $(OBJS) $(LDFLAGS) $(LIBS)

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ lib$(NAME).so

depend: $(SRCS)
	makedepend $(INCLUDES) $^


