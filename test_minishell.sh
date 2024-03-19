#!/bin/bash

# Path to your minishell executable, adjust as necessary
MINISHELL="mini-shell/minishell"

# Function to run a command in your minishell and display the result
run_command() {
    echo "Executing in Minishell: $1"
    echo $1 | $MINISHELL
    echo "-------------------------------------------"
}

# Display a header for clarity in output
echo "Starting script to test Minishell commands"
echo "-------------------------------------------"

# List of commands to test
commands=(
    "echo Hello World"
    "echo \"Double quotes test\""
    "echo 'Single quotes test'"
    "env"
    "export TEST_VAR=42"
    "echo \$TEST_VAR"
    "unset TEST_VAR"
    "echo \$?"
    "pwd"
    "cd .."
    "pwd"
    "cat < /etc/passwd"
    "grep root < /etc/passwd"
    "echo Hello World > testfile.txt"
    "cat testfile.txt"
    "echo Append test >> testfile.txt"
    "cat testfile.txt"
    "cat testfile.txt | grep Append"
    "rm testfile.txt"
)

# Execute each command using the run_command function
for cmd in "${commands[@]}"; do
    run_command "$cmd"
done

# End of the script
echo "Script to test Minishell commands completed"
