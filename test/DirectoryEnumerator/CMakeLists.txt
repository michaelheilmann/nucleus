# Copyright (c) 2017, 2018 Michael Heilmann
# Assert minimum CMake version.
cmake_minimum_required(VERSION 3.8)
# Define the test.
set(libraries Nucleus.Library)
define_test(Nucleus Nucleus.Test.DecimalEnumerator ${libraries} ${NUCLEUS_LANGUAGE_ID_C})
