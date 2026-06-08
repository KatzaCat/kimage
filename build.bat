@ECHO OFF

CD ./build

        cmake                 ^
          -G "MinGW Makefiles" ^
          -DKI_TEST=FALSE     ^
          -DKI_EXAMPLE=FALSE  ^
          ..

        ECHO ===== Make =====

        make

CD ..
