#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct vector{
	float x[4];
};

void add_SISD(float x, float y){

	asm(
	"FLDS %1 \n"
	"FADDS %2  \n"
	"FSTPS %0 \n"
	:"=m"(x)
	:"m"(x),"m"(y)
	);

}

void sub_SISD(float x, float y){

	asm(
	"FLDS %1 \n"
	"FSUBS %2 \n"
	"FSTPS %0 \n"
	:"=m"(x)
	:"m"(x),"m"(y)
	);

}

void mul_SISD(float x, float y){

	asm(
	"FLDS %1 \n"
	"FMULS %2 \n"
	"FSTPS %0 \n"
	:"=m"(x)
	:"m"(x),"m"(y)
	);

}

void div_SISD(float x, float y){

	asm(
	"FLDS %1 \n"
	"FDIVS %2 \n"
	"FSTPS %0 \n"
	:"=m"(x)
	:"m"(x),"m"(y)
	);

}

void add_SIMD(struct vector vec_x, struct vector vec_y){

	asm(
		"movups %1, %%xmm0 \n"
		"movups %2, %%xmm1 \n"
		"addps %%xmm1, %%xmm0 \n"
		"movups %%xmm0, %0 \n"
		:"=g"(vec_x)
		:"g"(vec_x),"g"(vec_y)

	);

}

void sub_SIMD(struct vector vec_x, struct vector vec_y){

	asm(
		"movups %1, %%xmm0 \n"
		"movups %2, %%xmm1 \n"
		"subps %%xmm1, %%xmm0 \n"
		"movups %%xmm0, %0 \n"
		:"=g"(vec_x)
		:"g"(vec_x),"g"(vec_y) 
	);

}

void div_SIMD(struct vector vec_x, struct vector vec_y){

	asm(
		"movups %1, %%xmm0 \n"
		"movups %2, %%xmm1 \n"
		"divps %%xmm1, %%xmm0 \n"
		"movups %%xmm0, %0 \n"
		:"=g"(vec_x)
		:"g"(vec_x),"g"(vec_y)
	);

}

void mul_SIMD(struct vector vec_x, struct vector vec_y){

	asm(
		"movups %1, %%xmm0 \n"
		"movups %2, %%xmm1 \n"
		"mulps %%xmm1, %%xmm0 \n"
		"movups %%xmm0, %0 \n"
		:"=g"(vec_x)
		:"g"(vec_x),"g"(vec_y)
	);

}

float randFloat(){

	return (float)(rand()%100)/10;
}

struct vector randVector(){

	struct vector random;

	random.x[0] = randFloat();
	random.x[1] = randFloat();
	random.x[2] = randFloat();
	random.x[3] = randFloat();

	return random;
}

void show(struct vector vec){
	printf("Vector : %f %f %f %f\n", vec.x[0], vec.x[1], vec.x[2], vec.x[3]);
}

