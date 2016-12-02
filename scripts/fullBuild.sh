checkExit () {
    if [ $? -eq 0 ]
    then
        echo $1
    else
        echo "Exiting build due to: $2" >&2
        exit 1
    fi
}



if [ -d "build" ]; then
    echo "Cleaning build/"
    rm -rf build
fi

mkdir build
cd build

cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
checkExit "" "cmake failure"

cppcheck --project=compile_commands.json --enable=all --error-exitcode=1
#TODO when you feel confident, put this back in:
#checkExit "" "cppcheck failure"

make
checkExit "" "make failure"

make test
checkExit "" "make test failure"
