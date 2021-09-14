#include <stdio.h>
#include <stdlib.h>
#include <Math.h>

#define EXIT_SUCESS 100
#define EXIT_FAILURE 101

int main(int argc, char* argv[]){
	 printf("hola mundo .........................");
    printf("primer cadena de argv %s",argv[1]);

    return 0;
}
/*
	CAada
*/
	void convertFractionInBaseDiez(int* srcBase,int* dstBase,char* fraction,int* outcome){
		int valor;
		if(*fraction!='\n'){
			valor=2;//valor que respresenta *fraction en ese punto
			if(*(fraction+1)!='\n'){
				*(outcome)=(*(outcome)+valor)/(*(srcBase));
			}
			else{
				convertFractionInBaseDiez(srcBase,dstBase,(fraction+1),outcome);
				*(outcome)=(*(outcome)+*(fraction))/(*(srcBase));
			}
		}
	}
	/*
		srcBase es un puntero de un entero
		dstBase es un puntero de un entero
		fraction es un puntero que apunta a un double
		outcomme es un puntero al primer elemento de un arreglo de car
	*/
	void convertFractionFromBaseDiez(int* srcBase,int* dstBase,double* fraction,char* outcome){
		double valor;
		if(*fraction!='\n'){
			int i=0;
			while(i<4){
				*(fraction)=modf((*(fraction))*(*(dstBase)),&valor);
				convertToBase(srcBase,dstBase,&valor,outcome);
				outcome++;
				i++;
			}

		}
	}
	void convertToBase(int* srcBase,int* dstBase,double* value,char* outcome){
		if(*(value)<=9)
			*(outcome)=*(value);
		else
			if(*(value)=='10')
				*(outcome)='A';
			else
				if(*(value)=='11')
					*(outcome)='B';
				else
					if(*(value)=='12')
						*(outcome)='C';
					else
						if(*(value)=='13')
							*(outcome)='D';
						else
							if(*(value)=='14')
								*(outcome)='E';
							else
								if(*(value)=='15')
									*(outcome)='F';
	}
/*

De Rodrigo Herlein para todos:  03:55 PM
https://www.youtube.com/watch?v=8Ib7nwc33uA&list=LL&index=1

*/
