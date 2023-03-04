#include<stdio.h>
#include<time.h>
void ShowWord(unsigned int w){
	for(int i=1;i<=8;i++){
		unsigned int hexan= (w>>32-i*4) & 0xF;
		printf("%X", hexan);
	}
	
}

unsigned int RotWord(unsigned int w){
//Dich vòng trái 1 byte
	unsigned int byte1 = (w>>24) & 0xFF;
	unsigned int byte234 = w & 0xFFFFFF;
	unsigned int rot =(byte234 << 8) | byte1;
//	printf("\n\tRotWord(%X)=",w); ShowWord(rot);
	return rot;

}

unsigned int SubWord(unsigned int w){
	int S[]={
	0x63,  0x7c,  0x77,  0x7b,  0xf2,  0x6b,  0x6f,  0xc5,  0x30,  0x01,  0x67,  0x2b,  0xfe,  0xd7,  0xab,  0x76,
    0xca,  0x82,  0xc9,  0x7d,  0xfa,  0x59,  0x47,  0xf0,  0xad,  0xd4,  0xa2,  0xaf,  0x9c,  0xa4,  0x72,  0xc0,
    0xb7,  0xfd,  0x93,  0x26,  0x36,  0x3f,  0xf7,  0xcc,  0x34,  0xa5,  0xe5,  0xf1,  0x71,  0xd8,  0x31,  0x15,
    0x04,  0xc7,  0x23,  0xc3,  0x18,  0x96,  0x05,  0x9a,  0x07,  0x12,  0x80,  0xe2,  0xeb,  0x27,  0xb2,  0x75,
    0x09,  0x83,  0x2c,  0x1a,  0x1b,  0x6e,  0x5a,  0xa0,  0x52,  0x3b,  0xd6,  0xb3,  0x29,  0xe3,  0x2f,  0x84,
    0x53,  0xd1,  0x00,  0xed,  0x20,  0xfc,  0xb1,  0x5b,  0x6a,  0xcb,  0xbe,  0x39,  0x4a,  0x4c,  0x58,  0xcf,
    0xd0,  0xef,  0xaa,  0xfb,  0x43,  0x4d,  0x33,  0x85,  0x45,  0xf9,  0x02,  0x7f,  0x50,  0x3c,  0x9f,  0xa8,
    0x51,  0xa3,  0x40,  0x8f,  0x92,  0x9d,  0x38,  0xf5,  0xbc,  0xb6,  0xda,  0x21,  0x10,  0xff,  0xf3,  0xd2,
    0xcd,  0x0c,  0x13,  0xec,  0x5f,  0x97,  0x44,  0x17,  0xc4,  0xa7,  0x7e,  0x3d,  0x64,  0x5d,  0x19,  0x73,
    0x60,  0x81,  0x4f,  0xdc,  0x22,  0x2a,  0x90,  0x88,  0x46,  0xee,  0xb8,  0x14,  0xde,  0x5e,  0x0b,  0xdb,
    0xe0,  0x32,  0x3a,  0x0a,  0x49,  0x06,  0x24,  0x5c,  0xc2,  0xd3,  0xac,  0x62,  0x91,  0x95,  0xe4,  0x79,
    0xe7,  0xc8,  0x37,  0x6d,  0x8d,  0xd5,  0x4e,  0xa9,  0x6c,  0x56,  0xf4,  0xea,  0x65,  0x7a,  0xae,  0x08,
    0xba,  0x78,  0x25,  0x2e,  0x1c,  0xa6,  0xb4,  0xc6,  0xe8,  0xdd,  0x74,  0x1f,  0x4b,  0xbd,  0x8b,  0x8a,
    0x70,  0x3e,  0xb5,  0x66,  0x48,  0x03,  0xf6,  0x0e,  0x61,  0x35,  0x57,  0xb9,  0x86,  0xc1,  0x1d,  0x9e,
    0xe1,  0xf8,  0x98,  0x11,  0x69,  0xd9,  0x8e,  0x94,  0x9b,  0x1e,  0x87,  0xe9,  0xce,  0x55,  0x28,  0xdf,
    0x8c,  0xa1,  0x89,  0x0d,  0xbf,  0xe6,  0x42,  0x68,  0x41,  0x99,  0x2d,  0x0f,  0xb0,  0x54,  0xbb,  0x16
	};
			unsigned int kq=0;
			for (int i=1;i<=4;i++){
				unsigned int bytei = ( w >> (32 - i*8)) & 0xff;
				unsigned int subB = S[bytei];
				kq = (kq << 8) | subB;
				
			}
			//printf("\n\tSubWord(%X)=",w); ShowWord(kq);
			return kq;
			
}

