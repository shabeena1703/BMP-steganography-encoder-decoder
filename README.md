📘 Steganography in C using LSB Technique

📝 Brief Summary

This project implements Image Steganography using the Least Significant Bit (LSB) technique in the C programming language.

The main objective of this project is to securely hide a secret file inside a 24-bit BMP image without causing any visible changes to the image. Although the encoded image appears identical to the original, it secretly contains hidden information that can only be retrieved through the decoding process.

The project supports two main operations:

🔐 Encoding
Hides a secret file inside a BMP image.
Generates a new encoded image containing the hidden data.
🔓 Decoding
Extracts the hidden secret file from the encoded BMP image.
Reconstructs the original file successfully.

This project demonstrates the practical implementation of bitwise operations, binary file handling, BMP image processing, and modular programming in C.

📌 Overview

Steganography is a technique used to conceal confidential information inside another file so that the existence of the hidden data remains unnoticed.

Unlike encryption, which converts information into unreadable text and indicates that protected information exists, steganography hides the data completely inside another file. As a result, the communication appears completely normal.

In this project:

🖼️ The cover image is a 24-bit BMP image.
📄 The secret file can be a text file, C source file, or any other small file.
🖼️ The output is another BMP image that secretly contains the hidden file.

The project works by replacing the Least Significant Bit (LSB) of each image byte with the bits of the secret file.

Since only the last bit of each byte is modified, the difference in the image is extremely small and cannot be noticed by the human eye.

Along with the secret data, the project also stores:

Magic String (#*)
Secret file extension
Secret file size

During decoding, this information is extracted first, followed by the hidden file, allowing the original file to be reconstructed successfully.

This project helped me understand:

BMP image structure
Binary file handling
Bitwise operations
Information hiding techniques
Modular programming in C
🎯 Problem Statement

Sharing confidential information over digital communication channels always carries security risks.

Although encryption protects the contents of a file, it also reveals that confidential information is being transmitted.

Steganography overcomes this limitation by hiding confidential information inside an ordinary image, making it difficult for anyone to detect the presence of hidden data.

The objective of this project is to:

Hide confidential information inside a BMP image.
Preserve the visual quality of the original image.
Recover the original secret file accurately.
Demonstrate secure information hiding using the Least Significant Bit (LSB) technique.
📂 Datasets Used

This project does not require any external datasets.

Instead, it uses the following files:

🖼️ Cover Image

A 24-bit BMP image that acts as the carrier image for embedding the secret data.

📄 Secret File

Any small file that needs to be hidden inside the image.

Examples include:

Text files
C source files
Header files
Other supported small files
🖼️ Encoded BMP Image

The output image generated after embedding the secret data.

📄 Decoded Output File

The recovered secret file obtained after decoding.

🛠️ Tools and Technologies Used
Programming Language
C
Operating System
Linux (Ubuntu)
Compiler
GCC
Development Tools
Visual Studio Code
Vim
Git
GitHub
Concepts Used
File Handling
Binary File Handling
Bitwise Operations
BMP Image Processing
Least Significant Bit (LSB) Technique
Modular Programming
Command-Line Programming
🔧 Methods (How the Project Works)

The project consists of two major phases:

🔐 Encoding Process (Hiding Data)

The encoding process hides the secret file inside the BMP image by modifying only the Least Significant Bit (LSB) of each image byte.

Step 1 – Read the BMP Image

The original 24-bit BMP image is opened and read.

Step 2 – Copy the BMP Header

The first 54 bytes (BMP Header) are copied directly to the output image to preserve the image format.

Step 3 – Read the Secret File

The file that needs to be hidden is opened and read.

Step 4 – Embed Metadata

The following information is stored inside the image:

Magic String (#*)
Secret File Extension
Secret File Size
Step 5 – Embed Secret Data

Each byte of the secret file is converted into bits.

One bit is embedded into the Least Significant Bit of each image byte.

Step 6 – Generate Encoded Image

The modified image is saved as a new BMP image containing the hidden data.

The encoded image appears visually identical to the original image while secretly storing the confidential information.

In the next part, I'll provide:

🔍 
Decoding Process
