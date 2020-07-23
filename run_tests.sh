#!/bin/bash

print_test_fail() {
  printf "\nFAIL: $1\nExpected:\n"
  printf "$expected"
  printf "\nActual:\n"
  printf "$result\n"
}

evaluate_result() {
  if [[ $result == $expected ]]
  then
    printf "."
  else
    print_test_fail "$1"
  fi
}

gcc -o koine_test src/koine.c

#Test 1
expected=`cat ./files/usage`
result=`./koine_test`
evaluate_result 'Test 1'

#Test 2
expected=`cat ./files/alphabet`
result=`./koine_test -a`
evaluate_result 'Test 2'

#Test 3
expected=`cat ./files/alphabet-extra`
result=`./koine_test -A`
evaluate_result 'Test 3'

#Test 4
expected=`cat ./files/cases`
result=`./koine_test -c`
evaluate_result 'Test 4'

printf "\n"
rm koine_test
