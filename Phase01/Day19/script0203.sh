#!/bin/bash
read -p "Enter number:" num
#tenPercent=$(expr $num / 100 \* 10 )
#newNum=$( expr $num + $tenPercent )
let tenPercent=num/100*10
let newNum=num+tenPercent

echo "10% raised number of $num is $newNum."

