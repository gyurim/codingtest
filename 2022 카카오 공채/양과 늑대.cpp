// 2022.04.22
// 바킹독 풀이 (다시 풀어보기!)

#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;
// 왼쪽 자식, 오른쪽 자식, 양/늑대 값
int l[20], r[20], val[20];
int n;
int ans = 1;
int vis[1<<17]; // vis[x]: 상태 x를 방문했는가? // 1 00000 00000 00000 00

// 상태에 대한 dfs 함수 
void solve(int state){ // state: 현재 state 
    if(vis[state]) return;
    vis[state] = 1;
    // wolf : 늑대의 수, num: 전체 정점의 수 
    int wolf = 0, num = 0;
    for (int i = 0; i < n; i++) {
        if (state & (1 << i)) {
            num++;
            wolf += val[i];
        }
    }
    cout << state << ": w (" << wolf <<"), num (" << num <<")\n";
    
    // 만약 늑대가 절반 이상일 경우 방문할 수 없는 상태이니 종료
    if (2 * wolf >= num) return;

    // 현재 state의 양의 수가 ans보다 클 경우 ans를 갱신
    ans = max(ans, num - wolf);
    // 이제 다음 상태로 넘어갈 시간 
    for (int i = 0; i < n; i++) {
        // i번째 비트가 꺼져있는 경우 해당 정점이 없으니 넘어감
        if (!(state & (1<<i))) continue;

        // 현재 보고 있는 i번째 정점의 left가 있다면
        if (l[i] != -1)
            solve(state | (1 << l[i]));

        // 현재 보고 있는 i번째 정점의 right가 있다면
        if (r[i] != -1)
            solve(state | (1 << r[i]));
    }
}

int solution(vector<int> info, vector<vector<int>> edges) {
    n = info.size();
    fill(l, l+n, -1);
    fill(r, r+n, -1);
    for(int i = 0; i < n; i++)
        val[i] = info[i];

    for (int i = 0; i < n - 1; i++) {
        int a = edges[i][0]; // 부모
        int b = edges[i][1]; // 자식 
        if (l[a] == -1) 
            l[a] = b;
        else r[a] = b;
    }
    solve(1); // 0번 노드만 포함된 상태에서 dfs 시작 
    return ans;
}

int main(){
    vector<int> info {0,0,1,1,1,0,1,0,1,0,1,1};
    vector<vector<int>> edges;
    string s = "[[0,1],[1,2],[1,4],[0,8],[8,7],[9,10],[9,11],[4,3],[6,5],[4,6],[8,9]]";
    
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ',') {
            if (s[i-1] == ']') continue;
            int a = s[i-1] - '0';
            int b = s[i+1] - '0';
            edges.push_back({a, b});
            i++;
        }
    }
    solution(info, edges);
}