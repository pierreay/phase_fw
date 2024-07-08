FROM ubuntu:22.04

RUN apt-get update

RUN DEBIAN_FRONTEND=noninteractive apt-get install -y tzdata

RUN apt-get install -y build-essential gdb lcov pkg-config \
    libbz2-dev libffi-dev libgdbm-dev libgdbm-compat-dev liblzma-dev \
    libncurses5-dev libreadline6-dev libsqlite3-dev libssl-dev \
    lzma lzma-dev tk-dev uuid-dev zlib1g-dev curl

RUN apt-get install -y libusb-dev make git avr-libc gcc-avr gcc-arm-none-eabi \
    libusb-1.0-0-dev usbutils

RUN adduser cw
USER cw

WORKDIR /home/cw

ENV PYENV_ROOT /home/cw/.pyenv
RUN curl https://pyenv.run | bash
ENV PATH $PYENV_ROOT/shims:$PYENV_ROOT/bin:$PATH
RUN echo 'export PATH="~/.pyenv/bin:$PATH"' >> ~/.bashrc && \
    echo 'export PATH="~/.pyenv/shims:$PATH"' >> ~/.bashrc && \
    echo 'eval "$(pyenv init -)"' >> ~/.bashrc && \
    echo 'eval "$(pyenv virtualenv-init -)"' >> ~/.bashrc

RUN pyenv install 3.9.5
RUN pyenv virtualenv 3.9.5 cw

RUN git clone --branch 5.7.0 --single-branch https://github.com/newaetech/chipwhisperer

WORKDIR ./chipwhisperer

RUN eval "$(pyenv init -) && $(pyenv virtualenv-init -)" && pyenv activate cw && \
    python -m pip install --upgrade pip && \
    python -m pip install -e .

RUN mkdir -p /home/cw/work
WORKDIR /home/cw/work

COPY shell_env.sh /home/cw/shell_env.sh

ENTRYPOINT /bin/bash --init-file ~/shell_env.sh