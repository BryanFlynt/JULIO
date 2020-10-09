
#---------------------------------------------------------------------
# BISON Generator
#---------------------------------------------------------------------
find_package(BISON 2.4 REQUIRED)
set(BISON_OUTPUT ${MY_INSTALL_SRCDIR}/json.tab.cpp)
set(BISON_DEFINES ${MY_INSTALL_INCDIR}/json.tab.hpp)
if(BISON_FOUND)
	add_custom_command(
		OUTPUT ${BISON_OUTPUT}
		COMMAND ${BISON_EXECUTABLE}
			--defines=${BISON_DEFINES}
			--output=${BISON_OUTPUT}
			${MY_PROJECT_SRCDIR}/json.y
		DEPENDS ${MY_PROJECT_SRCDIR}/json.y
		COMMENT "Generating json.tab.hh, json.tab.cc (parser)"
	)
endif(BISON_FOUND)

#---------------------------------------------------------------------
# FLEX Generator
#---------------------------------------------------------------------
find_package(FLEX 2.5 REQUIRED)
set(FLEX_OUTPUT ${MY_INSTALL_SRCDIR}/lex.yy.cpp)
if(FLEX_FOUND)
	add_custom_command(
		OUTPUT ${FLEX_OUTPUT}
		COMMAND ${FLEX_EXECUTABLE}
			--outfile=${FLEX_OUTPUT}
			${MY_PROJECT_SRCDIR}/json.l
		DEPENDS ${MY_PROJECT_SRCDIR}/json.l
		COMMENT "Generating lex.yy.cc (lexer)"
	)
set_source_files_properties(${FLEX_OUTPUT} PROPERTIES COMPILE_FLAGS "-Wno-deprecated-register")
endif(FLEX_FOUND)

#---------------------------------------------------------------------
# Define the Target
#---------------------------------------------------------------------

add_library(json json_types.cpp ${BISON_OUTPUT} ${FLEX_OUTPUT})
target_compile_features(json PUBLIC cxx_std_17)
set_target_properties(json PROPERTIES CXX_EXTENSIONS OFF)
target_include_directories(json
	PUBLIC
		"$<BUILD_INTERFACE:${MY_INSTALL_INCDIR}>"
		"$<BUILD_INTERFACE:${MY_PROJECT_INCDIR}>"
		"$<BUILD_INTERFACE:${MY_PROJECT_SRCDIR}>"
)

install(TARGETS json
		LIBRARY DESTINATION "${MY_INSTALL_LIBDIR}"
		ARCHIVE DESTINATION "${MY_INSTALL_LIBDIR}")
		