double time_add_SIMD(int n){

	double time = 0;
	int i;
	int j;
	for(i=0; i<10 ;i++){
		for(j=0;j<(n/4);j++){
			struct vector x = randVector();
			struct vector y = randVector();
			clock_t start = clock();
			add_SIMD(x,y);
			clock_t end = clock() - start;
			time += ((double)end)/CLOCKS_PER_SEC;
		}
	}

	return (time/10);
}
double time_sub_SIMD(int n){
	double time = 0;
	int i;
	int j;
	for(i=0; i<10 ;i++){
		for(j=0;j<(n/4);j++){
			struct vector x = randVector();
			struct vector y = randVector();
			clock_t start = clock();
			sub_SIMD(x,y);
			clock_t end = clock() - start;
			time += ((double)end)/CLOCKS_PER_SEC;
		}
	}

	return (time/10);
}
double time_mul_SIMD(int n){
	double time = 0;
	int i;
	int j;
	for(i=0; i<10 ;i++){
		for(j=0;j<(n/4);j++){
			struct vector x = randVector();
			struct vector y = randVector();
			clock_t start = clock();
			mul_SIMD(x,y);
			clock_t end = clock() - start;
			time += ((double)end)/CLOCKS_PER_SEC;
		}
	}

	return (time/10);
}
double time_div_SIMD(int n){
	double time = 0;
	int i;
	int j;
	for(i=0; i<10 ;i++){
		for(j=0;j<(n/4);j++){
			struct vector x = randVector();
			struct vector y = randVector();
			clock_t start = clock();
			div_SIMD(x,y);
			clock_t end = clock() - start;
			time += ((double)end)/CLOCKS_PER_SEC;
		}
	}

	return (time/10);
}
double time_add_SISD(int n){
	double time = 0;
	int i;
	int j;
	for(i=0; i<10 ;i++){
		for(j=0;j<n;j++){
			float x = randFloat();
			float y = randFloat();
			clock_t start = clock();
			add_SISD(x,y);
			clock_t end = clock() - start;
			time += ((double)end)/CLOCKS_PER_SEC;
		}
	}

	return (time/10);
}
double time_sub_SISD(int n){
	double time = 0;
	int i;
	int j;
	for(i=0; i<10 ;i++){
		for(j=0;j<n;j++){
			float x = randFloat();
			float y = randFloat();
			clock_t start = clock();
			sub_SISD(x,y);
			clock_t end = clock() - start;
			time += ((double)end)/CLOCKS_PER_SEC;
		}
	}

	return (time/10);
}
double time_mul_SISD(int n){
	double time = 0;
	int i;
	int j;
	for(i=0; i<10 ;i++){
		for(j=0;j<n;j++){
			float x = randFloat();
			float y = randFloat();
			clock_t start = clock();
			mul_SISD(x,y);
			clock_t end = clock() - start;
			time += ((double)end)/CLOCKS_PER_SEC;
		}
	}

	return (time/10);
}
double time_div_SISD(int n){
	double time = 0;
	int i;
	int j;
	for(i=0; i<10 ;i++){
		for(j=0;j<n;j++){
			float x = randFloat();
			float y = randFloat();
			clock_t start = clock();
			div_SISD(x,y);
			clock_t end = clock() - start;
			time += ((double)end)/CLOCKS_PER_SEC;
		}
	}

	return (time/10);
}

int main(){

	srand(time(0));

	int n = 2048;

	time_add_SIMD(n); // pierwszy wynik zawsze byl dziwnie duzy

	int i;

	// zapis na ekran
	
	for(i=0;i<3;i++){
		printf("\nTyp obliczen: SIMD\n");
		printf("Liczba liczb: %d\n", n);
		printf("Sredni czas [s]:\n");
		printf("+ %f\n",time_add_SIMD(n));
		printf("- %f\n",time_sub_SIMD(n));
		printf("* %f\n",time_mul_SIMD(n));
		printf("/ %f\n",time_div_SIMD(n));

		printf("\nTyp obliczen: SISD\n");
		printf("Liczba liczb: %d\n", n);
		printf("Sredni czas [s]:\n");
		printf("+ %f\n",time_add_SISD(n));
		printf("- %f\n",time_sub_SISD(n));
		printf("* %f\n",time_mul_SISD(n));
		printf("/ %f\n",time_div_SISD(n));

		n = n*2;
	}

	// zapis do pliku


	FILE *plik = fopen("lab4.txt","w");

	if(plik == NULL){
		fprintf(stderr, "Nie mozna utworzyc pliku\n");
		exit(1);
	}

	n = 2048;

	for(i = 0; i < 3; i++){
		fprintf(plik,"\nTyp obliczen: SIMD\n");
		fprintf(plik,"Liczba liczb: %d\n", n);
		fprintf(plik,"Sredni czas [s]:\n");
		fprintf(plik,"+ %f\n",time_add_SIMD(n));
		fprintf(plik,"- %f\n",time_sub_SIMD(n));
		fprintf(plik,"* %f\n",time_mul_SIMD(n));
		fprintf(plik,"/ %f\n",time_div_SIMD(n));	

		fprintf(plik,"\nTyp obliczen: SISD\n");
		fprintf(plik,"Liczba liczb: %d\n", n);
		fprintf(plik,"Sredni czas [s]:\n");
		fprintf(plik,"+ %f\n",time_add_SISD(n));
		fprintf(plik,"- %f\n",time_sub_SISD(n));
		fprintf(plik,"* %f\n",time_mul_SISD(n));
		fprintf(plik,"/ %f\n",time_div_SISD(n));
		n = n*2;
	}	


	fclose(plik);

	return 0;

}
