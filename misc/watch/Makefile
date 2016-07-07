# $Id: Makefile,v 1.9 2011/08/10 21:32:15 demon Exp $

COMMENT=	"execute program periodically, showing output fullscreen"

DISTNAME=	watch-2.1
CATEGORIES=	misc

HOMEPAGE=	https://www.dim13.org/
MASTER_SITES=	ftp://ftp.dim13.org/pub/src/

MAINTAINER=	Dimitri Sokolyuk <demon@dim13.org>

PERMIT_PACKAGE_CDROM=	Yes
WANTLIB=		c curses

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/watch ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/watch.1 ${PREFIX}/man/man1

.include <bsd.port.mk>
