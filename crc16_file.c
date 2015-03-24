#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint16_t crc16_update(uint16_t crc, uint8_t a); 

int main(int argc, char * argv[])
{
   char ch;
   FILE *fp;
   FILE *output;
 
	 if(argc != 2){
	   printf("Example usage: crc16 filename\r\n");
     printf("   Automatically generates output.txt\r\n");
     printf("   First number output is File Size in bytes\r\n");
     printf("   Second number output is CRC16 checksum of contents\r\n");
		 exit(EXIT_FAILURE);
   }

 	 uint16_t crc = 0;
	 uint32_t num_bytes = 0;
   fp = fopen(argv[1],"r"); // read mode
   output = fopen("output.txt", "w");

   if( fp == NULL )
   {
      perror("Error while opening the input file.\n");
      exit(EXIT_FAILURE);
   }

   if( output == NULL )
   {
      perror("Error while opening the output file.\n");
      exit(EXIT_FAILURE);
   }
 
   while( ( ch = fgetc(fp) ) != EOF ){
      crc = crc16_update(crc, ch);
			printf("%c", ch);
			num_bytes++;
   }
 
	 printf("\r\n\r\n");
	 printf("Checksum: %d\r\n", crc);
	 printf("Size: %d\r\n", num_bytes);
   fclose(fp);

	 fprintf(output, "%d %d", num_bytes, crc);
	 fclose(output);

   return 0;
}

uint16_t crc16_update(uint16_t crc, uint8_t a)
{
	int i;
	crc ^= a;
	for (i = 0; i < 8; ++i)
	{
		if (crc & 1)
			crc = (crc >> 1) ^ 0xA001;
		else
			crc = (crc >> 1);
	}
	return crc;
}