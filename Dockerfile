FROM ubuntu:xenial

RUN apt-get update -y
RUN apt-get upgrade -y
RUN apt-get install build-essential libssl-dev wget -y

COPY Message_Broadcaster /message_broadcaster
COPY build_Message_Broadcaster.sh /message_broadcaster
COPY build_cmake.sh /tmp
COPY build_boost.sh /tmp

WORKDIR /tmp
RUN /usr/bin/env bash build_cmake.sh
RUN /usr/bin/env bash build_boost.sh


WORKDIR /message_broadcaster
RUN /usr/bin/env bash build_Message_Broadcaster.sh

EXPOSE 9000
EXPOSE 9001
