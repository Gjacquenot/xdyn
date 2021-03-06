# - Returns a version string from Git
#
# These functions force a re-configure on each git commit so that you can
# trust the values of the variables in your build system.
#
#  get_git_head_revision(<refspecvar> <hashvar> [<additional arguments to git describe> ...])
#
# Returns the refspec and sha hash of the current head revision
#
#  git_describe(<var> [<additional arguments to git describe> ...])
#
# Returns the results of git describe on the source tree, and adjusting
# the output so that it tests false if an error occurs.
#
#  git_get_exact_tag(<var> [<additional arguments to git describe> ...])
#
# Returns the results of git describe --exact-match on the source tree,
# and adjusting the output so that it tests false if there was no exact
# matching tag.
#
# Requires CMake 2.6 or newer (uses the 'function' command)
#
# Original Author:
# 2009-2010 Ryan Pavlik <rpavlik@iastate.edu> <abiryan@ryand.net>
# http://academic.cleardefinition.com
# Iowa State University HCI Graduate Program/VRAC
#
# Copyright Iowa State University 2009-2010.
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at
# http://www.boost.org/LICENSE_1_0.txt)

if(__get_git_revision_description)
	return()
endif()
set(__get_git_revision_description YES)

# We must run the following at "include" time, not at function call time,
# to find the path to this module rather than the path to a calling list file
get_filename_component(_gitdescmoddir ${CMAKE_CURRENT_LIST_FILE} PATH)

