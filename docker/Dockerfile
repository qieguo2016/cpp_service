FROM ubuntu:20.04
MAINTAINER qieguo.chow

# timezone
RUN ln -snf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime \ 
    && echo 'Asia/Shanghai' > /etc/timezone

# base
RUN apt-get update -y \ 
    && apt-get install -y build-essential wget unzip openjdk-8-jdk vim git g++ make cmake gdb ant autoconf libtool curl iputils-ping sysstat net-tools clang-format-12 ninja-build ccache \
    && apt-get install -y libssl-dev libbz2-dev zlib1g-dev libgoogle-perftools-dev libsnappy-dev libcurl4-openssl-dev libconfig++-dev libcppunit-dev libzstd-dev libtbb-dev libgflags-dev libleveldb-dev \ 
    && gcc --version \ 
    && cmake --version \ 
    && echo "set enc=utf8" >> /etc/vim/vimrc \ 
    && ln -s /usr/bin/clang-format-12 /usr/bin/clang-format

# jemalloc
RUN cd /home \ 
    && git clone -b 5.3.0 https://github.com/jemalloc/jemalloc.git \ 
    && cd jemalloc \ 
    && ./autogen.sh --prefix=/opt/jemalloc \ 
    && make -j 16 \ 
    && make install \ 
    && cd /opt \ 
    && rm -rf /home/jemalloc

# # zookeeper
# RUN cd /opt \
#         && wget http://archive.apache.org/dist/zookeeper/zookeeper-3.5.8/apache-zookeeper-3.5.8.tar.gz \
#         && tar -xzvf apache-zookeeper-3.5.8.tar.gz \
#         && rm -rf apache-zookeeper-3.5.8.tar.gz \
#         && cd /opt/apache-zookeeper-3.5.8 \
#         && ant compile_jute \
#         && cd /opt/apache-zookeeper-3.5.8/zookeeper-client/zookeeper-client-c \
#         && autoreconf -if \
#         && ./configure \
#         && make -j16 && make install

# python
RUN cd /opt \
        && apt-get -y install python2.7 libpython2.7-dev python3.8 libpython3-dev\
        && apt-get -y install libpython2.7-dev \
        && ln -s /usr/bin/python2.7 /usr/bin/python \
        && curl https://bootstrap.pypa.io/pip/2.7/get-pip.py --output get-pip.py \
        && python get-pip.py \
        && ln -s /usr/local/bin/pip /usr/bin/pip \
        && mkdir ~/.pip \
        && echo "[global]\nindex-url = https://pypi.garenanow.com/\n[install]\ntrusted-host=pypi.garenanow.com" >> ~/.pip/pip.conf \
        && rm get-pip.py \
        && pip install "urllib3<=1.23"

# # rapidjson
# RUN cd /home \
#         && git clone https://github.com/Tencent/rapidjson.git \
#         && cd rapidjson && mkdir build  && cd build \
#         && cmake .. -DCMAKE_INSTALL_PREFIX=/opt/rapidjson \
#         && make install \
#         && rm -rf /home/rapidjson

# # protobuf
# RUN cd /opt \
#         && wget https://github.com/protocolbuffers/protobuf/releases/download/v3.16.0/protobuf-cpp-3.16.0.tar.gz \
#         && mkdir /opt/protobuf && tar -zxvf protobuf-cpp-3.16.0.tar.gz \
#         && cd /opt/protobuf-3.16.0 &&./autogen.sh && ./configure --prefix=/opt/protobuf && make -j 16 && make install && ldconfig \
#         && rm -rf /opt/protobuf-cpp-3.16.0.tar.gz /opt/protobuf-3.16.0/

# # gtest
# RUN cd /home \
#         && git clone -b release-1.11.0  https://github.com/google/googletest \
#         && cd googletest \
#         && CXXFLAGS=-fPIC && mkdir -p build && cd build && cmake .. && make -j 16 \
#         && mkdir -p /opt/gtest/lib \
#         && cp lib/libgtest.a /opt/gtest/lib \
#         && cp lib/libgtest_main.a /opt/gtest/lib \
#         && cp -r ../googletest/include /opt/gtest \
#         && rm -rf /home/googletest

# # librdkafka
# RUN cd /home \
#         && git clone -b v1.8.0 https://github.com/edenhill/librdkafka \
#         && mkdir librdkafka/build \
#         && cd librdkafka/build \
#         && cmake -DCMAKE_INSTALL_PREFIX=/opt/rdkafka -DBUILD_TESTING=OFF -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_BUILD_TYPE=Release -DRDKAFKA_BUILD_STATIC=1 .. \
#         && make -j 16 \
#         && make install \
#         && rm -rf /home/librdkafka

# # brpc
# RUN cd /home \
#         && git clone -b 1.4.0 https://github.com/apache/brpc.git \
#         && cd brpc && mkdir build && cd build \
#         && cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/opt/brpc -DBUILD_SHARED_LIBS=OFF -DCMAKE_CXX_STANDARD=17 .. \
#         && make -j 16 \
#         && make install \
#         && rm -rf /home/brpc
        
ENV IMAGE_VERSION=v0.0.1