set terminal wxt size 1000,700

set title "Merging k Sorted Arrays - Method 1 vs Method 2"

set xlabel "Number of Arrays (k)"
set ylabel "Growth"

set grid
set key outside

plot \
"q3_merge.txt" using 1:2 with lines title "Method 1 O(nk^2)", \
"q3_merge.txt" using 1:3 with lines title "Method 2 O(nk log k)"

pause -1