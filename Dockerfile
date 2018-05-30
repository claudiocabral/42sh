FROM gcc:6.4.0

LABEL maintainer="iomonad <iomonad@riseup.net>"
LABEL description="Isolated fuzzing environnement"

COPY . /usr/src/42sh
WORKDIR /usr/src/42sh

RUN make -j4 && make compile_fuzz
RUN make test
