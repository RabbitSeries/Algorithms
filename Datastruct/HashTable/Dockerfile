FROM gcc:latest

COPY . /app

WORKDIR /app

RUN g++ -DONLINE_JUDGE -fno-tree-ch -O2 -Wall -std=gnu++20 -pipe u_mapVsArray.cc -lm -o u_mapVsArray

CMD ["./u_mapVsArray"]