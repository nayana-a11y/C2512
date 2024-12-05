#!/bin/bash
find_sum() {
    sum=$(( $1 + $2 ))
    echo "Sum of $1 and $2: $sum"
}

read -p "Enter first number: " num1
read -p "Enter second number: " num2
find_sum $num1 $num2

#report=$(find_sum $num1 $num2)
#printf "The report is\n$report\n"

#printf "The report is\n$(find_sum $num1 $num2)\n"