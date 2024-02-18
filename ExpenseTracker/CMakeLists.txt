# CMakeList.txt : CMake project for ExpenseTracker, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (ExpenseTracker "main.cpp"  "Expense.h" "Expense.cpp" "Date.h" "Date.cpp" "ExpenseTracker.h" "ExpenseTracker.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ExpenseTracker PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
