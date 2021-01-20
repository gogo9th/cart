#!/bin/bash

answers=(
100
370
280
270
375
50
30
20
15
130
45
30
95
0
)
for (( i = 1; i <= ${#answers[@]}; i++)); do
	echo "<Test $i>"
	./sku test$i.txt
	echo "- Expected Total Price: ${answers[$((i - 1))]}"
	echo
done
