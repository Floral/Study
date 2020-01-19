
# include <iostream>
using namespace std;
 
int main(){
	long long n, m, count = 0;
	double sum = 0;
	while(cin >> n >> m){
		count++;
		if(n > m || (n == 0 && m == 0)){
			cout << "Case " << count  << ": " << "GG" << endl;
			return 0;
		}
		for(long long i = n; i <= m; i++)
			sum += 1 / (double) i / i; 
		printf("Case %d: %.5lf\n", count, sum);
	}
	return 0;	
}