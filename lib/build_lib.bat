echo LIB_ROOT %LIB_ROOT%

SET BOOST_159=%LIB_ROOT%\boost_1_59_0
SET BOOST_LAST=%LIB_ROOT%\boost_1_62_0
SET MYSQL_ROOT=%LIB_ROOT%\mysql-cluster-gpl-7.5.4



REM window 에서는 download & 압축 해제는 수동으로 한다.



REM build boost 1.59
SET BOOST_ROOT=%BOOST_159%
pushd . > nul
cd boost
call build.bat
popd > nul

REM build boost last
SET BOOST_ROOT=%BOOST_LAST%
pushd . > nul
cd boost
call build.bat
popd > nul

REM build mysql
pushd . > nul
cd mysql
call build.bat
popd > nul
