<img width="1366" height="720" alt="image" src="https://github.com/user-attachments/assets/ce60a24b-f926-4fdb-bd5c-878add8a53b4" />Steganography in C using LSB Technique
-----------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------
📝 Brief Summary
-----------------------------------------------------------------------------------------------------------------------------------------
This project hides a secret file inside a 24‑bit BMP image using the Least Significant Bit (LSB) technique.
The image looks completely normal to the human eye, but it secretly contains hidden data.

The project supports both:

Encoding → hiding the secret file inside the image

Decoding → extracting the hidden file back from the image

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
📌 Overview
-----------------------------------------------------------------------------------------------------------------------------------------
Steganography is a method of hiding information inside another file so that no one knows the data exists.

In this project:

The cover image is a BMP file

The secret file can be any small file (text, C program, etc.)

The output image is a BMP file that contains the hidden data

The idea is simple:
We take each byte of the image and replace its last bit with the bits of the secret file.
This tiny change does not affect the image visually, but it stores the hidden data safely.

This project helped me understand:

How BMP images are structured

How binary files work

How bitwise operations store data inside pixels

How to design modular C programs

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
🎯 Problem Statement
-----------------------------------------------------------------------------------------------------------------------------------------
Sending sensitive information online is risky.
Encryption protects the data, but it also reveals that something secret is being sent.

Steganography solves this problem by hiding the data inside an image, so no one even knows something confidential is present.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
📂 Datasets Used
-----------------------------------------------------------------------------------------------------------------------------------------
No external datasets are required.

This project uses:

A 24‑bit BMP image (cover image)

A secret file (text or any small file)

An encoded BMP image (after hiding the data)

A decoded output file (after extraction)

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
🛠️ Tools and Technologies Used
-----------------------------------------------------------------------------------------------------------------------------------------
Programming Language
C

Operating System
Linux (Ubuntu)

Compiler
GCC

Development Tools
VS Code / Vim

Git & GitHub

Concepts Used
File Handling

Bitwise Operations

BMP Image Processing

Modular Programming

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
🔧 Methods 
-----------------------------------------------------------------------------------------------------------------------------------------
🔐 Encoding Process (Hiding Data)
-----------------------------------------------------------------------------------------------------------------------------------------

Read the BMP image

Copy the BMP header (first 54 bytes)

Read the secret file

Embed metadata:

Magic string (#*)

Secret file extension

Secret file size

Convert secret data into bits

Replace the least significant bit of each image byte with secret bits

Save the modified image as a new BMP file

🔍 Decoding Process (Extracting Data)
-----------------------------------------------------------------------------------------------------------------------------------------
Read the encoded BMP image

Check the magic string to confirm hidden data exists

Extract the secret file extension

Extract the secret file size

Extract secret data bit‑by‑bit

Reconstruct the original secret file

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
💡 Key Insights
-----------------------------------------------------------------------------------------------------------------------------------------
Learned how BMP headers and pixel data are structured

Understood binary file reading and writing

Improved bitwise operation skills

Explored real‑world information hiding

Practiced modular programming in C

Strengthened debugging and command‑line skills

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
📦 Output
-----------------------------------------------------------------------------------------------------------------------------------------
🔐 Encoding
-----------------------------------------------------------------------------------------------------------------------------------------
Code

$ ./a.out -e beautiful.bmp secret.txt output.bmp

Encoding Successful!

Output File:

output.bmp

🔍 Decoding
-----------------------------------------------------------------------------------------------------------------------------------------
Code

$ ./a.out -d output.bmp decode_secret.txt

Decoding Successful!

Recovered Secret Message:

My password is Secret ;)

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

🚀 How to Run This Project
-----------------------------------------------------------------------------------------------------------------------------------------
Clone Repository
-----------------------------------------------------------------------------------------------------------------------------------------
Code

git clone https\://github.com/yourusername/steganography.git

Navigate to Project Folder
-----------------------------------------------------------------------------------------------------------------------------------------

Code

cd steganography

Compile
-----------------------------------------------------------------------------------------------------------------------------------------

Code
gcc *.c -o steganography

or

Code

make

Encode
-----------------------------------------------------------------------------------------------------------------------------------------
Code
./steganography -e input.bmp secret.txt output.bmp

Decode
-----------------------------------------------------------------------------------------------------------------------------------------
Code
./steganography -d output.bmp recovered.txt

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

🧪 Result and Conclusion
-----------------------------------------------------------------------------------------------------------------------------------------
This project successfully hides confidential data inside a BMP image while keeping the image visually unchanged.
It shows how steganography can be used for secure and invisible data transmission using simple bitwise operations.

----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
🔮 Future Work
-----------------------------------------------------------------------------------------------------------------------------------------
Support PNG and JPEG formats

Encrypt secret message before embedding

Add password protection

Support hiding PDFs, audio, video

Build a GUI

Improve embedding capacity

Optimize for larger files

------------------------------------------------------------------------------------------------------------------------------------------
-----------------------------------------------------------------------------------------------------------------------------------------
👤 Author & Contact
-----------------------------------------------------------------------------------------------------------------------------------------
Shaik Shabeena  
Electronics and Communication Engineering
Email: shaikshabeena@gmail.com
Linkedin: https://www.linkedin.com/in/shaik-shabeena-36a7b9332/

-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
