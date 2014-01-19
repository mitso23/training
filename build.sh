export PRJ_ROOT=/home/dimitrios/training

export CC=g++ 
export CFLAGS="-Wall -DDEBUG -g -O2"
export INCLUDES="-I${PRJ_ROOT}/include"
export LDFLAGS="-Wl,-rpath=${PRJ_ROOT}/src/libipc"

#build the libraries
for dir in `ls ${PRJ_ROOT}/src` 
do	
	pushd ./
	
	cd ${PRJ_ROOT}/src/$dir;
		
	make clean;
	make || exit
	cp *.so  ${PRJ_ROOT}/lib
	
	popd
done

#build the testapps
for dir in `ls ${PRJ_ROOT}/testapps`
do
        pushd ./
	
	cd ${PRJ_ROOT}/testapps/$dir;
      	
	make clean;
       	make || exit
	cp *.out ${PRJ_ROOT}/bin

        popd
done

