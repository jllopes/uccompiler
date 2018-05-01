int hey_im_global = 1;
double also_global = 12.7e-8;

//int x = 99;
//int x = -99;

int r1 = 10;
int r2 = 20;
int r3 = 30;
int global_variables_in_params_definition(int r1, int r2) // mesmo nome que variáveis globais
{
	int r3 = 999;
	return r1*r2;
}
void global_variables_in_params_declaration(double r1, double r2);

void im_just_a_function_declaration(void);
int i_have_no_parameter_names(char,short,int,double);

short func_e(int a, char b, double c, short e);
double func_d(double d, int n);
char func_c(char a, int b);

double func_between_c_and_b(short s)
{
	int x, y, z;
	short local_short;
	return also_global;
}

int func_b(int n);
void func_a(void);

void last_func(int);
void last_func(int n);
void last_func(int nnnnnnnnnnnnn);
//void last_func(double,int);
// double last_func = 2.0;

void func_a(void)
{
	int temp = b(2);
}

int func_b(int n)
{
	int temp;
	return 0;
}

char func_c(char a, int b)
{
	int temp;
	return 'x';
}

void last_func(int n)
{
	putchar(n);
}

double func_d(double d, int n)
{
	double temp = d / n;
	return temp;
}

short func_e(int a, char b, double c, short e)
{
	int temp = a + c * e - b;
	return temp;
}

void i_have_a_lot_of_stuff(int x,  char y, short y, double w,
						  int x1,  char y1, short y1, double w1,
						  int x2,  char y2, short y2, double w2,
						  int x3,  char y3, short y3, double w3,
						  int x4,  char y4, short y4, double w4,
						  int x5,  char y5, short y5, double w5,
						  int x6,  char y6, short y6, double w6,
						  int x7,  char y7, short y7, double w7,
						  int x8,  char y8, short y8, double w8,
						  int x9,  char y9, short y9, double w9,
						  int x10, char y10, short y10, double w10,
						  int x11, char y11, short y11, double w11,
						  int x12, char y12, short y12, double w12,
						  int x13, char y13, short y13, double w13,
						  int x14, char y14, short y14, double w14,
						  int x15, char y15, short y15, double w15,
						  int x16, char y16, short y16, double w16,
						  int x17, char y17, short y17, double w17,
						  int x18, char y18, short y18, double w18,
						  int x19, char y19, short y19, double w19,
						  int x20, char y20, short y20, double w20)
{
	int a, b, c, d, e, f, g, h, j;
	char a1, b1, c1, d1, e1, f1, g1, h1, j1;
	short a2, b2, c2, d2, e2, f2, g2, h2, j2;
	double a3, b3, c3, d3, e3, f3, g3, h3, j3;
}

char the_end = '\n';

/*
char i_have_parameters_with_the_same_name(int a, int a);
char hey_i_also_have_parameters_with_the_same_name(int b, int b)
{
	return '0';
}

int normal_params(int a, int b);                        // OK
int omitted_params(int, int);                           // OK
int pseudo_params(int a, int);                          // OK
int pseudo_params_2(int, int b);                        // OK
int pseudo_params_definition(int a, int){return 0;}     // ERROR
int pseudo_params_definition_2(int, int b){return 0;}   // ERROR
*/