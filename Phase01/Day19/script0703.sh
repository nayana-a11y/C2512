#!/bin/bash
read -p "Enter month name:" month_name

case $month_name in
    January) month_number=1 ;;
    February) month_number=2;;
    March) month_number=3;;
    April)
        month_number=4
        ;;
    May)  
        month_number=5
        ;;
    June)
        month_number=6
        ;;
    July)
        month_number=7
        ;;
    August)
        month_number=8
        ;;
    September)
        month_number=9
        ;;
    October) 
        month_number=10
        ;;
    November) 
        month_number=11
        ;;
    December)
        month_number=12
        ;;
    *)
        echo "Invalid month name"
        exit 1
        ;;
esac

echo "Month number of month name $month_name is $month_number."