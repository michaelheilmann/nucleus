# Copyright (c) 2017, 2018 Michael Heilmann
# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)
# Define the demo.
set(libraries Nucleus.Library)
define_executable(Nucleus Nucleus.Demo ${libraries} ${NUCLEUS_LANGUAGE_ID_C})
