struct matrix
{
	int val[M][M];
	matrix() { memset(val, 0, sizeof(val)); }
	matrix operator * (const matrix &oth) const
	{
		matrix res;
		for(int i = 0; i < M; i++)
			for(int j = 0; j < M; j++)
				for(int k = 0; k < M; k++)
					res.val[i][j] = (res.val[i][j] + 1LL * val[i][k] * oth.val[k][j] % MOD) % MOD;
		return res;
	}
} trans; 
matrix qpow(matrix a, long long power)
{
	matrix res;
	for(int i = 0; i < M; i++) res.val[i][i] = 1;
	while(power)
	{
		if(power & 1) res = res * a;
		a = a * a;
		power >>= 1;
	}
	return res;
}
//矩阵快速幂