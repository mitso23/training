FROM ubuntu:18.04

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
gcc-7 \
openjdk-8-jre 
 
ARG https_proxy
ARG http_proxy


RUN useradd -ms /bin/bash mitso23 && adduser mitso23 sudo
WORKDIR /home/mitso23/
RUN chown -R mitso23:mitso23 /usr/local/lib/
RUN chown -R mitso23:mitso23 /usr/local/include/

RUN update-alternatives --install /usr/bin/java java /usr/lib/jvm/java-8-openjdk-amd64/jre/bin/java 50

USER mitso23
RUN git config --global http.proxy $http_proxy 
RUN git config --global https.proxy $https_proxy

RUN cd /home/mitso23 && mkdir training && git clone https://github.com/mitso23/training.git && cd training && git checkout hotFixes #redo 

RUN cd /home/mitso23/training/packages/googletest/ &&  rm CMakeCache.txt && cmake -DBUILD_SHARED_LIBS=ON && make && cp googlemock/libgmock.so /usr/local/lib/  && cp -r googlemock/include/* /usr/local/include/
RUN cd /home/mitso23/training/packages/googletest/googletest/ && cmake ./ && make && cp libgtest.a /usr/local/lib && cp -r include/* /usr/local/include/

RUN wget https://www.mirrorservice.org/sites/download.eclipse.org/eclipseMirror/technology/epp/downloads/release/neon/3/eclipse-cpp-neon-3-linux-gtk-x86_64.tar.gz && tar -zxvf eclipse-cpp-neon-3-linux-gtk-x86_64.tar.gz  

RUN cd eclipse && ./eclipse > /dev/null 2>&1 &

#RUN git clone https://github.com/imatix/zguide.git && tar -zxvf zeromq-3.2.5.tar.gz && cd zeromq-3.2.5 && ./configure --prefix=/usr/local/  && make && make install 


RUN mkdir /home/mitso23/training/bin
ENV PRJ_ROOT=/home/mitso23/training



