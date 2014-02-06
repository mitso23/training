# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
#               # 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
# #
#

CFLAGS := $(CFLAGS)
INCLUDES := $(INCLUDES)
LFLAGS := $(LDFLAGS) 
LIBS = 
SRCS = C++11.cpp

OBJS = $(SRCS:.c=.o)
NAME = C++11.out
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


