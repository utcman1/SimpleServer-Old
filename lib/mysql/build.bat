set MYSQL_ROOT=%LIB_ROOT%\mysql-cluster-gpl-7.5.3
echo MYSQL_ROOT %MYSQL_ROOT%

pushd .
cd %MYSQL_ROOT%
del .gitignore
del Docs\INFO_SRC
git init
git add .
git commit -m " - first commit"

popd
copy .gitignore %MYSQL_ROOT%
cd %MYSQL_ROOT%
vim -e -s +"set bomb|set encoding=utf-8|wq" sql\sql_locale.cc
git add .gitignore sql\sql_locale.cc
git commit -m " - add .gitignore, add BOM to sql/sql_locale.cc"

del libmysqld\sql_hints.yy.cc
del libmysqld\sql_hints.yy.h
del libmysqld\sql_yacc.cc
del libmysqld\sql_yacc.h
del sql\sql_hints.yy.cc
del sql\sql_hints.yy.h
del sql\sql_yacc.cc
del sql\sql_yacc.h
cmake -DWITH_NDBCLUSTER=ON -DWITH_NDB_JAVA=OFF -DWITH_NDB_TEST=ON -DWITH_BOOST=..\boost_1_59_0 -G "Visual Studio 14 2015 Win64" .
git add .
git add -u .
git commit -m " - cmake result"

echo "프로젝트 준비 완료. Visual Studio로 직접 빌드하세요"
echo "제외 프로젝트 : mysql_client_test_embedded, mysql_embedded, mysqltest_embedded"
