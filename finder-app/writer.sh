#!/bin/sh
if [ "$#" -ne 2 ] ; then
 echo "number of arguments shall be 2" 
 exit 1
fi
if !   mkdir -p "${1%/*}"  ; then 
 echo "directory cannot be created"
 exit 1
fi
if ! >filename ; then
echo "file cannot be created"
exit 1
fi
if [ -f "$1" ] ; then
echo "file cannot be created"
exit 1
fi
if ! echo "$2" > "$1" ; then
echo "file cannot be created"
exit 1
fi

