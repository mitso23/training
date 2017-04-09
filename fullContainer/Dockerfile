FROM mitso23/ubuntu:basic
RUN apt-get update && apt-get install -y \
git \
cmake \
libboost-test-dev \
xutils-dev \
eclipse \
eclipse-cdt  

RUN useradd -ms /bin/bash mitso23
WORKDIR /home/mitso23/
RUN chown -R mitso23:mitso23 /usr/local/lib/
RUN chown -R mitso23:mitso23 /usr/local/include/

USER mitso23
RUN cd /home/mitso23 && mkdir training && git clone https://github.com/mitso23/training.git && cd training && git checkout hotFixes 

RUN cd /home/mitso23/training/packages/googletest/ &&  rm CMakeCache.txt && cmake -DBUILD_SHARED_LIBS=ON && make && cp googlemock/libgmock.so /usr/local/lib/  && cp -r googlemock/include/* /usr/local/include/
RUN cd /home/mitso23/training/packages/googletest/googletest/ && cmake ./ && make && cp libgtest.a /usr/local/lib && cp -r include/* /usr/local/include/

#RUN git clone https://github.com/imatix/zguide.git && tar -zxvf zeromq-3.2.5.tar.gz && cd zeromq-3.2.5 && ./configure --prefix=/usr/local/  && make && make install 


RUN mkdir /home/mitso23/training/bin
ENV PRJ_ROOT=/home/mitso23/training

