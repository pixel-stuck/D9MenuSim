#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <3ds.h>

#include "e9menu.h"

u8* buffer;
int  i, j, k = 0, m = 0;
char n[sizeof(path) + 15];

void displayimage()
{
	snprintf(n, sizeof(n), "/%s/menu%04i.bin", path, l[m]);
	FILE *file = fopen(n,"rb");
	if (file == NULL) return 0;
	fseek(file,0,SEEK_END);
	off_t size = ftell(file);
	fseek(file,0,SEEK_SET);
	buffer=malloc(size);
	if(!buffer) return 0;
	off_t bytesRead = fread(buffer,1,size,file);
	fclose(file);
	if(size!=bytesRead) return 0;
	memcpy(gfxGetFramebuffer(GFX_BOTTOM, GFX_BOTTOM, NULL, NULL), buffer, size);
	gfxSwapBuffersGpu();
	gspWaitForEvent(GSPGPU_EVENT_VBlank0, false);
}

int main(int argc, char** argv)
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);
	for (j = 0; j < num_menus; j++){
		while (k < menu[j]){
		l[m] = (j*100 + k);
		++k;
		++m;
		}
		if ((k = menu[j])){
			k = 0;
		}
	}
	m = 0;
	displayimage();
	while(aptMainLoop()){
		hidScanInput();
		if(hidKeysDown() & KEY_START) break;
		if(hidKeysDown() & KEY_DOWN){
			if (!(l[m + 1] > (l[m] + 1)) & !(m == (max_entries - 1))){
				++m;
				if(m >= (max_entries - 1)){
					m = (max_entries - 1);
				}
			}else{
				i = ((l[m] / 100) * 100);
				while(i != l[m]){
					--m;
				}
			}
			displayimage();
		}else if(hidKeysDown() & KEY_UP){
			if (!(l[m - 1] < (l[m] - 1)) & !(m == 0)){
				--m;
				if(m <= 0){
					m = 0;
				}	
			}else{
				i = (l[m] / 100);
				i = ((menu[i] - 1) + i * 100);
				while(i != l[m]){
					++m;
					if(m > (max_entries - 1)){
						m = 0;
					}
				}
			}
			displayimage();
		}else if(hidKeysDown() & KEY_L){
			i = ((l[m] / 100 - 1) * 100);
			if((i < 0)){
				i = ((menu[num_menus - 1] - 1) + ((l[max_entries - 1] / 100) * 100));
			}
			printf("%i\n", i);
			while(i != l[m]){
				--m;
				if((m < 0)){
					m = (max_entries - 1);
				}
			}
			displayimage();
		}else if(hidKeysDown() & KEY_R){
			i = ((l[m] / 100 + 1) * 100);
			if((i > (l[max_entries - 1] / 100) * 100)){
				i = 0;
			}
			while(i != l[m]){
				m++;
				if((m > (max_entries - 1))){
					m = 0;
				}
			}
			displayimage();		
		}
	}
	return 0;
}