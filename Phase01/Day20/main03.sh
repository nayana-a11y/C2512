#!/bin/bash
is_odd() {
    if [ $(($1 % 2)) -eq 1 ]; then
        return 0
    else 
        return 1
    fi
}

read -p "Enter number: " num
is_odd $num
if [ $? -eq 0 ]; then 
    echo "Odd number"
else 
    echo "Even number"
fi