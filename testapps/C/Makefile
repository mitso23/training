# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
#               # 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
# #
#
include ../../common.mk

############EDIT THIS FOR PROJECT SPECIFIC SETTINGS ################################### 

export DIR=$(patsubst $(PRJ_ROOT)%,%,$(shell pwd))
export SRCS:= $(wildcard *.cpp)
export LIBS= 
export NAME= C.out

.PHONY: depend clean

all:
	make -C ../../ -f rules.mk depend 	
	make -C ../../ -f rules.mk $(NAME)

clean:
	make -C ../../ -f rules.mk clean

