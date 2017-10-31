#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>

typedef int bool;
#define true 1
#define false 0

void sensorTmp007Convert(uint16_t rawAmbTemp, uint16_t rawObjTemp, float * tAmb, float *tObj);
bool str_to_uint(char *input, uint16_t *output);


void main(int args,char * argv[]){

    //uint16_t r = 0x0854;
    uint16_t global = 0x0854;
    uint16_t local = 0x0ff4;
    float a, b;

    sensorTmp007Convert(global, local, &a, &b);
	printf("global = %f, local= %f\n", a, b);

    char* str = "0x058f";

    int i;
    unsigned u;
    if (sscanf(str, "%x", &u) != 1)
        printf("fail\n");
    i = (int) u;

    uint16_t u16;
    str_to_uint(str, &u16);

    printf("i: 0x%04x  i16: 0x%04" PRIx16 "\n", i, u16);

}

bool str_to_uint(char *input, uint16_t * output){

    if (sscanf(input, "%" SCNx16, output) != 1)
        return false;

    return true;
}

void sensorTmp007Convert(uint16_t rawAmbTemp, uint16_t rawObjTemp, float * tAmb, float *tObj)
{
	const float SCALE_LSB = 0.03125;
	float t;
	int it;
	it = (int)((rawObjTemp) >> 2);
	t = ((float)(it)) * SCALE_LSB;
	*tObj = t;
	it = (int)((rawAmbTemp) >> 2);
	t = (float)it;
	*tAmb = t * SCALE_LSB;
}

