#include <bits/stdc++.h>
using namespace std;

const string R[4][8]={
	{
		"loooloooo",
		"loooooooo",
		"loooooloo",
		"loooooooo",
		"loolooooo",
		"loooooolo",
		"llooooooo",
		"loooooolo"
	},
	{
		"loooolooo",
		"loolooooo",
		"loooooooo",
		"llooooooo",
		"loooooloo",
		"loooooooo",
		"loooooloo",
		"loooloolo"
	},
	{
		"loooloooo",
		"loooooloo",
		"llooooooo",
		"loooooooo",
		"loooooloo",
		"loooooooo",
		"loolooooo",
		"loooooolo"
	},
	{
		"loloooooo",
		"loooloooo",
		"loloooooo",
		"loooooolo",
		"loooooooo",
		"loooooooo",
		"loolooooo",
		"loooooolo"
	}
}, C[4][8]={
	{
		"loooolooo",
		"loooooloo",
		"loooloooo",
		"loooooooo",
		"loooooooo",
		"loolooooo",
		"loooooooo",
		"looooollo"
	},
	{
		"loooolooo",
		"loooloooo",
		"loloooooo",
		"loooooool",
		"loooooooo",
		"loooooloo",
		"loooloooo",
		"loooooolo"
	},
	{
		"loooloooo",
		"loolooooo",
		"loooooloo",
		"loooooooo",
		"loooooooo",
		"loloooooo",
		"loooloooo",
		"loooooolo"
	},
	{
		"loooooloo",
		"loloooooo",
		"loooooooo",
		"loooooolo",
		"llooooooo",
		"loooooooo",
		"loooloooo",
		"loooooolo"
	}
};

const string Gx[4]={"cefg", "bdegh", "bceg", "bcdg"},
			 Gy[4]={"fchb", "cbgfd", "fbgc", "ebgd"};

string r[16], c[16];
int gx[17], gy[17]; // the 17 position of the goal
int step, gr, g, score=0;
int per[4]; // the random permutation of the board
int hardness=0, statistics[100];

void changeColor(char c){
	string s="\033[1;", t="RGYBPC";
	if(c=='W')s+="0m";
	for(int i=0; i<t.size(); ++i)if(c==t[i])s+='3', s+=(char)(49+i), s+='m';
	cout<<s;
}

void initMap(){
	for(int i=0; i<4; ++i)per[i]=i;
	random_shuffle(per, per+4);
	for(int i=0; i<16; ++i)r[i]=c[i]="ooooooooooooooooo";
	auto cor=[](char &a, char b){if(a=='o')a=b;};
	for(int i=0; i<8; ++i)for(int j=0; j<9; ++j)
		cor(r[i][j], R[per[0]][i][j]), cor(c[i][j], C[per[0]][i][j]),
		cor(c[i][16-j], R[per[1]][i][j]), cor(r[15-i][j], C[per[1]][i][j]),
		cor(r[15-i][16-j], R[per[2]][i][j]), cor(c[15-i][16-j], C[per[2]][i][j]),
		cor(c[15-i][j], R[per[3]][i][j]), cor(r[i][16-j], C[per[3]][i][j]);
	int k=0;
	for(int i=0; i<Gx[per[0]].size(); ++i, ++k)gx[k]=Gx[per[0]][i]-'a', gy[k]=Gy[per[0]][i]-'a';
	for(int i=0; i<Gx[per[1]].size(); ++i, ++k)gx[k]=-Gy[per[1]][i]+'p', gy[k]=Gx[per[1]][i]-'a';
	for(int i=0; i<Gx[per[2]].size(); ++i, ++k)gx[k]=-Gx[per[2]][i]+'p', gy[k]=-Gy[per[2]][i]+'p';
	for(int i=0; i<Gx[per[3]].size(); ++i, ++k)gx[k]=Gy[per[3]][i]-'a', gy[k]=-Gx[per[3]][i]+'p';
}

struct point{
	int x, y;
	point(){}
	point(int _x, int _y):x(_x), y(_y){}
	point operator+(const point rhs){return point(x+rhs.x, y+rhs.y);}
	void operator+=(const point rhs){x+=rhs.x, y+=rhs.y;}
	bool operator==(const point rhs){return x==rhs.x&&y==rhs.y;}
	bool operator!=(const point rhs){return x!=rhs.x||y!=rhs.y;}
}robot[4];