unsigned int XorRcon(unsigned int w, int j){
	int Rc[]={
	0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
	0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39,
	
	};
	unsigned int byte1 = ( w >> 24 )& 0xff;
	unsigned int kqXor =(byte1 ^ Rc[j]) & 0xff;
	unsigned int byte234= w & 0xffffff;
	unsigned int kq=(kqXor<<24)|byte234;
	return kq;
	
}
unsigned int G(unsigned int w, int j){
	
	unsigned int rotW =RotWord(w);
	unsigned int subW =SubWord(rotW);
	unsigned int kq=XorRcon(subW,j);
//	printf("\n\tG(%X)= ",w); ShowWord(kq);
	return kq;
	
}
unsigned int* KeyExpansion(unsigned int Key[4]){
	unsigned int *w= new unsigned int[44];
	w[0]=Key[0];
	w[1]=Key[1];
	w[2]=Key[2];
	w[3]=Key[3];
	for(int i=4;i<44;i++){
		if(i%4==0) w[i]=G(w[i-1],i/4)^w[i-4];
		else w[i]=w[i-1]^w[i-4];
//	printf("\nw[%d]=",i); ShowWord(w[i]);
		
	}
	return w;
}
unsigned int* AddRoundKey(unsigned int state[4], unsigned int *K){
	unsigned int *kq= new unsigned int[4];

    kq[0]=state[0]^K[0];

	kq[1]=state[1]^K[1];
	kq[2]=state[2]^K[2];
	kq[3]=state[3]^K[3];
//	printf("\nAddroundKey\n");
//	for(int i=0;i<4;i++){
//		
//		printf("\n\t"); ShowWord(kq[i]);
//		
//	}
	return kq;
}
unsigned int* SubBytes(unsigned int state[4]){
	unsigned int *kq= new unsigned int[4];
	for(int i=0;i<4;i++)
		kq[i]=SubWord(state[i]);	
//	printf("\nSubByte\n");
//	for(int i=0;i<4;i++){
//		printf("\n\t"); ShowWord(kq[i]);	
//	}
	return kq;
}
unsigned int* ShiftRows(unsigned int state[4]){
	unsigned int *kq= new unsigned int[4];
	for(int i=0;i<4;i++){
		unsigned int byte1=state[i]&0xFF000000;
		unsigned int byte2=state[(i+1)%4]&0xFF0000;
		unsigned int byte3=state[(i+2)%4]&0xFF00;
		unsigned int byte4=state[(i+3)%4]&0xFF;
		kq[i]=byte1 | byte2 | byte3 | byte4;
	}
//	printf("\nShiftRows:\n");
	for(int i=0;i<4;i++){
//		printf("\n\t"); ShowWord(kq[i]);
	}
	return kq;
	
}

unsigned int Nhan2(unsigned int w){
	unsigned int kq=w<<1;
	if(kq>256)kq=kq^0x11b;
	kq=kq&0xFF;
	return kq;
}
unsigned int Nhan3(unsigned int w){
	unsigned int kq=w^Nhan2(w);
	kq=kq&0xFF;
	return kq;
}
unsigned int NhanCot(unsigned int w){
	unsigned int kq;
	unsigned int byte1=(w>>24) & 0xFF;
	unsigned int byte2=(w>>16) & 0xFF;
	unsigned int byte3=(w>>8) & 0xFF;
	unsigned int byte4=(w) & 0xFF;
	unsigned int kq1= Nhan2(byte1) ^ Nhan3(byte2) ^ byte3 ^ byte4;
	unsigned int kq2= byte1 ^ Nhan2(byte2) ^ Nhan3(byte3) ^ byte4;
	unsigned int kq3= byte1 ^ byte2 ^ Nhan2(byte3) ^ Nhan3(byte4);
	unsigned int kq4= Nhan3(byte1) ^ byte2 ^ byte3 ^ Nhan2(byte4);
	kq=(kq1<<24) | (kq2<<16) | (kq3<<8) | kq4;
//	printf("\n\t"); ShowWord(kq);
	return kq;
}
unsigned int* MixColumns(unsigned int state[4]){
	unsigned int *kq= new unsigned int[4];
//	printf("\nMixColumns:\n");
	for (int i=0; i<4; i++)
		kq[i]=NhanCot(state[i]);
		return kq;
	
} 
void ShowMatrix(unsigned int w[4]){
	
	for(int i=0; i<4; i++){
		printf("\n\t"); ShowWord(w[i]);
	
	}
}

