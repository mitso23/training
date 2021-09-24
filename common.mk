export CC=gcc-10
export CFLAGS=-Wall -std=c++17 -O3 -g
export INCLUDES= -I${PRJ_ROOT}/include -I/usr/include/dbus-1.0/ -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include
export LDFLAGS= -lstdc++ -fopenmp -Wl,-rpath=${PRJ_ROOT}/lib -Wl,-rpath=/usr/local/lib/ -L${PRJ_ROOT}/lib -L/usr/lib/x86_64-linux-gnu/
