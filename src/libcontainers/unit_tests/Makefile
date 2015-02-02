# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
#               # 'make'        build executable file 'mycc'
# 'make clean'  removes all .o and executable files
# #
#
include $(PRJ_ROOT)/common.mk

############EDIT THIS FOR PROJECT SPECIFIC SETTINGS ################################### 

export DIR=$(patsubst $(PRJ_ROOT)%,%,$(shell pwd))
export SRCS:= $(wildcard *.cpp)
export NAME= containers_unit_test.out
export CFLAGS:= ${CFLAGS} -DBOOST_TEST_DYN_LINK
export LDFLAGS= -lpthread -lboost_unit_test_framework
.PHONY: depend clean

all:
	make -j4 -C $(PRJ_ROOT) -f rules.mk depend 	
	make -j4 -C $(PRJ_ROOT) -f rules.mk $(NAME)

clean:
	make -j4 -C $(PRJ_ROOT) -f rules.mk clean

