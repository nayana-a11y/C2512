
//while1
#!/bin/bash
read -p "Number of Terms:" N

echo "Natural Numbers:"
I=1
while [ $I -le $N ]; do
    echo -n "$I "
    I=$(( I + 1 ))
done
echo 


//while2
#!/bin/bash
# read -p "Number of Terms:" N

# echo "Natural Numbers:"
# I=1
# while [ $I -le $N ]; do
#     echo -n "$I "
#     I=$(( I + 1 ))
# done
# echo 

//until true
#!/bin/bash
# read -p "Number of Terms:" N

# echo "Natural Numbers:"
# I=1
# until [ $I -gt $N ]; do
#     echo -n "$I "
#     I=$(( I + 1 ))
# done
# echo 

//
#!/bin/bash
read -p "Number of Terms:" N

echo "Natural Numbers:"
I=$N
until [ ! $I -ge 1 ]; do
    echo -n "$I "
    I=$(( I - 1 ))
done
echo 