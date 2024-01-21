FROM ubuntu:22.04
WORKDIR /tmp
COPY docker/installers .

RUN bash update_cache.sh

RUN bash install_essentials.sh
RUN bash install_python_modules.sh
RUN bash install_cmake.sh
RUN bash install_boost.sh

RUN bash clean_cache.sh

WORKDIR /cycleon
RUN rm -rf /tmp/*
