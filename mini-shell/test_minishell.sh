#!/bin/bash

# Color Codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;35m'
NC='\033[0m' # No Color

# Path to your minishell executable, adjust as necessary
MINISHELL="./minishell"

# Function to run a command in your minishell and display the result
run_command() {
    echo -e "${YELLOW}Executing in Minishell: $1${NC}"
    echo $1 | $MINISHELL
    echo -e "${RED}-------------------------------------------${NC}"
}

# Display a header for clarity in output
# echo -e "${GREEN}Starting script to test Minishell commands${NC}"
# echo -e "${RED}-------------------------------------------${NC}"

# List of commands to test
commands=(
    # Basic Commands
    "echo Hello World"
    "pwd"
    
    # Quoting
    "echo \"Double quotes test\""
    "echo 'Single quotes test'"
    
    # Variable Expansion
    "export TEST_VAR=42"
    "echo \$TEST_VAR"
    "unset TEST_VAR"
    "echo \$?"
    
    # Redirections and Piping
    "echo Hello World > testfile.txt"
    "cat testfile.txt"
    "echo Append test >> testfile.txt"
    "cat testfile.txt"
    "cat testfile.txt | grep Append"
    
    # Environment and Exiting
    "env"
    "exit"
)

# Execute each command using the run_command function
for cmd in "${commands[@]}"; do run_command "$cmd"
done

# echo -e "${GREEN}Testing file manipulation${NC}"
# file_commands=(
# "touch tempfile.txt"
# "ls -l tempfile.txt"
# "rm tempfile.txt"
# )

# for cmd in "${file_commands[@]}"; do
# run_command "$cmd"
# done

# echo -e "${GREEN}Testing error handling${NC}"
# error_commands=(
# "cd nosuchdirectory"
# "cat nonexistentfile"
# )

# for cmd in "${error_commands[@]}"; do
# run_command "$cmd"
# done
   
# echo -e "${GREEN}Script to test Minishell commands completed${NC}"
