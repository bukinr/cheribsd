# $FreeBSD$

.include <src.opts.mk>

COMPILERRTDIR=	${SRCTOP}/contrib/compiler-rt
.if ${MK_CHERI} != "no"
WANT_CHERI?=	hybrid
UNWINDINCDIR=	${SRCTOP}/contrib/subrepo-cheri-libunwind/include
UNWINDSRCDIR=	${SRCTOP}/contrib/subrepo-cheri-libunwind/src
.elif ${MACHINE_ARCH:Mmips*}
UNWINDINCDIR=	${SRCTOP}/contrib/subrepo-cheri-libunwind/include
UNWINDSRCDIR=	${SRCTOP}/contrib/subrepo-cheri-libunwind/src
.else
UNWINDINCDIR=	${SRCTOP}/contrib/libunwind/include
UNWINDSRCDIR=	${SRCTOP}/contrib/libunwind/src
.endif

STATIC_CFLAGS+=${PICFLAG} -fvisibility=hidden -DVISIBILITY_HIDDEN

ALLOW_MIPS_SHARED_TEXTREL=

.PATH: ${COMPILERRTDIR}/lib/builtins
.PATH: ${UNWINDSRCDIR}
SRCS_EXC+=	gcc_personality_v0.c
SRCS_EXC+=	int_util.c
SRCS_EXC+=	Unwind-EHABI.cpp
SRCS_EXC+=	Unwind-sjlj.c
SRCS_EXC+=	UnwindLevel1-gcc-ext.c
SRCS_EXC+=	UnwindLevel1.c
SRCS_EXC+=	UnwindRegistersRestore.S
SRCS_EXC+=	UnwindRegistersSave.S
SRCS_EXC+=	libunwind.cpp

SRCS+=		${SRCS_EXC}
.for file in ${SRCS_EXC:M*.c}
CFLAGS.${file}+=	-fno-exceptions -funwind-tables
.endfor
.for file in ${SRCS_EXC:M*.cpp}
CXXFLAGS.${file}+=	-fno-exceptions -funwind-tables
.endfor

CFLAGS+=	-I${UNWINDINCDIR} -I${.CURDIR} -D_LIBUNWIND_IS_NATIVE_ONLY
CXXFLAGS+=	-fno-rtti
CXXSTD?=	c++11
STATIC_CXXFLAGS+= -fvisibility=hidden -fPIC
# Probably need to just move this earlier or use CXXFLAGS
.if ${MK_DIRDEPS_BUILD} == "yes"
# Avoid dependency on lib/libc++
.if ${MK_CHERI} != "no" || ${MACHINE_ARCH:Mmips*}
CFLAGS+=	-isystem ${SRCTOP}/contrib/subrepo-cheri-libc++/include -nostdinc++
.else
CFLAGS+=	-isystem ${SRCTOP}/contrib/libc++/include -nostdinc++
.endif
.endif
