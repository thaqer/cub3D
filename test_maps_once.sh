#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Create reports directory if it doesn't exist
REPORTS_DIR="valgrind_reports"
mkdir -p "$REPORTS_DIR"

echo -e "${BLUE}=== CUB3D Memory Leak Single Test ===${NC}\n"

# Clean and rebuild
echo -e "${YELLOW}Building project...${NC}"
make re > /dev/null 2>&1

if [ ! -f "./cub3D" ]; then
    echo -e "${RED}Build failed! Exiting...${NC}"
    exit 1
fi

echo -e "${GREEN}Build successful!${NC}\n"

TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

# Test all bad maps
echo -e "${BLUE}Testing BAD maps (should exit with error):${NC}"
for map in maps/bad/*; do
    if [ -f "$map" ]; then
        TOTAL_TESTS=$((TOTAL_TESTS + 1))
        MAP_NAME=$(basename "$map")
        REPORT_FILE="$REPORTS_DIR/bad_${MAP_NAME}.log"
        
        echo -n "  Testing $MAP_NAME... "
        
        # Run valgrind
        valgrind --leak-check=full \
                 --show-leak-kinds=all \
                 --track-origins=yes \
                 --log-file="$REPORT_FILE" \
                 ./cub3D "$map" > /dev/null 2>&1
        
        # Check for leaks
        if grep -q "ERROR SUMMARY: 0 errors" "$REPORT_FILE" && \
           grep -q "All heap blocks were freed -- no leaks are possible" "$REPORT_FILE"; then
            echo -e "${GREEN}✓ SUCCESS (no leaks)${NC}"
            PASSED_TESTS=$((PASSED_TESTS + 1))
            rm "$REPORT_FILE"  # Clean up successful tests
        else
            echo -e "${RED}✗ LEAKS DETECTED${NC}"
            FAILED_TESTS=$((FAILED_TESTS + 1))
            echo -e "${YELLOW}    Report saved: $REPORT_FILE${NC}"
            
            # Show leak summary
            LEAKED=$(grep "definitely lost:" "$REPORT_FILE" | awk '{print $4, $5}')
            INDIRECT=$(grep "indirectly lost:" "$REPORT_FILE" | awk '{print $4, $5}')
            if [ ! -z "$LEAKED" ]; then
                echo -e "${RED}    Definitely lost: $LEAKED${NC}"
            fi
            if [ ! -z "$INDIRECT" ]; then
                echo -e "${RED}    Indirectly lost: $INDIRECT${NC}"
            fi
        fi
    fi
done

# Final summary
echo -e "\n${BLUE}========================================${NC}"
echo -e "${BLUE}Test Summary:${NC}"
echo -e "${BLUE}========================================${NC}"
echo -e "Total tests: $TOTAL_TESTS"
echo -e "${GREEN}Passed: $PASSED_TESTS${NC}"
echo -e "${RED}Failed: $FAILED_TESTS${NC}"

if [ $FAILED_TESTS -eq 0 ]; then
    echo -e "\n${GREEN}🎉 ALL TESTS PASSED! NO MEMORY LEAKS! 🎉${NC}"
else
    echo -e "\n${RED}⚠️  Some tests failed. Check reports in: $REPORTS_DIR/${NC}"
fi

# Clean up
echo -e "\n${YELLOW}Cleaning up...${NC}"
make fclean > /dev/null 2>&1

echo -e "${GREEN}Done!${NC}"