const point direction[4]={point(1, 0), point(0, 1), point(-1, 0), point(0, -1)};

void makeMap(){
	cout<<"Score: "<<score<<'\t'<<step<<" steps\tRobot #"<<gr<<" to X\n";
	changeColor('W');
	for(int i=0; i<65; ++i)cout<<(i&3?'_':'.'); cout<<endl;
	for(int i=0; i<16; ++i){
		for(int j=0; j<65; ++j){
			if(j&3){
				if((j&3)==2){
					int k=0;
					if(gx[g]==i&&gy[g]==j>>2){
						for(; k<4; ++k)if(robot[k]==point(i, j>>2)){
							if(k==gr)changeColor('Y');
							cout<<'Y';
							if(k==gr)changeColor('W');
							break;
						}
						if(k==4)cout<<'X';
						k=5;
					}
					for(; k<4; ++k)if(robot[k]==point(i, j>>2)){
						if(k==gr)changeColor('G');
						else changeColor('R');
						cout<<k;
						changeColor('W');
						break;
					}
					if(k==4)cout<<' ';
				}
				else cout<<' ';
			}
			else cout<<(r[i][j>>2]=='l'?'|':' ');
		}
		cout<<endl;
		for(int j=0; j<65; ++j)cout<<(j&3?c[j>>2][i+1]=='l'?'_':' ':r[i][j>>2]=='l'?'|':'.');
		cout<<endl;
	}
	changeColor('W');
	for(int i=0; i<4; ++i)for(int j=i+1; j<4; ++j)assert(robot[i]!=robot[j]);
}

void init(int _g, int r){ // when a game start
	//step=0, gr=rand()%4, g=rand()%17;
	step=0, gr=r, g=_g;
	makeMap();
}

const uint kN=1<<23;
uint H[kN], from[kN], goal[17], gd[17][4]; // goal distance
point nxt[16][16][4];
bool vis[kN];
int dis[kN];

int h(uint x){
	uint y=x;
	do x=((x<<2u)+x+1u)&kN-1u; while(H[x]&&H[x]!=y);
	H[x]=y;
	return x;
}

point nxtPos(point q, int d){
	point p=direction[d];
	for(;;q+=p){
		if(d==0&&c[q.y][q.x+1]=='l')break;
		if(d==1&&r[q.x][q.y+1]=='l')break;
		if(d==2&&c[q.y][q.x]=='l')break;
		if(d==3&&r[q.x][q.y]=='l')break;
	}
	return q;
}

point getPos(uint x, uint r){
	uint pos=x>>(r<<3u)&255u;
	return point(pos>>4u, pos&15u);
}

void addRobot(uint &x, point p, uint r){
	x&=(uint)(-1)^(255u<<(r<<3u));
	x|=(uint)(p.x<<4|p.y)<<(r<<3u);
}

uint bfsInit(){
	for(int i=0; i<kN; ++i)H[i]=vis[i]=0, dis[i]=-1;
	//goal=(gx[g]<<4)+gy[g], gbot=gr<<3;
	for(int i=0; i<17; ++i)goal[i]=gx[i]<<4|gy[i];
	for(int i=0; i<16; ++i)for(int j=0; j<16; ++j)for(int k=0; k<4; ++k)nxt[i][j][k]=nxtPos(point(i, j), k);
	uint x=0;
	for(int i=0; i<4; ++i)addRobot(x, robot[i], i);
	for(int i=0; i<17; ++i)for(int j=0; j<4; ++j)gd[i][j]=-1;
	return x;
}

uint Nxt(uint x, uint y){
	uint r=y>>2, d=y&3;
	point p=getPos(x, r), q=nxt[p.x][p.y][d];
	for(int i=0; i<4; ++i)if(i!=r){
		point pr=getPos(x, i);
		if(pr.x==p.x&&d&1){
			if(p.y<pr.y&&pr.y<=q.y)q=pr+point(0, -1);
			else if(q.y<=pr.y&&pr.y<p.y)q=pr+point(0, 1);
		}
		else if(pr.y==p.y&&!(d&1)){
			if(p.x<pr.x&&pr.x<=q.x)q=pr+point(-1, 0);
			else if(q.x<=pr.x&&pr.x<p.x)q=pr+point(1, 0);
		}
	}
	addRobot(x, q, r);
	return x;
}

