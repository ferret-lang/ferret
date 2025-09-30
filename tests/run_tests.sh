#!/bin/bash

# Building and running the tests.
cd ./build && make
cd ../tests/ && ../build/tests/run_tests
