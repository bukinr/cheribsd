# $FreeBSD$

.include <src.opts.mk>

PACKAGE= tests

TESTSDIR= ${TESTSBASE}

${PACKAGE}FILES+=		README

KYUAFILE= yes

SUBDIR.${MK_CHERI}+=	cheri
SUBDIR+= etc
SUBDIR+= sys

SUBDIR_PARALLEL=

afterinstall: install-tests-local
install-tests-local: .PHONY
	${INSTALL_SYMLINK} ../local/tests ${DESTDIR}${TESTSDIR}/local

.include "Makefile.inc0"
.include <bsd.test.mk>
