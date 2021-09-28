FROM ubuntu:20.04

ENV TZ=Asia/Dubai
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update && apt-get install -y \
build-essential \
vim \
tar \
wget \
net-tools \
iputils-ping \
ssh \
git \
cmake \
libboost-test-dev \
xutils-dev \
libboost-dev \ 
libboost-program-options-dev \
libboost-system-dev \ 
libboost-filesystem-dev \
libevent-dev \
automake \
libtool \
flex \
bison \
pkg-config \
g++ \
libssl-dev \
curl \
sudo \
gcovr \
valgrind \
cppcheck \
gdb \
linux-tools-common \
linux-tools-generic \ 
linux-tools-`uname -r` \ 
openjdk-8-jre
 
ARG https_proxy
ARG http_proxy

ENV http_proxy $http_proxy
ENV https.proxy $http_proxy

RUN useradd -ms /bin/bash mitso23 && adduser mitso23 sudo
RUN chown -R mitso23:mitso23 /usr/local/lib/
RUN chown -R mitso23:mitso23 /usr/local/include/
RUN chown -R mitso23:mitso23 /usr/include/
RUN chown -R mitso23:mitso23 /usr/local/share


RUN update-alternatives --install /usr/bin/java java /usr/lib/jvm/java-8-openjdk-amd64/jre/bin/java 50

USER mitso23
#RUN git config --global http.proxy $http_proxy
#RUN git config --global https.proxy $https_proxy

RUN cd /tmp && mkdir training && git clone https://github.com/mitso23/training.git && cd training && git checkout hotFixes #redo 

RUN cd /tmp/training/packages/googletest/ &&  rm CMakeCache.txt && cmake -DBUILD_SHARED_LIBS=ON && make && cp googlemock/libgmock.so /usr/local/lib/  && cp -r googlemock/include/* /usr/local/include/
RUN cd /tmp/training/packages/googletest/googletest/ && cmake ./ && make && cp libgtest.a /usr/local/lib && cp -r include/* /usr/local/include/

RUN cd /tmp && git clone https://github.com/google/benchmark.git && cd benchmark && cmake -E make_directory "build" && cmake -E chdir "build" cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release -DBENCHMARK_ENABLE_GTEST_TESTS=OFF ../ && cmake --build "build" --config Release --target install

#RUN git clone https://github.com/imatix/zguide.git && tar -zxvf zeromq-3.2.5.tar.gz && cd zeromq-3.2.5 && ./configure --prefix=/usr/local/  && make && make install

ENV PRJ_ROOT=/home/mitso23/c++/training
WORKDIR /home/mitso23





