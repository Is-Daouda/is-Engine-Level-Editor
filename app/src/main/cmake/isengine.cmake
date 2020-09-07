# engine source file
set(
    isengine

	${ISENGINE_SRC_DIR}/main.cpp

	# Basic SFML rendering loop
	${ISENGINE_SRC_DIR}/basicSFMLmain.cpp

	# core
	${ISENGINE_SRC_DIR}/isEngine/core/GameEngine.cpp

	# system
	# display
	${ISENGINE_SRC_DIR}/isEngine/system/display/GameDisplay.cpp
	
	# entity
	${ISENGINE_SRC_DIR}/isEngine/system/entity/MainObject.cpp
	
	# function
	${ISENGINE_SRC_DIR}/isEngine/system/function/GameFunction.cpp		
	${ISENGINE_SRC_DIR}/isEngine/system/function/GameKeyData.cpp
	${ISENGINE_SRC_DIR}/isEngine/system/function/GameSystem.cpp
	${ISENGINE_SRC_DIR}/isEngine/system/function/GameTime.cpp
	
	# ext
	${ISENGINE_SRC_DIR}/isEngine/ext_lib/TinyFileDialogs/tinyfiledialogs.cpp
)
