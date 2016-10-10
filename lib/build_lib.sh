#!/bin/bash

echo LIB_ROOT ${LIB_ROOT}

BOOST_159=${LIB_ROOT}/boost_1_59_0
BOOST_LAST=${LIB_ROOT}/boost_1_62_0
MYSQL_ROOT=${LIB_ROOT}/mysql-cluster-gpl-7.5.3
export MYSQL_ROOT



# download and extract boost 1.59
# 1.59 버전은 mysql 빌드에 필요하다
if [ ! -f ${BOOST_159}.tar.bz2 ]; then
	wget -c -P ${LIB_ROOT} https://sourceforge.net/projects/boost/files/boost/1.59.0/boost_1_59_0.tar.bz2
fi
rm -rf ${BOOST_159}
tar xvjf ${BOOST_159}.tar.bz2 -C ${LIB_ROOT}

# download and extract boost last
if [ ! -f ${BOOST_LAST}.tar.bz2 ]; then
	wget -c -P ${LIB_ROOT} https://sourceforge.net/projects/boost/files/boost/1.62.0/boost_1_62_0.tar.bz2
fi
rm -rf ${BOOST_LAST}
tar xvjf ${BOOST_LAST}.tar.bz2 -C ${LIB_ROOT}

# download and extract mysql
# mysql은 소스 설치를 yum으로 하기 때문에 download는 패스
# src.rpm을 설치하면 LIB_ROOT 위치에 src.tar.gz 파일이 설치된다.
rm -rf ${MYSQL_ROOT}
tar xvzf ${MYSQL_ROOT}.tar.gz -C ${LIB_ROOT}



# build boost 1.59
pushd . > /dev/null
BOOST_ROOT=${BOOST_159}
export BOOST_ROOT
cd boost; ./build.sh
popd > /dev/null

# build boost last
BOOST_ROOT=${BOOST_LAST}
export BOOST_ROOT
pushd . > /dev/null
cd boost; ./build.sh
popd > /dev/null

# build mysql
pushd . > /dev/null
cd mysql; ./build.sh
popd > /dev/null

