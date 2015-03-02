export CC=gcc-4.9
export CFLAGS= -Wall -g -std=c99 
export INCLUDES= -I${PRJ_ROOT}/include
export LDFLAGS= -Wl,-rpath=${PRJ_ROOT}/lib -L${PRJ_ROOT}/lib
