#include<bits/stdc++.h>
using namespace std;

string plain, key;
int plaintx[64], keys[64], rg_o[32];
bitset<8> bil ;
bitset<4> sb;
int lf[32], rg[32], c[32], d[32], pc2_out[48], exp_out[48], s_out[32], p[32];

//fungsi mengkonversi string ke deretan biner 64 bit
void toBinSubs(string tx, int cek){
	int a= tx.length();
	int pos=0;
	for(int i=0; i<a; i++){
		bil=tx[i];
		for(int j=0; j<8; j++){
			//jika 1 maka kita mengkonversi plaintext ke biner
			//jika tidak maka kita menkonversi key ke biner
			if(cek==1) plaintx[pos]= bil[abs(7-j)];
			else keys[pos]= bil[abs(7-j)];
			pos++;
		}
	}	
}
void toStrsubs(){
	int pos=0;
	bitset<8> ch;
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			ch[7-j]=plaintx[pos];
			pos++;
		}
	cout<<(char)ch.to_ulong();
	}
}
//fungsi subsitusi
void subs(int cek){
	int hslIP[64];
	int hslkey[56];
	int IPtablefinal[64]={	40,8,48,16,56,24,64,32,
							39,7,47,15,55,23,63,31,
							38,6,46,14,54,22,62,30,
							37,5,45,13,53,21,61,29,
							36,4,44,12,52,20,60,28,
							35,3,43,11,51,19,59,27,
							34,2,42,10,50,18,58,26,
							33,1,41,9,49,17,57,25};
						
	int IPtable[64]={	58,50,42,34,26,18,10,2,
							60,52,44,36,28,20,12,4,
							62,54,46,38,30,22,14,6,
							64,56,48,40,32,24,16,8,
							57,49,41,33,25,17,9,1,
							59,51,43,35,27,19,11,3,
							61,53,45,37,29,21,13,5,
							63,55,47,39,31,23,15,7};
								
	int PC1[56]={	57,49,41,33,25,17,9,
					1,58,50,42,34,26,18,
					10,2,59,51,43,35,27,
					19,11,3,60,52,44,36,
					63,55,47,39,31,23,15,
					7,62,54,46,38,30,22,
					14,6,61,53,45,37,29,
					21,13,5,28,20,12,4};
																
		/*1 menjalankan fungsi initial permutaion
		  2 menjalankan fungsi final permutation
		  3 menjalankan fungsi permutation choice 1 
		*/
	if((cek==1)|| (cek==2)){
		for(int i=0; i<64; i++){
			if(cek==1) { hslIP[i]= plaintx[IPtable[i]-1]; } 
			else if(cek==2) {hslIP[i]= plaintx[IPtablefinal[i]-1];}
		}
		copy(hslIP, hslIP+64, plaintx);
		//membagi menjadi left dan right
		for(int i=0; i<64; i++){
			if(i<32) lf[i]= plaintx[i];
			else rg[i-32]= plaintx[i];
		}
	}
	else if(cek==3) {
		for(int i=0; i<56; i++){
			hslkey[i]=keys[PC1[i]-1];}
			copy(hslkey, hslkey+56, keys);
		for(int i=0; i<56; i++){
			if(i<28) c[i]= keys[i];
			else d[i-28]= keys[i];
		}
	}
}

void expan(){
	int expPermutate[48]={	32,1,2,3,4,5,
							4,5,6,7,8,9,
							8,9,10,11,12,13,
							12,13,14,15,16,17,
							16,17,18,19,20,21,
							20,21,22,23,24,25,
							24,25,26,27,28,29,
							28,29,30,31,32,1};
	int hslexp[48];
	for(int i=0; i<48; i++){
		hslexp[i]=rg[expPermutate[i]-1];
	}
	copy(hslexp, hslexp+48, exp_out); 
}

void PC2(){
	int PC_2[48]={	14,17,11,24,1,5,
					3,28,15,6,21,10,
					23,19,12,4,26,8,
					16,7,27,20,13,2,
					41,52,31,37,47,55,
					30,40,51,45,33,48,
					44,49,39,56,34,53,
					46,42,50,36,29,32};
	for(int i=0; i<56; i++){
		if(i<28) keys[i]= c[i];
		else keys[i]=d[i-28];
	}
	int hslpc2[48];
	for(int i=0; i<48; i++){
		hslpc2[i]= keys[PC_2[i]-1];
	}
	copy(hslpc2, hslpc2+48, pc2_out);
}

void shlcircular(int jum){
	//karena setiap round berbeda jumlah shift nya
	int shiftround[16]={ 1,1,2,2,2,2,2,2,
						 1,2,2,2,2,2,2,1};
	rotate(c,c+shiftround[jum-1],c+28);
	rotate(d,d+shiftround[jum-1],d+28);
}
void sbox(int x[6], int num){
	int S[512]={14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
				0,15,75,4,14,2,13,1,10,6,12,11,9,5,3,8,
				4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
				15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13,
				15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
				3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
				0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
				13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9,
				10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
				13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
				13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
				1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12,
				7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
				13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
				10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
				3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14,
				2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
				14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
				4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
				11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3,
				12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
				10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
				9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
				4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13,
				4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
				13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,			
				1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
				6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12,
				13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
				1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
				7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
				2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11};
	int row, col, pos=num*4, poss;
	row= 2*x[0]+ 1*x[5];
	col= 8*x[1]+ 4*x[2]+ 2*x[3]+1*x[4];
	poss=num*64+(row)*16+col;
	sb=S[poss];
	for(int j=0; j<4; j++){
			s_out[pos]= sb[abs(3-j)];
			pos++;
		}
}

void permutate(){
	//permutation function				
	int permfc[32]= {	16,7,20,21,29,12,28,17,
						1,15,23,26,5,18,31,10,
						2,8,24,14,32,27,3,9,
						19,13,30,6,22,11,4,25};
	int hslp[32];
	for(int i=0; i<32; i++){
		hslp[i]= s_out[permfc[i]-1];
	}
	copy(hslp, hslp+32, p);
	for(int i=0; i<32; i++)
		rg_o[i]= lf[i]^p[i];
}

void round(){
	int s_b[6], jum=0;
	int round[48];
	PC2();
	expan();
	for(int i=0; i<48; i++){
		round[i]= exp_out[i]^pc2_out[i];
		s_b[i % 6]=round[i];
		if(i%6==5) { sbox(s_b, jum); jum++;}
	}
	int temp[32];
	copy(rg, rg+32, temp);
	copy(temp, temp+32, lf);
	permutate();
	copy(rg_o, rg_o+32, rg);
}

int main(){
	cout<<"Masukkan Plaintext: ";
	//hanya untuk 8 byte
	cin>>plain;
	toBinSubs(plain,1); 
	cout<<"Masukkan Key: ";
	cin>>key;
	toBinSubs(key,2);
	subs(1); //initial permutation
	subs(3); //PC 1

	for(int i=1; i<=16; i++){
		shlcircular(i); //left sirculair shift
		round(); //round ke i
	}
	int temp[32];
	copy(lf, lf+32, temp);
	copy(rg, rg+32, lf);
	copy(temp, temp+32, rg);

	for(int i=0; i<64; i++){
			if(i<32) plaintx[i]=lf[i];
			else plaintx[i]=rg[i-32];
		}
	subs(2);
	cout<<"\nChiper text :\n";
	for(int i=0; i<64; i++){
		cout<<plaintx[i];
	}
	cout<<"\nString text :\n";
	toStrsubs();
}
