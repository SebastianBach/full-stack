# see https://docs.docker.com/build/building/multi-stage/

FROM gcc:12.2.0 AS builder

RUN apt-get update && apt-get -y install cmake protobuf-compiler

WORKDIR /project
COPY src /project/src
COPY CMakeLists.txt /project/CMakeLists.txt
COPY src/docker/build.sh /project/build.sh
RUN /bin/bash /project/build.sh


FROM python:3.8-slim-buster

RUN useradd -ms /bin/bash local_user
USER local_user
WORKDIR /app
COPY src/docker/requirements.txt requirements.txt
RUN pip3 install -r requirements.txt

COPY src/web /app/web
COPY --from=builder /project/build/product/tools/title_case /app/title_case

WORKDIR /app/web/

CMD [ "python3", "web.py", "/app/web/resources/", "/app/"]
