add_executable(tutorial-servo-pot-control.${TARGET}-board.elf)
target_sources(tutorial-servo-pot-control.${TARGET}-board.elf
PRIVATE src/main.cpp)
target_set_firmware_properties(tutorial-servo-pot-control.${TARGET}
-b oard.elf)

add_subdirectory(apps/tutorial-servo-pot-control)

add_library (TutorialServo STATIC)
target_sources (TutorialServo PRIVATE src/TutorialServo.cpp)
target_link_libraries (tutorial-servo-can-control. ${TARGET} -board.elf PRIVATE
TutorialServo
)
target_include_directories (TutorialServo PUBLIC include)
target_set_mbed_dependency (TutorialServo)