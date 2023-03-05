#include <bits/stdc++.h>
using namespace std;

//Minesweeper version 1 (Not full gameplay)
//NOTE: This version isn't as optimized as the second one and still has bugs, which i have fixed in the full version
//Made by Luong Gia Khanh - 22024558 - T-CLC

bool live = true;
int steps_to_win = 0;

// update evertime user input a location
void updatemap(int x, int y, int m, int n, char pre_map[100][100], int map[100][100]){
    if(map[x][y]==0){
        pre_map[x][y]=' ';
        steps_to_win--;
    }
    else if(map[x][y]==-1){
        pre_map[x][y] = '*';
        live = false;
    }
    else{
        switch (map[x][y]){
            case 1:
                pre_map[x][y] = '1';
                steps_to_win--;
                break;
            case 2:
                pre_map[x][y] = '2';
                steps_to_win--;
                break;
            case 3:
                pre_map[x][y] = '3';
                steps_to_win--;
                break;
            case 4:
                pre_map[x][y] = '4';
                steps_to_win--;
                break;
            case 5:
                pre_map[x][y] = '5';
                steps_to_win--;
                break;
            case 6: 
                pre_map[x][y] = '6';
                steps_to_win--;
                break;
            case 7:
                pre_map[x][y] = '7';
                steps_to_win--;
                break;
            case 8:
                pre_map[x][y] = '8';
                steps_to_win--;
                break;
            default:
                break;
        }
    }  
}

//the numbers to indicate how many mines around that area
void mines_indication(int m, int n, int map[100][100]){
    // mines indication
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++){
            if(map[i][j]==-1){
                if(map[i-1][j+1]!=-1&&i-1>0&&j+1<m)
                    map[i-1][j+1]++;
                if(map[i][j+1]!=-1&&j+1<m)
                    map[i][j+1]++;
                if(map[i+1][j+1]!=-1&&i+1<n&&j+1<m)
                    map[i+1][j+1]++;
                if(map[i+1][j]!=-1&&i+1<n)
                    map[i+1][j]++;
                if(map[i+1][j-1]!=-1&&i+1<n&&j-1>0)
                    map[i+1][j-1]++;
                if(map[i][j-1]!=-1&&j-1>0)
                    map[i][j-1]++;
                if(map[i-1][j-1]!=-1&&i-1>0&&j-1>0)
                    map[i-1][j-1]++;
                if(map[i-1][j]!=-1&&i-1>0)
                    map[i-1][j]++;
            }
        }
    }
}

// print the map
void printmap(int x, int y, int m, int n, int map[100][100], char pre_map[100][100]){
    updatemap(x, y, m, n, pre_map, map);
    for(int i = 1; i <= m; i++){
        for(int j = 1; j <= n; j++)
            cout << pre_map[i][j] << " ";
        cout << endl;
    }
}

//build the map
void buildmap(int x1, int y1, int m, int n, int k, int map[100][100], char pre_map[100][100]){
    int numb_of_mines = k;
    int temp_x, temp_y;
    // build the first display layer of the map
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
                pre_map[i][j] = '~';
    printmap(x1, y1, m, n, map, pre_map);
    // build the frame of the map
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
            map[i][j]=0;
    // place mines in random location
    // for every value of (x, y) can't be the same like another
    srand(time(NULL));
    while(numb_of_mines>0){
        int x = rand() % (m - 1 + 1) + 1;
        int y = rand() % (n - 1 + 1) + 1;
        if(x!=temp_x&&y!=temp_y){
            for(int i = 1; i <= m; i++){
                for(int j = 1; j <= n; j++)
                    if(j==y&&i==x)
                        map[i][j] = -1;
            }
            numb_of_mines--;
        }
        temp_x = x;
        temp_y = y;
    }
    //count steps to win the game
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
            if(map[i][j]!=-1)
                steps_to_win++;
    mines_indication(m, n, map);
}


int main(){
    int m, n, k;
    int x, y;
    int map[100][100];
    char pre_map[100][100];
    cout << "Select the size of the map m*n: ";
    cin >> m >> n;
    cout << "Select number of mines: ";
    cin >> k;
    buildmap(x, y, m, n, k, map, pre_map);
    while(live&&steps_to_win>0){
        cout << "Choose your location (x, y): ";
        cin >> x >> y;
        if(x<=m&&y<=n&&x>0&&y>=0){
             printmap(x, y, m, n, map, pre_map);
        }
        else
            cout << "Please input a valid value!" << endl;
    }
    if(!live) cout << "You're dead";
    else if(steps_to_win==0) cout << "You won";
}