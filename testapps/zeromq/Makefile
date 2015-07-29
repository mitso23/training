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
export LIBS= -lzmq -lpthread
export NAME= zeromq.out

.PHONY: depend clean

all:
	make -C ../../ -f rules.mk depend 	
	make -C ../../ -f rules.mk $(NAME)

clean:
	make -C ../../ -f rules.mk clean

# DO NOT DELETE

main.o: request_reply_pattern.h /usr/local/include/zhelpers.h
main.o: /usr/local/include/zmq.h /usr/include/errno.h /usr/include/features.h
main.o: /usr/include/stdc-predef.h /usr/include/stdio.h /usr/include/libio.h
main.o: /usr/include/_G_config.h /usr/include/wchar.h /usr/include/assert.h
main.o: /usr/include/signal.h /usr/include/time.h /usr/include/stdint.h
main.o: /usr/include/stdlib.h /usr/include/alloca.h /usr/include/string.h
main.o: /usr/include/xlocale.h /usr/local/include/zmq.hpp
main.o: /usr/include/c++/4.9/algorithm /usr/include/c++/4.9/utility
main.o: /usr/include/c++/4.9/bits/stl_relops.h
main.o: /usr/include/c++/4.9/bits/stl_pair.h /usr/include/c++/4.9/bits/move.h
main.o: /usr/include/c++/4.9/bits/concept_check.h
main.o: /usr/include/c++/4.9/bits/stl_algobase.h
main.o: /usr/include/c++/4.9/bits/functexcept.h
main.o: /usr/include/c++/4.9/bits/exception_defines.h
main.o: /usr/include/c++/4.9/bits/cpp_type_traits.h
main.o: /usr/include/c++/4.9/ext/type_traits.h
main.o: /usr/include/c++/4.9/ext/numeric_traits.h
main.o: /usr/include/c++/4.9/bits/stl_iterator_base_types.h
main.o: /usr/include/c++/4.9/bits/stl_iterator_base_funcs.h
main.o: /usr/include/c++/4.9/debug/debug.h
main.o: /usr/include/c++/4.9/bits/stl_iterator.h
main.o: /usr/include/c++/4.9/bits/ptr_traits.h
main.o: /usr/include/c++/4.9/bits/predefined_ops.h
main.o: /usr/include/c++/4.9/bits/stl_algo.h /usr/include/c++/4.9/cstdlib
main.o: /usr/include/c++/4.9/bits/algorithmfwd.h
main.o: /usr/include/c++/4.9/bits/stl_heap.h
main.o: /usr/include/c++/4.9/bits/stl_tempbuf.h
main.o: /usr/include/c++/4.9/bits/stl_construct.h /usr/include/c++/4.9/new
main.o: /usr/include/c++/4.9/exception
main.o: /usr/include/c++/4.9/bits/atomic_lockfree_defines.h
main.o: /usr/include/c++/4.9/ext/alloc_traits.h
main.o: /usr/include/c++/4.9/bits/allocator.h
main.o: /usr/include/c++/4.9/bits/memoryfwd.h /usr/include/c++/4.9/cassert
main.o: /usr/include/c++/4.9/cstring /usr/include/c++/4.9/string
main.o: /usr/include/c++/4.9/bits/stringfwd.h
main.o: /usr/include/c++/4.9/bits/char_traits.h
main.o: /usr/include/c++/4.9/bits/postypes.h /usr/include/c++/4.9/cwchar
main.o: /usr/include/c++/4.9/bits/localefwd.h /usr/include/c++/4.9/iosfwd
main.o: /usr/include/c++/4.9/cctype /usr/include/ctype.h
main.o: /usr/include/endian.h /usr/include/c++/4.9/bits/ostream_insert.h
main.o: /usr/include/c++/4.9/bits/cxxabi_forced.h
main.o: /usr/include/c++/4.9/bits/stl_function.h
main.o: /usr/include/c++/4.9/backward/binders.h
main.o: /usr/include/c++/4.9/bits/range_access.h
main.o: /usr/include/c++/4.9/bits/basic_string.h
main.o: /usr/include/c++/4.9/ext/atomicity.h
main.o: /usr/include/c++/4.9/bits/basic_string.tcc
main.o: /usr/include/c++/4.9/vector
main.o: /usr/include/c++/4.9/bits/stl_uninitialized.h
main.o: /usr/include/c++/4.9/bits/stl_vector.h
main.o: /usr/include/c++/4.9/bits/stl_bvector.h
main.o: /usr/include/c++/4.9/bits/vector.tcc /usr/include/c++/4.9/iterator
main.o: /usr/include/c++/4.9/ostream /usr/include/c++/4.9/ios
main.o: /usr/include/c++/4.9/bits/ios_base.h
main.o: /usr/include/c++/4.9/bits/locale_classes.h
main.o: /usr/include/c++/4.9/bits/locale_classes.tcc
main.o: /usr/include/c++/4.9/streambuf
main.o: /usr/include/c++/4.9/bits/streambuf.tcc
main.o: /usr/include/c++/4.9/bits/basic_ios.h
main.o: /usr/include/c++/4.9/bits/locale_facets.h
main.o: /usr/include/c++/4.9/cwctype
main.o: /usr/include/c++/4.9/bits/streambuf_iterator.h
main.o: /usr/include/c++/4.9/bits/locale_facets.tcc
main.o: /usr/include/c++/4.9/bits/basic_ios.tcc
main.o: /usr/include/c++/4.9/bits/ostream.tcc /usr/include/c++/4.9/istream
main.o: /usr/include/c++/4.9/bits/istream.tcc
main.o: /usr/include/c++/4.9/bits/stream_iterator.h /usr/include/unistd.h
main.o: /usr/include/getopt.h /usr/include/c++/4.9/iostream
main.o: publish_subscribe_pattern.h pull_push_pattern.h simple_req_router.h
main.o: router_to_req.h /usr/include/pthread.h /usr/include/sched.h
main.o: router_to_dealer.h request_broker_reply.h
main.o: /usr/include/c++/4.9/functional /usr/include/c++/4.9/thread
main.o: /usr/include/c++/4.9/bits/c++0x_warning.h
