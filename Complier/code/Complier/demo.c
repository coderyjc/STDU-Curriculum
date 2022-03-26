	int t = *a;
	write(t);
	printf("\n");
	*a = *b;
	write(*b);
	printf("\n");
	*b = t;
	write(*b);
	printf("\n");