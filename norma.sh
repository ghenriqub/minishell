#!/bin/bash
norm()
{
	clear
	local target_dir="."
	
	# Check if an argument was provided
	if [ $# -eq 1 ]; then
		target_dir="$1"
		# Check if the provided directory exists
		if [ ! -d "$target_dir" ]; then
			echo -e "\033[1;91m✖ Error: Directory '$target_dir' does not exist\033[0m"
			return 1
		fi
	elif [ $# -gt 1 ]; then
		echo -e "\033[1;93m[USAGE]\033[0m norm [directory]"
		echo "	directory: optional path to check (defaults to current directory)"
		return 1
	fi
	
	# Run norminette and remove "OK" and the locale line
	output=$(norminette -R CheckForbiddenSourceHeader -R CheckDefine $target_dir | grep -v -e "OK" -e "Setting locale")

	if [ -z "$output" ]; then
		# No other output
		echo -e "\033[1;92m✔ All good! Your code passed Norminette!\033[0m"
	else
		# Show errors/warnings
		echo -e "$output"
	fi
}