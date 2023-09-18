pushd ../pure_inst > /dev/null && make -s
popd > /dev/null && cp ../pure_inst/payload.bin ./assets

includes=$(find -E . -iregex  ".*\.h" | xargs dirname | sort -u | awk '{printf("-I %s ", $0)}')
files=$(find -E . -iregex ".*\.(c|s)")

cc $files -g $includes -o rv64 && ./rv64