function(get_git_head_revision _refspecvar _hashvar)
	set(GIT_PARENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
	set(GIT_DIR "${GIT_PARENT_DIR}/.git")
	while(NOT EXISTS "${GIT_DIR}")	# .git dir not found, search parent directories
		set(GIT_PREVIOUS_PARENT "${GIT_PARENT_DIR}")
		get_filename_component(GIT_PARENT_DIR ${GIT_PARENT_DIR} PATH)
		if(GIT_PARENT_DIR STREQUAL GIT_PREVIOUS_PARENT)
			# We have reached the root directory, we are not in git
			set(${_refspecvar} "GITDIR-NOTFOUND" PARENT_SCOPE)
			set(${_hashvar} "GITDIR-NOTFOUND" PARENT_SCOPE)
			return()
		endif()
		set(GIT_DIR "${GIT_PARENT_DIR}/.git")
	endwhile()
	# check if this is a submodule
	if(NOT IS_DIRECTORY ${GIT_DIR})
		file(READ ${GIT_DIR} submodule)
		string(REGEX REPLACE "gitdir: (.*)\n$" "\\1" GIT_DIR_RELATIVE ${submodule})
		get_filename_component(SUBMODULE_DIR ${GIT_DIR} PATH)
		get_filename_component(GIT_DIR ${SUBMODULE_DIR}/${GIT_DIR_RELATIVE} ABSOLUTE)
	endif()
	set(GIT_DATA "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/git-data")
	if(NOT EXISTS "${GIT_DATA}")
		file(MAKE_DIRECTORY "${GIT_DATA}")
	endif()

	if(NOT EXISTS "${GIT_DIR}/HEAD")
		return()
	endif()
	set(HEAD_FILE "${GIT_DATA}/HEAD")
	configure_file("${GIT_DIR}/HEAD" "${HEAD_FILE}" COPYONLY)

	configure_file("${_gitdescmoddir}/GetGitRevisionDescription.cmake.in"
		"${GIT_DATA}/grabRef.cmake"
		@ONLY)
	include("${GIT_DATA}/grabRef.cmake")

	set(${_refspecvar} "${HEAD_REF}" PARENT_SCOPE)
	set(${_hashvar} "${HEAD_HASH}" PARENT_SCOPE)
endfunction()

function(git_describe _var)
	if(NOT GIT_FOUND)
		find_package(Git QUIET)
	endif()
	get_git_head_revision(refspec hash)
	if(NOT GIT_FOUND)
		set(${_var} "GIT-NOTFOUND" PARENT_SCOPE)
		return()
	endif()
	if(NOT hash)
		set(${_var} "HEAD-HASH-NOTFOUND" PARENT_SCOPE)
		return()
	endif()

	# TODO sanitize
	#if((${ARGN}" MATCHES "&&") OR
	#	(ARGN MATCHES "||") OR
	#	(ARGN MATCHES "\\;"))
	#	message("Please report the following error to the project!")
	#	message(FATAL_ERROR "Looks like someone's doing something nefarious with git_describe! Passed arguments ${ARGN}")
	#endif()

	#message(STATUS "Arguments to execute_process: ${ARGN}")

	execute_process(COMMAND
		"${GIT_EXECUTABLE}"
		describe
		${ARGN}
		WORKING_DIRECTORY
		"${CMAKE_SOURCE_DIR}"
		RESULT_VARIABLE
		res
		OUTPUT_VARIABLE
		out
		ERROR_QUIET
		OUTPUT_STRIP_TRAILING_WHITESPACE)
	if(NOT res EQUAL 0)
		set(out "GIT_UNTAGGED_REVISION")
	endif()

	set(${_var} "${out}" PARENT_SCOPE)
endfunction()

function(git_get_exact_tag _var)
	git_describe(out --exact-match ${ARGN})
	set(${_var} "${out}" PARENT_SCOPE)
endfunction()

FUNCTION(git_is_dirty _var)
    IF(NOT GIT_FOUND)
        FIND_PACKAGE(Git QUIET)
    ENDIF()

    # Run diff-index to check whether the tree is clean or not.
    EXECUTE_PROCESS(
        COMMAND ${GIT} diff-index --name-only HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE GIT_DIFF_INDEX_RESULT
        OUTPUT_VARIABLE GIT_DIFF_INDEX_OUTPUT
        ERROR_VARIABLE GIT_DIFF_INDEX_ERROR
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    # Check if the tree is clean.
    IF(NOT GIT_DIFF_INDEX_RESULT AND NOT GIT_DIFF_INDEX_OUTPUT)
        SET(PROJECT_DIRTY False)
    ELSE()
        SET(PROJECT_DIRTY True)
    ENDIF()
    SET(${_var} "${PROJECT_DIRTY}" PARENT_SCOPE)
ENDFUNCTION()

FUNCTION(get_short_git_hash _hash)
    get_git_head_revision(_refspecvar, _hashvar)
    STRING(REGEX REPLACE "(................).*" "\\1" short_hash ${_hashvar})
    set(${_hash} ${short_hash} PARENT_SCOPE)
ENDFUNCTION()

GET_GIT_HEAD_REVISION(GIT_REFSPEC GIT_SHA1)
MESSAGE(STATUS "GIT_SHA1 : ${GIT_SHA1}")
GET_GIT_HEAD_REVISION(GIT_REFSPEC GIT_SHA1)

GIT_DESCRIBE(GIT_VERSION --tags --dirty=-dirty)
IF(${GIT_VERSION} STREQUAL "GIT_UNTAGGED_REVISION")
    MESSAGE(STATUS "GIT : Untagged working revision")
    SET(GIT_VERSION_MAJOR 0)
    SET(GIT_VERSION_MINOR 0)
    SET(GIT_VERSION_PATCH 0)
    SET(GIT_VERSION_SHORT ${GIT_SHA1})
    GIT_IS_DIRTY(GIT_VERSION_DIRTY)
ELSE()
    #parse the version information into pieces.
    MESSAGE(STATUS "GIT_VERSION :  ${GIT_VERSION}")
    STRING(REGEX REPLACE "^v([0-9]+)\\..*" "\\1" GIT_VERSION_MAJOR "${GIT_VERSION}")
    STRING(REGEX REPLACE "^v[0-9]+\\.([0-9]+).*" "\\1" GIT_VERSION_MINOR "${GIT_VERSION}")
    STRING(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.([0-9]+).*" "\\1" GIT_VERSION_PATCH "${GIT_VERSION}")
    STRING(REGEX REPLACE "^v[0-9]+\\.[0-9]+\\.[0-9]+-(.*)" "\\1" GIT_VERSION_SHA1 "${GIT_VERSION}")
    STRING(REGEX MATCH   "^v[0-9]+\\.[0-9]+.*(-dirty)" "\\1" GIT_VERSION_DIRTY "${GIT_VERSION}")
    SET(GIT_VERSION_SHORT "${GIT_VERSION_MAJOR}.${GIT_VERSION_MINOR}.${GIT_VERSION_PATCH}")
    MESSAGE(STATUS "GIT_VERSION_DIRTY ${GIT_VERSION_DIRTY}")
    MESSAGE(STATUS "GIT_VERSION_SHA1 ${GIT_VERSION_SHA1}")
    IF(GIT_VERSION_SHA1)
        SET(GIT_VERSION_SHORT "${GIT_VERSION_SHORT}-${GIT_VERSION_SHA1}")
        IF(NOT ${GIT_VERSION} STREQUAL ${GIT_VERSION_SHA1})
            SET(GIT_VERSION_PATCH "${GIT_VERSION_PATCH}_${GIT_VERSION_SHA1}")
        ENDIF()
    ENDIF()
ENDIF()
IF(${GIT_VERSION_DIRTY})
    SET(GIT_VERSION_SHORT "${GIT_VERSION_SHORT}_dirty")
ENDIF()
SET(${PROJECT_NAME}_MAJOR_VERSION ${GIT_VERSION_MAJOR})
SET(${PROJECT_NAME}_MINOR_VERSION ${GIT_VERSION_MINOR})
SET(${PROJECT_NAME}_PATCH_VERSION ${GIT_VERSION_PATCH})

MESSAGE(STATUS "VERSION_MAJOR : ${${PROJECT_NAME}_MAJOR_VERSION}")
MESSAGE(STATUS "VERSION_MINOR : ${${PROJECT_NAME}_MINOR_VERSION}")
MESSAGE(STATUS "VERSION_PATCH : ${${PROJECT_NAME}_PATCH_VERSION}")
SET(${PROJECT_NAME}_VERSION
    ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_VERSION})
SET(${PROJECT_NAME}_VERSION_STR
    ${${PROJECT_NAME}_MAJOR_VERSION}-${${PROJECT_NAME}_MINOR_VERSION}-${${PROJECT_NAME}_PATCH_VERSION})


