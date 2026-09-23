build:
    cmake -B build -DCMAKE_BUILD_TYPE=Release
    cp build/compile_commands.json .
    cmake --build build --target gb

format:
    clang-format -i include/**.hpp src/**.cpp

check:
    clang-tidy include/**.hpp src/**.cpp

fix:
    clang-tidy --fix include/**.hpp src/**.cpp

run:
    cmake -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build --target gb
    ./build/gb

run_debug:
    cmake -B build_debug -DCMAKE_BUILD_TYPE=Debug
    cmake --build build_debug --target gb
    ./build_debug/gb

clean:
    rm -rf build
    rm -rf build_debug
