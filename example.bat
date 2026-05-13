@ECHO OFF

CD ./build

        cmake                   ^
          -G "Unix Makefiles"   ^
          -DKI_TEST=FALSE       ^
          -DKI_EXAMPLE=TRUE     ^
          -DKI_EXAMPLE_RUN="%1" ^
          ..

        ECHO ===== Make =====

        make

CD ..
