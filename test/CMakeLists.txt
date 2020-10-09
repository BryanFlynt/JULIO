#
# === Unit Tests
#

# 
# Build list of all tests to create
#
set(test_tbox_files  
		check_values.cpp
		interface.cpp
        parse_file.cpp
)
		       
# Set include headers unique to testing
set(include_headers "")

# Set libraries the test need
# - Gets library include paths from here
set(linked_libraries 
		json
	)

#
# Loop over each test building and adding to ctest
# - Build test name
#	             
FOREACH(test_src ${test_tbox_files})
	string(REPLACE ".cpp" "" test_name ${test_src})
	add_executable(${test_name} ${test_src})
	target_compile_options(${test_name} PRIVATE ${compiler_options})
	target_include_directories(${test_name} PRIVATE ${include_headers})
	target_link_libraries(${test_name} ${linked_libraries})
	
	add_test(NAME ${test_name} COMMAND ./${test_name})
ENDFOREACH(test_src)


# Install test data
install(
	DIRECTORY "${MY_PROJECT_TSTDIR}/data"
	DESTINATION "${MY_INSTALL_TSTDIR}"  
	FILES_MATCHING 
	PATTERN "*"
)
