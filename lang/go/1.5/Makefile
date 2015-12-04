# $OpenBSD: Makefile,v 1.25.4.1 2015/08/22 08:19:06 jasper Exp $

VERSION =		1.5.2

BUILD_DEPENDS =		go->=1.4.3:lang/go/1.4
INSTALLED !=		(pkg_info -qe "go->=1.5" && echo yes) || echo no
.if ${INSTALLED:L} == "yes"
MAKE_ENV =		GOROOT_BOOTSTRAP=${GOROOT}
.else
MAKE_ENV =		GOROOT_BOOTSTRAP=${GOROOT:H}/go14
.endif

.include <bsd.port.mk>