unsigned int* MahoaAES(unsigned int state[4],unsigned int key[4]){
	unsigned int *w= KeyExpansion(key);
	unsigned int *output;
	state = AddRoundKey(state,&w[0]);
	for (int j=1; j<=9; j++){
	
		state=SubBytes(state);
		state=ShiftRows(state);
		state=MixColumns(state);
		state=AddRoundKey(state,&w[4*j]);
		//printf("\nVong %d: \n",j); ShowMatrix(state); 
	}
	//Vongthu10
		state=SubBytes(state);
		state=ShiftRows(state);
		state=AddRoundKey(state,&w[40]);
		//printf("\nVong 10: \n"); ShowMatrix(state); 
		unsigned int *kq= new unsigned int[4];
		kq=state;
		return kq;//kq la output
} 
unsigned int* InvShiftRows(unsigned int state[4]){
	unsigned int *kq = new unsigned int[4];
	for (int i=0;i<4;i++){
		unsigned int byte1=state[i]&0xFF000000;
		unsigned int byte2=state[(i+3)%4]&0xFF0000;
		unsigned int byte3=state[(i+2)%4]&0xFF00;
		unsigned int byte4=state[(i+1)%4]&0xFF;
		kq[i]=byte1|byte2|byte3|byte4;
		
		
	}
//	printf("\nInvShiftRows:\n");
//		for (int i=0;i<16;i++){
//	//		printf("\n\t"); ShowWord(kq[i]);
//		} 
		return kq;
}

unsigned int InvSubWord(unsigned int w){
	int InvS[]={
	0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb, 
	0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb, 
	0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e, 
	0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25, 
	0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92, 
	0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84, 
	0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06, 
	0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b, 
	0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73, 
	0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e, 
	0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b, 
	0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4, 
	0x1f, 0xdd,	0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
	0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
	0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
	0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
	};
	unsigned int kq=0;
	for(int i=1;i<=4;i++){
		unsigned int bytei=(w>>(32-i*8))&0xFF;
		unsigned int subB=InvS[bytei];
		kq=(kq<<8)|subB;
	}
	return kq;
}
unsigned int* InvSubBytes(unsigned int state[4]){
	unsigned int *kq=new unsigned int[4];
	for(int i=0;i<4;i++)
		kq[i]=InvSubWord(state[i]);
	
	return kq;
}
unsigned int Nhan9(unsigned int w){
	unsigned int kq=(w<<3)^w;
	if(kq>(256<<2))kq=kq^(0x11b<<2);
	if(kq>(256<<1))kq=kq^(0x11b<<1);
	if(kq>256)kq=kq^0x11b;
	kq=kq&0xFF;
	return kq;
}
unsigned int NhanB(unsigned int w){
	unsigned int kq=(w<<3)^(w<<1)^w;
	if(kq>(256<<2))kq=kq^(0x11b<<2);
	if(kq>(256<<1))kq=kq^(0x11b<<1);
	if(kq>256)kq=kq^0x11b;
	kq=kq&0xFF;
	return kq;
}
unsigned int NhanD(unsigned int w){
	unsigned int kq=(w<<3)^(w<<2)^w;
	if(kq>=(256<<2))kq=kq^(0x11b<<2);
	if(kq>=(256<<1))kq=kq^(0x11b<<1);
	if(kq>=256)kq=kq^0x11b;
	kq=kq&0xFF;
	return kq;
}
unsigned int NhanE(unsigned int w){
	unsigned int kq=(w<<3)^(w<<2)^(w<<1);
	if(kq>=(256<<2))kq=kq^(0x11b<<2);
	if(kq>=(256<<1))kq=kq^(0x11b<<1);
	if(kq>=256)kq=kq^0x11b;
	kq=kq&0xFF;
	return kq;
}
unsigned int InvNhanCot(unsigned int w){
	unsigned int kq;
	unsigned int byte1=(w>>24) & 0xFF;
	unsigned int byte2=(w>>16) & 0xFF;
	unsigned int byte3=(w>>8) & 0xFF;
	unsigned int byte4=(w) & 0xFF;
	unsigned int kq1= NhanE(byte1) ^ NhanB(byte2) ^ NhanD(byte3) ^ Nhan9(byte4);
	unsigned int kq2= Nhan9(byte1) ^ NhanE(byte2) ^ NhanB(byte3) ^ NhanD(byte4);
	unsigned int kq3= NhanD(byte1) ^ Nhan9(byte2) ^ NhanE(byte3) ^ NhanB(byte4);
	unsigned int kq4= NhanB(byte1) ^ NhanD(byte2) ^ Nhan9(byte3) ^ NhanE(byte4);
	kq=(kq1<<24) | (kq2<<16) | (kq3<<8) | kq4;
//	printf("\n\t"); ShowWord(kq);
	return kq;
}
unsigned int* InvMixColumns(unsigned int state[4]){
	unsigned int *kq= new unsigned int[4];
//	printf("\nMixColumns:\n");
	for (int i=0; i<4; i++)
		kq[i]=InvNhanCot(state[i]);
		return kq;
	
} 
unsigned int* GiaiMaAES(unsigned int C[4], unsigned int key[4]){
	unsigned int *w=KeyExpansion(key);
	unsigned int *state=AddRoundKey(C,&w[40]); 
	for(int j=1;j<=9;j++){
	state=InvShiftRows(state); 
	state=InvSubBytes(state); 
	state=AddRoundKey(state,&w[40-4*j]); 
	state=InvMixColumns(state); 
	}
	//vong thu 10
	state=InvShiftRows(state); 
	state=InvSubBytes(state); 
	state=AddRoundKey(state,&w[0]); 
	return state;
	
}
 //Hàm d?c khóa t? file