bool on(uint x, int g, uint r){return (x>>(r<<3u)&255u)==goal[g];}

point bfs(uint x){
	vector<point> r;
	//for(int i=0; i<17; ++i)for(int j=0; j<4; ++j)r.push_back(point(i, j));
	for(int i=0; i<hardness; ++i)r.push_back(point(rand()%17, rand()&3));
	queue<uint> b;
	b.push(x), dis[h(x)]=from[h(x)]=0, vis[h(x)]=1;
	for(int i=0; i<r.size(); ++i)if(on(x, r[i].x, r[i].y))gd[r[i].x][r[i].y]=x, r.erase(r.begin()+i), --i;
	//if((x>>gbot&255u)==goal)return x;
	while(!b.empty()&&r.size()){
		x=b.front(), b.pop();
		for(int i=0; i<16; ++i){
			uint y=Nxt(x, i);
			int z=h(y);
			if(!vis[z]){
				vis[z]=1, dis[z]=dis[h(x)]+1, from[z]=x;
				for(int i=0; i<r.size(); ++i)if(on(y, r[i].x, r[i].y))gd[r[i].x][r[i].y]=y, r.erase(r.begin()+i), --i;
				//if((y>>gbot&255u)==goal)return y;
				b.push(y);
			}
		}
	}
	point mx=point(0, 0);
	for(int i=0; i<17; ++i)for(int j=0; j<4; ++j)if(dis[h(gd[i][j])]>dis[h(gd[mx.x][mx.y])])mx=point(i, j);
	return point(mx.x, mx.y);
}

void print(uint x){
	for(int i=0; i<4; ++i)robot[i]=getPos(x, i);
	makeMap();
}

void waitRes(){
#ifndef fast
	string s;
	cout<<"Press enter to continue...", getline(cin, s);
#endif
}

int move(uint x, string s){
	string t0="sdwa", t1="jkl;"; int r=gr, cnt=0;
	for(char i:s){
		for(int j=0; j<4; ++j)if(i==t0[j])x=Nxt(x, r*4+j), ++cnt;
		for(int j=0; j<4; ++j)if(i==t1[j])r=j;
	}
	if(on(x, g, gr))return cnt;
	else return -1;
}

int ask(uint x){
	string s; getline(cin, s);
	int r=gr;
	if(s=="skip")return -2;
	return move(x, s);
}

int main(){
	cout<<"Ricochet Robots\n\
Author: Po-Hsiang, Hsu\n", waitRes();
	cout<<"The robot won't stop until it bumps into a wall or another robot.\n\
The mission is to move the given robot to the right place (which is ususally marked X).\n\
The place is marked Y if there's a robot on it.\n\
Have fun!\n", waitRes();
	ofstream out;
	while(1){
		cout<<"Which mode do you want to play? (easy/medium/hard): ";
		string s; getline(cin, s);
		if(s=="easy"){hardness=1, out.open("easy.txt"); break;}
		if(s=="medium"){hardness=3, out.open("medium.txt"); break;}
		if(s=="hard"){hardness=5, out.open("hard.txt"); break;}
		cout<<"I can't understand.\n";
	}
	robot[0]=point(0, 0), robot[1]=point(0, 15), robot[2]=point(15, 15), robot[3]=point(15, 0);
	srand(time(0)), initMap();
	for(int cnt=1; ; ++cnt){
		point g=bfs(bfsInit());
		uint x=gd[g.x][g.y];
		init(g.x, g.y);
		int ans=dis[h(x)];
		cout<<ans<<" steps in total!\n";
		++statistics[ans];
		if(cnt%100==0){
			for(int i=0; i<100; ++i)out<<statistics[i]<<' ';
			out<<endl;
		}
		vector<uint> route;
		route.push_back(x);
		assert(x!=0&&x!=-1);
		while(from[h(x)])route.push_back(x=from[h(x)]);
		reverse(route.begin(), route.end());
#ifdef play
		while(1){
			int y=ask(x);
			if(y==-2)break;
			if(y==-1)cout<<"Wrong! Enter skip to skip.\n";
			else if(y<=ans){cout<<"Correct!\n", score+=ans*ans; break;}
			else cout<<"It can be better! Enter skip to skip.\n";
		}
#else
		waitRes();
#endif
		for(uint i:route){
			print(i);
#ifndef fast
			usleep(500000);
#endif
			++step;
		}
	}
}
