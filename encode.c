#include <stdio.h>
#include<string.h>
#include "encode.h"
//#include "types.h"
#define RED       "\033[1;31m"
#define GREEN     "\033[1;32m"
#define YELLOW    "\033[1;33m"
#define MAGENTA   "\033[1;35m"
#define CYAN      "\033[1;36m"
#define WHITE      "\033[1;37m"
#define RESET     "\033[0m"

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
unsigned int get_image_size_for_bmp(FILE *fptr_image)
{
    unsigned int width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf(YELLOW "width = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf(YELLOW "height = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: success or failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    encInfo->src_image_fptr = fopen(encInfo->src_image_fname, "r");

    if (encInfo->src_image_fptr == NULL)
    {
    	//perror("fopen");
    	fprintf(stderr, RED "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return failure;
    }

    encInfo->secret_fptr = fopen(encInfo->secret_fname, "r");

    if (encInfo->secret_fptr == NULL)
    {
    	//perror("fopen");
    	fprintf(stderr, RED "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return failure;
    }

    encInfo->output_image_fptr = fopen(encInfo->output_image_fname, "w");

    if (encInfo->output_image_fptr == NULL)
    {
    	fprintf(stderr, RED "ERROR: Unable to open file %s\n", encInfo->output_image_fname);
        return failure;
    }

    return success;
}


unsigned int get_file_size(FILE *fptr)
{
    fseek(fptr, 0, SEEK_END);
    unsigned int size = ftell(fptr);
    fseek(fptr, 0, SEEK_SET);
    return size;
}

Status validate_encode_args(char *argv[],EncodeInfo *encInfo)
{
    //source file validation
    char *validate=strstr(argv[2],".bmp");
    if(validate ==NULL)
    {
        printf(RED "ERROR: source file must be .bmp\n");
        return failure;
    }

    FILE *fp=fopen(argv[2],"r");
    if(fp==NULL)
    {
        printf(RED "source file does not exist\n");
        return failure;
    }
    encInfo->src_image_fname=argv[2];     //store in structure


     //secret file validation
    char *secret[]={".txt",".c",".cpp"};
    int ext_count=3;
    int valid=0;
    for(int i=0;i<ext_count;i++)
    {
        if (strstr(argv[3], secret[i]) != NULL)  
        {
            strcpy(encInfo->secret_extn,secret[i]); //store the extension..so we can directly call it in status encode_secret_file_extn()
            valid=1;
            break;
        }
    }
    if(!valid)
    {
        printf(RED "secret file must be .txt,.c,.cpp\n");
        return failure;
    }
    encInfo->secret_fname = argv[3];
    FILE *fptr=fopen(argv[3],"r");
    if(fp==NULL)
    {
        printf(RED "secret file doesn't exist\n");
        return failure;
    }

    //output file validation
    if(argv[4]!=NULL)
    {
        char *output=strstr(argv[4],".bmp");
        {
            if(output==NULL)
            {
               printf(RED "ERROR: output file must be .bmp only\n");
                return failure;
            }
        }
        FILE *fpt=fopen(argv[4],"r");
        if(fp==NULL)
        {
            printf("Output File does not exist\n");
            return failure;
        }
        encInfo->output_image_fname=argv[4];
        return success;
    }
    encInfo->output_image_fname="stego.bmp";  //default file
    return success;

}




Status do_encoding(char *argv[], EncodeInfo *encInfo)
{
    printf(MAGENTA "Opening required files.....\n" RESET);
    if (open_files(encInfo) != success)
    {
        printf(RED "ERROR: Opening files failed\n" RESET);
        return failure;
    }
    printf(GREEN "DONE \n");
    printf(MAGENTA "Checking image capacity.....\n" RESET);
    if (check_capacity(encInfo) != success)
    {
        printf(RED "ERROR: Image does not have enough capacity\n" RESET);
        return failure;
    }
    printf(GREEN "DONE \n" RESET);
    printf(MAGENTA "Copying BMP header.....\n" RESET);
    if (copy_bmp_header(encInfo) != success)
    {
        printf(RED "ERROR: Copying BMP header failed\n" RESET);
        return failure;
    }
    printf(GREEN "DONE \n" RESET);
    printf(MAGENTA "Encoding Magic String.....\n" RESET);
    if (encode_magic_string(MAGIC_STRING, encInfo) != success)
    {
        printf(RED "ERROR: Encoding magic string failed\n" RESET);
        return failure;
    }
    printf(GREEN "DONE \n" RESET);
    printf(MAGENTA "Encoding Secret File Extension.....\n" RESET);
    if (encode_secret_file_extn(encInfo) != success)
    {
        printf(RED "ERROR: Encoding extension failed\n" RESET);
        return failure;
    }
    printf(GREEN "DONE \n" RESET);
    printf(MAGENTA "Encoding Secret File Size.....\n" RESET);
    if (encode_secret_file_size(encInfo) != success)
    {
        printf(RED "ERROR: Encoding secret file size failed\n" RESET);
        return failure;
    }
    printf(GREEN "DONE \n" RESET);
    printf(MAGENTA "Encoding Secret File Data.....\n" RESET);
    if (encode_secret_file_data(encInfo) != success)
    {
        printf(RED "ERROR: Encoding secret file data failed\n" RESET);
        return failure;
    }
    printf(GREEN "DONE \n" RESET);
    printf(MAGENTA "Copying remaining image data.....\n" RESET);
    if (copy_remaining_img_data(encInfo) != success)
    {
        printf(RED "ERROR: Copying remaining data failed\n" RESET);
        return failure;
    }
    printf(GREEN "DONE \n" RESET);
     printf(GREEN "ENCODING COMPLETED SUCCESSFULLY\n" RESET);
    return success;
}





//check the capacity of source file
Status check_capacity(EncodeInfo *encInfo)
{
    unsigned int img_capacity=get_image_size_for_bmp(encInfo->src_image_fptr);
    encInfo->secret_file_size=get_file_size(encInfo->secret_fptr);
    unsigned long long int encoding_things=(strlen(MAGIC_STRING)+ 4 +strlen(encInfo->secret_extn) + 4 + encInfo->secret_file_size)*8;

    if(img_capacity > encoding_things)
    {
        return success;
    }
    else
    {
         return failure;
    }
}




//copy 54 bytes from source file to destination file
Status copy_bmp_header(EncodeInfo *encInfo)
{
    unsigned char header[54];
    fseek(encInfo->src_image_fptr,0,SEEK_SET);
    fread(header,54,sizeof(unsigned char),encInfo->src_image_fptr);
    fwrite(header,54,sizeof(unsigned char),encInfo->output_image_fptr);
    return success;
}





Status encode_1byte_to_lsb(char data, char *buffer_8)
{
    for(int i=0;i<8;i++)
    {
        buffer_8[i]=buffer_8[i] & ~(1<<0);  //to clear lsb bit
        int bit = (data >> (7 - i)) & 1;
        buffer_8[i]=buffer_8[i] | bit;  //to set bit
    }
    return success;
}



Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    int length=strlen(magic_string);
    
    for(int i=0;i<length;i++)
    {
        char buffer[8];
        fread(buffer,sizeof(unsigned char),8,encInfo->src_image_fptr);
        encode_1byte_to_lsb(magic_string[i],buffer);
        fwrite(buffer,sizeof(unsigned char),8,encInfo->output_image_fptr);
    }
    return success;
}




Status encode_secret_file_extn(EncodeInfo *encInfo)
{
    //take extension which is already stored in validation
    char *ext = encInfo->secret_extn;
    int len=strlen(ext);  //find length of extn
    encInfo->secret_extn_size=len; //store length in file


     //encode extension(any extension,it is integer only..so 4*8=32 bytes)
    char buffer_32[32];
    fread(buffer_32,sizeof(unsigned char),32,encInfo->src_image_fptr);
    encode_4byte_to_lsb(len,buffer_32);
    fwrite(buffer_32, sizeof(unsigned char), 32, encInfo->output_image_fptr);

    for (int i = 0; i < len; i++)
    {
        //encode extension characters
        char buffer_8[8];
        fread(buffer_8,sizeof(unsigned char),8,encInfo->src_image_fptr);
        encode_1byte_to_lsb(encInfo->secret_extn[i], buffer_8);
        fwrite(buffer_8,sizeof(unsigned char),8,encInfo->output_image_fptr);
    }

    return success;
}



Status encode_4byte_to_lsb(int data, char *buffer_32)
{
    for(int i=0;i<32;i++)
    {
        buffer_32[i]=buffer_32[i] & ~(1<<0);  //to clear lsb bit
        int bit = (data >> (31 - i)) & 1;  //to go through each bit
        buffer_32[i]=buffer_32[i] | bit;  //to set bit
    }
    return success;
}






Status encode_secret_file_size(EncodeInfo *encInfo)
{
    char buffer_32[32];

    // Read 32 bytes from source image
    fread(buffer_32, 1, 32, encInfo->src_image_fptr);

    // Encode the file size
    encode_4byte_to_lsb(encInfo->secret_file_size, buffer_32);

    // Write 32 bytes to output image
    fwrite(buffer_32, 1, 32, encInfo->output_image_fptr);

    return success;
}

 //to encode data of secret file
Status encode_secret_file_data(EncodeInfo *encInfo)
{
    
    for(int i=0;i<encInfo->secret_file_size;i++)
    {
        char buffer_8[8];    //we need to encode 8 bytes of image for 1 byte so use array
        char secret_1;     //from secret file,we need to encode byte by byte..so use character
        fread(buffer_8,sizeof(unsigned char),8,encInfo->src_image_fptr);   //buffer itself pointer so no need of &
        fread(&secret_1,sizeof(unsigned char),1,encInfo->secret_fptr);    //fread 1st arfument must be pointer..so use &
        encode_1byte_to_lsb(secret_1, buffer_8);
        fwrite(buffer_8,sizeof(unsigned char),8,encInfo->output_image_fptr);
    }
    return success;
}







//copy the remaining bytes into output
Status copy_remaining_img_data(EncodeInfo * encInfo)
{
    char ch;
    while(fread(&ch,sizeof(unsigned char),1,encInfo->src_image_fptr)==1)
    {
        fwrite(&ch,sizeof(unsigned char),1,encInfo->output_image_fptr);
    }
    return success;
}

