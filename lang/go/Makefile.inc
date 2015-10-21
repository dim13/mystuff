# $OpenBSD: Makefile,v 1.25.4.1 2015/08/22 08:19:06 jasper Exp $

ONLY_FOR_ARCHS =	${GO_ARCHS}

COMMENT =		Go programming language

EXTRACT_SUFX =		.src.tar.gz
DISTNAME = 		go${VERSION}
PKGNAME = 		go-${VERSION}
CATEGORIES =		lang lang/go

HOMEPAGE =		http://golang.org/

MAINTAINER = 		Joel Sing <jsing@openbsd.org>

# software: BSD, documentation: CC-BY-3.0
PERMIT_PACKAGE_CDROM =	Yes

WANTLIB +=		c pthread

MASTER_SITES =		http://golang.org/dl/

BUILD_DEPENDS +=	shells/bash

SEPARATE_BUILD =	simple
CONFIGURE_STYLE =	None
SUBST_VARS =		GOEXE GOCFG

WRKDIST =		${WRKDIR}/go
WRKSRC =		${WRKDIST}/src

GOOS = 			openbsd
GOARCH =		unknown
GOROOT ?= 		${PREFIX}/go

.if ${MACHINE_ARCH} == "amd64"
GOARCH =		amd64
EXEPREFIX =		6
PKG_ARGS +=		-Damd64=1
PKG_ARGS +=		-Di386=0
.elif ${MACHINE_ARCH} == "i386"
GOARCH =		386
EXEPREFIX =		8
PKG_ARGS +=		-Damd64=0
PKG_ARGS +=		-Di386=1
.else
PKG_ARGS += 		-Damd64=0 -Di386=0
.endif

GOCFG =			/${GOOS}_${GOARCH}
GOEXE =			${GOCFG}/${EXEPREFIX}

MAKE_ENV +=		CC="${CC}" \
			CXX="${CXX}" \
			GOROOT=${WRKDIST} \
			GOBIN=${WRKDIST}/bin \
			GOROOT_FINAL=${GOROOT}

DIRS +=			doc lib misc src pkg

do-configure:
.	if ${GOARCH} == "unknown"
		@echo "Unable to determine GOARCH for ${MACHINE_ARCH}."
		@exit 1
.	endif

do-build:
	@cd ${WRKSRC} && ${MAKE_ENV} ./make.bash --no-banner

do-test:
	@cd ${WRKSRC} && \
		ulimit -n 256 -d 2097152 && \
		PATH=${WRKDIST}/bin:${PATH} GOROOT=${WRKDIST} \
		./run.bash --no-rebuild

do-install:
	${INSTALL_PROGRAM_DIR} ${GOROOT}/bin
	${INSTALL_PROGRAM} -p ${WRKDIST}/bin/* ${GOROOT}/bin

	@cd ${WRKDIST} && \
		find . ! -name .hg\* -type f -maxdepth 1 \
			-exec ${INSTALL_DATA} -p {} \
			${GOROOT} \;

.	for dir in ${DIRS}
		@cd ${WRKDIST} && \
			find ${dir} -type d \
				-exec ${INSTALL_DATA_DIR} \
				${GOROOT}/{} \;
		@cd ${WRKDIST} && \
			find ${dir} ! -name \*.orig -type f \
				-exec ${INSTALL_DATA} -p {} \
				${GOROOT}/{} \;
.	endfor

	# These get installed via `find' however we need them to be executable
	${INSTALL_PROGRAM_DIR} ${GOROOT}/pkg/tool/${GOOS}_${GOARCH}
	${INSTALL_PROGRAM} -p ${WRKDIST}/pkg/tool/${GOOS}_${GOARCH}/* \
		${GOROOT}/pkg/tool/${GOOS}_${GOARCH}
