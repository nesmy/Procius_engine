#! /bin/sh

cmake -DGLFW_BUILD_DOCS=OFF -S . -B ./build -G "Unix Makefiles"