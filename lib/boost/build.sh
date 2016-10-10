#!/bin/bash

echo BOOST_ROOT ${BOOST_ROOT}

pushd .
cd ${BOOST_ROOT}
git init
git add .
git commit -m " - first commit"

popd
cp .gitignore ${BOOST_ROOT}
cd ${BOOST_ROOT}
git add .gitignore
git commit -m " - add .gitignore"

./bootstrap.sh
./b2 --stagedir=stage64 -j4 variant=release link=static threading=multi address-model=64 runtime-link=static --without-mpi --without-python
