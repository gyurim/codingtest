#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> d, int budget) {
    int answer = 0;

    sort(d.begin(), d.end());
    int num = 0;
    
    for (int i = 0; i < d.size(); i++){
        if (budget >= d[i]){
            budget -= d[i];
            num++;
        } else break;
    }

    answer = num;

    return answer;
}