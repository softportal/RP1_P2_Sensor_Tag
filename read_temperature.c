#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>

typedef int bool;

#define PAIR 4
#define true 1
#define false 0

void sensorTmp007Convert(uint16_t rawAmbTemp, uint16_t rawObjTemp, float * tAmb, float *tObj);
bool str_to_uint(char *input, uint16_t *output);


    //str_to_uint("0x0854", &global);
    //str_to_uint("0x0ff4", &local);
void main(int args,char * argv[]){
    char global_str[PAIR*2];
    char local_str[PAIR*2];
    uint16_t global, local;
    float a, b;
    memset (global_str, '\0', PAIR*2);
    memset (local_str, '\0', PAIR*2);

    global_str[0] = '0';
    global_str[1] = 'x';
    global_str[2] = argv[2][0];
    global_str[3] = argv[2][1];
    global_str[4] = argv[1][0];
    global_str[5] = argv[1][1];

    local_str[0] = '0';
    local_str[1] = 'x';
    local_str[2] = argv[4][0];
    local_str[3] = argv[4][1];
    local_str[4] = argv[3][0];
    local_str[5] = argv[3][1];

    str_to_uint(global_str, &global);
    str_to_uint(local_str, &local);


    sensorTmp007Convert(global, local, &a, &b);
	printf("global = %f, local= %f\n", a, b);
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

