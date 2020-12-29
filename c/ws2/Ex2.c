/* returns (-1) if fails*/
int CopyArray ( int *arr1 , int size1 , int *arr2 , int size2)
{
	int i = 0;
	if ( size1 != size2 )
		return -1;
	for ( i=0 ; i<size1 ; i++ )
		arr2[i] = arr1[i];
	return 0;
}
