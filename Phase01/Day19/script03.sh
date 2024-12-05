#!/bin/bash
read -p "Enter number:" num

if [ $(( $num % 2 )) -eq 1 ]; then
	echo "$num is odd number"
else
	echo "$num is even number"
fi
