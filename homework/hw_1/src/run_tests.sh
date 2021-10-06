echo "\nRun test01\n"
./bin/hw1 -f ./tests/test01.txt ./tests/out01-1 ./tests/out01-2

echo "\nRun test02\n"
./bin/hw1 -f ./tests/test02.txt ./tests/out02-1 ./tests/out02-2

echo "\nRun test03\n"
./bin/hw1 -f ./tests/test03.txt ./tests/out03-1 ./tests/out03-2

echo "\nRun test04\n"
./bin/hw1 -f ./tests/test04.txt ./tests/out04-1 ./tests/out04-2

echo "\nRun test05\n"
./bin/hw1 -f ./tests/test05.txt ./tests/out05-1 ./tests/out05-2

echo "\nRun test random\n"
./bin/hw1 -n 100 ./tests/outrand-1 ./tests/outrand-2
