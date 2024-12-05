#!/bin/bash
findSquare()
{
    square=$(($1 * $1))
    echo $square
}

findCube()
{
    cube=$(($1 * $1 *$1))
    echo $cube
}

read -p "Enter a number: " num
square=$(findSquare $num)
cube=$(findCube $num)
echo "Square of $num is $square"
echo "Cube of $num is $cube"