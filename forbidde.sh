#!/bin/bash
forbidden_functions()
{
	if [ $# -lt 2 ]; then
		echo "Usage: forbidden_functions <binary> <allowed_functions>"
		echo "Example: forbidden_functions ./myprogram 'printf,malloc,free'"
		echo "		or: forbidden_functions ./myprogram printf malloc free"
		return 1
	fi
	
	local binary="$1"
	shift
	
	# Check if binary exists and is readable
	if [[ ! -r "$binary" ]]; then
		echo "Error: Cannot read binary '$binary'" >&2
		return 1
	fi
	
	# Handle multiple arguments or single string with separators
	local allowed_input="$*"
	echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	echo " \033[1;32m✔\033[0m Checking binary: $binary"
	echo " \033[1;32m✔\033[0m Allowed functions: $allowed_input"
	echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	
	# Normalize allowed functions: convert separators to spaces, remove duplicates, filter out system functions
	local allowed_functions
	allowed_functions=($(echo "$allowed_input" | tr ',\t\n' ' ' | tr -s ' ' | xargs -n1 | sort -u))
	
	# Add common system functions that should typically be ignored
	local system_functions=("__libc_start_main" "__gmon_start__" "_start" "_init" "_fini")
	for sys_func in "${system_functions[@]}"; do
		allowed_functions+=("$sys_func")
	done
	
	# Try multiple methods to extract used functions
	local used_functions
	
	# Method 1: nm -D (dynamic symbols)
	used_functions=$(nm -D --undefined-only "$binary" 2>/dev/null \
		| awk '/U / {print $NF}' \
		| sed 's/@.*//' \
		| sort -u)
	
	# Method 2: objdump if nm fails
	if [[ -z "$used_functions" ]]; then
		used_functions=$(objdump -T "$binary" 2>/dev/null \
			| awk '$2 ~ /\*UND\*/ && NF >= 7 {print $NF}' \
			| sed 's/@.*//' \
			| sort -u)
	fi
	
	# Method 3: readelf if objdump fails
	if [[ -z "$used_functions" ]]; then
		used_functions=$(readelf -Ws "$binary" 2>/dev/null \
			| awk '$4 == "UND" && $5 == "GLOBAL" && NF >= 8 {print $8}' \
			| sed 's/@.*//' \
			| sort -u)
	fi
	
	# Method 4: ldd + nm combination (for some edge cases)
	if [[ -z "$used_functions" ]]; then
		used_functions=$(nm -u "$binary" 2>/dev/null \
			| awk '{print $NF}' \
			| sed 's/@.*//' \
			| sort -u)
	fi
	
	if [[ -z "$used_functions" ]]; then
		echo "Error: No external functions found using nm, objdump, readelf, or ldd" >&2
		echo "This might be a statically linked binary or unsupported format" >&2
		# Debug info
		echo "Debug: file type of '$binary':" >&2
		file "$binary" >&2
		return 1
	fi
	
	# Use associative array for O(1) lookup instead of nested loops
	local -A allowed_set
	for func in "${allowed_functions[@]}"; do
		allowed_set[$func]=1
	done
	
	# Find and print forbidden functions
	local forbidden_found=0
	local forbidden_list=()
	
	while IFS= read -r func; do
		if [[ -z "${allowed_set[$func]:-}" ]]; then
			forbidden_list+=("$func")
			forbidden_found=1
		fi
	done <<< "$used_functions"
	
	if [[ $forbidden_found -eq 1 ]]; then
		echo " \033[1;31m✖\033[0m Forbidden functions found:"
		for func in "${forbidden_list[@]}"; do
			echo "   \033[1;31m•\033[0m $func"
		done
	else
		echo " \033[1;32m✔\033[0m No forbidden functions found!"
	fi
	
	echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
	
	return $forbidden_found
}