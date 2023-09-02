#!/bin/sh
if [ "$#" -ne 2 ] ; then
 echo "number of arguments shall be 2" >&2
 exit 1
fi

if !   mkdir -p "${1%/*}"  ; then 
 echo "file cannot be created"
fi
if ! touch "$1" ; then
echo "file cannot be created"
fi
if ! echo "$2" > "$1" ; then
echo "file cannot be created"
fi
