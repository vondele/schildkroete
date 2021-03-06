#include <iostream>
#include <string>

#include "hashtable.h"
#include "FEN_leser.h"
#include "types.h"

using namespace std;

void feltleser(feldType& felt, char cpin){
    static int a=7;
    static int b=0;
    switch(cpin){
        case '/':
            a-=1;
            b=-1;
            break;
        case '?':
            a=7;
            b=-1;
            break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
            b+=int(cpin)-int('0');
            b-=1;
            break;
        case 'r':
            felt[a][b]=-3;
            break;
        case 'R':
            felt[a][b]= 3;
            break;
        case 'n':
            felt[a][b]=-1;
            break;
        case 'N':
            felt[a][b]= 1;
            break;
        case 'b':
            felt[a][b]=-2;
            break;
        case 'B':
            felt[a][b]= 2;
            break;
        case 'q':
            felt[a][b]=-4;
            break;
        case 'Q':
            felt[a][b]= 4;
            break;
        case 'k':
            felt[a][b]=-5;
            break;
        case 'K':
            felt[a][b]= 5;
            break;
        case 'p':
            felt[a][b]=-6;
            break;
        case 'P':
            felt[a][b]= 6;
            break;
    }
    b+=1;
}

void FEN_leser(position& pos, string cppin){
    std::hash<position> hash_fn;
    unsigned int was=0;
    pos.felt = {};
    if(cppin[0]=='a')
        cppin="rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    for (unsigned int i=0; i<cppin.size(); i++) {
        if(cppin[i]!=' ')
            feltleser(pos.felt, cppin[i]);
        else{
            was=i+1;
            break;
        }
    }
    feltleser(pos.felt, '?');
    if(cppin[was]=='w')
        pos.farbe= 1;
    if(cppin[was]=='b')
        pos.farbe=-1;
    was+=2;
    //rokaden
    if(cppin[was]=='-')
        was+=1;
    if(cppin[was]=='K'){
        pos.rokaden[0]=1;
        was+=1;
    }
    else
        pos.rokaden[0]=0;

    if(cppin[was]=='Q'){
        was+=1;
        pos.rokaden[1]=1;
    }
    else
        pos.rokaden[1]=0;

    if(cppin[was]=='k'){
        was+=1;
        pos.rokaden[2]=1;
    }
    else
        pos.rokaden[2]=0;

    if(cppin[was]=='q'){
        was+=1;
        pos.rokaden[3]=1;
    }
    else
        pos.rokaden[3]=0;
    was+=1;

    //enpassent
    if(cppin[was]=='-'){
        pos.enpassent[0]=0;
        pos.enpassent[1]=0;
    }
    else{
        pos.enpassent[0]=int(cppin[was])-int('a');
        pos.enpassent[1]=(pos.farbe==1 ? 2 : 5);
        was+=1;
    }
    was+=2;

    //fuenfzig
    pos.fuenfzigzuege=0;
    while(was<cppin.size() && cppin[was]!=' '){
        pos.fuenfzigzuege*=10;
        pos.fuenfzigzuege+=int(cppin[was])-int('0');
        was+=1;
    }
    was+=1;
    //zugtiefe
    pos.zugtiefe=0;
    while(was<cppin.size() && cppin[was]!=' '){
        pos.zugtiefe*=10;
        pos.zugtiefe+=int(cppin[was])-int('0');
        was+=1;
    }
    pos.hash=hash_fn(pos);
}
