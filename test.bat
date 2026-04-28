@ECHO OFF

CD ./build

        cmake                 ^
          -G "Unix Makefiles" ^
          -DKI_TEST=TRUE      ^
          ..

        ECHO ===== Make =====

        make

        ECHO ===== Test =====

        ctest

CD ..
