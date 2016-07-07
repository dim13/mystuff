# $OpenBSD$

COMMENT =		sndiod spectrogram visualization
DISTNAME =		spectrogram-2.0
CATEGORIES =		audio x11
HOMEPAGE =		http://www.dim13.org/Tags/spectrogram
MASTER_SITES =		ftp://ftp.dim13.org/pub/src/
MAINTAINER =		Dimitri Sokolyuk <demon@dim13.org>

# ISC
PERMIT_PACKAGE_CDROM =	Yes

WANTLIB +=		X11 c m sndio fftw3

LIB_DEPENDS =		math/fftw3

.include <bsd.port.mk>
