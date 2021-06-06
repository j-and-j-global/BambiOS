# BambiOS

A small application running as an embedded kernel which acts as a lookup menu to show which flightcase (and which position _in_ that flightcase) records in my collection may be found.

Runs from a small laptop.

## Building

A kernel image may be built as per:

```bash
$ make all
```

Or, since this is the default tasK:

```bash
$ make
```

### Building on a Mac/ Windows

The BambiOS kernel needs some gnu elf tools which may not be available on non-linux.

The kernel can, instead, be built via docker:

```bash
$ docker run -v $(pwd):$(pwd) -w $(pwd) runar0/docker-gcc-nasm-cmake make
```

## Testing

BambiOS may be run via qemu, via `make`

```bash
$ make boot
```
