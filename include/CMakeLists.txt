#
# Copy all header files to the installation folder
#
install(
	DIRECTORY ${MY_PROJECT_INCDIR} 
	DESTINATION ${MY_INSTALL_PREFIX}
    FILES_MATCHING PATTERN "*.hpp"
    )