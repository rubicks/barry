#!/usr/bin/env bash
#
# barry/dock-o-matic.sh

_tag="tag-${RANDOM}"
_name="name-${RANDOM}"
_here=$(dirname $(readlink -f ${BASH_SOURCE}))

echo -n && \
    docker build --tag=${_tag} ${_here} && \
    docker run --name=${_name} ${_tag}  && \
    echo "${BASH_SOURCE} big win"
