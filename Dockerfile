FROM alpine:3
LABEL maintainer="Gioele Minardi <gioelem3@gmail.com>"
RUN apk add --no-cache curl-dev openssl-dev sqlite-dev zlib-dev build-base cmake boost-dev bash
WORKDIR /turbabot
COPY . .
WORKDIR /turbabot/build
RUN cmake -DCMAKE_BUILD_TYPE=Release ..
RUN make -j
RUN mkdir data
VOLUME ["/turbabot/build/data"]
ENTRYPOINT ["./TurbaMovieBot"]