@ECHO OFF

CD ./build

        cmake                 ^
          -G "Unix Makefiles" ^
          ..

        ECHO ===== Make =====

        make

CD ..
