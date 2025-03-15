To launch the application you need to use mingw64 and link such libraries:<br/>
<ul>
    <li>"-lmingw32"</li>
    <li>"-lSDL2main" ({project_directory}/SDL/lib)</li>
    <li>"-lSDL2" ({project_directory}/SDL/lib)</li>
    <li>"-mwindows"</li>
    <li>"-static"</li>
    <li>"-lsetupapi"</li>
    <li>"-lole32"</li>
    <li>"-limm32"</li>
    <li>"-lwinmm"</li>
    <li>"-lversion"</li>
    <li>"-loleaut32"</li>
    <li>"-luuid"</li>
    <li>"-lws2_32"</li>
    <li>"-lmingwex"</li>
    <li>"-lgcc"</li>
    <li>"-lSDL2_ttf" ({project_directory}/SDL/lib)</li>
    <li>"-lrpcrt4"</li>
</ul>
mingw32 also can be used, but then you will have to download SDL for 32-bit mingw and SDL_ttf respectively. And also connect other libraries.<br/>
The command line argument can be the path to the .txt file from which the values ​​for the table need to be loaded.<br/>
The file syntax can be viewed in data/data.txt, for example:<br/>

{0|"name"|12.05.2023|12.43}<br/>
{1|"second name"|12.05.2022|124.43}<br/>

ect.
