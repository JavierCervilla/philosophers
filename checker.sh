#!/bin/bash

./dist/philo 8 120 60 60 5 > res.txt
echo "philo 1"
cat res.txt | grep "1 is eating" | wc -l
echo "philo 2"
cat res.txt | grep "2 is eating" | wc -l
echo "philo 3"
cat res.txt | grep "3 is eating" | wc -l
echo "philo 4"
cat res.txt | grep "4 is eating" | wc -l 
echo "philo 5"
cat res.txt | grep "5 is eating" | wc -l
echo "philo 6"
cat res.txt | grep "6 is eating" | wc -l
echo "philo 7"
cat res.txt | grep "7 is eating" | wc -l
echo "philo 8"
cat res.txt | grep "8 is eating" | wc -l 

rm res.txt