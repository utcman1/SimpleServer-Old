set BOOST_ROOT=%LIB_ROOT%\boost_1_61_0
echo BOOST_ROOT %BOOST_ROOT%

pushd .
cd %BOOST_ROOT%
git init
git add .
git commit -m " - first commit"

popd
copy .gitignore %BOOST_ROOT%
cd %BOOST_ROOT%
git add .gitignore
git commit -m " - add .gitignore"

call bootstrap.bat
b2 --stagedir=stage64 -j8 variant=debug,release link=static threading=multi address-model=64 toolset=msvc-14.0 runtime-link=static --without-mpi --without-python
