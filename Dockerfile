FROM ubuntu:xenial-20161213

COPY . /opt/porcupine

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        # for creating C++ build environment
        build-essential \
        # for the SVG support that isn't included in the standard Qt
        libqt5svg5* \
        # for creating Qt build environment
        qtbase5-dev \
    && cd /opt/porcupine \
    && qmake -qt=qt5 \
    && make \
    && apt-get purge -yq build-essential \
    && apt-get -yq autoremove \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

ENTRYPOINT ["/opt/porcupine/bin/Porcupine"]
