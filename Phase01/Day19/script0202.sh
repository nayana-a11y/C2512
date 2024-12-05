#!/bin/bash
read -p "Enter number:" num
tenPercent=$(( ($num / 100)* 10 ))
newNum=$(( $num + $tenPercent ))
echo "10% raised number of $num is $newNum."
