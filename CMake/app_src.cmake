# game source file
set(
    app_src
	
	# game system extended
	app_src/gamesystem_ext/GameSystemExtended.cpp

	# game scene
	app_src/scenes/Intro/Intro.cpp
	app_src/scenes/LevelEditor/LevelEditorConstructor.cpp
	app_src/scenes/LevelEditor/LevelEditorDraw.cpp
	app_src/scenes/LevelEditor/LevelEditorLoadResource.cpp
	app_src/scenes/LevelEditor/LevelEditorStep.cpp
	app_src/scenes/LevelEditor/LevelEditorStepSubFunction.cpp
	app_src/scenes/MainMenu/MainMenu.cpp
	app_src/scenes/MainMenu/MainMenuDraw.cpp
	app_src/scenes/MainMenu/MainMenuLoadResource.cpp

	# game objects
	# app_src/objects/...

	# widgets
	app_src/objects/widgets/Cursor.cpp
	app_src/objects/widgets/GridCase.cpp
	app_src/objects/widgets/Tile.cpp
)