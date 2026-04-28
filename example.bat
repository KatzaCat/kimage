@ECHO OFF

CD ./build

        cmake                 ^
          -G "Unix Makefiles" ^
          -DKI_EXAMPLE=TRUE   ^
          ..

        ECHO ===== Make =====

        make

CD ..
