# Use Ubuntu 16.04 LTS
FROM ubuntu:xenial-20161213

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
                    #for downloading online material
                    ca-certificates \
                    #for pulling code from GitHub
                    git=1:2.7.4-0ubuntu1 \
                    #for creating C++ build environment
                    build-essential \
                    #for creating Qt build environment
                    qtbase5-dev

RUN apt-get update && \
    apt-get clean && \
	rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

RUN git clone https://github.com/TimVanMourik/Porcupine.git
WORKDIR /Porcupine
	
RUN qmake -qt=qt5 && \
	make

#ENTRYPOINT ["./bin/Porcupine"]