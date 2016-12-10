export PRJ_ROOT=/home/mitso23/training

export CC=gcc-5
export CFLAGS= -Wall -g -std=c99 
export INCLUDES= -I${PRJ_ROOT}/include
export LDFLAGS= -Wl,-rpath=${PRJ_ROOT}/lib -L${PRJ_ROOT}/lib
