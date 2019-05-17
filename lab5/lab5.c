#include <stdio.h>

typedef struct{
	float x[4];
}vector;

float M[4][4]={
	{6.0,3.5,1.0,-8.0},
	{3.0,2.0,2.0,6.0},
	{5.0,-2.0,0.0,4.0},
	{7.0,1.0,4.0,1.0}
	};

void show(){
	int i,j;
	for(i=0;i<4;i++){
	  for(j=0;j<4;j++){
	    printf("%.1f|",M[i][j]);
	  }
	  printf("\n");
	}
}

float detM(vector v0, vector v1, vector v2, vector v3){

	vector res;

	asm(
	// A'B'
	//  a1 a0 a2 a0
	//x b2 b3 b0 b1
	"movups %1, %%xmm0 \n"// a
	"movups %2, %%xmm1 \n"// b
	"shufps $0x48, %%xmm0, %%xmm0 \n" // 01 00 10 00
	"shufps $0xb1, %%xmm1, %%xmm1 \n" // 10 11 00 01
	"mulps %%xmm1, %%xmm0 \n"
	// xmm0 -> 1)

	// A''B''
	//  a2 a3 a0 a1
	//x b1 b0 b2 b0

	"movups %1, %%xmm1 \n"// a
	"movups %2, %%xmm2 \n"// b
	"shufps $0xb1, %%xmm1, %%xmm1 \n" // 10 11 00 01
	"shufps $0x48, %%xmm2, %%xmm2 \n" // 01 00 10 00
	"mulps %%xmm2, %%xmm1 \n"
	// xmm1 -> 2)

	"subps %%xmm1, %%xmm0 \n"
// xmm0 =  A'B' - A''B''

	// C'D'
	//  c0 c1 c1 c2
	//x d3 d2 d3 d3

	"movups %3, %%xmm1 \n"//c
	"movups %4, %%xmm2 \n"//d
	"shufps $0x16, %%xmm1, %%xmm1  \n" // 00 01 01 10
	"shufps $0xEF, %%xmm2, %%xmm2 \n" // 11 10 11 11
	"mulps %%xmm2, %%xmm1 \n"
	// xmm1 -> 3)

	// C''D''
	//  c3 c2 c3 c3
	//x d0 d1 d1 d2

	"movups %3, %%xmm2 \n"//c
	"movups %4, %%xmm3 \n"//d
	"shufps $0xEF, %%xmm2, %%xmm2 \n"// 11 10 11 11
	"shufps $0x16, %%xmm3, %%xmm3 \n"// 00 01 01 10
	"mulps %%xmm3, %%xmm2 \n"
	// xmm2 -> 4)

	"subps %%xmm2, %%xmm1 \n"
// xmm1 = C'D' - C''D''
	"mulps %%xmm1, %%xmm0 \n"
// xmm0 = (A'B' - A''B'')*(C'D' - C''D'')


// uzyskanie zer
// (a3*b3-a3*b3)*(c3d3-c3d3) + (a3*b3-a3*b3)*(c3d3-c3d3) = 0

	// A'B'
	//  a3 a3 a3 a2
	//x b3 b3 b1 b3

	"movups %1, %%xmm1 \n"//a
	"movups %2, %%xmm2 \n"//b
	"shufps $0xFE, %%xmm1, %%xmm1 \n" // 11 11 11 10
	"shufps $0xF7, %%xmm2, %%xmm2 \n" // 11 11 01 11
	"mulps %%xmm2, %%xmm1 \n"
	// xmm1 -> 5)

	// A''B''
	//  a3 a3 a1 a3
	//x b3 b3 b3 b2

	"movups %1, %%xmm2 \n"//a
	"movups %2, %%xmm3 \n"//b
	"shufps $0xF7, %%xmm2, %%xmm2 \n" // 11 11 01 11
	"shufps $0xFE, %%xmm3, %%xmm3 \n" // 11 11 11 10
	"mulps %%xmm3, %%xmm2 \n"
	// xmm2 -> 6)

	"subps %%xmm2, %%xmm1 \n"
// xmm1 = A'B' - A''B''

	// C'D'
	//  c3 c3 c0 c0
	//x d3 d3 d2 d1

	"movups %3, %%xmm2 \n"//c
	"movups %4, %%xmm3 \n"//d
	"shufps $0xF0, %%xmm2, %%xmm2 \n" // 11 11 00 00
	"shufps $0xF9, %%xmm3, %%xmm3 \n" // 11 11 10 01
	"mulps %%xmm3, %%xmm2 \n"
	// xmm2 -> 7)

	// C''D''
	//  c3 c3 c2 c1
	//x d3 d3 d0 d0

	"movups %3, %%xmm3 \n"//c
	"movups %4, %%xmm4 \n"//d
	"shufps $0xF9, %%xmm3, %%xmm3 \n"// 11 11 10 01
	"shufps $0xF0, %%xmm4, %%xmm4 \n"// 11 11 00 00
	"mulps %%xmm4, %%xmm3 \n"
	// xmm3 -> 8)

	"subps %%xmm3, %%xmm2 \n"
// xmm2 = C'D' - C''D''
	"mulps %%xmm2, %%xmm1 \n"
// xmm1 = (A'B' - A''B'')*(C'D'-C''D'')
	"addps %%xmm1,%%xmm0 \n"
// xmm0 = xmm0 + xmm1
	"movups %%xmm0, %0 \n"
// res = xmm0
	:"=m"(res)
	:"m"(v0),"m"(v1),"m"(v2),"m"(v3)
	);

	float det = 0.0;

	for(int i=0;i<4;i++){
		det += res.x[i];
	}



	return det;
}

int main(){

	show();

	vector v[4];

	int i,j;
	for(i=0;i<4;i++){
		for(j=0;j<4;j++){
			v[i].x[j] = M[i][j];
		}
	}

	printf("%.2f\n",detM(v[0],v[1],v[2],v[3]));

	return 0;
}
