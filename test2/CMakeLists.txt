cmake_minimum_required(VERSION 3.26)
project(test2 C)

set(CMAKE_C_STANDARD 99)

add_executable(test2 main.c
        setup.c
        setup.h
        menu.c
        menu.h
        musique.c
        musique.h
        commandes.c
        commandes.h
        initiaallegro.c
        initiaallegro.h
        background.c
        background.h
        client.c
        client.h
        images/deplacement.c
        images/deplacement.h
        deplace.c
        deplace.h
        nv1.c
        nv1.h
        ingredient.c
        ingredient.h
        plat.c
        plat.h
        clients.c
        clients.h
        saisirpseudo.c
        saisirpseudo.h
        parametreson.c
        parametreson.h)

target_link_libraries(test2 -lmingw32 -lalleg44)
