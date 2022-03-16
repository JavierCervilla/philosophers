#!/bin/bash

philos=5
time2Die=800
time2Eat=200
time2Sleep=200
maxEat=7

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
    printf "$died\n"
    rm res.txt
}

check 1 800 200 200
check 5 800 200 200 50
check 5 800 200 200 7
check 4 410 200 200 50
check 4 310 200 100 50