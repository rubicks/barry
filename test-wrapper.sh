#!/usr/bin/env bash

set -euv
set -o pipefail

_this=$(readlink -f ${BASH_SOURCE})
_here=$(dirname ${_this})

echo
echo "\${_this} == \"${_this}\""
echo
echo "\${_here} == \"${_here}\""
echo
echo ${@}
echo
env | sort

test -x ${1}
