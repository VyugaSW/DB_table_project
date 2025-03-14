To launch the application you need to use mingw64 and link such libraries:
    "-lmingw32"
    "-lSDL2main" ({project_directory}/SDL/lib)
    "-lSDL2" ({project_directory}/SDL/lib)
    "-mwindows"
    "-static"
    "-lsetupapi"
    "-lole32"
    "-limm32"
    "-lwinmm"
    "-lversion"
    "-loleaut32"
    "-luuid"
    "-lws2_32"
    "-lmingwex"
    "-lgcc"
    "-lSDL2_ttf" ({project_directory}/SDL/lib)
    "-lrpcrt4"
mingw32 also can be used, but then you will have to download SDL for 32-bit mingw and SDL_ttf respectively. And also connect other libraries.
The command line argument can be the path to the .txt file from which the values ​​for the table need to be loaded.
The file syntax can be viewed in data/data.txt, for example:

{0|"name"|12.05.2023|12.43}
{1|"second name"|12.05.2022|124.43}

ect.
