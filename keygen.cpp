#include <iostream>
#include <stdlib.h>     
#include <time.h>
#include <string>
#include <memory.h>
#include <ctime>
#include <fstream>

using namespace std;
//AES-128 cipher in CBC mode
// the first 1024 bytes of PDF files are reserved for headers 

const unsigned int KEY_SIZE = 16;
const unsigned int BYTE_VALUE_OVERFILL = 256;

// byte2str function converts a byte into
// its HEX representation, e.g.
// 179 => B3,
// 161 => A1,
// 56 => 38
// etc.
// Taken from https://stackoverflow.com/questions/10723403/char-array-to-hex-string-c
std::string byte2str(char byte) {
    const char hex_chars[16] = {
        '0', '1', '2', '3',
        '4', '5', '6', '7',
        '8', '9', 'A', 'B',
        'C', 'D', 'E', 'F'
    };
    std::string hex = "";
    hex += hex_chars[ ( byte & 0xF0 ) >> 4 ];
    hex += hex_chars[ ( byte & 0x0F ) >> 0 ];
    return hex;
}

//
std::string byteArray2hexString(char* bytes, unsigned int array_size) {
    std::string hexs = "";
    for (unsigned int i = 0; i < array_size; i++) {
        hexs += byte2str(bytes[i]);
    }
    return hexs;
}

time_t strTime2unix(std::string timeStamp)  
{  
    struct tm tm;  
    memset(&tm, 0, sizeof(tm));  
      
    sscanf(timeStamp.c_str(), "%d-%d-%d %d:%d:%d",   
           &tm.tm_year, &tm.tm_mon, &tm.tm_mday,  
           &tm.tm_hour, &tm.tm_min, &tm.tm_sec);  
  
    tm.tm_year -= 1900;  
    tm.tm_mon--;  
  
    return mktime(&tm);  
}  

int main(int argc, const char * argv[]) {
    
    // seed for PRG
    // equal to the current UNIX timestamp
    // last timestamp
    std::string str = "2020-02-10 18:53:00";
    time_t t = strTime2unix(str);
    unsigned int seed = (unsigned int)time(NULL);
    
    std::ofstream write("key.txt");
    for(int i=0;i<7200;i++){

   	 seed = t; 
   	 /* initialize PRG with the given seed */
   	 srand (seed);
    
   	 char key[KEY_SIZE];
   	 
   	 for (unsigned int i = 0; i < KEY_SIZE; i++) {
        	key[i] = rand() % BYTE_VALUE_OVERFILL;
    	 }
    
    	std::string key_str = byteArray2hexString(key, KEY_SIZE);
    	write << "KEY: " << key_str << "\n";
	t--;
    }
    write.close();
    return 0;
}
