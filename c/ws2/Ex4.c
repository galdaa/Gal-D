/* Swap values of 2 size_t variables */
void Swap ( size_t *a , size_t *b )
{
	size_t temp;
	temp= *a;
	*a= *b;
	*b= temp;
}

/* Swap values of 2 size_t* variables */
void Swap ( size_t **a , size_t **b )
{
	size_t *temp;
	temp= *a;
	*a= *b;
	*b= temp;
}
