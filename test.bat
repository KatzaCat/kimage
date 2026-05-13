@ECHO OFF

CD ./build

        cmake                 ^
          -G "Unix Makefiles" ^
          -DKI_TEST=TRUE      ^
          -DKI_EXAMPLE=FALSE  ^
          ..

        ECHO ===== Make =====

        make

        ECHO ===== Test =====

        ctest

CD ..
