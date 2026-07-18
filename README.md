📘 Steganography in C using LSB Technique
------------------------------------------------------------------------------------------------------------------------------------------
📝 Brief Summary
Steganography is the practice of hiding confidential information inside digital media without revealing its existence.
This project hides a secret file inside a 24‑bit BMP image using the Least Significant Bit (LSB) technique.
The hidden message can be extracted later without any visible change in the image.
-----------------------------------------------------------------------------------------------------------------------------------------
📘 Overview
The objective of this project is to securely hide text or small files inside bitmap images while keeping the image visually unchanged.
Unlike encryption, which makes data unreadable, steganography hides the existence of the message itself.

This project demonstrates:

Low‑level file manipulation

Bitwise programming

BMP image processing

Modular C programming
------------------------------------------------------------------------------------------------------------------------------------------
🎯 Problem Statement
Digital communication often requires secure transmission of sensitive information.
Encryption protects the content but also signals that confidential information exists.

The challenge is to hide the existence of the data itself.

This project solves that problem by embedding secret text into the least significant bits of image pixels, making the modifications invisible to the human eye.
------------------------------------------------------------------------------------------------------------------------------------------
📁 Datasets
No external datasets are required.

This project uses:

24‑bit BMP image (cover image)

Secret text file

Encoded BMP image

Decoded output file
------------------------------------------------------------------------------------------------------------------------------------------
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

Command‑Line Programming
------------------------------------------------------------------------------------------------------------------------------------------
🧩 Methods (How the Project Works)
Encoding Process
Read the cover BMP image

Copy the BMP header

Read the secret file

Embed metadata:

Magic string (#*)

Secret file extension

Secret file size

Replace the LSB of each image byte with secret data bits

Save the modified image

Decoding Process
Read the encoded BMP image

Verify the magic string

Extract the secret file extension

Extract the secret file size

Extract the secret data bit‑by‑bit

Reconstruct the original file
------------------------------------------------------------------------------------------------------------------------------------------
💡 Key Insights
Learned BMP image structure

Understood binary file handling

Improved bitwise operation skills

Explored information hiding techniques

Practiced modular programming

Strengthened debugging skills
------------------------------------------------------------------------------------------------------------------------------------------
📦 Output
------------------------------------------------------------------------------------------------------------------------------------------
Encoding
Code
$ ./a.out -e beautiful.bmp secret.txt output.bmp

Encoding Successful!

Output File:
output.bmp
Decoding
Code
$ ./a.out -d output.bmp decode_secret.txt

Decoding Successful!

Recovered Secret Message:
My password is Secret ;)
🚀 How to Run This Project
Clone Repository
Code
git clone https://github.com/yourusername/steganography.git
Navigate to Project Folder
Code
cd steganography
Compile
Code
gcc *.c -o steganography
or

Code
make
Encode
Code
./steganography -e input.bmp secret.txt output.bmp
Decode
Code
./steganography -d output.bmp recovered.txt
------------------------------------------------------------------------------------------------------------------------------------------
🧪 Result and Conclusion
The project successfully hides confidential text inside a BMP image while preserving the visual quality of the image.
The hidden data can be extracted accurately, proving the effectiveness of the LSB steganography technique.
------------------------------------------------------------------------------------------------------------------------------------------
🔮 Future Work
Support PNG and JPEG formats

Encrypt the secret message before embedding

Add password‑based authentication

Support hiding PDF, audio, and video files

Develop a GUI

Improve embedding capacity

Optimize for larger files
------------------------------------------------------------------------------------------------------------------------------------------
👤 Author
Shaik Shabeena  
Electronics and Communication Engineering

I enjoy working on low‑level and system‑focused projects where I can understand how things work internally — from bits and bytes to complete embedded systems.

Interests
Embedded Systems

C Programming

Image Processing

Information Security
