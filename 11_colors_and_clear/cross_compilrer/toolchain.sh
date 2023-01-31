#!/bin/bash

# Install Dependencies

sudo apt update

sudo apt install	\
	build-essential	\
	bison			\
	flex			\
	libgmp3-dev		\
	libmpc-dev		\
	libmpfr-dev		\
	texinfo

# Setup Build Env

export PREFIX="/usr/local/x86_64elfgcc"
export TARGET="x86_64-elf"
export PATH="$PATH:$PREFIX/bin"

mkdir /tmp/src
cd /tmp/src

# Build Binutils

curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.35.1.tar.gz
tar -xf binutils-2.35.1.tar.gz

mkdir binutils-build
cd binutils-build

../binutils-2.35.1/configure	\
	--target=$TARGET			\
	--enable-interwork			\
	--enable-multilib			\
	--disable-nls				\
	--disable-werror			\
	--prefix="$PREFIX"			\
	2>&1 | tee configure.log

sudo make all install 2>&1 | tee make.log


# Build GCC

cd /tmp/src

curl -O https://ftp.gnu.org/gnu/gcc/gcc-10.2.0/gcc-10.2.0.tar.gz
tar -xf gcc-10.2.0.tar.gz

mkdir gcc-build
cd gcc-build

../gcc-10.2.0/configure		\
	--target=$TARGET		\
	--prefix="$PREFIX"		\
	--disable-nls			\
	--disable-libssp		\
	--enable-language=c++	\
	--without-headers

../gcc-10.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-libssp --enable-language=c++ --without-headers

sudo make all-gcc
sudo make all-target-libgcc
sudo make install-gcc
sudo make install-target-libgcc


# Check Results

ls /usr/local/x86_64elfgcc/bin


# Add Path to PATH

echo '''
export PATH="$PATH:/usr/local/x86_64elfgcc/bin"
''' >> ~/.bashrc
