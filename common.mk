export CC=g++-4.8
export CFLAGS= -Wall -std=c++11  -g
export INCLUDES= -I${PRJ_ROOT}/include
export LDFLAGS= -Wl,-rpath=${PRJ_ROOT}/lib -L${PRJ_ROOT}/lib
export MAKE_CPP=1 
