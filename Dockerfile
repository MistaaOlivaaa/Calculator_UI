FROM ubuntu:22.04


ENV DEBIAN_FRONTEND=noninteractive
ENV DISPLAY=host.docker.internal:0.0

# Install system dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    pkg-config \
    libgtk-3-dev \
    libx11-dev \
    x11-apps \
    xauth \
    && rm -rf /var/lib/apt/lists/*


WORKDIR /app


COPY calculator.c .
COPY CMakeLists.txt .


RUN cmake . && make


RUN echo '#!/bin/bash\n\
echo "Starting Calculator..."\n\
echo "Make sure you have an X11 server running on Windows (like VcXsrv or Xming)"\n\
echo "And run: docker run -e DISPLAY=host.docker.internal:0.0 --rm calculator"\n\
./calculator' > run_calculator.sh && chmod +x run_calculator.sh


CMD ["./run_calculator.sh"] 