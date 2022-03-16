#!/bin/bash

philos=5
time2Die=200
time2Eat=60
time2Sleep=60
maxEat=5


function check {
    ./dist/philo $1 $2 $3 $4 $5 > res.txt
    printf "Check:\n -philos: $1\n -time2Die: $2\n -time2Eat: $3\n -time2Sleep: $4\n -maxEats: $5\n"
    i=1
    while [ $i -le $1 ]
    do
        timesEaten=$(cat res.txt | grep "$i is eating" | wc -l | tr -d ' ')
        died=$(cat res.txt | grep "died")
        printf "philo $i has eaten $timesEaten times\n"
        ((i++))
    done
    printf "$died"
    rm res.txt

}

check $philos $time2Die $time2Eat $time2Sleep $maxEat