#!/bin/sh

echo "Enter a date"
read Date
#echo "The date entered is : $Date"
DATE=$Date
#echo "$DATE"

DAY=$(echo $DATE | cut -d " " -f 1) 
MONTH=$(echo $DATE | cut -d " " -f 3) 
YEAR=$(echo $DATE | cut -d " " -f 5) 

#echo "$DAY"
#echo "$MONTH"
#echo "$YEAR"

case "$MONTH" in
Jan) M=01;;
Feb) M=02;;
Mar) M=03;;
Apr) M=04;;
May) M=05;;
Jun) M=06;;
Jul) M=07;;
Aug) M=08;;
Sep) M=09;;
Oct) M=10;;
Nov) M=11;;
Dec) M=12;;
esac

NEW_DATE="$M-$DAY-$YEAR"
#echo "$NEW_DATE" 
 
DAY_NOW=$(date -d $(echo $NEW_DATE|awk -F- '{print $3 "-" $1 "-" $2}') +%A)
echo "Happy $DAY_NOW - CED18I034 Mridul Harish"
