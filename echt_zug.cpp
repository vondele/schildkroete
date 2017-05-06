#include <iostream>

#include "echt_zug.h"
#include "rokade.h"
#include "fuenfzig_zuege_regel.h"

using namespace std;

bool farben(int felt, int farbe){
    if(farbe== 1)
        if(felt>0){
            return true;
         }
    if(farbe==-1)
        if(felt<0){
            return true;
         }
     return false;
}

int promovieren(int Zahl[4], int farbe){
    bool darf_man_promovieren=false;
    if((Zahl[2]==0) && (farbe==-1))
        darf_man_promovieren=true;
    if((Zahl[2]==7) && (farbe== 1))
        darf_man_promovieren=true;
    if(darf_man_promovieren==true){
        char zu_was_man_promovieren_will;
        cin >> zu_was_man_promovieren_will;
        switch(zu_was_man_promovieren_will){
            case 'd':
            case 'D':
                return farbe*4;
            case 't':
            case 'T':
                return farbe*3;
            case 'p':
            case 'P':
                return farbe;
            case 'l':
            case 'L':
                return farbe*2;
        }
    }
    return farbe*6;
}

void wegnemen_von_promowiren(int felt[8][8], int farbe, int onpassent){
            if(farbe== 1)
                felt[4][onpassent]=0;
            if(farbe==-1)
                felt[3][onpassent]=0;
}

bool bauer(int felt[8][8], int Zahl[4], int farbe, int& onpassent, int& onpassenttester){
    if(farben(felt[Zahl[2]][Zahl[3]], farbe*-1)==true){
        if((Zahl[0]==(Zahl[2]-(farbe))) && (Zahl[1]==(Zahl[3]-1))){
            felt[Zahl[0]][Zahl[1]] = promovieren(Zahl, farbe);
            return true;
        }
        else if((Zahl[0]==(Zahl[2]-farbe)) && (Zahl[1]==(Zahl[3]+1))){
            felt[Zahl[0]][Zahl[1]] = promovieren(Zahl, farbe);
            return true;
        }
    }
    else if(felt[Zahl[2]][Zahl[3]]==0){
        if(Zahl[1]==Zahl[3]){
            if(Zahl[0]==(Zahl[2]-farbe)){
                felt[Zahl[0]][Zahl[1]] = promovieren(Zahl, farbe);
                return true;
            }
            if((Zahl[0]==1) && (farbe== 1)){
                if(Zahl[0]==(Zahl[2]-2)){
                    onpassenttester=1;
                    onpassent=Zahl[1];
                    return true;
                }
            }
            if((Zahl[0]==6) && (farbe==-1)){
                if(Zahl[0]==(Zahl[2]+2)){
                    onpassenttester=1;
                    onpassent=Zahl[1];
                    return true;
                }
            }
        }
    }
    if(Zahl[3]==onpassent){
        if((Zahl[0]==(Zahl[2]-farbe)) && (Zahl[1]==(Zahl[3]-1))){
            wegnemen_von_promowiren(felt, farbe, onpassent);
            return true;
        }
        else if((Zahl[0]==(Zahl[2]-farbe)) && (Zahl[1]==(Zahl[3]+1))){
            wegnemen_von_promowiren(felt, farbe, onpassent);
            return true;
        }
    }
    return false;
}

bool Koenig(int felt[8][8], int Zahl[4], int farbe){
    if(farben(felt[Zahl[2]][Zahl[3]], farbe)==false)
        for(int i=-1; i<=1; i++)
            for(int j=-1; j<=1; j++)
                if((Zahl[0]==(Zahl[2]+i)) && (Zahl[1]==(Zahl[3]+j)))
                    return true;
    return false;
}

bool turm(int felt[8][8], int zahl[4], int farbe){
    if(zahl[0]==zahl[2]){
        int abstand = zahl[1]-zahl[3]+1;
        if(zahl[1]-zahl[3]>0)
            abstand = zahl[1]-zahl[3]-1;
        int dazwischen=0;
        for(int i=abstand; i!=0; (zahl[1]-zahl[3]<0) ? i++ : i--)
            if(felt[zahl[0]][zahl[3]+i]==0)
                dazwischen+=1;
        if(dazwischen==(abstand<0 ? -abstand : abstand))
            if(farben(felt[zahl[2]][zahl[3]], farbe)==false)
                return true;
    }
    if(zahl[1]==zahl[3]){
        int abstand = zahl[0]-zahl[2]+1;
        if(zahl[0]-zahl[2]>0)
            abstand = zahl[0]-zahl[2]-1;
        int dazwischen=0;
        for(int i=abstand; i!=0; (zahl[0]-zahl[2]<0) ? i++ : i--)
            if(felt[zahl[2]+i][zahl[1]]==0)
                dazwischen+=1;
        if(dazwischen==(abstand<0 ? -abstand : abstand))
            if(farben(felt[zahl[2]][zahl[3]], farbe)==false)
                return true;
    }
    return false;
}

