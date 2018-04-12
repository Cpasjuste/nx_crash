#include <string.h>
#include <stdio.h>

#include <switch.h>

void audio_initialize(void);
extern void audio_exit(void);

void read_file() {

	printf("read start\n");

	unsigned char buffer[1024 * 512];
	FILE *fd = fopen("/data.bin","rb");
	
	while(fread(buffer, 1024 * 512, 1, fd)) {
		printf("read\n");
	}

	fclose(fd);

	printf("read end\n");
}

int main(int argc, char **argv)
{
	int done = 0;
    gfxInitDefault();
    consoleInit(NULL);

	audio_initialize();

    while(!done)
    {
	appletMainLoop();
        hidScanInput();
        u32 kDown = hidKeysHeld(CONTROLLER_P1_AUTO);
        if (kDown & KEY_PLUS) done = 1; 

	if(!done) read_file();

        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
    }

	audio_exit();
    gfxExit();
    return 0;
}

