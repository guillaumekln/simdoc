# simdoc

**simdoc** associates most similar documents in a dataset using the [TF-IDF](https://en.wikipedia.org/wiki/Tf%E2%80%93idf) method.

## Requirements

* *C++11*
* *boost*
* *Intel TBB*
* *CMake*

## Usage

```shell
./simdoc [options] input
```

where `input` is either a directory or a text file with one file per line.

See `--help` option for a complete usage.

## Example

The command

```shell
./simdoc -t 8 -c 5 -r data/ > output.json
```

associates the 5 most similar documents to each document in the `data` directory and its sub-directories using 8 threads.

See `examples/output.json` for an output example.
