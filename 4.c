#include <stdio.h>

int graph[7][7] = {
    {0,1,0,0,0,1,1},
    {1,0,1,0,0,0,1},
    {0,1,0,1,0,0,1},
    {0,0,1,0,1,0,0},
    {0,0,0,1,0,1,1},
    {1,0,0,0,1,0,1},
    {1,1,1,0,1,1,0}
};

void dfs(int state, int start, int visited[]) {
    visited[start] = 1;
    for (int i = 0; i < 7; i++) {
        if ((state & (1 << i)) && graph[start][i] && !visited[i]) {
            dfs(state, i, visited);
        }
    }
}

int isConnected(int state) {
    if (state == 0) return 0;
    
    int visited[7] = {0};
    int start = -1;
    for (int i = 0; i < 7; i++) {00
        if (state & (1 << i)) {
            start = i;
            break;
        }
    }
    
    dfs(state, start, visited);
    
    for (int i = 0; i < 7; i++) {
        if ((state & (1 << i)) && !visited[i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int count = 0;
    for (int state = 1; state < (1 << 7); state++) {
        if (isConnected(state)) {
            count++;
        }
    }
    printf("%d\n", count);
    return 0;
}