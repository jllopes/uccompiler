int main(int a, int b, char, short c, double d, void){ /* Function Definition, ParameterList*/
	if(a == 5){
		return;
	}
}

int main(void); /* Function Declaration */

int main(void){ /* Function Definition, Function Body, Multiple Declarations */
	int a, b;
	double a, c;
}

int main(void){ /* Function Definition, Function Body, One Declaration */
	int a;
}

int main(void){ /* Function Definition, Function Body, One Declaration, One Statement */
	int a, b;
	return ;
}

int main(void){ /* Function Definition, Function Body, One If Statement with braces */
	if(1){
		return ;
	}
}

int main(void){ /* Function Definition, Function Body, One If Statement with braces, return expression */
	if(1)
		return a+b;
}

int main(void){ /* Function Definition, Function Body, One If Else Statement without braces */
	if(1)
		return a;
	else
		return 1;
}

int main(void){ /* Function Definition, Function Body, One If Else Statement with braces */
	if(1){
		return a;
	}
	else{
		return a=b;
	}
}

int main(void){ /* Function Definition, Function Body, One While Statement without braces */
	while(1)
		a=b;
	d=e;
}

int main(void){ /* Function Definition, Function Body, One While Statement with braces, Return Expression */
	while(1){
		a=b;
	}
	return d=e;
}