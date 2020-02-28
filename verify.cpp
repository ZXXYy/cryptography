#include <iostream>
#include <stdlib.h>     
#include <time.h>

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

int main(int argc, const char * argv[]) {
    
    // seed for PRG
    unsigned int seed = 1581389580;
    
    /* initialize PRG with the given seed */
    srand (seed);
    
    char key[KEY_SIZE];
    
    for (unsigned int i = 0; i < KEY_SIZE; i++) {
        key[i] = rand() % BYTE_VALUE_OVERFILL;
    }
    
    std::string key_str = byteArray2hexString(key, KEY_SIZE);
    
    std::cout << "KEY: " << key_str << "\n";
    
    return 0;
}
