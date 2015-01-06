FROM ubuntu:latest
MAINTAINER rubicks

RUN dpkg --add-architecture i386
RUN apt-get -qq update
RUN apt-get -qq dist-upgrade
RUN apt-get -qq install make autoconf automake libtool git
RUN apt-get -qq install mingw32 mingw32-binutils mingw32-runtime wine
# RUN apt-get -qq install software-properties-common
# RUN add-apt-repository ppa:ubuntu-wine/ppa
# RUN apt-get -qq update
RUN useradd luser
WORKDIR /home/luser
ADD . /home/luser
# RUN apt-get -y  install wine1.6
CMD /bin/bash ./build-o-matic.sh
