#!/bin/sh

for file in $*
do
    echo "[31m# checking file [35m$file[0m"
    while read line
    do
	time1=0
	time2=0
	echo -n "[32m- running command [35m$line[0m "
	echo "$line" | tcsh > tcsh_stdout 2> tcsh_stderr
	echo -n "	[34m[tcsh][0m "
	echo "$line" | ./42sh > 42sh_stdout 2> 42sh_stderr
	echo "	[34m[42sh][0m "
	diff tcsh_stdout 42sh_stdout > /dev/null
	if [ "$?" -eq "1" ]
	    then
	    echo "[33m# diff between tcsh std output and 42sh std output :[0m"
	    diff tcsh_stdout 42sh_stdout
	fi
	diff tcsh_stderr 42sh_stderr > /dev/null
	if [ "$?" -eq "1" ]
	    then
	    echo "[31m# diff between tcsh err output and 42sh err output :[0m"
	    diff tcsh_stderr 42sh_stderr
	fi
    done < $file
done