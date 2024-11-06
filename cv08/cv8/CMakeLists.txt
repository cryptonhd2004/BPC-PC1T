# CMakeList.txt: Projekt CMake pro cv8, sem přidejte logiku zdrojového
# kódu a definic specifickou pro projekt.
#

# Přidejte zdrojový kód ke spustitelnému souboru tohoto projektu.
add_executable (cv8 "cv8.cpp" "cv8.h" "sindelar.cpp" "sindelar.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET cv8 PROPERTY CXX_STANDARD 20)
endif()

# TODO: V případě potřeby přidejte testy a cíle instalace.
