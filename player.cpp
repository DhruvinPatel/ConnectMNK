//Running format is: <object file> <ip of server> <port no>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <bits/stdc++.h>
/* Added Code */
#include <time.h> 
#include <sys/time.h>
/* */

#define FOR(i,n) for (int i = 0; i < n; i++)
#define PB push_back
using namespace std;
/* Complete the function below to print 1 integer which will be your next move 
   */
int N, M, K, player;
vector<string> board;

/* Added Code */
double time_left = 0;
/* */

vector<string> board1;

void update(int n)
{
    for(int i = 0; i < N; i++)
        if(board[i][n] == '.')
        {
            board[i][n] = 'X';
            return;
        }
}

void update1(int n)
{
    for(int i = 0; i < N; i++)
        if(board1[i][n] == '.')
        {
            board1[i][n] = 'X';
            return;
        }
}

void updateO(int n)
{
    for(int i = 0; i < N; i++)
        if(board[i][n] == '.')
        {
            board[i][n] = 'O';
            return;
        }
}
void updateO1(int n)
{
    for(int i = 0; i < N; i++)
        if(board1[i][n] == '.')
        {
            board1[i][n] = 'O';
            return;
        }
}

void remove(int n){
    for(int i =1; i< N; i++){
      if(board[i][n] == '.')
      {
        board[i-1][n] = '.';
        return;
      }

    }
    board[N-1][n] = '.';
    return;
}
void remove1(int n){
    for(int i =1; i< N; i++){
      if(board1[i][n] == '.')
      {
        board1[i-1][n] = '.';
        return;
      }

    }
    board1[N-1][n] = '.';
    return;
}
string getChar(int i,int j)
{
  string c;
  if(i>=0 && i<N && j>=0 && j<M)
    c=board1[i][j];
  else
    c="null";
  return c;
}


int calculate_heuristic_ndot_ch (vector<string> v,char ch,int Dots)
{
  int arr[2] = {0, 0};
    int k = K;
    //cout<<"REPOR:"<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3]<<" "<<v[4]<<" "<<v[5]<<" "<<v[6]<<" "<<v[7]<<" "<<v[7][8]<<" "<<v[N-1][M-1]<<" PP";
    for(int i = 0; i < N; i++)
    {
        for(int j=0;j<M;j++)
        {
            if(v[i][j] == '.')
                {

            int l_k = 1;//counted '.'
            int dot=1;
            // diagonally upwards
            for(;(l_k < k)&&(i-l_k>=0)&&(j+l_k<M); l_k++)
            {
                if(v[i - l_k][j + l_k]!=ch)//'X'
                  { if (v[i-l_k][j+l_k]=='.'&&(dot<Dots))
                      {dot++;}
                    else
                      break;
                  }
            }
            if(l_k == k&&(dot==Dots))
                arr[ch == 'O']++;

            l_k = 1;
            dot=1;
            // rightside
            for(;(l_k < k)&&(j+l_k<M); l_k++)
            {
                if(v[i][j + l_k]!=ch)
                 {  if(v[i][j+l_k]=='.'&&(dot<Dots))
                      {dot++;}
                    else
                     break;
                 }
            }
            if(l_k == k&&(dot==Dots))
                arr[ch == 'O']++;          

            l_k = 1;
            dot=1;
            // diagonally downwards
            for(;(l_k < k)&&(i+l_k<N)&&(j+l_k<M); l_k++)
            {
                if(ch != v[i + l_k][j + l_k])
                  { if(v[i+l_k][j+l_k]=='.'&&(dot<Dots))
                    {dot++;}
                    else  
                      break;
                  }
            }
            if(l_k == k&&(dot==Dots))
                arr[ch == 'O']++;

            l_k = 1;
            dot=1;
            // downwards
            for(;(l_k < k)&&(i + l_k<N); l_k++)
            {
                if(ch != v[i + l_k][j])
                  {
                    if(v[i+l_k][j]=='.'&&(dot<Dots))
                      {dot++;}
                    else
                      break;
                  }
            }
            if(l_k == k&&(dot==Dots))
                arr[ch == 'O']++;                        
                
                }
            else
            {

            int l_k = 0;
            int dot=0;
            // diagonally upwards
            for(;(l_k < k)&&(i-l_k>=0)&&(j+l_k<M); l_k++)
            {
                if(v[i][j] != v[i - l_k][j + l_k])
                  { if ((v[i-l_k][j+l_k]== '.')&&(dot<Dots))
                      dot++;
                    else
                      break;
                  }
            }
            if(l_k == k&&(dot==Dots))
                arr[v[i][j] == 'O']++;

            l_k = 0;
            dot=0;
            // rightside
            for(;(l_k < k)&&(j+l_k<M); l_k++)
            {
                if(v[i][j] != v[i][j + l_k])
                 {
                  if(v[i][j+l_k]=='.'&&(dot<Dots))
                   dot++;
                   else
                    break;
                 }
            }
            if(l_k == k&&(dot==Dots))
                arr[v[i][j] == 'O']++;          

            l_k = 0;
            dot=0;
            // diagonally downwards
            for(;(l_k < k)&&(i+l_k<N)&&(j+l_k<M); l_k++)
            {
                if(v[i][j] != v[i + l_k][j + l_k])
                  { if (v[i+l_k][j+l_k]=='.'&&(dot<Dots))
                      dot++;
                    else
                     break;
                  }
            }
            if(l_k == k&&(dot==Dots))
                arr[v[i][j] == 'O']++;

            l_k = 0;
            dot=0;
            // downwards
            for(;(l_k < k)&&(i + l_k<N); l_k++)
            {
                if(v[i][j] != v[i + l_k][j])
                  {
                    if(v[i+l_k][j]=='.'&&(dot<Dots))
                      dot++;
                    else
                      break;
                  }
            }
            if(l_k == k&&(dot==Dots))
                arr[v[i][j] == 'O']++;
            }
        }
    }

    return arr[ch == 'O'];
}




