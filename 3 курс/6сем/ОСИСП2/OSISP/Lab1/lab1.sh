#!/bin/bash
a=1664525
b=1013904223
m=4294967296 #2**32

cols=$(tput cols)
screen_cols=$((cols * 50 / 100))

lines=$(tput lines)
screen_lines=$((lines * 60 / 100))

#(a*seconds+b)modm
get_random_number()
{
 seconds=$(date +%s) #Get the seconds since epoch(Jan 1 1970)
 random=$(( (a*seconds+b)%m ))
 echo $random
}

border() 
{
#top
for (( i=0; i<=$((screen_cols+9-1)); i++)); do
   echo -n "*"
done

#left
for (( i=0; i<=$((screen_lines-1)); i++)); do
   echo  "*"
done

#bottom
for (( i=1; i<=$((screen_cols+9)); i++)); do
   echo -n "*"
done

#right
for (( i=0; i<=$((screen_lines)); i++)); do
   tput cup $i $((screen_cols+9))
     echo  "*"
  done  
}

while true; do
clear
x=$(( $(get_random_number)%screen_cols ))
y=$(( $(get_random_number)%screen_lines ))
border

tput cup $y $x
current_time=$(date +%T)
echo $current_time

sleep 2s
done
