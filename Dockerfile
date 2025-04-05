FROM emscripten/emsdk:latest

WORKDIR /raylib
RUN sudo apt update
RUN sudo apt upgrade -y
RUN sudo apt install -y libasound2-dev libx11-dev libxrandr-dev libxi-dev \
                        libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev \
                        libxinerama-dev libwayland-dev libxkbcommon-dev \
                        ninja-build

RUN git clone https://github.com/raysan5/raylib.git .
RUN git checkout tags/5.5

RUN echo "if (EMSCRIPTEN)\n"\
        "   set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -s GL_ENABLE_GET_PROC_ADDRESS=1")\n"\
        "   set(CMAKE_EXECUTABLE_SUFFIX ".html")\n"\
        "endif ()" >> CMakeLists.txt

RUN emcmake cmake -S . -B build -DPLATFORM=Web
RUN cmake --build build

WORKDIR /src
ENTRYPOINT ["/emsdk/docker/entrypoint.sh"]
