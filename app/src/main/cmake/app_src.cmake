# game source file
set(
    app_src
	
	# game system extended
	${ISENGINE_SRC_DIR}/app_src/gamesystem_ext/GameSystemExtended.cpp

	# game scene
	${ISENGINE_SRC_DIR}/app_src/scenes/Intro/Intro.cpp
	${ISENGINE_SRC_DIR}/app_src/scenes/LevelEditor/LevelEditorConstructor.cpp
	${ISENGINE_SRC_DIR}/app_src/scenes/LevelEditor/LevelEditorDraw.cpp
	${ISENGINE_SRC_DIR}/app_src/scenes/LevelEditor/LevelEditorLoadResource.cpp
	${ISENGINE_SRC_DIR}/app_src/scenes/LevelEditor/LevelEditorStep.cpp
	${ISENGINE_SRC_DIR}/app_src/scenes/LevelEditor/LevelEditorStepSubFunction.cpp
	${ISENGINE_SRC_DIR}/app_src/scenes/MainMenu/MainMenu.cpp
	${ISENGINE_SRC_DIR}/app_src/scenes/MainMenu/MainMenuDraw.cpp
	${ISENGINE_SRC_DIR}/app_src/scenes/MainMenu/MainMenuLoadResource.cpp

	# widgets
	${ISENGINE_SRC_DIR}/app_src/objects/widgets/Cursor.cpp
	${ISENGINE_SRC_DIR}/app_src/objects/widgets/GridCase.cpp
	${ISENGINE_SRC_DIR}/app_src/objects/widgets/Tile.cpp
)