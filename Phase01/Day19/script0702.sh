#!/bin/bash
read -p "Enter month number:" month_number

case $month_number in
    1) month_name="January" ;;
    2) month_name="February";;
    3) month_name="March";;
    4)
        month_name="April"
        ;;
    5)  
        month_name="May"
        ;;
    6)
        month_name="June"
        ;;
    7)
        month_name="July"
        ;;
    8)
        month_name="August"
        ;;
    9)
        month_name="September"
        ;;
    10) 
        month_name="October"
        ;;
    11) 
        month_name="November"
        ;;
    12)
        month_name="December"
        ;;
    *)
        echo "Invalid month number"
        exit 1
        ;;
esac

echo "Month name of month number $month_number is $month_name."