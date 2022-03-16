#!/bin/bash

numPhilos=10
timeToDie=100
timeToEat=60
timeToSleep=60
maxEating=5

./dist/philo $numPhilos $timeToDie $timeToEat $timeToSleep $maxEating > res.txt
i=1
while [ $i -le $numPhilos ]
do
    timesEaten=$(cat res.txt | grep "$i is eating" | wc -l)
    died=$(cat res.txt | grep "died")
    printf "philo $i: has eaten $timesEaten times\n"
    ((i++))
done
printf "$died"
rm res.txt
