#!/bin/bash
nums=() #array 
read -p "Enter number of numbers: " size

for (( I = 0; I < $size; I++ )); do
    read -p "Enter number: " num
    nums+=($num)
done


echo "The numbers in array:" 
for (( I = 0; I < ${#nums[@]}; I++ )); do #element iterator 
    echo -n "${nums[I]} "
done
echo 