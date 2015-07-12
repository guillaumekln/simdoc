# simdoc

**simdoc** associates most similar documents in a dataset using the [TF-IDF](https://en.wikipedia.org/wiki/Tf%E2%80%93idf) method.

## Requirements

* *C++11*
* *boost*
* *Intel TBB*
* *CMake*

## Usage

```shell
./simdoc [options] directory
```

See `--help` options for a complete usage.

## Example

The command

```shell
./simdoc -t 8 -c 3 -r data/ > output.json
```

associates the 3 most similar documents to each document in the `data` directory and its sub-directories using 8 threads.

See `examples/output.json` for an output example.
