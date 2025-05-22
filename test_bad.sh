#!/bin/bash
# filepath: /home/nmellal/final_cub3d/test_bad_maps.sh

# ANSI color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${YELLOW}===== Testing cub3D with invalid maps =====${NC}"
echo

# Check for cub3D executable
if [ ! -f "./cub3D" ]; then
    echo -e "${RED}Error: cub3D executable not found${NC}"
    exit 1
fi

# Check for valgrind
if ! command -v valgrind &> /dev/null; then
    echo -e "${RED}Error: valgrind is not installed. Please install it with 'sudo apt-get install valgrind'${NC}"
    exit 1
fi

# Make sure it's executable
chmod +x ./cub3D

total_maps=0
passed=0
failed=0
leaks_detected=0

# Process all files in maps/bad
for map_file in maps/bad/*; do
    if [ -f "$map_file" ]; then
        ((total_maps++))
        map_name=$(basename "$map_file")
        
        echo -e "\n${YELLOW}Testing: ${map_name}${NC}"
        
        # Run cub3D with the map file and capture output
        output=$(./cub3D "$map_file" 2>&1)
        exit_code=$?
        
        # The program should exit with non-zero status for bad maps
        if [ $exit_code -ne 0 ]; then
            echo -e "${GREEN}✓ Program correctly rejected the map (exit code: $exit_code)${NC}"
            echo -e "  Output: ${output}"
            ((passed++))
        else
            echo -e "${RED}✗ Program accepted an invalid map! (exit code: $exit_code)${NC}"
            echo -e "  Output: ${output}"
            ((failed++))
        fi
        
        # Run with valgrind to check for memory leaks
        echo -e "\n${BLUE}Running Valgrind on ${map_name}:${NC}"
        valgrind_output=$(valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./cub3D "$map_file" 2>&1)
        
        # Check for memory leaks in the valgrind output
        if echo "$valgrind_output" | grep -q "definitely lost"; then
            echo -e "${RED}❌ Memory leaks detected!${NC}"
            ((leaks_detected++))
            
            # Extract and display leak summary
            leak_summary=$(echo "$valgrind_output" | grep -A 4 "LEAK SUMMARY")
            echo -e "${RED}$leak_summary${NC}"
        else
            echo -e "${GREEN}✅ No memory leaks detected${NC}"
        fi
        
        # Show full valgrind output if requested (uncomment to enable)
        # echo -e "${BLUE}Full Valgrind output:${NC}\n$valgrind_output"
        echo "-----------------------------------------------------------"
    fi
done

# Print summary
echo -e "\n${YELLOW}===== Testing Summary =====${NC}"
echo -e "Total maps tested: ${total_maps}"
echo -e "${GREEN}Correctly rejected: ${passed}${NC}"
echo -e "${RED}Incorrectly accepted: ${failed}${NC}"
echo -e "${RED}Maps with memory leaks: ${leaks_detected}${NC}"

if [ $failed -eq 0 ] && [ $leaks_detected -eq 0 ]; then
    echo -e "${GREEN}All invalid maps were correctly rejected with no memory leaks!${NC}"
    exit 0
elif [ $failed -eq 0 ]; then
    echo -e "${YELLOW}All invalid maps were correctly rejected, but memory leaks were detected.${NC}"
    exit 2
elif [ $leaks_detected -eq 0 ]; then
    echo -e "${RED}Some invalid maps were incorrectly accepted, but no memory leaks were detected.${NC}"
    exit 1
else
    echo -e "${RED}Some invalid maps were incorrectly accepted and memory leaks were detected.${NC}"
    exit 3
fi