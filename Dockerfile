# Dockerfile
FROM mongodb/mongo-cxx-driver:3.10.1-redhat-ubi-9.4

WORKDIR /src

RUN microdnf upgrade -y && microdnf install -y g++ cmake

COPY ./src/ /src/

RUN mkdir build && cd build && cmake .. && make

CMD build/device-registry
