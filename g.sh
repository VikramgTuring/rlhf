#!/bin/bash
 
# Ensure both task number and turn are provided
if [ $# -lt 3 ]; then
  echo "Usage: $0 <task_number> <model>  <turn>"
  exit 1
fi
 
# Capture the arguments
TASK_NUM=$1
MODEL=$2
TURN=$3
 
# Define directory names
DIR1="task_${TASK_NUM}_Model${MODEL}_turn${TURN}"
 
# Create the directories
git stash
git pull origin main
git stash pop
git add $DIR1
git commit -m "$DIR1"
git push -u origin main
 
# Confirm the current directory
echo "https://github.com/VikramgTuring/rlhf/tree/main/task_${TASK_NUM}_Model${MODEL}_turn${TURN}"
 
