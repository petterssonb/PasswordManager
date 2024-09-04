# Minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(passwordManager VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Compiler flags to not show deprecated warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" OR CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_options(-Wno-deprecated-declarations)
endif()

# Define source and include directories
set(SRC_DIR src)
set(INC_DIR include)

# Add source files
set(SRC_FILES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/passwordManager.cpp
)

# Include directories for headers
include_directories(${INC_DIR})

# Detect the platform and set libraries
if(WIN32)
    set(LIBS ssl crypto)
    add_executable(main.exe ${SRC_FILES})
    target_link_libraries(main.exe ${LIBS})
    include_directories(${INC_DIR})
elseif(APPLE)
    # macOS specific settings for OpenSSL
    set(LIBS /opt/homebrew/opt/openssl@3/lib/libssl.dylib /opt/homebrew/opt/openssl@3/lib/libcrypto.dylib)
    include_directories(/opt/homebrew/opt/openssl@3/include ${INC_DIR})
    add_executable(main ${SRC_FILES})
    target_link_libraries(main ${LIBS})
else()
    # Linux settings
    set(LIBS ssl crypto)
    add_executable(main ${SRC_FILES})
    target_link_libraries(main ${LIBS})
endif()

# Optional: You can add Cppcheck target if you want static analysis in CMake
# find_program(CPPCHECK cppcheck)
# if(CPPCHECK)
#     # Set OpenSSL include path for macOS (adjust for Linux/Windows as needed)
#     if(APPLE)
#         set(OPENSSL_INCLUDE_DIR /opt/homebrew/opt/openssl@3/include)
#     endif()

#     # Add Cppcheck target for static analysis
#     add_custom_target(
#         cppcheck ALL
#         COMMAND ${CPPCHECK}
#         --quiet
#         --enable=all
#         --error-exitcode=1
#         --inline-suppr
#         -I${CMAKE_SOURCE_DIR}/include              # Include project headers
#         -I${CMAKE_SOURCE_DIR}/src                  # Include source files
#         -I${OPENSSL_INCLUDE_DIR}                   # OpenSSL include directory
#         -I/usr/include                             # System include directory (macOS/Linux)
#         -I/usr/local/include                       # Another common system include directory (optional)
#         ${SRC_FILES}
#         WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#         COMMENT "Running cppcheck"
#     )
# endif()