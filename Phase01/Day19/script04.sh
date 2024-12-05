#!/bin/bash
read -p "Number of Terms:" N

echo "Natural Numbers:"
for I in $(seq 1 $N); do
    echo -n "$I "
done
echo 