bool leufer(int felt[8][8], int zahl[4], int farbe){
    int abstand[2]={zahl[0]-zahl[2], zahl[1]-zahl[3]}; 
    if(abstand[0]==abstand[1]){
        if(zahl[0]-zahl[2]>0){
            abstand[0] = zahl[0]-zahl[2]-1;
            abstand[1] = zahl[1]-zahl[3]-1;
        }
        else{
            abstand[0] = zahl[0]-zahl[2]+1;
            abstand[1] = zahl[1]-zahl[3]+1;
        }
        int dazwischen=0;
        for(int i=abstand[0]; i!=0; (zahl[0]-zahl[2]<0) ? i++ : i--)
            if(felt[zahl[0]+i][zahl[1]+i]==0)
                dazwischen+=1;
        if(dazwischen==(abstand[0]<0 ? -abstand[0] : abstand[0]))
            if(farben(felt[zahl[2]][zahl[3]], farbe)==false)
                return true;

    }
    if(abstand[0]==(abstand[1]*-1)){
        if(zahl[0]-zahl[2]<0){
            abstand[0] = zahl[0]-zahl[2]+1;
            abstand[1] = zahl[1]-zahl[3]-1;
        }
        else{
            abstand[0] = zahl[0]-zahl[2]-1;
            abstand[1] = zahl[1]-zahl[3]+1;
        }
        int dazwischen=0;
        for(int i=abstand[0]; i!=0; (zahl[0]-zahl[2]<0) ? i++ : i--)
            if(felt[zahl[0]-i][zahl[1]+i]==0)
                dazwischen+=1;
        if(dazwischen==(abstand[0]<0 ? abstand[1] : abstand[0]))
            if(farben(felt[zahl[2]][zahl[3]], farbe)==false)
                return true;
    }
    return false;
}

bool fperd(int felt[8][8], int zahl[4], int farbe){
    for(int i : {-2, 2})
        for(int j : {-1, 1})
            if((zahl[0]==zahl[2]+i) && (zahl[1]==zahl[3]+j))
                return true;
            else if((zahl[0]==zahl[2]+j) && (zahl[1]==zahl[3]+i))
                return true;
    return false;
}

bool echt_zug(int felt[8][8], int Zahl[4], int farbe, bool ifcompi, int& onpassenttester){
    static int onpassent=8;
    if(onpassenttester==0)
        onpassent=8;
    for(int i=0; i<4; i++)
        if(!(Zahl[i]>=0) && !(Zahl[i]<8)){
            if(ifcompi==false)
                 cout << "du darfst das nicht machen.\n";
            return false;
        }
    if(farben(felt[Zahl[0]][Zahl[1]], farbe)==true){
        if(!((Zahl[0]==Zahl[2]) && (Zahl[1]==Zahl[3]))){
            switch(felt[Zahl[0]][Zahl[1]]){
                case  6:
                    if(bauer(felt, Zahl, 1, onpassent, onpassenttester)==true){
                        fuenfzig_zuege_regel(0);
                        return true;
                    }
                    break;
                case -6:
                    if(bauer(felt, Zahl,-1, onpassent, onpassenttester)==true){
                        fuenfzig_zuege_regel(0);
                        return true;
                    }
                    break;
                case  5:
                    if((Koenig(felt, Zahl, 1)==true)
                    || (rokade(felt, Zahl, true)==true))
                        return true;
                    break;
                case -5:
                    if((Koenig(felt, Zahl,-1)==true)
                    || (rokade(felt, Zahl, true)==true))
                        return true;
                    break;
                case  4:
                    if((  turm(felt, Zahl,-1)==true)
                    || (leufer(felt, Zahl,-1)==true))
                        return true;
                    break;
                case -4:
                    if((  turm(felt, Zahl, 1)==true)
                    || (leufer(felt, Zahl, 1)==true))
                        return true;
                    break;
                case  3:
                    if(  turm(felt, Zahl, 1)==true)
                        return true;
                    break;
                case -3:
                    if(  turm(felt, Zahl,-1)==true)
                        return true;
                    break;
                case  2:
                    if(leufer(felt, Zahl, 1)==true)
                        return true;
                    break;
                case -2:
                    if(leufer(felt, Zahl,-1)==true)
                        return true;
                    break;
                case  1:
                    if( fperd(felt, Zahl, 1)==true)
                        return true;
                    break;
                case -1:
                    if( fperd(felt, Zahl,-1)==true)
                        return true;
                    break;
                }
            }
        }
    if(ifcompi==false)
        cout << "du darfst das nicht machen\n";
    return false;
}
