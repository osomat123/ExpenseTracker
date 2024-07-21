# CMakeList.txt : CMake project for ExpenseTracker, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_library(ExpenseTracker STATIC
    Expense.h
    Expense.cpp
    Date.h
    Date.cpp
    ExpenseTracker.h
    ExpenseTracker.cpp
    MappingInfo.h
    MappingInfo.cpp "IUserInput.h")

target_include_directories(ExpenseTracker PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ExpenseTracker PUBLIC OpenXLSX)



if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ExpenseTracker PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
