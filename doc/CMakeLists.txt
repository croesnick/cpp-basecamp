# Generate Doxygen API documentation via cmake.
# Heavily inspired by http://www.tty1.net/blog/2014/cmake-doxygen_en.html

find_package (Doxygen)  # sets DOXYGEN_FOUND and DOXYGEN_EXECUTABLE
# Optional dependency.
# UML diagrams are generated via dot if graphviz is installed.
# TODO Enable the following command by provinding a FindGraphviz.cmake
#find_package (graphviz) # sets GRAPHVIZ_FOUND 
set (GRAPHVIZ_FOUND 0)

option (
	BUILD_DOCUMENTATION
	"Create and install the HTML based API documentation (requires Doxygen)"
	${DOXYGEN_FOUND})

if (BUILD_DOCUMENTATION)
	if (NOT DOXYGEN_FOUND)
		message (FATAL_ERROR "Doxygen is needed to build the documentation.")
	endif()

	# Tell Doxygen whether dot could be found or not via
	# HAVE_DOT = @DOXYGEN_HAVE_DOT@ in Doxyfile.in
	if (GRAPHVIZ_FOUND)
		set (DOXYGEN_HAVE_DOT "YES")
	else  ()
		set (DOXYGEN_HAVE_DOT "NO")
	endif ()

	set (DOXYFILE_IN  ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
	set (DOXYFILE_CFG ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

	configure_file (${DOXYFILE_IN} ${DOXYFILE_CFG} @ONLY)

	add_custom_target (
		doc
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE_CFG}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen."
		VERBATIM)
endif()
	
