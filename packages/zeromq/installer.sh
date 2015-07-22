trap cleanup SIGINT EXIT
trap error_handling ERR

cleanup()
{
	popd > /dev/null 2>&1
	exit 0
}

error_handling()
{
	popd > /dev/null 2>&1
	exit 1
}

tar -zxvf zeromq-3.2.5.tar.gz
pushd ./
cd zeromq-3.2.5 
./configure 
make
make install 
cp ../zguide/examples/C/zhelpers.h /usr/local/include/
cp ../zguide/examples/C++/zhelpers.hpp /usr/local/include/
cp zmq.hpp /usr/local/include/



