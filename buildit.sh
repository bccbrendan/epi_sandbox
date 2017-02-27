cd build && \
cmake ../ -DBUILD_TEST=TRUE && \
cmake --build . && \
cd ../ && \
./build/bin/epi_test

