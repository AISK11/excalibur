# Excalibur

*- malware analyzer.*

## About

## Installation

## Compilation (Manual Installation)

### Linux

1. Install dependency tools:
    - `git`
    - `make`
    - `musl-gcc`
    - `x86_64-w64-mingw32-gcc`
1. Compile Excalibur from source:
    ```sh
    git clone --depth 1 'https://gitlab.com/AISK11/excalibur/' /opt/excalibur/
    cd /opt/excalibur/ && make linux
    ```
1. Link to system location:
    ```sh
    ln -s -f /opt/excalibur/bin/excalibur /usr/local/bin/excalibur
    ```

## Usage

1. Analyze file:
    ```sh
    excalibur <FILE>
    ```
