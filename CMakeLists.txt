cmake_minimum_required( VERSION 2.8 )

add_subdirectory( Box2D )

project(Survival)

Find_Package( SDL REQUIRED )
Find_Package( SDL_image REQUIRED )
Find_Package( SDL_mixer REQUIRED )
Find_Package( SDL_ttf REQUIRED )

set (CMAKE_MODULE_PATH
     "${CMAKE_CURRENT_SOURCE_DIR}/cmake/"
     ${CMAKE_MODULE_PATH}
)

Find_Package( SDL_gfx REQUIRED )

if ( NOT SDL_FOUND )
    message( FATAL_ERROR "SDL not found!" )
endif ( NOT SDL_FOUND )

if( NOT SDLIMAGE_FOUND )
    message( FATAL_ERROR "SDL_Image not found!" )
endif( NOT SDLIMAGE_FOUND )

if( NOT SDLMIXER_FOUND )
    message( FATAL_ERROR "SDL_Mixer not found" )
endif( NOT SDLMIXER_FOUND )

if( NOT SDLTTF_FOUND )
    message( FATAL_ERROR "SDL_TTF not found" )
endif( NOT SDLTTF_FOUND )

if( NOT SDLGFX_FOUND )
    message( FATAL_ERROR "SDL_GFX not found" )
endif( NOT SDLGFX_FOUND )

include_directories(
  ${CMAKE_SOURCE_DIR}
  ${CMAKE_SOURCE_DIR}/Box2D/
  )

set( SRCS
  
  Agent.cpp
  App.cpp
  Box2DEntity.cpp
  Bullet.cpp
  Camera.cpp
  ContactFilter.cpp
  ContactListener.cpp
  DebugDraw.cpp
  Game.cpp
  GameStates.cpp
  main.cpp
  Map.cpp
  Monster.cpp
  MonsterManager.cpp
  Monster_SB.cpp
  Neural_SB.cpp
  Obstacle.cpp
  Player.cpp
  Projectile.cpp
  Score.cpp
  Shield.cpp
  Star.cpp
  SteeringBehaviors.cpp
  TextBox.cpp
  Timer.cpp

  Engine/Effect.cpp
  Engine/Engine.cpp
  Engine/Entity.cpp
  Engine/Keyboard.cpp
  Engine/Mouse.cpp
  Engine/SoundEffect.cpp
  Engine/Sprite.cpp

  Engine/Managers/EffectManager.cpp
  Engine/Managers/MessageManager.cpp

  Image/Fog.cpp
  Image/PerlinNoise.cpp
  Image/Plasma.cpp
  Image/SDL_SurfacePtr.cpp
  Image/Rand/mtrand.cpp

  Menu/AppStates.cpp
  Menu/Credits.cpp
  Menu/Help.cpp
  Menu/Highscore.cpp
  Menu/Menu.cpp
  Menu/Page_1.cpp
  Menu/Page_2.cpp
  Menu/Page_3.cpp
  Menu/Page_4.cpp
  Menu/Page_5.cpp
  Menu/Page.cpp

  NeuralNetwork/NeuralNetwork.cpp
  NeuralNetwork/NN_File.cpp

  tinyxml/tinystr.cpp
  tinyxml/tinyxml.cpp
  tinyxml/tinyxmlerror.cpp
  tinyxml/tinyxmlparser.cpp
)

add_executable(Survival ${SRCS})

target_link_libraries(Survival
  ${SDL_LIBRARY}
  ${SDLIMAGE_LIBRARY}
  ${SDLMIXER_LIBRARY}
  ${SDLTTF_LIBRARY}
  ${SDLGFX_LIBRARY}
  box2d
)

