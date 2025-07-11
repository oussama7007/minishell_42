#!/bin/bash

# Output file
OUTPUT_FILE="combined.txt"

# Clear the output file if it already exists
> "$OUTPUT_FILE"

# Function to append file content with its path
append_file() {
    local file_path="$1"
    echo "// Path: $file_path" >> "$OUTPUT_FILE"
    cat "$file_path" >> "$OUTPUT_FILE"
    echo -e "\n" >> "$OUTPUT_FILE"
}

# Iterate through all *.h and *.c files, excluding the LIBFT folder
find ./srcs -type f \( -name "*.h" -o -name "*.c" \) ! -path "./srcs/c_spuvr/LIBFT/*" | while read -r file; do
    append_file "$file"
done

echo "All files have been combined into $OUTPUT_FILE"
