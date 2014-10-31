export PRJ_ROOT=/home_local/miranda/training

export CC=g++ -std=c++0x  
export CFLAGS="-Wall -fPIC"
export INCLUDES="-I${PRJ_ROOT}/include"
export LDFLAGS=" -Wl,-rpath=${PRJ_ROOT}/lib -L${PRJ_ROOT}/lib"

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

