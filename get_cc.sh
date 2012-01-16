#!/bin/sh

str=`uname -s`
if [ "$str" = "SunOS" ]
then
    echo "/usr/sfw/bin/gcc"
    else
    echo "gcc"
fi