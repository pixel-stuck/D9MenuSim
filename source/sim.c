#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <3ds.h>

u8* buffer;
char n[19];

void displayimage()
{
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

int main()
{
	gfxInitDefault();
	consoleInit(GFX_TOP, NULL);
	int  i, j, k = 0, l[88], m = 0, menu[13] = {4, 3, 8, 9, 6, 6, 6, 6, 6, 8, 9, 8, 9};
	for (j = 0; j < 13; j++){
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
	snprintf(n, sizeof(n), "/D9UI/menu%04i.bin", l[m]);
	printf("%s\n", n);
	displayimage();
	while(l[m] >= 0 && l[m] <= 1208 ){
		hidScanInput();
		if(hidKeysDown() & KEY_START) break;
		if(hidKeysDown() & KEY_DOWN){
			if (!(l[m + 1] > (l[m] + 1))){
				++m;
				if(m >= 87){
					m = 87;
				}
			}
			snprintf(n, sizeof(n), "/D9UI/menu%04i.bin", l[m]);
			printf("%s\n", n);
			displayimage();
		}else if(hidKeysDown() & KEY_UP){
			if (!(l[m - 1] < (l[m] - 1))){
				--m;
				if(m <= 0){
					m = 0;
				}	
			}
			snprintf(n, sizeof(n), "/D9UI/menu%04i.bin", l[m]);
			printf("%s\n", n);
			displayimage();
		}else if(hidKeysDown() & KEY_L){
			i = ((l[m] / 100 - 1) * 100);
			if((i < 0)){
				i = 1200;
			}
			while(i != l[m]){
				--m;
				if((m < 0)){
					m = 87;
				}
			}
			snprintf(n, sizeof(n), "/D9UI/menu%04i.bin", l[m]);
			printf("%s\n", n);
			displayimage();
		}else if(hidKeysDown() & KEY_R){
			i = ((l[m] / 100 + 1) * 100);
			if((i > 1200)){
				i = 0;
			}
			while(i != l[m]){
				m++;
				if((m > 87)){
					m = 0;
				}
			}
			snprintf(n, sizeof(n), "/D9UI/menu%04i.bin", l[m]);
			printf("%s\n", n);
			displayimage();		
		}
	}
	return 0;
}