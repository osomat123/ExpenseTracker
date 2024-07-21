# CMakeList.txt : CMake project for AppCLI, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable(AppCLI
    main.cpp
    UserInputCli.h)

target_include_directories(AppCLI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(AppCLI PUBLIC ExpenseTracker)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET AppCLI PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
