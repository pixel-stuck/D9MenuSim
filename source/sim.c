#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include <3ds.h>

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
	printf("currently displaying menu%04i.bin\n", l[m]);
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
			printf("currently displaying menu%04i.bin\n", l[m]);
		}else if(hidKeysDown() & KEY_UP){
			if (l[m - 1] < (l[m] - 1)){
			printf("nope\n");
			}else{
				--m;
				if(m <= 0){
					m = 0;
				}	
			}
			printf("currently displaying menu%04i.bin\n", l[m]);
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
				printf("%02i %04i %i\n", m, l[m], i);
			}
			printf("menu decremented\ncurrently displaying menu%04i.bin\n", l[m]);
		}else if(hidKeysDown() & KEY_R){
			i = ((l[m] / 100 + 1) * 100);
			if((i > 1200)){
				i = 0;
			}
			while(i != l[m]){
				m++;
				printf("%02i %04i %i\n", m, l[m], i);
				if((m > 87)){
					m = 0;
				}
			}
			printf("menu incremented\ncurrently displaying menu%04i.bin\n", l[m]);		
		}else if(hidKeysDown() & KEY_LEFT){
			m++;
			printf("menu incremented\n");
		}
	}
	return 0;
}