#include <bits/stdc++.h>
using namespace std;

//Minesweeper version 2 (Full gameplay)
//NOTE: The vertical vector stands for x; the horizontal vector stands for y.
//When you input (x, y) please select the indication in the vertical vector first, then horizontal.
//Made by Luong Gia Khanh - 22024558


bool live = true;
int steps_to_win = 0;
char pre_map[100][100];

void loang(int x, int y, int m, int n, int Map[100][100]){
    pre_map[x][y] = ' ';
    steps_to_win--;
    for(int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            if(x + i >= 0 && x + i <= m && y + j >= 0 && y + j <= n){
                if(pre_map[x + i][y + j]=='~'&&Map[x + i][y + j]==0)
                    loang(x + i, y + j, m, n, Map);
                else if(pre_map[x + i][y + j]=='~'&&Map[ x + i][ y + j]>0){
                    int pos_x = x + i;
                    int pos_y = y + j;
                    switch (Map[pos_x][pos_y]){
                        case 1:
                            pre_map[pos_x][pos_y] = '1';
                            steps_to_win--;
                            break;
                        case 2:
                            pre_map[pos_x][pos_y] = '2';
                            steps_to_win--;
                            break;
                        case 3:
                            pre_map[pos_x][pos_y] = '3';
                            steps_to_win--;
                            break;
                        case 4:
                            pre_map[pos_x][pos_y] = '4';
                            steps_to_win--;
                            break;
                        case 5:
                            pre_map[pos_x][pos_y] = '5';
                            steps_to_win--;
                            break;
                        case 6: 
                            pre_map[pos_x][pos_y] = '6';
                            steps_to_win--;
                            break;
                        case 7:
                            pre_map[pos_x][pos_y] = '7';
                            steps_to_win--;
                            break;
                        case 8:
                            pre_map[pos_x][pos_y] = '8';
                            steps_to_win--;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
    }
}

// update evertime user input a location
void updatemap(int x, int y, int m, int n, char pre_map[100][100], int Map[100][100]){
    if(Map[x][y]==0&&x!=0&&y!=0){
        loang(x, y, m, n, Map);
    }
    else if(Map[x][y]==-1){
        pre_map[x][y] = '*';
        live = false;
    }
    else{
        switch (Map[x][y]){
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


//the numbers to show how many mines around that area
void mines_indication(int m, int n, int Map[100][100]){
    // mines indication
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
            if(Map[i][j]==-1)
                for(int k = -1; k < 2; k++)
                    for(int h = -1; h < 2; h++)
                        if(i + k >= 0 && i + k <= m && j + h >= 0 && j + h <= n && Map[i+k][j+h]!=-1)
                                Map[i+k][j+h]++;
}

// print the map
void printmap(int x, int y, int m, int n, int Map[100][100], char pre_map[100][100]){
    updatemap(x, y, m, n, pre_map, Map);
    int indication_row = 0;
    int indication_col = 0;
    for(int i = 1; i <= m; i++){
        indication_row++;
        for(int j = 1; j <= n; j++)
            cout << pre_map[i][j] << "  ";
        cout << "|" << indication_row;
        if(i == 1) cout << " x";
        cout << endl;
    }
    for(int i = 0; i < n; i++)
        cout << "_  ";
    cout << endl;
    for(int i = 0; i < n; i++){
        indication_col++;
        cout << indication_col << "  ";
    }
    cout << "y";
    cout << endl;
}

//build the map
void buildmap(int x, int y, int m, int n, int k, int Map[100][100], char pre_map[100][100]){
    int numb_of_mines = k;
    // build the first display layer of the map
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
                pre_map[i][j] = '~';
    printmap(x, y, m, n, Map, pre_map);
    // build the frame of the map
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
            Map[i][j]=0;
    // place mines in random location
    // for every value of (x, y) can't be the same like another
    srand(time(NULL));
    while(numb_of_mines>0){
        int x1 = rand() % (m - 1 + 1) + 1;
        int y1 = rand() % (n - 1 + 1) + 1;
        if(Map[x1][y1]!=-1){
            for(int i = 1; i <= m; i++){
                for(int j = 1; j <= n; j++)
                    if(j==y1&&i==x1)
                        Map[i][j] = -1;
            }
            numb_of_mines--;
        }
    }
    //count steps to win the game
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
            if(Map[i][j]!=-1)
                steps_to_win++;
    mines_indication(m, n, Map);
}

int main(){
    int m, n, k;
    int x = 0;
    int y = 0;
    int Map[100][100];
    cout << "Select the size of the map m*n: ";
    cin >> m >> n;
    cout << "Select number of mines: ";
    cin >> k;
    buildmap(x, y, m, n, k, Map, pre_map);
    while(live&&steps_to_win>0){
        cout << "Choose your location (x, y): ";
        cin >> x >> y;
        if(x<=m&&y<=n&&x>0&&y>=0){
             printmap(x, y, m, n, Map, pre_map);
        }
        else
            cout << "Please input a valid value!" << endl;
    }
    if(!live) cout << "You're dead";
    else if(steps_to_win<=0) cout << "You won";
}