#include<cstdio>
#include<utility>

using namespace std;

int main()
{
    int N;

    while (scanf("%d", &N)!=EOF && N!=0)
    {
        pair<double, double> point[3];
        pair<double, double> result;
        while (N--)
        {
            result.first = result.second = .0;
            scanf("%lf %lf %lf %lf %lf %lf", &point[0].first, &point[0].second, 
            &point[1].first, &point[1].second, &point[2].first, &point[2].second);
            for (int i = 0; i < 3; i++)
            {
                result.first += point[i].first;
                result.second += point[i].second;
            }
            result.first /= 3;
            result.second /= 3;
            printf("%.1f %.1f\n", result.first, result.second);
        }
    }
    
    return 0;
}