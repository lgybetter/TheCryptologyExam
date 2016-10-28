#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "rijndael-api-fst.h"

#define SUBMITTER "Joan Daemen"

static void blockPrint(FILE *fp, const BYTE *block, int e) {
	int i;
	for (i = 0; i < e; i++) {
		fprintf (fp, "%c",block[i]);
	}
	fflush (fp);
} /* blockPrint */

int makeFIPS(char *inputFile,char *outputFile,int kL,int type) {
	int i, keyLength, r;
	keyInstance keyInst;
	cipherInstance cipherInst;
	BYTE keyMaterial[320];
	u8 pt[16], ct[16],fpt[100000];
	FILE *fp;
	FILE *fp2;
	fp = fopen(inputFile, "wb");
	fp2 = fopen(outputFile,"rb");
	keyLength = kL;
	int o = 0, e = 0, k = 0;
	int flag = 0;
	while(1) {
		memset(keyMaterial, 0, sizeof (keyMaterial));
		for (i = 0; i < keyLength/8; i++) {
			sprintf(&keyMaterial[2*i], "%02X", i);
		}
		if(type == 1) {
			/* encryption: */
			if(flag != 1)
			{
				for(i = 0; i < 16; i ++) {
					if(feof(fp2)) {
						o = i - 2;
						k = 16 - o;
						flag = 1;
						break;
					}
					fread(pt + i,sizeof(u8),1,fp2);		
				}
				if(o != 0) {
					for(i = o; i < 16; i ++) {
						pt[i] = '!';
					}
					pt[15] = 'a' + k;
				}
			}
			if(feof(fp2) && o == 0) {
				break;
			}
			makeKey(&keyInst, DIR_ENCRYPT, keyLength, keyMaterial);
			cipherInit(&cipherInst, MODE_ECB, NULL);
			// blockPrint(fp, pt, 16);
			for (i = 1; i < keyInst.Nr; i++) {
				cipherUpdateRounds(&cipherInst, &keyInst, pt, 16, ct, i);
			}
			cipherUpdateRounds(&cipherInst, &keyInst, pt, 16, ct, keyInst.Nr);
			blockPrint(fp, ct, 16);
		} else {
			/* decryption: */
			for(i = 0; i< 16; i ++) {
				fread(ct + i,sizeof(u8),1,fp2);
			}
			if(feof(fp2)) {
				break;
			}
			makeKey(&keyInst, DIR_DECRYPT, keyLength, keyMaterial);
			cipherInit(&cipherInst, MODE_ECB, NULL);
			for (i = 1; i < keyInst.Nr; i++) {
				cipherUpdateRounds(&cipherInst, &keyInst, ct, 16, pt, i);
			}
			cipherUpdateRounds(&cipherInst, &keyInst, ct, 16, pt, keyInst.Nr);
			for(i = 0; i < 16; i ++) {
				fpt[e] = pt[i];
				e ++;
			}
		}
		o = 0;
	}
	if(type != 1) {
		k = fpt[e -1] - 'a';
		e = e - k;
		for(i = 0;i < e; i++) {
			fprintf (fp, "%c",fpt[i]);
		}
	}
	fclose(fp);
	fclose(fp2);
	return k;
}
