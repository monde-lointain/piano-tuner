###################
# CppCheck Module #
###################
#
# This module provides `cppcheck` and `cppcheck-xml` targets, as well as an option
# to enable building the project with cppcheck analysis.
#
# To enable cppcheck output during the build process, set the `BUILD_WITH_CPPCHECK_ANALYSIS`
# option to "ON"
#
# You can control the behavior of cppcheck by setting the following variables
# before you include this module:
#   CPPCHECK_ENABLE_CHECKS, which is passed to the --enable= argument
#     By default, "style" is used
#   CPPCHECK_DIRS, which is a CMake list of directories to include in cppcheck analysis
#     By default, the src and test directories are included
#   CPPCHECK_INCLUDE_DIRS, which is a CMake list of directories to pass as include arguments
#     to CppCheck
#     By default, no include directories are specified.
#  CPPCHECK_EXCLUDES, which is a CMake list of directories or files to exclude from analysis.
#     By defaulut, no excludes are specified
#
# You can completely override the default vaules by setting the variables above.
# If you wish to use the defaults for CPPCHECK_DIRS but add additional directories or files,
# you can set the CPPCHECK_ADDITIONAL_DIRS variable.

find_program(CPPCHECK cppcheck)

if(NOT CPPCHECK)
    message(WARNING "CppCheck is not installed. CppCheck targets are disabled.")
    return()
endif()

# --- User-configurable options ---
set(CPPCHECK_ENABLE_CHECKS "style" CACHE STRING "Checks to enable in cppcheck")
set(CPPCHECK_DIRS "src" CACHE STRING "Directories to analyze with cppcheck")
set(CPPCHECK_INCLUDE_DIRS "" CACHE STRING "Include directories for cppcheck")
set(CPPCHECK_EXCLUDES "" CACHE STRING "Files/directories to exclude from cppcheck")
set(CPPCHECK_ADDITIONAL_DIRS "" CACHE STRING "Additional directories to analyze")
set(CPPCHECK_CUSTOM_RULES "" CACHE STRING "Custom cppcheck rule XML files")
set(CPPCHECK_ADDITIONAL_CUSTOM_RULES "" CACHE STRING "Additional custom rule files")

option(BUILD_WITH_CPPCHECK_ANALYSIS "Compile the project with cppcheck support" OFF)

# --- Prepare directory lists ---
if(CPPCHECK_ADDITIONAL_DIRS)
  list(APPEND CPPCHECK_DIRS ${CPPCHECK_ADDITIONAL_DIRS})
endif()

# --- Include/exclude arguments ---
set(CPPCHECK_INCLUDE_ARGS "")
foreach(dir ${CPPCHECK_INCLUDE_DIRS})
  list(APPEND CPPCHECK_INCLUDE_ARGS -I ${dir})
endforeach()

set(CPPCHECK_EXCLUDE_ARGS "")
foreach(path ${CPPCHECK_EXCLUDES})
  list(APPEND CPPCHECK_EXCLUDE_ARGS -i ${path})
endforeach()

# --- Default custom rules ---
if(NOT CPPCHECK_CUSTOM_RULES)
  set(CPPCHECK_CUSTOM_RULES
    ${CMAKE_CURRENT_LIST_DIR}/cppcheck-rules/BitwiseOperatorInConditional/rule.xml
    ${CMAKE_CURRENT_LIST_DIR}/cppcheck-rules/CollapsibleIfStatements/rule.xml
    ${CMAKE_CURRENT_LIST_DIR}/cppcheck-rules/EmptyElseBlock/rule.xml
    ${CMAKE_CURRENT_LIST_DIR}/cppcheck-rules/EmptyCatchStatement/rule.xml
    ${CMAKE_CURRENT_LIST_DIR}/cppcheck-rules/EmptyDoWhileStatement/rule.xml
    ${CMAKE_CURRENT_LIST_DIR}/cppcheck-rules/EmptyForStatement/rule.xml
    ${CMAKE_CURRENT_LIST_DIR}/cppcheck-rules/EmptyIfStatement/rule.xml
    ${CMAKE_CURRENT_LIST_DIR}/cppcheck-rules/EmptySwitchStatement/rule.xml
    ${CMAKE_CURRENT_LIST_DIR}/cppcheck-rules/ForLoopShouldBeWhileLoop/rule.xml
    ${CMAKE_CURRENT_LIST_DIR}/cppcheck-rules/InvertedLogic/rule.xml
    ${CMAKE_CURRENT_LIST_DIR}/cppcheck-rules/MultipleUnaryOperator/rule.xml
    ${CMAKE_CURRENT_LIST_DIR}/cppcheck-rules/RedundantConditionalOperator/rule.xml
    ${CMAKE_CURRENT_LIST_DIR}/cppcheck-rules/RedundantIfStatement/rule.xml
    ${CMAKE_CURRENT_LIST_DIR}/cppcheck-rules/UnnecessaryElseStatement/rule.xml
    ${CMAKE_CURRENT_LIST_DIR}/cppcheck-rules/UseStlAlgorithm/rule.xml
  )
endif()

if(CPPCHECK_ADDITIONAL_CUSTOM_RULES)
  list(APPEND CPPCHECK_CUSTOM_RULES ${CPPCHECK_ADDITIONAL_CUSTOM_RULES})
endif()

set(CPPCHECK_RULE_ARGS "")
foreach(rule ${CPPCHECK_CUSTOM_RULES})
  list(APPEND CPPCHECK_RULE_ARGS --rule-file=${rule})
endforeach()

# --- Build CppCheck argument list ---
set(CPPCHECK_ARGS
  ${CPPCHECK} --quiet --enable=${CPPCHECK_ENABLE_CHECKS} --force
  ${CPPCHECK_INCLUDE_ARGS}
  ${CPPCHECK_EXCLUDE_ARGS}
  ${CPPCHECK_RULE_ARGS}
)

# --- Enable cppcheck during build ---
if(BUILD_WITH_CPPCHECK_ANALYSIS)
  set(CMAKE_C_CPPCHECK "${CPPCHECK_ARGS}")
  set(CMAKE_CXX_CPPCHECK "${CPPCHECK_ARGS}")
endif()

# --- Add custom targets ---
add_custom_target(cppcheck
  COMMAND ${CPPCHECK_ARGS} ${CPPCHECK_DIRS}
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_custom_target(cppcheck-xml
  COMMAND ${CPPCHECK_ARGS} --xml --xml-version=2 ${CPPCHECK_DIRS} 2>${CMAKE_BINARY_DIR}/cppcheck.xml
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