double calculate_heuritic(vector<string> v)
{
  double q = 2.1;//3.0; 
  double r = 2.1;
  double s = 3.0;
  if(K==5)//7 better
    return (q*q*q*q)*(calculate_heuristic_ndot_ch(v,'X',0)-0.9*calculate_heuristic_ndot_ch(v,'O',0))+(q*q*q)*(calculate_heuristic_ndot_ch(v,'X',1)-0.9*calculate_heuristic_ndot_ch(v,'O',1))+(q*q)*(calculate_heuristic_ndot_ch(v,'X',2)-0.9*calculate_heuristic_ndot_ch(v,'O',2))
  +(q)*(calculate_heuristic_ndot_ch(v,'X',3)-0.9*calculate_heuristic_ndot_ch(v,'O',3))+(1)*(calculate_heuristic_ndot_ch(v,'X',4)-0.9*calculate_heuristic_ndot_ch(v,'O',4));


  else if(K==6)
     return (r*r*r*r*r)*(calculate_heuristic_ndot_ch(v,'X',0)-0.9*calculate_heuristic_ndot_ch(v,'O',0))+(r*r*r*r)*(calculate_heuristic_ndot_ch(v,'X',1)-0.9*calculate_heuristic_ndot_ch(v,'O',1))
    +(r*r*r)*(calculate_heuristic_ndot_ch(v,'X',2)-0.9*calculate_heuristic_ndot_ch(v,'O',2))+(r*r)*(calculate_heuristic_ndot_ch(v,'X',3)-0.9*calculate_heuristic_ndot_ch(v,'O',3))+(r)*(calculate_heuristic_ndot_ch(v,'X',4)-0.9*calculate_heuristic_ndot_ch(v,'O',4))+(1)*(calculate_heuristic_ndot_ch(v,'X',5)-0.9*calculate_heuristic_ndot_ch(v,'O',5));


  else if(K==7)return (s*s*s*s*s*s)*(calculate_heuristic_ndot_ch(v,'X',0)-0.9*calculate_heuristic_ndot_ch(v,'O',0))+(s*s*s*s*s)*(calculate_heuristic_ndot_ch(v,'X',1)-0.9*calculate_heuristic_ndot_ch(v,'O',1))
    +(s*s*s*s)*(calculate_heuristic_ndot_ch(v,'X',2)-0.9*calculate_heuristic_ndot_ch(v,'O',2))+(s*s*s)*(calculate_heuristic_ndot_ch(v,'X',3)-0.9*calculate_heuristic_ndot_ch(v,'O',3))+(s*s)*(calculate_heuristic_ndot_ch(v,'X',4)-0.9*calculate_heuristic_ndot_ch(v,'O',4))+(s)*(calculate_heuristic_ndot_ch(v,'X',5)-0.9*calculate_heuristic_ndot_ch(v,'O',5))+(1)*(calculate_heuristic_ndot_ch(v,'X',6)-0.9*calculate_heuristic_ndot_ch(v,'O',6));   
}

struct node{
  double val;
  vector<string> play;
  vector<node*> v;
  node(){
  val=0;
  }
};

int globalindex;
int depth;
int movecounter = 0;

