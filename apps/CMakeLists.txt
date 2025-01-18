add_executable(shell shell.c)
target_link_libraries(shell PRIVATE shell-utils)

# Default optimization
add_executable(benchmark benchmark.c)
target_link_libraries(benchmark PRIVATE loaders argtable3)

# O1 optimization
add_executable(benchmark-O1 benchmark.c)
target_link_libraries(benchmark-O1 PRIVATE loaders argtable3)
target_compile_options(benchmark-O1 PRIVATE -O1)

# O2 optimization
add_executable(benchmark-O2 benchmark.c)
target_link_libraries(benchmark-O2 PRIVATE loaders argtable3)
target_compile_options(benchmark-O2 PRIVATE -O2)

# O3 optimization
add_executable(benchmark-O3 benchmark.c)
target_link_libraries(benchmark-O3 PRIVATE loaders argtable3)
target_compile_options(benchmark-O3 PRIVATE -O3)
