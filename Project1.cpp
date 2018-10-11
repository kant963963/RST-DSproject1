#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <time.h>
using namespace std;

int main(int argc,char *argv[]){
	int i,j,count = 0,m,n,*A1,*A2,*A3,*B1,*B2;
    queue<int> row,col;
    string str(argv[1]);

    fstream fin;
    fin.open(str+"/matrix.data", ios::in);
    
    if(!fin) return 1;
    fin>>m>>n;

    A1 = new int[n+2];
    A2 = new int[n+2];
    A3 = new int[n+2];

    for(i=0;i<=n+1;i++) A1[i] = -2147483648;
    
    A2[0] = -2147483648;
    A2[n+1] = -2147483648;
    A3[0] = -2147483648;
    A3[n+1] = -2147483648;
    
    for(i=1;i<=n;i++) fin>>A2[i];
    
    for(i=2;i<=m;i++){
        for(j=1;j<=n;j++){
            if(i%3 == 2){
                fin>>A3[j];
                if( A2[j] >= A2[j-1] && A2[j] >= A2[j+1] && A2[j] >= A1[j] && A2[j] >= A3[j] ){
                    count++;
                    row.push(j);
                    col.push(i-1);
                }   
            }
            else if(i%3 == 0){
                fin>>A1[j];
                if( A3[j] >= A3[j-1] && A3[j] >= A3[j+1] && A3[j] >= A2[j] && A3[j] >= A1[j] ){
                    count++;
                    row.push(j);
                    col.push(i-1);
                }   
            }
            else{
                fin>>A2[j];
                if( A1[j] >= A1[j-1] && A1[j] >= A1[j+1] && A1[j] >= A3[j] && A1[j] >= A2[j] ){
                    count++;
                    row.push(j);
                    col.push(i-1);
                }   
            }
        }
    }

    for(j=1;j<=n;j++){
        if(m%3 == 2){
            A1[j] = -2147483648;
            if( A3[j] >= A3[j-1] && A3[j] >= A3[j+1] && A3[j] >= A2[j] && A3[j] >= A1[j] ){
                count++;
                row.push(j);
                col.push(m);
            }   
        }
        else if(m%3 == 0){
            A2[j] = -2147483648;
            if( A1[j] >= A1[j-1] && A1[j] >= A1[j+1] && A1[j] >= A3[j] && A1[j] >= A2[j] ){
                count++;
                row.push(j);
                col.push(m);
            }   
        }
        else{
            A3[j] = -2147483648;
            if(  A2[j] >= A2[j-1] && A2[j] >= A2[j+1] && A2[j] >= A1[j] && A2[j] >= A3[j] ){
                count++;
                row.push(j);
                col.push(m);
            }   
        }
    }

    fin.close();
    fin.open(str+"final.peak", ios::out);
    fin<<count<<endl;
    for(i=1;i<=count;i++){
        fin<<col.front()<<" "<<row.front()<<endl;
        row.pop();
        col.pop();
    }
    fin.close();
    
    cout << (double)clock() / CLOCKS_PER_SEC << " S";
    
    return 0;
}

