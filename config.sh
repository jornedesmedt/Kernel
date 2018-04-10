SYSTEM_HEADER_PROJECTS="libc src"
PROJECTS="libc src"

export MAKE=${MAKE:-make}
export HOST=${HOST:-$(./default-host.sh)}

export AR=${HOST}-ar
export AS=${HOST}-as
export CC=${HOST}-g++
export CC1=${HOST}-gcc

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include

export CFLAGS='-O2 -g'
export CPPFLAGS=''

export SYSROOT="$(pwd)/sysroot"
export CC="$CC --sysroot=$SYSROOT"
export CC1="$CC1 --sysroot=$SYSROOT"

if echo "$HOST" | grep -Eq -- '-elf|-'; then
    export CC="$CC -isystem=$INCLUDEDIR"
    export CC1="$CC1 -isystem=$INCLUDEDIR"
fi