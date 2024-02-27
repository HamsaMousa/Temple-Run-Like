cmake_minimum_required(VERSION 3.10)
project(TempleRun LANGUAGES CXX)

set(SRCDIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDEDIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(ASSETSDIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
file(GLOB_RECURSE SRC "${SRCDIR}/*.cpp")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()


# Conditional compilation flags based on the build type
if(CMAKE_BUILD_TYPE MATCHES Debug)
  set(CMAKE_CXX_FLAGS "-MMD -MP -pedantic -Wall -Wextra -Wold-style-cast -Wshadow -Wwrite-strings")
  set(CMAKE_CXX_FLAGS_DEBUG "-g")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
  set(CMAKE_CXX_FLAGS "-MMD -MP -pedantic -w") # -w disables all warning messages
  set(CMAKE_CXX_FLAGS_RELEASE "-O2")
endif()

find_package(SFML 2.5 COMPONENTS audio graphics window system REQUIRED)

include_directories(${SRCDIR} ${INCLUDEDIR})

add_executable(TempleRun ${SRC})

# Set the output directory for the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

target_link_libraries(TempleRun sfml-audio sfml-graphics sfml-window sfml-system)

# -------------------------------------------------------------------
# COPY NECESSARY FILES TO BUILD FOLDER
# -------------------------------------------------------------------
# Copy assets to the build folder
add_custom_command(TARGET TempleRun POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ASSETSDIR}"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/assets"
    COMMENT "Copying assets to build folder"
)

# Copy "resources" folder to build directory
add_custom_command(TARGET TempleRun POST_BUILD
                  COMMAND ${CMAKE_COMMAND} -E copy_directory
                  ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:TempleRun>/resources)

# -------------------------------------------------------------------
# VALGRIND
# -------------------------------------------------------------------
# Add a custom target to run valgrind with the executable as argument
#find_program(VALGRIND_EXE valgrind)
#if(VALGRIND_EXE)
#  add_custom_target(valgrind
#    #COMMAND ${VALGRIND_EXE} --leak-check=full --show-leak-kinds=all $<TARGET_FILE:TempleRun>
#    COMMAND ${VALGRIND_EXE} --leak-check=full $<TARGET_FILE:TempleRun>
#    COMMENT "Running Valgrind on the executable"
#  )
#endif()

# -------------------------------------------------------------------
# TESTS
# -------------------------------------------------------------------
# Add a new executable for the tests
add_executable(TempleRunTests tests/tests.cpp)

# Add the necessary source files to the tests executable
file(GLOB_RECURSE TEST_SRC "${SRCDIR}/*.cpp")
list(REMOVE_ITEM TEST_SRC "${SRCDIR}/main.cpp")  # Exclude main.cpp from tests
target_sources(TempleRunTests PRIVATE ${TEST_SRC})

# Link the Catch2 library with the tests executable
target_link_libraries(TempleRunTests PRIVATE sfml-audio sfml-graphics sfml-window sfml-system)

# Include the "tests" folder as an include directory
target_include_directories(TempleRunTests PRIVATE tests)

# Copy assets to the build folder for the tests
add_custom_command(TARGET TempleRunTests POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${ASSETSDIR}"
        "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_CFG_INTDIR}/assets"
    COMMENT "Copying assets to build folder for tests"
)

# Copy "resources" folder to build directory for the tests
add_custom_command(TARGET TempleRunTests POST_BUILD
                  COMMAND ${CMAKE_COMMAND} -E copy_directory
                  ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:TempleRunTests>/resources)


# -------------------------------------------------------------------
# CLEANING
# -------------------------------------------------------------------
# Add a custom target to clean all generated files
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/CMakeFiles
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/bin
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}/lib
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/CMakeCache.txt
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/cmake_install.cmake
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/Makefile
)

# Add a custom command to run "make clean-all" to the "clean" target
add_custom_target(vclean
    COMMAND ${CMAKE_MAKE_PROGRAM} clean-all
)
