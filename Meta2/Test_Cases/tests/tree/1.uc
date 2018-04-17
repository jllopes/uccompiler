int a = 0, b, c;
short d, e, f = 0;
char g, h, i = 'a';
void j, k, l;

int main (void);
int declarations(int, short, char c, double, void);
short stat_and_expr(int a, int, int, int d);

int main ( void ) {
    char i = 'A';
    while (i <= 'Z') {
        putchar (i);
        i = i + 1;
    }
    return 0;
}

double declarations( int i, short s, char c, double d, void v) {
	int i1, i2, i3;
	short s1, s2, s3;
	char c1, c2, c3;
	double d1, d2, d3;
	void v1, v2, v3;

	int    i4 = 0  , i5 = 0  , i6 = 0  ;
	short  s4 = 0  , s5 = 0  , s6 = 0  ;
	char   c4 = 0  , c5 = 0  , c6 = 0  ;
	double d4 = 0.0, d5 = 0.0, d6 = 0.0;
	void   v4 = 0  , v5 = 0  , v6 = 0  ;

	return d;
}

short stat_and_expr(int a, int b, int c, int d) {
	short s = '\000';
	a = (b + c, d + e) * d | a & b - -(a && b);
	return s;
}

int expr1 = ((1 + 1, 2 + 2) & a + b) * -(+(-c,d),e);
