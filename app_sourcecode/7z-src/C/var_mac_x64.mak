PLATFORM=x64
O=b/m_$(PLATFORM)
IS_X64=1
IS_X86=
IS_ARM64=
CROSS_COMPILE=riscv64-linux-musl-
MY_ARCH=-arch x86_64
USE_ASM=
CC=$(CROSS_COMPILE)clang
CXX=$(CROSS_COMPILE)clang++
USE_CLANG=1