export PRJ_ROOT=/home/mitso23/training
export GOOGLE_DIR=${PRJ_ROOT}/packages/googletest
export GTEST_DIR=${GOOGLE_DIR}/googletest/
export GMOCK_DIR=/${GOOGLE_DIR}/googlemock

export CC=g++
export CFLAGS= -Wall -std=c++11  -g
export INCLUDES= -I${PRJ_ROOT}/include -isystem ${GTEST_DIR}/include -isystem ${GMOCK_DIR}/include 
export LDFLAGS= -Wl,-rpath=${PRJ_ROOT}/lib -Wl,-rpath=/usr/local/lib/ -L${PRJ_ROOT}/lib -L${GOOGLE_DIR}