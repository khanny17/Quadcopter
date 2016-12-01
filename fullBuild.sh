if [ ! -d "build" ]; then
    mkdir build
fi

cd build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ../src/
cppcheck --project=compile_commands.json --enable=all
make
