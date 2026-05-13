@ECHO OFF

CD ./build

        cmake                 ^
          -G "Unix Makefiles" ^
          -DKI_TEST=FALSE     ^
          -DKI_EXAMPLE=FALSE  ^
          ..

        ECHO ===== Make =====

        make

CD ..
