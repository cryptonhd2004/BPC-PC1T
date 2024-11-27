# CMakeList.txt: Projekt CMake pro 2048, sem přidejte logiku zdrojového
# kódu a definic specifickou pro projekt.
#

# Přidejte zdrojový kód ke spustitelnému souboru tohoto projektu.
add_executable (2048 "2048.cpp" "2048.h" "game.h" "statistics.h" "statistics.cpp" "game.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET 2048 PROPERTY CXX_STANDARD 20)
endif()

# TODO: V případě potřeby přidejte testy a cíle instalace.
