.RECIPEPREFIX = >
.PHONY: all linux windows clean

ENV     := SOURCE_DATE_EPOCH=0
CFLAGS  := -std=gnu18 -Wall -Wextra -Wpedantic -Werror -pipe -O2 -s
LDFLAGS := -lm
SOURCES := $(wildcard src/*.c) $(wildcard src/WjCryptLib/*.c)

all: linux windows

linux: $(SOURCES)
> @mkdir -p bin/
> $(ENV) musl-gcc $(CFLAGS) -o bin/excalibur $(SOURCES) $(LDFLAGS) -static

windows: $(SOURCES)
> @mkdir -p bin/
> $(ENV) x86_64-w64-mingw32-gcc $(CFLAGS) -o bin/excalibur.exe $(SOURCES) $(LDFLAGS) -static

clean:
> @rm -r -f bin/
