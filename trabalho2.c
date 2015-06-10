#include <stdio.h>
#include <stdlib.h>

/***************************************************************************
*** ***
*** LABORAT´ORIO 1 ***
*** Grupo n.: ***
*** Nome completo dos alunos que comp~oe o grupo ***
*** ***
***************************************************************************/


double potencia(double x, int n);
double raiz_quadrada(double x);
double valor_absoluto(double x);
double juros(double vbem, int n, double prestacao);
double erro_relativo(double x, double y);
double func_juros(double j, double vbem, int n, double prestacao);



int main(){
	
  double vbem; /*Valor do bem, produto*/
  double prestacao;   /*Valor a se pagar em cada prestação*/
  double j; /*Taxa mensal de juros*/
  int n; /*Numero de prestações a se pagar*/
  
  	
	do{
		printf("Valor do bem: ");
		scanf("%lf", &vbem);
		if(vbem < 0)
			printf("FIM DO PROGRAMA\n\n");
		else{
			printf("Numero de prestacoes: ");
			scanf("%d", &n);
			printf("Valor da prestacao: ");
			scanf("%lf", &prestacao);
			
			j = juros(vbem, n, prestacao);
			
			printf("Juros = %.6f\n\n", j);
		}
	}while(vbem >= 0);
		
	system("PAUSE");
	return 0;
	
}
/*Para calcular a "x" elevado a "n", utilizamos um laço simples e crescente, note que quanto maior o valor de n, mais tempo a função irá consumir.*/
double potencia(double x, int n){
	
  int i;
  double res;
   
	res = x;
	
	for(i = 1; i < n; i++){
		res = res * x;	
	}
	
	return res;
}
/*Foi utilizada a mesma tecnica do exercício programa 01, repare que o cálculo do erro da raíz quadrada se difere da função erro_relativo()*/
double raiz_quadrada(double x){	

  double ra;
  double rb;
  double erro;
	
    ra = x;
	
	do{
		rb = 0.5 * (ra + x/ra);
		erro = valor_absoluto((rb - ra)/ra);
		ra = rb;
	}while ( erro > 0.000000001);
	
	return rb;
}

double valor_absoluto(double x){
	
	if( x <= 0)
		return -x;
	else
		return x;	
}

/*Implementação do método de Muller.
Podemos ver que o cálculo do valor inicial de q se difere do cálculo inicial de q, ou seja, calculamos qn+1 diferente de q0.
O laço principal dessa função possúi uma condicional grande pois algum dos chutes iniciais pode ser uma raíz da função, e se for o caso, não queremos perder esse valor.*/
double juros(double vbem, int n, double prestacao){
	
  double j1;
  double j2;
  double j3;
  double f1;
  double f2;
  double f3;
  double a;
  double b;
  double c;
  double q;
  double ql;
  double qll;
  double h3;
  double h2;
  
    j1 = 0;
	j2 = 0.3 * prestacao/(vbem - prestacao);
	j3 = prestacao/(vbem - prestacao);
	
	h3 = j3 - j2;
	h2 = j2 - j1;
	q = h3/h2;
	
	while(func_juros(j1, vbem, n, prestacao) != 0 && func_juros(j2, vbem, n, prestacao) != 0 && func_juros(j3, vbem, n, prestacao) != 0 && erro_relativo(j2, j3) > 0.000000001){
		
		h3 = j3 - j2;
		h2 = j2 - j1;
		
		f1 = func_juros(j1, vbem, n, prestacao);
		f2 = func_juros(j2, vbem, n, prestacao); 
		f3 = func_juros(j3, vbem, n, prestacao);
		
		a = q * f3 - q * (1 + q) * f2 + potencia(q, 2) * f1;
		b = (2 * q + 1) * f3 - potencia((1 + q), 2) * f2 - potencia(q, 2) * f1;
		c = (1 + q) * f3;
		
		ql = -1 * (double) ((2 * c) / (b + raiz_quadrada((potencia(b, 2) - 4 * a * c))));
		qll = -1 * (double) ((2 * c) / (b - raiz_quadrada((potencia(b, 2) - 4 * a * c))));
		
		if(valor_absoluto(ql) < valor_absoluto(qll))
			q = ql;
		else
			q = qll;
			
		j1 = j2;
		j2 = j3;		
		j3 = j3 + h3 * q;
		
		
	}
	
	if(func_juros(j1, vbem, n, prestacao) == 0)
		return j1;
	if(func_juros(j2, vbem, n, prestacao) == 0)
		return j2;
	if(func_juros(j3, vbem, n, prestacao) == 0 || erro_relativo(j2, j3) < 0.00000001)
		return j3;

}

double erro_relativo(double x, double y){
	
	if(y != 0)		
		return valor_absoluto(((x - y)/y));
	else
		return 1;
		
}

/*Função de auxílio para facilitar a formatação do programa.
Ela equivale a função polinomial passada no enunciado:
		f(j) = S - Vbem/P
*/
double func_juros(double j, double vbem, int n, double prestacao){
  
  double s;
  double t;

    t = 1/(1 + j);
	
	if(j > 0)
		s = (1 - potencia(t, n))/(1 - t);
	else if( j == 0)
		s = n;
	
	return (s - vbem/prestacao);
	
}