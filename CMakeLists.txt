cmake_minimum_required(VERSION 3.29)
project(projet_personnel_ascenseur)

set(CMAKE_CXX_STANDARD 20)

add_executable(projet_personnel_ascenseur
        main.cpp
        Ascenseur.cpp
        AlgorithmeAscenseur.cpp
        Personne.cpp)
