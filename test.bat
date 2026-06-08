@ECHO OFF

CD ./build

        cmake                  ^
          -G "MinGW Makefiles" ^
          -DKI_TEST=TRUE       ^
          -DKI_EXAMPLE=FALSE   ^
          -DKI_TEST_RUN="%1"   ^
          ..

        ECHO ===== Make =====

        make

        ECHO ===== Test =====

        ctest

CD ..
