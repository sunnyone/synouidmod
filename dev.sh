#!/bin/bash
. ./env.sh

export LD_LIBRARY_PATH=/usr/local/$PLATFORM/$PLATFORM/sys-root/usr/lib $LD_LIBRARY_PATH
./synouidmod "$@"
