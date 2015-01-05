#!/usr/bin/env bash
#
# barry/build-o-matic.sh

echo -n                                                         && \
    export PROJECT_DIR=$(dirname $(readlink -f ${BASH_SOURCE})) && \
    export BARRY_BUILD_DIR=$(mktemp -t -d barry-build-XXXXXX)   && \
    cd ${BARRY_BUILD_DIR}                                       && \
    autoreconf -ivf ${PROJECT_DIR}                              && \
    export BARRY_PREFIX_DIR=$(mktemp -t -d barry-prefix-XXXXXX) && \
    ${PROJECT_DIR}/configure --prefix=${BARRY_PREFIX_DIR}       && \
    make -j3                                                    && \
    make -j3 check                                              && \
    make -j3 distcheck                                          && \
    make -j3 install                                            && \
    echo && echo "big win"