void readKey(char *filename, unsigned int *w) {
FILE *fp;
int i;
fp = fopen(filename, "r");
for (i = 0; i < 4; i++) {
    fscanf(fp, "%x", &w[i]);
}
fclose(fp);
}

// Hàm d?c d? li?u t? file
void readData(char *filename, unsigned int *data) {
FILE *fp;
int i;
fp = fopen(filename, "r");
for (i = 0; i < 4; i++) {
    fscanf(fp, "%x", &data[i]);
}
fclose(fp);
}

// Hàm ghi d? li?u vào file
void writeData(char *filename, unsigned int *data) {
FILE *fp;
int i;
fp = fopen(filename, "w");
for (i = 0; i < 4; i++) {
    fprintf(fp, "%00x", data[i]);
}
fclose(fp);
}

int main(){
//	unsigned int w0,w1,w2,w3;
//	unsigned int Key[]={w0, w1, w2, w3};
//	unsigned int input[16], output[16];
	

	//int Key=0x2b7e151628aed2a6abf7158809cf4f3c;
	//unsigned int w0 = 0x2b7e1516, w1 = 0x28aed2a6, w2= 0xabf71588, w3=0x09cf4f3c;
	unsigned int *Key= new unsigned[4];
	//input M=3243f6a8885a308d313198a2e0370734

//	state[0] = 0x3243f6a8; state[1] = 0x885a308d; state[2] = 0x313198a2; state[3] = 0xe0370734;
	//Bat dau test
//	unsigned int rot= RotWord(w3);	
//	unsigned int sub=SubWord(rot);
//	unsigned int g3=G(w3,1);
//	unsigned int *w= KeyExpansion(Key);
// Ð?c khóa t? file
//readKey("key.txt", w0);
//readKey("key.txt", w1);
//readKey("key.txt", w2);
readKey("key.txt", Key);

// Ð?c d? li?u vào input
unsigned int *state	= new unsigned[4];
readData("input.txt", state);
unsigned int *kq;
// Mã hóa d? li?u và ghi vào output
clock_t start = clock();
unsigned int *C=MahoaAES(state,Key);
writeData("output.txt", C);
printf("\nBan ma: \n"); ShowMatrix(C);
clock_t end = clock();
double time_taken = ((double)(end - start))/CLOCKS_PER_SEC;
printf("\nThoi gian ma hoa: %f seconds\n", time_taken);

//// Ð?c d? li?u dã du?c mã hóa t? file
//readData("output.txt", input);
//unsigned int *C=MahoaAES(state,Key,input,output);
// Gi?i mã d? li?u và ghi vào output
clock_t start1 = clock();
unsigned int *M= GiaiMaAES(C,Key);
writeData("decrypted.txt", M);
printf("\nGiai ma: \n"); ShowMatrix(M);
clock_t end1 = clock();
double time_taken1 = ((double)(end1 - start1))/CLOCKS_PER_SEC;
printf("\nThoi gian giai ma: %f seconds\n", time_taken1);
}


