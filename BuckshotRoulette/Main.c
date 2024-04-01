#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include"bulletsHandler.h"

int main(void) {
	//Test to see if loadRandom works
	BulletLink handle = NULL;
	loadRandomBullets(&handle, 10);
	printBulletsInOrder(handle);

	printf("%d\n", bulletCount(handle));
	printf("%d\n", liveBullets(handle));

	printf("%d\n", blankBullets(handle));

	return 0;
}
