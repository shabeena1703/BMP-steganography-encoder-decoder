#include<stdio.h>
#include<string.h>
#include"decode.h"

#define RED       "\033[1;31m"
#define GREEN     "\033[1;32m"
#define YELLOW    "\033[1;33m"
#define MAGENTA   "\033[1;35m"
#define CYAN      "\033[1;36m"
#define WHITE     "\033[1;37m"
#define RESET     "\033[0m"
Status open_img_file(DecodeInfo *decInfo)
{
    decInfo->stego_image_fptr=fopen(decInfo->stego_image_fname,"r");
    if(decInfo->stego_image_fptr==NULL)
    {
        fprintf(stderr,RED "ERROR: unable to open file %s\n",decInfo->stego_image_fname);
        return failure;
    }

    return success;
}






Status validate_decode_args(char *argv[], DecodeInfo *decInfo)
{
    // Validate output image
    char *validate = strstr(argv[2], ".bmp");
    if (validate == NULL)
    {
        printf(RED "ERROR: Stego image must be .bmp\n");
        return failure;
    }
    FILE *fp = fopen(argv[2], "r");
    if (fp == NULL)
    {
        printf(RED "ERROR: Stego image does not exist\n");
        return failure;
    }
    fclose(fp);
    decInfo->stego_image_fname = argv[2];   // store in structure


    // Validate secret file
    if (argv[3] != NULL)
    {
        strcpy(decInfo->secret_fname, argv[3]);
        return success;
    }
    else
    {
        // Default secret file name
        strcpy(decInfo->secret_fname,"decoded_secret");
    
    }
    return success;
}





Status do_decoding(char *argv[], DecodeInfo *decInfo)
{
    printf(MAGENTA "Opening required files.....\n" RESET);
    if (open_img_file(decInfo) != success)
    {
        printf(RED "ERROR: Opening files failed\n" RESET);
        return failure;
    }
    printf(GREEN "DONE \n" RESET);

    printf(MAGENTA "Decoding Magic String.....\n" RESET);
    if (decode_magic_string(decInfo) != success)
    {
        printf(RED "ERROR: Decoding magic string failed\n" RESET);
        return failure;
    }
    printf(GREEN "DONE \n" RESET);

    printf(MAGENTA "Decoding Secret File Extension.....\n" RESET);
    if (decode_secret_file_extn(argv,decInfo) != success)
    {
        printf(RED "ERROR: Decoding extension failed\n" RESET);
        return failure;
    }
    printf(GREEN "DONE \n" RESET);

    printf(MAGENTA "Decoding Secret File Size.....\n" RESET);
    if (decode_secret_file_size(decInfo) != success)
    {
        printf(RED "ERROR: Decoding secret file size failed\n" RESET);
        return failure;
    }
    printf(GREEN "DONE \n" RESET);

    printf(MAGENTA "Decoding Secret File Data.....\n" RESET);
    if (decode_secret_file_data(decInfo) != success)
    {
        printf(RED "ERROR: Decoding secret file data failed\n" RESET);
        return failure;
    }
    printf(GREEN "DONE \n" RESET);

    printf(GREEN "DECODING COMPLETED SUCCESSFULLY\n" RESET);
    return success;
}









char decode_1byte_from_lsb(char *buffer_8)
{
    char ch=0;
     for(int i=0;i<8;i++)
    {
        int bit=buffer_8[i] & 1;
        ch=ch << 1;
        ch=ch | bit;
    }
    return ch;
}






Status decode_magic_string(DecodeInfo *decInfo)
{
    int len = strlen(MAGIC_STRING);   
    char decoded_magic[len+1];
    char buffer_8[8];
    fseek(decInfo->stego_image_fptr, 54, SEEK_SET);

    // Decode each character
    for (int i = 0; i < len; i++)
    {
        fread(buffer_8, sizeof(unsigned char), 8, decInfo->stego_image_fptr);
        decoded_magic[i] = decode_1byte_from_lsb(buffer_8);
    }
    decoded_magic[len] = '\0';
    if (strcmp(decoded_magic,MAGIC_STRING) == 0)
    {
        printf(GREEN "Magic string decoded successfully\n");
        return success;
    }
    else
    {
        printf(RED "ERROR: Magic string mismatch. Found: %s\n", decoded_magic);
        return failure;
    }

}






int  decode_4bytes_from_lsb(char *buffer_32)
{

    int data = 0;
    for (int i = 0; i < 32; i++)
    {
        data = data << 1;             
        int bit = buffer_32[i] & 1;    // take LSB
        data = data | bit;             // set that bit
    }
    return data;
}






Status decode_secret_file_extn(char *argv[],DecodeInfo *decInfo)
{
    char buffer_32[32];
    fread(buffer_32, sizeof(unsigned char), 32, decInfo->stego_image_fptr);
    int extn_size = decode_4bytes_from_lsb(buffer_32);
    char secret_extn[extn_size + 1];

    // Decode extension characters
    for (int i = 0; i < extn_size; i++)
    {
        char buffer_8[8];
        fread(buffer_8, sizeof(unsigned char), 8, decInfo->stego_image_fptr);

        secret_extn[i] = decode_1byte_from_lsb(buffer_8);
    }

    secret_extn[extn_size] = '\0';   
    strcpy(decInfo->secret_extn, secret_extn);   
    int i = 0;
    while (decInfo->secret_fname[i] != '\0')
    {
        if (decInfo->secret_fname[i] == '.')
        {
            decInfo->secret_fname[i] = '\0';  
            break;
        }
        i++;
    }
    
    //concate the secret file name and its entension(which have done in encoding)
    strcat(decInfo->secret_fname, decInfo->secret_extn);  
    printf(YELLOW "Secret file name is : %s\n", decInfo->secret_fname);

    // Open secret file for writing
    decInfo->secret_fptr = fopen(decInfo->secret_fname, "w");
    if (decInfo->secret_fptr == NULL)
    {
        printf(RED "ERROR: Could not create output file\n");
        return failure;
    }
    return success;
}







Status decode_secret_file_size(DecodeInfo *decInfo)
{
    char buffer_32[32];
    // Read 32 bytes from stego image
    fread(buffer_32, sizeof(char), 32, decInfo->stego_image_fptr);
    decInfo->secret_file_size = decode_4bytes_from_lsb(buffer_32);
    printf(YELLOW "Secret file size = %d bytes\n",decInfo->secret_file_size);

    return success;
}







Status decode_secret_file_data(DecodeInfo *decInfo)
{
    for(int i = 0; i < decInfo->secret_file_size; i++)
    {
        char buffer_8[8];   // 8 bytes from image
        char secret_1;      // decoded character

        // Read 8 bytes from stego image
        fread(buffer_8, sizeof(unsigned char), 8,decInfo->stego_image_fptr);

        // Decode 1 byte from LSBs
        secret_1 = decode_1byte_from_lsb(buffer_8);

        // Write decoded byte into secret file
        fwrite(&secret_1, sizeof(unsigned char), 1,decInfo->secret_fptr);
    }

    return success;
}