double  minimax(node* n, int d, bool p, double a, double b){
    //cout<<"minimaxD:"<<d<<" ";
  ofstream fout;
  fout.open("debu",ios::out|ios::app);
  
    if ((d == 0) || (n->v.size()==0))
        {
          n->val=calculate_heuritic(n->play);
          
          return calculate_heuritic(n->play);
      }

    if (p){

        double bestValue=-20000.0;
        for (int i=0;i<n->v.size();i++) {

            double val = minimax(n->v[i], d - 1, false,a,b);

            a = max(val,a);

            if(a>b) 
              return a;
            //if(d==2)
            //{fout<<"VAL_d2:"<<i<<":"<<val<<" "<<"size:"<<n->v.size()<<endl;}
            if(d==depth)
            {fout<<"VAL_d4::"<<i<<":"<<val<<" "<<"size:"<<n->v.size()<<endl;}
            if(d==depth)//at the top,p=true
            {if(bestValue<val){
                bestValue = val;
                globalindex=i;
            }}
            else
            {
              if(bestValue<val){
                bestValue = val;}
            }
        }
        fout<<"GLOBALp:"<<globalindex<<" "<<bestValue<<endl;
        n->val=bestValue;
        return bestValue;
    }
    else{

        double bestValue=20000.0;
        for (int i=0;i<n->v.size();i++){

            double val = minimax(n->v[i], d - 1, true,a,b);

            b = min(val,b);

            if(a>b)
              return b;

            if(bestValue>val){
                bestValue = val;
                //globalindex=i;
            }
            
        }
        n->val=bestValue;
        //cout<<"GLOBAL:"<<globalindex<<" "<<bestValue<<endl;
        return bestValue;
    }
}

node* temp1=new node();



void nextMove(int count)
{
  vector<int> v;

  for(int j = 0; j< M; j++)
  {
      if(board1[N-1][j] == '.')
      {
        v.push_back(j);
      }
  }

  for(int j=0; j<v.size(); j++){

      node* x = new node();
      
      temp1->v.push_back(x);
      
      //double sum=uval;
      if(count%2==0){

        update1(v[j]);
        x->play=board1;

          node* temp=new node();
          temp = temp1;
          temp1 = temp1->v.at(j);
          nextMove(count+1);
          temp1 = temp;

        remove1(v[j]);

        }

        else{

          updateO1(v[j]);//depth of tree is 3
          x->play=board1;
          if (count+1<depth){//4
              node* temp=new node();
              temp = temp1;
              temp1 = temp1->v.at(j);
              nextMove(count+1);
              temp1 = temp;
          }

          remove1(v[j]);        
      }
  } 
 
  return;  
}



int makeMove(){
  cout<<"makeMove"<<globalindex;

  vector<int> v;
  for(int j = 0; j< M; j++)
  {
      if(board[N-1][j] == '.')
      {
        v.push_back(j);
      }
  }
  
  
double eps1, eps2;

    if(K==5)
    {
      eps1=0.0;//initially -10
      eps2=0.0;
    }

    else if(K==6)
    {
      eps1=-10.0;
      eps2=0.0;
    }

    else
    {
      eps1=-10.0;
      eps2=0.0;
    }

  double mainsum = minimax(temp1,depth,true,-20000,20000);//3
  vector<int>vtemp;
  for(int i=0;i<temp1->v.size();i++)
  {
    if (temp1->v[i]->val<=eps2 &&(temp1->v[i]->val>=eps1)) 
      vtemp.push_back(i);
  } 
//    cout<<endl<<mainsum<<endl;
    int iSecret=globalindex;
    cout<<iSecret<<endl<<endl;

    


  if (((mainsum<=eps2)&&(mainsum>=eps1) &&vtemp.size()>2)){//0.0
    cout<<"Yesssss"<<endl;
    int p=rand()%1000;

    if (M%2==1){
        if(p<100){//200
            iSecret=vtemp.size()/2-1;
            iSecret=vtemp[iSecret];
        }
        else if (p<900){
            iSecret=vtemp.size()/2 ;
            iSecret=vtemp[iSecret];
        }
        else{
            iSecret=vtemp.size()/2+1;
            iSecret=vtemp[iSecret];
        }
        
    }
    else{
      
      if (p<100){
        iSecret=vtemp.size()/2-1;
                   iSecret=vtemp[iSecret];
      }
      else if (p<900){
       iSecret=vtemp.size()/2 ; 
                  iSecret=vtemp[iSecret];
      }
      else{
        iSecret=vtemp.size()/2 +1;
                   iSecret=vtemp[iSecret];
      }
    }
  }
  ofstream fout;
  fout.open("debu",ios::out|ios::app);
  fout<<"iSecret:"<<v[iSecret]<<" "<<"board:"<<(board1)[0]<<" "<<(board1)[1]<<" "<<(board1)[2]<<" "<<(board1)[3]<<" "<<(board1)[4]<<" "<<(board1)[5]<<(board1)[6]<<(board1)[7]<<"  ;"<<endl;
  fout.close();
  update(v[iSecret]);
  return v[iSecret];
  

  
}






