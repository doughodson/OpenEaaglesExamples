REM -- Generate *.EDL files for all examples;
REM -- Windows version; for Linux use "make edl"

for /D %%G IN (demo*) do (
   pushd %%G
   if EXIST makeEdl.bat (
        call makeEdl.bat
      )
   popd
)

for /D %%G IN (main*) do (
   pushd %%G
   if EXIST makeEdl.bat (
        call makeEdl.bat
      )
   popd
)

for /D %%G IN (test*) do (
   pushd %%G
   if EXIST makeEdl.bat (
        call makeEdl.bat
      )
   popd
)

for /D %%G IN (tutorial*) do (
   pushd %%G
   if EXIST makeEdl.bat (
        call makeEdl.bat
      )
   popd
)
