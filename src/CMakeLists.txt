file(GLOB_RECURSE SHELL_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/shell/*.h")
file(GLOB_RECURSE SHELL_LIB_SRC CONFIGURE_DEPENDS "shell/*.c")
add_library(shell-utils ${SHELL_LIB_SRC} ${SHELL_HEADER_LIST})
target_include_directories(shell-utils PUBLIC "${PROJECT_SOURCE_DIR}/include")

file(GLOB_RECURSE LOADER_HEADER_LIST CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/loaders/*.h")
file(GLOB_RECURSE LOADER_LIB_SRC CONFIGURE_DEPENDS "loaders/*.c")
add_library(loaders ${LOADER_LIB_SRC} ${LOADER_HEADER_LIST})
target_include_directories(loaders PUBLIC "${PROJECT_SOURCE_DIR}/include")
