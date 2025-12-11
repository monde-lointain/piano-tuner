##############################
# Complexity Analysis Module #
##############################
#
# This module provides complexity analysis targets to the build.
#
# You can control the behavior of lizard by setting the following variables
# before you include this module:
#   LIZARD_DIRS, which is a CMake list of directories to include in complexity analysis
#     By default, the src and test directories are included
#   LIZARD_EXCLUDES, which is a CMake list of directories/files to exclude from analysis
#     By default, this variable is not set
#   LIZARD_LENGTH_LIMIT, which specifies the maximum funtion length in lines
#   LIZARD_CCN_LIMIT, which specifies the maximum CCN limit
#   LIZARD_ARG_LIMIT, which specifies the maximum number of arguments
#
# You can completely override the default vaules by setting the variables above.
# You can also add to the defaults by defining these variables:
#   LIZARD_ADDITIONAL_DIRS, which is a CMake List of directories to include
#   LIZARD_ADDITIONAL_OPTIONS, which is a CMake list of additional flags and values to pass to Lizard
# Find Lizard executable

find_program(LIZARD lizard)

if(NOT LIZARD)
    message(WARNING "Lizard is not installed. Complexity targets are disabled.")
    return()
endif()

# -----------------------------
# Default configuration
# -----------------------------
set(DEFAULT_LIZARD_DIRS "src")
set(DEFAULT_LENGTH_LIMIT 60)
set(DEFAULT_CCN_LIMIT 10)
set(DEFAULT_ARG_LIMIT 6)

# Use user-defined variables if provided
set(LIZARD_DIRS ${LIZARD_DIRS})
if(NOT LIZARD_DIRS)
    set(LIZARD_DIRS ${DEFAULT_LIZARD_DIRS})
endif()

# Append any additional directories
if(LIZARD_ADDITIONAL_DIRS)
    list(APPEND LIZARD_DIRS ${LIZARD_ADDITIONAL_DIRS})
endif()

# Set limits
set(LIZARD_LENGTH_LIMIT ${LIZARD_LENGTH_LIMIT})
if(NOT LIZARD_LENGTH_LIMIT)
    set(LIZARD_LENGTH_LIMIT ${DEFAULT_LENGTH_LIMIT})
endif()

set(LIZARD_CCN_LIMIT ${LIZARD_CCN_LIMIT})
if(NOT LIZARD_CCN_LIMIT)
    set(LIZARD_CCN_LIMIT ${DEFAULT_CCN_LIMIT})
endif()

set(LIZARD_ARG_LIMIT ${LIZARD_ARG_LIMIT})
if(NOT LIZARD_ARG_LIMIT)
    set(LIZARD_ARG_LIMIT ${DEFAULT_ARG_LIMIT})
endif()

# Prepare exclude arguments
set(LIZARD_EXCLUDE_ARGS "")
if(LIZARD_EXCLUDES)
    foreach(EXCLUDE_PATH ${LIZARD_EXCLUDES})
        list(APPEND LIZARD_EXCLUDE_ARGS -x ${EXCLUDE_PATH})
    endforeach()
endif()

# Base Lizard command
set(LIZARD_BASE_ARGS
    ${LIZARD}
    --length ${LIZARD_LENGTH_LIMIT}
    --CCN ${LIZARD_CCN_LIMIT}
    --arguments ${LIZARD_ARG_LIMIT}
    ${LIZARD_EXCLUDE_ARGS}
    ${LIZARD_ADDITIONAL_OPTIONS}
)

# -----------------------------
# Complexity Targets
# -----------------------------

# Warnings only
add_custom_target(complexity
    COMMAND ${LIZARD_BASE_ARGS} -w ${LIZARD_DIRS}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running Lizard complexity analysis (warnings only)"
)

# Full analysis
add_custom_target(complexity-full
    COMMAND ${LIZARD_BASE_ARGS} ${LIZARD_DIRS}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Running Lizard full complexity analysis"
)

# XML output
set(COMPLEXITY_XML_FILE "${CMAKE_BINARY_DIR}/complexity.xml")
add_custom_target(complexity-xml
    COMMAND ${LIZARD_BASE_ARGS} --xml ${LIZARD_DIRS} > ${CMAKE_BINARY_DIR}/complexity.xml
    BYPRODUCTS ${CMAKE_BINARY_DIR}/complexity.xml
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating Lizard complexity XML report at ${CMAKE_BINARY_DIR}/complexity.xml"
)
