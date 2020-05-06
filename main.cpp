#include <stdio.h>
#include <math.h>
#include "winbgi2.h"
#include "rk4.h"

double f(double t, double y); 
double y_analitycznie(double t); 
double lambda = 0.6;
double t0 = 0; //za³o¿ony warunek pocz¹tkowy
double y_0 = 0; 

void main()
{	double eps_eulera, eps_rk4;//bledy w metodzie eulera i RK
	double h = 0.03; //krok calkowania
	double t_max = 10;
	int m = 0;
	printf("Wykres funkcji(0) czy bledu wzglednego(1)?\n");
	scanf("%d", &m);

	graphics(800, 600);
	if (m == 0)
		scale(0, -5, t_max, 10);
	else
	{
		scale(0, 0, t_max, 0.3);
		title("Blad Eulera - kolor bialy i rk4-kolor czerwony", "", "");
	}
FILE* pf; //deklaracja pliku tekstowego
pf = fopen("menu.txt", "w"); 
	//metoda Eulera
	double t = t0;
	double y = y_0;
	for (int i = 0; i < t_max/h; i++)
	{
		t += h;  
		y += h*f(t, y);
		eps_eulera = fabs(y - y_analitycznie(t)) /fabs( y_analitycznie(t)); 
		printf("%lf\t %lf\t %lf\n ", t ,y, eps_eulera);
		fprintf(pf, "%lf\t %lf\t %lf\n",t,y, eps_eulera); //zapis wartosci calek do pliku tekstowego
		
		if (m == 0) 
			circle(t, y, 1);
		else
			circle(t, eps_eulera, 1);
	}

	//metoda rk4
	t = t0;
	y = y_0;
	for (int i = 0; i < t_max / h; i++)
	{
	t += h; 
	y = rk4(t, y, h, f);
	eps_rk4 = fabs(y - y_analitycznie(t)) / fabs(y_analitycznie(t));
	printf("\n%lf\t %lf\t %lf\n",t, y, eps_rk4);
	fprintf(pf, "%lf\t %lf\t %lf\n",t, y, eps_rk4);
	setcolor(0.95);
	
	if (m == 0)
			circle(t, y, 1);
		else
			circle(t, eps_rk4, 1);
	}
	// rachunek analityczny
	if (m == 0)
		for (int i = 0; i < t_max; i++)
		{
			setcolor(0.5);
			circle(i, y_analitycznie(i), 3);
		}
		fclose(pf); //zamkniecie pliku tekstowego
	wait();
}

double f(double t, double y)

{
	return ((-1.2*y)+7*exp(-0.3*t));
}
double y_analitycznie(double t)
{
	return (70/9*exp(-0.3*t)-43/9*exp(-1.2*t));
}

