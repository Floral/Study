#include<bits/stdc++.h>
using namespace std;
 
struct Station{
	double distance;
	double price;
}station[510];

bool hashTable[510] = {false};
 
double cmax,D,avg;
 
bool comp(Station s1,Station s2){
	if(s1.distance < s2.distance) return true;
	else if(s1.distance == s2.distance) return s1.price<s2.price;
	else return false;
}
 
int main(){
	int N,i,min,now;
	double cost=0,c;
	cin>>cmax>>D>>avg>>N;
	for(i=0;i<N;i++){
		scanf("%lf%lf",&station[i].price,&station[i].distance);
	}
	station[N].distance = D;
	station[N].price = 0;
	sort(station,station+N+1,comp);

    for (int i = 0; i < N+1; i++)
    {
        printf("%d:(%.2lf %.0lf) ", i, station[i].price, station[i].distance);
    }
    putchar('\n');
	if(station[0].distance !=0){
		cout<<"The maximum travel distance = 0.00";
	}else{
		while(now<N){
			min = now;
			if(station[now].distance+cmax*avg < station[now+1].distance){
				printf("The maximum travel distance = %.2f",station[now].distance+cmax*avg);
				break;
			}
			for(i=now+1;i<=N;i++){
				if(station[now].distance+cmax*avg < station[i].distance) break;
				if(station[i].price <= station[now].price){
					min = i;
					break;
				}
			}
			if(min == now){
				min = now +1; 
				for(i=now+2;i<=N;i++){
					if(station[now].distance+cmax*avg < station[i].distance) break;
					if(station[i].price <= station[min].price){
						min = i;
					}
				}
                hashTable[now] = true;
				cost += (cmax-c)*station[now].price;
				c = cmax - (station[min].distance - station[now].distance)/avg;
				now = min;
			}else{
                hashTable[now] = true;
				c = (station[min].distance - station[now].distance)/avg -c;
				cost += c*station[now].price;
				c = 0;
				now = min;
				
			}
		}
		if(now == N){
			printf("%.2f\n",cost);
		}
        for (int i = 0; i < N; i++)
        {
            if (hashTable[i])
                printf("%d ", i);
        }
        
	}
}