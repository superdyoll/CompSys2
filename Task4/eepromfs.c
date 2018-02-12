#include <eepromfs.h>

typedef struct file{
	int8_t name;
	int length
	int startBlock
} file;


void init_eepromfs(void){

}

void open_for_write(uint8_t filename){

}

void open_for_append(uint8_t filename){

}

void open_for_read(uint8_t filename){

}

void close(uint8_t filename){

}

void write(uint8_t filename, uint8_t *buff, uint16_t len){

}

void read(uint8_t filename,  uint8_t *buff, uint16_t len){

}

void delete(uint8_t filename){

}
