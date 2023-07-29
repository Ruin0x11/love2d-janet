(declare-project
  :name "love2d-janet"
  :description "Janet bindings to LÖVE2D"
  :url "https://github.com/Ruin0x11/love2d-janet"
  :author "Calvin Rose <calsrose@gmail.com>"

  :dependencies ["https://github.com/janet-lang/path.git"])

(def o (os/which))

(def cflags
  (case o
    :windows ["-IC:/Users/yuno/build/megasource/libs/love/src"]
    # :macos '["-Iraylib/src" "-ObjC" "-Iraylib/src/external/glfw/include"]
    # you might need to edit ./raylib/src/external/glfw/src/x11_init.c:1124
    # to match /usr/X11R6/lib/libX11.so*
    # :openbsd '["-Iraylib/src" "-Iraylib/src/external/glfw/include" "-I/usr/X11R6/include" "-Du_char=unsigned char" "-Dalloca(x)=malloc(x)"]
    #default
    '["TODO"]))

(def lflags
  (case o
    :windows '[
               "C:/Users/yuno/build/megasource/build/love/Release/liblove.lib"
               "C:/Users/yuno/build/megasource/build/freetype/Release/freetype.lib"
               "C:/Users/yuno/build/megasource/build/harfbuzz/Release/harfbuzz.lib"
               "C:/Users/yuno/build/megasource/build/libogg/Release/ogg-static.lib"
               "C:/Users/yuno/build/megasource/build/libvorbis/Release/vorbisfile-static.lib"
               "C:/Users/yuno/build/megasource/build/libvorbis/Release/vorbis-static.lib"
               "C:/Users/yuno/build/megasource/build/libtheora/Release/theora-static.lib"
               "C:/Users/yuno/build/megasource/build/libmodplug/Release/modplug-static.lib"
               "C:/Users/yuno/build/megasource/build/openal-soft/Release/OpenAL32.lib"
               "C:/Users/yuno/build/megasource/build/SDL2/Release/SDL2main.lib"
               "C:/Users/yuno/build/megasource/build/SDL2/Release/SDL2.lib"
               "C:/Users/yuno/build/megasource/build/zlib/Release/zlibstatic.lib"
               "C:/Users/yuno/build/megasource/build/bin/lua51.lib"
               "C:/Users/yuno/build/megasource/build/love/Release/love_3p_box2d.lib"
               "C:/Users/yuno/build/megasource/build/love/Release/love_3p_ddsparse.lib"
               "C:/Users/yuno/build/megasource/build/love/Release/love_3p_enet.lib"
               "C:/Users/yuno/build/megasource/build/love/Release/love_3p_glad.lib"
               "C:/Users/yuno/build/megasource/build/love/Release/love_3p_glslang.lib"
               "C:/Users/yuno/build/megasource/build/love/Release/love_3p_lodepng.lib"
               "C:/Users/yuno/build/megasource/build/love/Release/love_3p_luasocket.lib"
               "C:/Users/yuno/build/megasource/build/love/Release/love_3p_lua53.lib"
               "C:/Users/yuno/build/megasource/build/love/Release/love_3p_luahttps.lib"
               "C:/Users/yuno/build/megasource/build/love/Release/love_3p_lz4.lib"
               "C:/Users/yuno/build/megasource/build/love/Release/love_3p_noise1234.lib"
               "C:/Users/yuno/build/megasource/build/love/Release/love_3p_physfs.lib"
               "C:/Users/yuno/build/megasource/build/love/Release/love_3p_spirv_cross.lib"
               "C:/Users/yuno/build/megasource/build/love/Release/love_3p_wuff.lib"
               "C:/Users/yuno/build/megasource/build/love/Release/love_3p_xxhash.lib"
               "C:/Users/yuno/build/megasource/build/freetype/Release/freetype.lib"
               "C:/Users/yuno/build/megasource/build/zlib/Release/zlibstatic.lib"
               "C:/Users/yuno/build/megasource/build/libogg/Release/ogg-static.lib"
               "C:/Users/yuno/build/megasource/build/bin/lua51.lib"
               "ws2_32.lib"
               "winmm.lib"
               "dwmapi.lib"
               "shell32.lib"
               "ws2_32.lib"
               "ws2_32.lib"
               "secur32.lib"
               "kernel32.lib"
               "user32.lib"
               "gdi32.lib"
               "winspool.lib"
               "shell32.lib"
               "ole32.lib"
               "oleaut32.lib"
               "uuid.lib"
               "comdlg32.lib"
               "advapi32.lib"]
    # :macos '["-lpthread" "-framework" "Cocoa" "-framework" "CoreVideo" "-framework" "IOKit" "-framework" "OpenGL"]
    # :linux '["-lpthread" "-lX11"]
    # :openbsd '["-lpthread" "-lX11" "-L/usr/X11R6/lib"]
    #default
    '["TODO"]))

(declare-native
 :name "janet-love2d"

 :cflags [;default-cflags ;cflags]

 :defines {"PLATFORM_DESKTOP" true "_POSIX_C_SOURCE" "200809L" "_DARWIN_C_SOURCE" (if (= o :macos) "1" nil) "_GNU_SOURCE" true}

 :source ["src/main.c"]

 :headers ["src/core.h"
           "src/filesystem.h"]

 :lflags [;default-lflags ;lflags])

# `jpm run repl` to run a repl with access to jaylib
(phony "repl" ["build"]
       (os/execute ["janet" "-l" "build/jaylib"] :p))
