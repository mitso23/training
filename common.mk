export CC=g++-4.9
export CFLAGS= -Wall -std=c++11  -g
export INCLUDES= -I${PRJ_ROOT}/include
export LDFLAGS= -Wl,-rpath=${PRJ_ROOT}/lib -Wl,-rpath=/usr/local/lib/ -L${PRJ_ROOT}/lib 
