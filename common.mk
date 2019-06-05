export CC=gcc-7  
export CFLAGS=-Wall -std=c++17  -g
export INCLUDES= -I${PRJ_ROOT}/include -I/usr/include/dbus-1.0/ -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include `pkg-config --cflags glib-2.0`
export LDFLAGS= -lstdc++ -Wl,-rpath=${PRJ_ROOT}/lib -Wl,-rpath=/usr/local/lib/ -L${PRJ_ROOT}/lib -L/usr/lib/x86_64-linux-gnu/
