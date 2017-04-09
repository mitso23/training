FROM training:master
RUN apt-get update && apt-get install -y \
cmake \ 
wget

RUN cd /home && git checkout hotFixes

RUN cd /home/packages/googletest/ &&  rm CMakeCache.txt && cmake -DBUILD_SHARED_LIBS=ON && make && cp googlemock/libgmock.so /usr/local/lib/  && cp -r googlemock/include/* /usr/local/include/
RUN cd /home/packages/googletest/googletest/ && cmake ./ && make && cp libgtest.a /usr/local/lib && cp -r include/* /usr/local/include/

#RUN git clone https://github.com/imatix/zguide.git && tar -zxvf zeromq-3.2.5.tar.gz && cd zeromq-3.2.5 && ./configure --prefix=/usr/local/  && make && make install 


RUN mkdir /home/bin
ENV PRJ_ROOT=/home/

