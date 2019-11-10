#!/bin/bash

. ./env.sh

/usr/local/$PLATFORM/bin/$PLATFORM-gcc \
   -DNO_PROTO \
   -L/usr/local/$PLATFORM/$PLATFORM/sys-root/usr/lib \
   -lsynosdk \
   synouidmod.c -o synouidmod
