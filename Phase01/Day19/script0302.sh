#!/bin/bash
read -p "Enter first number:" num1
read -p "Enter second number:" num2
read -p "Enter third number:" num3

count=0

if [ $(( $num1 % 2 )) -eq 1 ]; then
    count=$(( $count + 1 ))
fi

if [ $(( $num2 % 2 )) -eq 1 ]; then
    count=$(( $count + 1 ))
fi

if [ $(( $num3 % 2 )) -eq 1 ]; then
    count=$(( $count + 1 ))
fi

echo "There are $count odd numbers among $num1, $num2 and $num3."