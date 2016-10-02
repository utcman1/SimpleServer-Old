#!/bin/bash

echo MYSQL_ROOT ${MYSQL_ROOT}

pushd .
cd ${MYSQL_ROOT}
rm .gitignore
rm Docs/INFO_SRC
git init
git add .
git commit -m " - first commit"

popd
cp .gitignore ${MYSQL_ROOT}
cd ${MYSQL_ROOT}
git add .gitignore
git commit -m " - add .gitignore"

rm libmysqld/sql_hints.yy.cc
rm libmysqld/sql_hints.yy.h
rm libmysqld/sql_yacc.cc
rm libmysqld/sql_yacc.h
rm sql/sql_hints.yy.cc
rm sql/sql_hints.yy.h
rm sql/sql_yacc.cc
rm sql/sql_yacc.h
cmake -DWITH_NDBCLUSTER=ON -DWITH_NDB_JAVA=OFF -DWITH_NDB_TEST=ON -DWITH_BOOST=../boost_1_59_0 .
git add .
git add -u .
git commit -m " - cmake result"

make -j4
