#!/bin/bash

if [ $# -ne 1 ]; then
    echo "usage: $0 filename" 1>&2
    exit 1
fi

if [ ! -r "$1" ]; then
    echo "$0: cannot open $1" 1>&2
    exit 1
fi

echo -n "Website password:"
read -s PASSWORD
echo ""

curl --silent --form username=$LOGNAME \
 --form password=$PASSWORD \
  --form filename=@"$1" \
  http://www.cse.scu.edu/~atkinson/teaching/sp20/012/online/cgi-bin/upload.cgi |
  grep "Submission Succeeded" >/dev/null 2>&1 && {
	echo "Submission succeeded"; exit 0; } || {
	echo "Submission failed"; exit 1; }
