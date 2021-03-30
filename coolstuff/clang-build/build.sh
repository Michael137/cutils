# Check for cmake installation
command -v cmake >/dev/null 2>&1 || { "CMake needed but not found. Exiting."; exit 1; }
command -v svn >/dev/null 2>&1 || { "SVN needed but not found. Exiting."; exit 1; }
command -v g++ >/dev/null 2>&1 || { "g++ needed but not found. Exiting"; exit 1; }
command -v ninja >/dev/null 2>&1 || { "ninja needed but not found. Exiting"; exit 1; }
if [ "$(whoami)" != "root" ]; then
	echo "Please rerun this script with sudo.";
	exit 1;
fi

mkdir llvm-build
cd llvm-build

#########################
## Do the checkout     ##
#########################
## Base llvm ##
svn co http://llvm.org/svn/llvm-project/llvm/trunk llvm

## Clang ##
cd llvm/tools
svn co http://llvm.org/svn/llvm-project/cfe/trunk clang

## extra-tools ##
cd clang/tools
svn co http://llvm.org/svn/llvm-project/clang-tools-extra/trunk extra

## LLD ##
# llvm-build/llvm/tools
cd ../..
svn co http://llvm.org/svn/llvm-project/lld/trunk lld

## Polly ##
svn co http://llvm.org/svn/llvm-project/polly/trunk polly

## Compiler-RT ##
# llvm-build/llvm/projects
cd ../projects
svn co http://llvm.org/svn/llvm-project/compiler-rt/trunk compiler-rt

## OpenMP ##
svn co http://llvm.org/svn/llvm-project/openmp/trunk openmp

## libc++ ##
svn co http://llvm.org/svn/llvm-project/libcxx/trunk libcxx

## libc++abi ##
svn co http://llvm.org/svn/llvm-project/libcxxabi/trunk libcxxabi

## Test-suite ##
svn co http://llvm.org/svn/llvm-project/test-suite/trunk test-suite

# llvm-build/
cd ../..

#########################
## Do the installation ##
#########################
# llvm-build/build
mkdir build
mkdir install
cd build

export CC=/home/gardei/Compilers/gcc/install/bin/gcc
export CXX=/home/gardei/Compilers/gcc/install/bin/g++
cmake -G Ninja ../llvm -DCMAKE_INSTALL_PREFIX=/home/gardei/Compilers/clang/install -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_ASSERTIONS=Off -DCLANG_DEFAULT_LINKER=lld -DCLANG_DEFAULT_RTLIB=compiler-rt -DCLANG_DEFAULT_CXX_STDLIB=libc++
ninja
ninja install

export LD_LIBRARY_PATH=/home/gardeimasei/cstuff/clang-build/llvm-build/install/lib:$LD_LIBRARY_PATH
export PATH=/home/gardeimasei/cstuff/clang-build/llvm-build/install/bin:$PATH
