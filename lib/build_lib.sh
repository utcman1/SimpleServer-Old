#!/bin/bash

echo LIB_ROOT ${LIB_ROOT}

BOOST_159=${LIB_ROOT}/boost_1_59_0
BOOST_LAST=${LIB_ROOT}/boost_1_62_0
MYSQL_ROOT=${LIB_ROOT}/mysql-cluster-gpl-7.5.3
export MYSQL_ROOT



# prepare tools
yum install gcc gcc-c++ make cmake bison git bzip2 bzip2-devel ncurses-devel -y



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
if [ ! -f ${MYSQL_ROOT}.tar.gz ]; then
	rpm -Uvh http://dev.mysql.com/get/Downloads/MySQL-Cluster-7.5/MySQL-Cluster-gpl-7.5.3-1.el7.src.rpm
fi
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

