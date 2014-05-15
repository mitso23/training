# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
#               # 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
# #
#

CFLAGS:= $(CFLAGS)-g
INCLUDES:=$(INCLUDES)
LFLAGS:=$(LDFLAGS) -lpthread -lthread
LIBS = 
SRCS = Threads.cpp

OBJS = $(SRCS:.c=.o)
NAME = Threads.out
.PHONY: depend clean


all: $(NAME)

$(NAME): $(OBJ)
	 $(CC) $(OBJS) $(LFLAGS) $(LIBS) $(INCLUDES) -o $(NAME) 

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) *.o *~ $(NAME)

depend: $(SRCS)
	makedepend $(INCLUDES) $^


