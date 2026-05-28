#!/usr/bin/env bash

G='\033[0;32m'
R='\033[0;31m'
RS='\033[0m'

BIN="./bin/clipboard"

qoute="Light bends around a dying star, still trying to reach you."

run_test() {
	local	lines=$1
	local	size=$(awk "BEGIN { printf \"%g\", (${lines} * ${#qoute}) / 1000000 }")

	start_time=$(date +%s.%N)
	yes ${qoute} | head -n $lines | "$BIN"
	end_time=$(date +%s.%N)

	elapsed=$(awk "BEGIN { printf \"%.3f\", $end_time - $start_time }")

	echo ""
	echo -e "| ${G}Time:${RS} ${elapsed} Seconds"
	echo -e "| ${G}Size:${RS} ${size}${RS} MB"
	echo ""
}

if [ ! -f "$BIN" ]; then
	echo -e "[${R}Error${RS}] Binary '$BIN' not found."
	exit 1
fi

echo ""
echo " $qoute"
echo ""

run_test 100
run_test 10000
run_test 1000000
run_test 5000000
run_test 10000000 # limit

