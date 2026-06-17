DESCRIPTION:
This project implements a complete encoding and decoding system for steganography using BMP images.
The program hides a secret file (like .txt, .c, .cpp) inside a 24‑bit BMP image by modifying the least significant bits of pixel data.
During decoding, the program extracts the hidden data and reconstructs the original secret file.

FEATURES:

Encode any small file into a BMP image

Decode and recover the exact original file

Validates all input files and arguments

Uses a magic string (#*) to confirm the image contains hidden data

Modular code (main, encode, decode, headers)

Colored terminal output for better readability

CHALLENGES FACED:

Understanding how BMP headers and pixel data work

Handling binary file operations correctly

Bit manipulation (shifting, masking, LSB operations)

Avoiding segmentation faults while dealing with multiple file pointers

Making the code modular and easy to understand

Validating user inputs and file extensions

I overcame all these challenges by breaking the project into small parts, understanding each concept step‑by‑step, testing every function 
carefully, and improving the code through debugging, validation, and modular design.
