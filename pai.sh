g++ -o test -std=c++20 test.cpp
g++ -o test__Good -std=c++20 test__Good.cpp
g++ -o test__Generator -std=c++20 test__Generator.cpp
i=1
echo "Running duipai"
while true; do
  echo "Test $i"
  ./test__Generator > data.in
  ./test < data.in > data.out
  ./test__Good < data.in > data__Good.out
  if diff data.out data__Good.out; then
    echo "AC"
  else
    echo "WA"
    echo "Input:"
    cat data.in
    echo "Output:"
    cat data.out
    echo "Expected:"
    cat data__Good.out
    break
  fi
  i=$((i + 1))
done 