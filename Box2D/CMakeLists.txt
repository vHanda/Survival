cmake_minimum_required (VERSION 2.6)
project (box2d CXX)
enable_language (CXX C)

include_directories (.)

##
# This file was automatically generated using:
#    /usr/local/bin/box2d_gen_sublib.sh box2d cpp
##
set(box2d_SOURCES
	"./Dynamics/b2Body.cpp"
	"./Dynamics/b2Island.cpp"
	"./Dynamics/b2World.cpp"
	"./Dynamics/b2ContactManager.cpp"
	"./Dynamics/Contacts/b2Contact.cpp"
	"./Dynamics/Contacts/b2PolyContact.cpp"
	"./Dynamics/Contacts/b2CircleContact.cpp"
	"./Dynamics/Contacts/b2PolyAndCircleContact.cpp"
	"./Dynamics/Contacts/b2EdgeAndCircleContact.cpp"
	"./Dynamics/Contacts/b2PolyAndEdgeContact.cpp"
	"./Dynamics/Contacts/b2ContactSolver.cpp"
	"./Dynamics/b2WorldCallbacks.cpp"
	"./Dynamics/Joints/b2MouseJoint.cpp"
	"./Dynamics/Joints/b2PulleyJoint.cpp"
	"./Dynamics/Joints/b2Joint.cpp"
	"./Dynamics/Joints/b2RevoluteJoint.cpp"
	"./Dynamics/Joints/b2PrismaticJoint.cpp"
	"./Dynamics/Joints/b2DistanceJoint.cpp"
	"./Dynamics/Joints/b2GearJoint.cpp"
	"./Dynamics/Joints/b2LineJoint.cpp"
	"./Dynamics/Controllers/b2Controller.cpp"
	"./Dynamics/Controllers/b2BuoyancyController.cpp"
	"./Dynamics/Controllers/b2GravityController.cpp"
	"./Dynamics/Controllers/b2TensorDampingController.cpp"
	"./Dynamics/Controllers/b2ConstantForceController.cpp"
	"./Dynamics/Controllers/b2ConstantAccelController.cpp"
	"./Common/b2StackAllocator.cpp"
	"./Common/b2Math.cpp"
	"./Common/b2BlockAllocator.cpp"
	"./Common/b2Settings.cpp"
	"./Collision/b2Collision.cpp"
	"./Collision/b2Distance.cpp"
	"./Collision/Shapes/b2Shape.cpp"
	"./Collision/Shapes/b2CircleShape.cpp"
	"./Collision/Shapes/b2PolygonShape.cpp"
	"./Collision/Shapes/b2EdgeShape.cpp"
	"./Collision/b2TimeOfImpact.cpp"
	"./Collision/b2PairManager.cpp"
	"./Collision/b2CollidePoly.cpp"
	"./Collision/b2CollideCircle.cpp"
	"./Collision/b2BroadPhase.cpp"
)

#if (TARGET_FLOAT32_IS_FIXED)
#  add_definitions(-DTARGET_FLOAT32_IS_FIXED)
#endif (TARGET_FLOAT32_IS_FIXED)

#if (TARGET_IS_NDS)
#
#  ###
#  # Tell cmake how to build an NDS library.
#  # shamelessly borrowed from: http://quirkygba.blogspot.com/2008/09/alternatives-to-make-part-1.html
#  ###
#  set(CMAKE_SYSTEM_NAME Generic)
#  set(CMAKE_SYSTEM_VERSION 1)
#  set(CMAKE_SYSTEM_PROCESSOR arm-eabi)
#
#  set(DEVKITARM $ENV{DEVKITARM})
#  set(DEVKITPRO $ENV{DEVKITPRO})
#  
#  if (NOT EXISTS ${DEVKITARM})
#    message(FATAL_ERROR "Please set DEVKITARM '${DEVKITARM}' in your environment")
#  endif (NOT EXISTS ${DEVKITARM})
#
#  if (NOT EXISTS ${DEVKITPRO})
#    message(FATAL_ERROR "Please set DEVKITPRO '${DEVKITPRO}' in your environment")
#  endif (NOT EXISTS ${DEVKITPRO})
#  
#  set(CMAKE_C_COMPILER ${DEVKITARM}/bin/arm-eabi-gcc)
#  set(CMAKE_CXX_COMPILER ${DEVKITARM}/bin/arm-eabi-g++)
#  set(CMAKE_FIND_ROOT_PATH ${DEVKITARM})
#  set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
#  set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
#  set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
#
#  add_definitions(-DTARGET_IS_NDS)
#endif (TARGET_IS_NDS)
#
add_library (box2d STATIC ${box2d_SOURCES})
set_target_properties (box2d PROPERTIES LINKER_LANGUAGE CXX)
