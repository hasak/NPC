#include<iostream>
#include<fstream>
#include<vector>
#include<string>

using namespace std;

vector<string> split(string s,char del){
    int i=0,j=0;
    vector<string> res;
    while(true){
        j=s.find_first_of(del,j);
        if(j==-1){
            res.push_back(s.substr(i,s.length()-i));
            break;
        }
        res.push_back(s.substr(i,j-i));
        i=++j;
    }
    return res;
}

int toSeconds(string s){
    vector<string> splitted=split(s,':');
    return 3600*stoi(splitted[0])+60*stoi(splitted[1])+stoi(splitted[2]);
}

vector<int> toint(vector<string> s){
    vector<int> d;
    for(int i=0;i<s.size();i++)
        d.push_back(stoi(s[i]));
    return d;
}

int main(){
    int i=0,pjes,konj,mas,resi,ukupno,ukrez=0,ukp=0,ukk=0,ukm=0,np,nk,nm,vrobuk;
    int rp,rk,rm;
    double rpsp,rpsk,rpsm,rps;
    string line;
    ifstream fin;
    vector<int> pjesaci,konji,masine,rezerva,rez={0,0,0,0};

    fin.open("parametri");
    while(getline(fin,line)){
        if(line[0]=='%' || line=="")
            continue;
        if(i==0)
            pjesaci=toint(split(line,' '));
        else if(i==1)
            konji=toint(split(line,' '));
        else if(i==2)
            masine=toint(split(line,' '));
        else if(i==3)
            pjes=toSeconds(line);
        else if(i==4)
            konj=toSeconds(line);
        else if(i==5)
            mas=toSeconds(line);
        else if(i==6)
            rezerva=toint(split(line,' '));
        else break;
        i++;
    }
    ukupno=pjes+konj+mas;
    for(int i=0;i<4;i++){
        ukp+=pjesaci[i];
        ukk+=konji[i];
        ukm+=masine[i];
        ukrez+=rezerva[i];
    }
    cout<<" Unesi ukupne rese: ";cin>>resi;
    resi-=ukrez;

    rpsp=1.0*ukp/pjes;
    rpsk=1.0*ukk/konj;
    rpsm=1.0*ukm/mas;
    rps=rpsp+rpsk+rpsm;

    rp=resi*rpsp/rps; np=rp/ukp; 
    rk=resi*rpsk/rps; nk=rk/ukk;
    rm=resi*rpsm/rps; nm=rm/ukm;

    cout<<"\nSamo male:";
    cout<<"\n NPC: ";
    for(i=0;i<4;i++){
        rez[i]=pjesaci[i]*np+konji[i]*nk+masine[i]*nm+rezerva[i];
        cout<<rez[i]<<" ";
    }
    vrobuk=nm*mas;
    cout<<"\n Pjesaci: "<<np<<"\n Konji: "<<nk<<"\n Masine: "<<nm;
    cout<<"\n "<<vrobuk/3600<<":"<<(vrobuk-vrobuk/3600*3600)/60<<":"<<(vrobuk-vrobuk/3600*3600)%60<<" h"<<endl;



    // Sa velikom kasarnom
    rpsp=4.0*ukp/pjes;
    rpsk=1.0*ukk/konj;
    rpsm=1.0*ukm/mas;
    rps=rpsp+rpsk+rpsm;

    rp=resi*rpsp/rps; np=rp/ukp/4; 
    rk=resi*rpsk/rps; nk=rk/ukk;
    rm=resi*rpsm/rps; nm=rm/ukm;
    cout<<"\nSa velikom kasarnom:";
    cout<<"\n NPC: ";
    for(i=0;i<4;i++){
        rez[i]=pjesaci[i]*np*4+konji[i]*nk+masine[i]*nm+rezerva[i];
        cout<<rez[i]<<" ";
    }
    vrobuk=nm*mas;
    cout<<"\n Pjesaci: "<<np<<" ("<<np<<")"<<"\n Konji: "<<nk<<"\n Masine: "<<nm;
    cout<<"\n "<<vrobuk/3600<<":"<<(vrobuk-vrobuk/3600*3600)/60<<":"<<(vrobuk-vrobuk/3600*3600)%60<<" h"<<endl;



    // Sa velikim
    rpsp=4.0*ukp/pjes;
    rpsk=4.0*ukk/konj;
    rpsm=1.0*ukm/mas;
    rps=rpsp+rpsk+rpsm;

    rp=resi*rpsp/rps; np=rp/ukp/4; 
    rk=resi*rpsk/rps; nk=rk/ukk/4;
    rm=resi*rpsm/rps; nm=rm/ukm;
    cout<<"\nSa velikim:";
    cout<<"\n NPC: ";
    for(i=0;i<4;i++){
        rez[i]=pjesaci[i]*np*4+konji[i]*nk*4+masine[i]*nm+rezerva[i];
        cout<<rez[i]<<" ";
    }
    vrobuk=nm*mas;
    cout<<"\n Pjesaci: "<<np<<" ("<<np<<")"<<"\n Konji: "<<nk<<" ("<<nk<<")"<<"\n Masine: "<<nm;
    cout<<"\n "<<vrobuk/3600<<":"<<(vrobuk-vrobuk/3600*3600)/60<<":"<<(vrobuk-vrobuk/3600*3600)%60<<" h"<<endl;
}