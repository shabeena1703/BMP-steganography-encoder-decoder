/*NAME: SHAIK SHABEENA
REGISTRATION NO: 25048_004

DESCRIPTION:
 * This project is used to hide the content of one file,message,image or video within other file,meaasage,
    image or video.
 * This technology is used in spying and military applications.
 * This technology is used to hide an invisible digital signature inside music or video to stop theft.
                                // main.c
 
 * This file controls the entire program.
 * It does NOT do encoding or decoding itself.
 * Its only job is to:
 *      1. Read the command-line arguments
 *      2. Check whether the user wants:
 *         - ENCODE (-e)
 *         - DECODE (-d)
 *      3. Call the correct functions from encode.c or decode.c
 
                             //encode.h
*This file contains everything needed for encoding:
1. EncodeInfo structure:
    - Stores source BMP file details
    - Stores secret file details
    - Stores output (stego) image details
2. Function declarations used in encoding.
* This file does NOT perform encoding.
* It only provides the structure and function names that encode.c will use.

                             //encode.c
 * This file performs the complete ENCODING process.
 * Encoding means hiding a secret file inside a BMP image.
 * Steps done here:
      1. Open the source BMP, secret file, and output file
      2. Check if the BMP has enough space to hide the secret file
      3. Copy the BMP header (first 54 bytes)
      4. Hide the magic string (#*) to mark the image as encoded
      5. Hide the secret file extension (like .txt)
      6. Hide the secret file size
      7. Hide the actual secret file data using LSB method
      8. Copy the remaining image data normally
 * Functions like encode_1byte_to_lsb() and encode_4byte_to_lsb() are used to hide data bit-by-bit inside the image.
 * This file contains ALL the logic for encoding.

                            // decode.h
 * This file contains everything needed for decoding:
 1. DecodeInfo structure:
      - Stores stego image details
      - Stores output secret file details
      - Stores extension and size of the hidden file
2. Function declarations used in decoding.
 * This file does NOT perform decoding.
 * It only provides the structure and function names that decode.c will use.

                        //decode.c
 * This file performs the complete DECODING process.
 * Decoding means extracting the hidden secret file from the stego BMP image.
 Steps done here:
    1. Open the stego BMP image
    2. Read and verify the magic string (#*)
    3. Read the secret file extension
    4. Read the secret file size
    5. Read the secret file data and write it to a new file
* Functions like decode_1byte_from_lsb() and decode_4bytes_from_lsb() are used to extract data bit-by-bit from the image.
* This file contains ALL the logic for decoding.

                        //common.h
 * This file stores common things used by both encoding and decoding.Instead of writing these things again and again in 
   every file, we keep them here.
 * MAGIC_STRING:
      - A small string "#*" that we hide inside the image.
      - During decoding, we check this string to confirm that the image actually contains hidden data.
 * Status:
      - Used as return values for functions.
      - success → everything worked
      - failure → something went wrong
 * Opr_type:
      - Tells what operation the user selected:
      - encode  → hide data
      - decode  → extract data
      - unsupported → invalid option




*/
#include <stdio.h>
#include<string.h>
#include "encode.h"
#include "decode.h"
#include "common.h"

#define RED       "\033[1;31m"
#define GREEN     "\033[1;32m"
#define YELLOW    "\033[1;33m"
#define MAGENTA   "\033[1;35m"
#define CYAN      "\033[1;36m"
#define WHITE     "\033[1;37m"
#define RESET     "\033[0m"


Opr_type check_operation(char *option)
{
    if (strcmp(option, "-e") == 0)
        return encode;

    else if (strcmp(option, "-d") == 0)
        return decode;

    else
        return unsupported;
}
int main(int argc, char *argv[])
{
    EncodeInfo encodeInfo;

    if( argc == 1 )
    {
	// print -> Error + usage msg
    printf(RED "ERROR: No arguments provided\n" RESET);
    printf(YELLOW "Usage: ./a.out -e <src.bmp> <secret>\n"RESET );
	return 0;
    }

    int opr = check_operation(argv[1]);

    if( opr == encode )
    {
        if( argc < 4 || argc > 5 )
        {
            // print -> Error + usage msg
            printf(RED "Invalid arguments\n" RESET);
            printf(YELLOW "The usage of arguments order should be : ./a.out -e <source_file.bmp> secret_file.ext>\n" RESET);
            return 0;
        }
        else
        {
            printf(CYAN "YOU SELECTED ENCODE OPERATION\n" RESET);
            if (validate_encode_args(argv, &encodeInfo) == failure)
            {
                printf(RED "Validation failed\n" RESET);
                return 0;
            }
            else    
            {
                printf(GREEN "Validation success\n" RESET);
                printf(WHITE "source image file name is %s\n" RESET, encodeInfo.src_image_fname);
                printf(WHITE "Secret file name is %s\n" RESET,encodeInfo.secret_fname);
                printf(WHITE "output file name is %s\n" RESET,encodeInfo.output_image_fname);
                do_encoding(argv, &encodeInfo);
            }
        }

    }
    else if( opr == decode )
    {
        DecodeInfo decInfo;
        if( argc < 3 || argc > 4 )	
        {
            // print -> Error + usage msg
            printf(RED "Invalid arguements\n" RESET);
            printf(YELLOW "The arguments order should be : ./a.out -d <stego.bmp> <secret>\n" RESET);
            
            return 0;
        }
        else
        {
            printf(CYAN  "YOU SELECTED DECODE OPERATION\n" RESET);
            if(validate_decode_args(argv, &decInfo) == failure)
            {
                printf(RED "Validation failed\n" RESET);
                return 0;
            }
            else
            {
                do_decoding(argv,&decInfo);
            }
        }
    }
    else
    {
	// Print -> Error + usage msg
    printf(RED "Invalid arguments other than encode and decode .please give the second argument as -e or -d only" RESET);
    }

return 0;


}
