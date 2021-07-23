int cmp( const void *a, const void *b ){
	return ((int *)a)[0] - ((int *)b)[0];
}

bool isCovered(int** ranges, int rangesSize, int* rangesColSize, int left, int right){
	
	qsort( ranges, rangesSize, sizeof(int)*2, cmp );
	
	if( left < ranges[0][0] || right > ranges[rangesSize-1][1] )
		return false;
	for( int i=0; i<rangesSize-1; i++ ){
		if( ranges[i][1]+1 < ranges[i+1][0] )
			return false;
	}
	return true;
}