int main(int argc, char *argv[])
{
	srand (time(NULL));
    int sockfd = 0, n = 0;
    char recvBuff[1024];
    char sendBuff[1025];
    struct sockaddr_in serv_addr; 

    if(argc != 3)
    {
        printf("\n Usage: %s <ip of server> <port no> \n",argv[0]);
        return 1;
    } 

    
    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Error : Could not create socket \n");
        return 1;
    } 

    memset(&serv_addr, '0', sizeof(serv_addr)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2])); 

    if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0)
    {
        printf("\n inet_pton error occured\n");
        return 1;
    } 

    if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
       printf("\n Error : Connect Failed \n");
       return 1;
    } 

    cout<<"Connect(N,M,K) will start"<<endl;

    memset(recvBuff, '0',sizeof(recvBuff));
    n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
    recvBuff[n] = 0;
    sscanf(recvBuff, "%d", &N);

    cout<<"N: "<<N<<endl;
    memset(recvBuff, '0',sizeof(recvBuff));
    n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
    recvBuff[n] = 0;
    sscanf(recvBuff, "%d", &M);

    cout<<"M: "<<M<<endl;
    memset(recvBuff, '0',sizeof(recvBuff));
    n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
    recvBuff[n] = 0;
    sscanf(recvBuff, "%d", &K);    
    
    cout<<"K: "<<K<<endl;

/* Added code */
    int TL;
    memset(recvBuff, '0',sizeof(recvBuff));
    n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
    recvBuff[n] = 0;
    sscanf(recvBuff, "%d", &TL);    
    
    cout<<"Time Limit: "<<TL<<endl;    
    time_left = TL;

/* */

    memset(recvBuff, '0',sizeof(recvBuff));
    n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
    recvBuff[n] = 0;
    sscanf(recvBuff, "%d", &player);  

    cout<<"Player "<<player<<endl;

    string temp = "";
    for(int j = 0; j< M; j++)
        temp += ".";
    FOR(i, N)
        board.PB(temp);


   // depth = 2;
         depth = 2;
	int totalmoves = N*M/2;
	movecounter=0;

    if(player == 1)
    {
        //cout << "hello" << endl;
        memset(sendBuff, '0', sizeof(sendBuff)); 
       	
       	board1=board;

        nextMove(0); 
        int temp = makeMove();
        temp1=new node();
        cout << "temp" << temp << endl;
        movecounter++;

        snprintf(sendBuff, sizeof(sendBuff), "%d", temp);
        write(sockfd, sendBuff, strlen(sendBuff));
    }

    while(1)
    {
        int nextColumn;

        memset(recvBuff, '0',sizeof(recvBuff));
        n = read(sockfd, recvBuff, sizeof(recvBuff)-1);

        /* Added Code */
        struct timeval  tv1, tv2;
        gettimeofday(&tv1, NULL);
        /* */

        recvBuff[n] = 0;
        sscanf(recvBuff, "%d", &nextColumn);
        //cout << "Rec: "<< nextColumn << endl;
        // if(player == 1)
	       //   update(nextColumn, 2);
        // else 
        //   update(nextColumn, 1);

        updateO(nextColumn);

	    cout << nextColumn << endl;
	    
        memset(sendBuff, '0', sizeof(sendBuff)); 

           int temp;

        board1=board;

        movecounter++;

      //     if(K==5)
      // {
      //    if(movecounter < 3*totalmoves/5)
      //      depth=4;
      //    else
      //     depth=6;
      // }

      // else if (K==6)
      // {
      //   if(movecounter < 3*totalmoves/5)
      //      depth=4;
      //    else
      //     depth=6;
      // }

      // else
      // {
        
      // }

          // if(K==5)
          // {
          //   if (time_left > 15)
          //   {
          //      if(movecounter < 3*totalmoves/5)
          //        depth=4;
          //      else
          //       depth=6;
          //   }

          //   else
          //   {
          //     depth = 4;
          //   }
          // }

          // else if (K==6)
          // {
          //   if (time_left > 15)
          //   {
          //     if(movecounter < 3*totalmoves/5)
          //        depth=3;
          //      else
          //       depth=5;
          //   }

          //   else
          //     depth=2;
          // }

          // else
          // {
          //   if (time_left > 15)
          //   {
          //     if(movecounter < 3*totalmoves/5)
          //        depth=2;
          //      else
          //       depth=4;
          //   }

          //   else
          //     depth=1;
          // }
          depth = 2;      


        cout<<"start next"<<endl;
        nextMove(0);
        cout<<"end next"<<endl;
        temp = makeMove();
        temp1=new node();

        cout << "temp" << temp << endl;

        snprintf(sendBuff, sizeof(sendBuff), "%d", temp);

        /** Added Code */
        gettimeofday(&tv2, NULL);
        double time_spent = (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec);
        time_left -= time_spent;

        cout << "time left now is "<<time_left<<endl;
        /* */

        write(sockfd, sendBuff, strlen(sendBuff));
    }

    return 0;
}
