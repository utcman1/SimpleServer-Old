#!/bin/bash

taskset -c 0 stdbuf -i0 -o0 -e0 ./SimpleServer 101 > log/101.log &
taskset -c 2 stdbuf -i0 -o0 -e0 ./SimpleServer 102 > log/102.log &
taskset -c 4 stdbuf -i0 -o0 -e0 ./SimpleServer 103 > log/103.log &
taskset -c 6 stdbuf -i0 -o0 -e0 ./SimpleServer 104 > log/104.log &
#taskset -c 8 stdbuf -i0 -o0 -e0 ./SimpleServer 105 > log/105.log &
#taskset -c 10 stdbuf -i0 -o0 -e0 ./SimpleServer 106 > log/106.log &
#taskset -c 12 stdbuf -i0 -o0 -e0 ./SimpleServer 107 > log/107.log &
#taskset -c 14 stdbuf -i0 -o0 -e0 ./SimpleServer 108 > log/108.log &
#taskset -c 16 stdbuf -i0 -o0 -e0 ./SimpleServer 109 > log/109.log &
#taskset -c 18 stdbuf -i0 -o0 -e0 ./SimpleServer 110 > log/110.log &
#taskset -c 20 stdbuf -i0 -o0 -e0 ./SimpleServer 111 > log/111.log &
#taskset -c 22 stdbuf -i0 -o0 -e0 ./SimpleServer 112 > log/112.log &
#taskset -c 24 stdbuf -i0 -o0 -e0 ./SimpleServer 113 > log/113.log &
#taskset -c 26 stdbuf -i0 -o0 -e0 ./SimpleServer 114 > log/114.log &
#taskset -c 28 stdbuf -i0 -o0 -e0 ./SimpleServer 115 > log/115.log &
#taskset -c 30 stdbuf -i0 -o0 -e0 ./SimpleServer 116 > log/116.log &
sleep 1
taskset -c 1 stdbuf -i0 -o0 -e0 ./SimpleServer 201 > log/201.log &
taskset -c 3 stdbuf -i0 -o0 -e0 ./SimpleServer 202 > log/202.log &
taskset -c 5 stdbuf -i0 -o0 -e0 ./SimpleServer 203 > log/203.log &
taskset -c 7 stdbuf -i0 -o0 -e0 ./SimpleServer 204 > log/204.log &
#taskset -c 9 stdbuf -i0 -o0 -e0 ./SimpleServer 205 > log/205.log &
#taskset -c 11 stdbuf -i0 -o0 -e0 ./SimpleServer 206 > log/206.log &
#taskset -c 13 stdbuf -i0 -o0 -e0 ./SimpleServer 207 > log/207.log &
#taskset -c 15 stdbuf -i0 -o0 -e0 ./SimpleServer 208 > log/208.log &
#taskset -c 17 stdbuf -i0 -o0 -e0 ./SimpleServer 209 > log/209.log &
#taskset -c 19 stdbuf -i0 -o0 -e0 ./SimpleServer 210 > log/210.log &
#taskset -c 21 stdbuf -i0 -o0 -e0 ./SimpleServer 211 > log/211.log &
#taskset -c 23 stdbuf -i0 -o0 -e0 ./SimpleServer 212 > log/212.log &
#taskset -c 25 stdbuf -i0 -o0 -e0 ./SimpleServer 213 > log/213.log &
#taskset -c 27 stdbuf -i0 -o0 -e0 ./SimpleServer 214 > log/214.log &
#taskset -c 29 stdbuf -i0 -o0 -e0 ./SimpleServer 215 > log/215.log &
#taskset -c 31 stdbuf -i0 -o0 -e0 ./SimpleServer 216 > log/216.log &
