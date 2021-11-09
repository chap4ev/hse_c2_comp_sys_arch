for VARIABLE in 01 02 03 04 05
do
    echo "\nRun test$VARIABLE\n"
    start=$(date +%s.%6N)
    python3 main.py -f ./tests/test$VARIABLE.txt ./tests/output/out$VARIABLE-1.txt ./tests/output/out$VARIABLE-2.txt
    echo "Runtime: "$(echo "scale=6; $(date +%s.%6N) - $start" | bc)" ms"
done

echo "\nRun test random 1000\n"
start=$(date +%s.%6N)
python3 main.py -n 1000 ./tests/output/outrand-1.txt ./tests/output/outrand-2.txt
echo "Runtime: "$(echo "scale=6; $(date +%s.%6N) - $start" | bc)" ms"