# Text-Compressor
A Text Compressor built on C++ using Huffman Technique.

## Efficiency
* Input Text - 500 KB
* Mapper - 2 KB
* Encoded Text - 412 KB
* Compressed file is 82% of the original file.


## How to run?
To compress the text file run the following command on terminal :-

```bash
g++ encode.cpp
./a.out input.txt encoded_message.txt mapper.txt
```

To get the original text file run the following command on terminal :-

```bash
g++ decode.cpp
./a.out encoded_message.txt mapper.txt output.txt
```
