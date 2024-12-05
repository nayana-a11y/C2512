#!/bin/bash
nums=(11 12 13) #array 
echo "number of numbers is ${#nums[@]}"
echo "first number is ${nums[0]}"
echo "second number is ${nums[1]}"
echo "third number is ${nums[2]}"

nums[0]=21
echo "first number is ${nums[0]}"
nums+=(14)
echo "number of numbers is ${#nums[@]}"
echo "fourth number is ${nums[3]}"


for e in ${nums[@]}; do #element iterator 
    echo $e
done

for (( I = 0; I < ${#nums[@]}; I++ )); do #element iterator 
    echo ${nums[I]}
done