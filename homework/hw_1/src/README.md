## Configure and build
`sh cmake_build.sh`

## Run all tests
`sh run_tests.sh`

## Convert string to test input
`g++ tests/string_to_test_converter.cpp -o ./tests/string_to_test_converter.out && ./tests/string_to_test_converter.out`

## Tests runtime
`sh run_tests.sh`

Run test01
...
Runtime: .003074 ms

Run test02
...
Runtime: .003175 ms

Run test03
...
Runtime: .003137 ms

Run test04
...
Runtime: .003519 ms

Run test05
...
Runtime: .009421 ms

Run test random 1000
...
Runtime: .099407 ms