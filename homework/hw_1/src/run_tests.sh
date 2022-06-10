for VARIABLE in 01 02 03 04 05
do
    echo "\nRun test$VARIABLE\n"
    start=$(date +%s.%6N)
    ./bin/hw1 -f ./tests/test$VARIABLE.txt ./tests/out$VARIABLE-1 ./tests/out$VARIABLE-2
    echo "Runtime: "$(echo "scale=6; $(date +%s.%6N) - $start" | bc)" ms"
done

echo "\nRun test random 1000\n"
start=$(date +%s.%6N)
./bin/hw1 -n 1000 ./tests/outrand-1 ./tests/outrand-2
echo "Runtime: "$(echo "scale=6; $(date +%s.%6N) - $start" | bc)" ms"