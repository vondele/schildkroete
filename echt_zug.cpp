#include "types.h"
#include "echt_zug.h"
#include "rokade.h"

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

void promovieren(const position& pos, zuege& zug){
    bool darf_man_promovieren=false;
    if((zug.Zahl[2]==0) && (pos.farbe==-1))
        darf_man_promovieren=true;
    if((zug.Zahl[2]==7) && (pos.farbe== 1))
        darf_man_promovieren=true;
    if(darf_man_promovieren==true)
            zug.promotion=1*pos.farbe;
}

bool wegnemen_von_enpassent(const position& pos, zuege& zug){
    if(pos.farbe== 1)
        if(pos.felt[4][pos.enpassent[0]]==-6)
            if(zug.Zahl[0]==4){
                zug.enpassent[2]=true;
                return true;
            }
    if(pos.farbe==-1)
        if(pos.felt[3][pos.enpassent[0]]== 6)
            if(zug.Zahl[0]==3){
                zug.enpassent[2]=true;
                return true;
            }
    return false;
}

bool bauer(const position& pos, zuege& zug){
    if(farben(pos.felt[zug.Zahl[2]][zug.Zahl[3]], pos.farbe*-1)==true){
        if((zug.Zahl[0]==(zug.Zahl[2]-pos.farbe)) && (zug.Zahl[1]==(zug.Zahl[3]-1))){
            promovieren(pos, zug);
            return true;
        }
        else if((zug.Zahl[0]==(zug.Zahl[2]-pos.farbe)) && (zug.Zahl[1]==(zug.Zahl[3]+1))){
            promovieren(pos, zug);
            return true;
        }
    }
    if(pos.felt[zug.Zahl[2]][zug.Zahl[3]]==0){
        if(zug.Zahl[1]==zug.Zahl[3]){
            if(zug.Zahl[0]==(zug.Zahl[2]-pos.farbe)){
                promovieren(pos, zug);
                return true;
            }
            if((zug.Zahl[0]==1) && (pos.farbe== 1) &&
               (pos.felt[2][zug.Zahl[1]]==0)){
                if(zug.Zahl[0]==(zug.Zahl[2]-2)){
                    zug.enpassent[1]=1;
                    zug.enpassent[0]=zug.Zahl[1];
                    return true;
                }
            }
            if((zug.Zahl[0]==6) && (pos.farbe==-1) &&
               (pos.felt[5][zug.Zahl[1]]==0)){
                if(zug.Zahl[0]==(zug.Zahl[2]+2)){
                    zug.enpassent[1]=1;
                    zug.enpassent[0]=zug.Zahl[1];
                    return true;
                }
            }
        }
    }
    if(zug.Zahl[3]==pos.enpassent[0] && pos.enpassent[1]==2){
        if((zug.Zahl[0]==(zug.Zahl[2]-pos.farbe)) && (zug.Zahl[1]==(zug.Zahl[3]-1))){
            if(wegnemen_von_enpassent(pos, zug)==true){
                return true;
            }
        }
        else if((zug.Zahl[0]==(zug.Zahl[2]-pos.farbe)) && (zug.Zahl[1]==(zug.Zahl[3]+1))){
            if(wegnemen_von_enpassent(pos, zug)==true)
                return true;
        }
    }
    return false;
}

bool Koenig(const position& pos, zuege& zug){
    if(farben(pos.felt[zug.Zahl[2]][zug.Zahl[3]], pos.farbe)==false)
        for(int i=-1; i<=1; i++)
            for(int j=-1; j<=1; j++)
                if((zug.Zahl[0]==(zug.Zahl[2]+i)) && (zug.Zahl[1]==(zug.Zahl[3]+j)))
                    return true;
    return false;
}

bool turm(const position& pos, zuege& zug){
    if(zug.Zahl[0]==zug.Zahl[2]){
        int abstand = zug.Zahl[1]-zug.Zahl[3]+1;
        if(zug.Zahl[1]-zug.Zahl[3]>0)
            abstand = zug.Zahl[1]-zug.Zahl[3]-1;
        int dazwischen=0;
        for(int i=abstand; i!=0; (zug.Zahl[1]-zug.Zahl[3]<0) ? i++ : i--)
            if(pos.felt[zug.Zahl[0]][zug.Zahl[3]+i]==0)
                dazwischen+=1;
        if(dazwischen==(abstand<0 ? -abstand : abstand))
            if(farben(pos.felt[zug.Zahl[2]][zug.Zahl[3]], pos.farbe)==false)
                return true;
    }
    if(zug.Zahl[1]==zug.Zahl[3]){
        int abstand = zug.Zahl[0]-zug.Zahl[2]+1;
        if(zug.Zahl[0]-zug.Zahl[2]>0)
            abstand = zug.Zahl[0]-zug.Zahl[2]-1;
        int dazwischen=0;
        for(int i=abstand; i!=0; (zug.Zahl[0]-zug.Zahl[2]<0) ? i++ : i--)
            if(pos.felt[zug.Zahl[2]+i][zug.Zahl[1]]==0)
                dazwischen+=1;
        if(dazwischen==(abstand<0 ? -abstand : abstand))
            if(farben(pos.felt[zug.Zahl[2]][zug.Zahl[3]], pos.farbe)==false)
                return true;
    }
    return false;
}

bool leufer(const position& pos, zuege& zug){
    int abstand[2]={zug.Zahl[0]-zug.Zahl[2], zug.Zahl[1]-zug.Zahl[3]}; 
    if(abstand[0]==abstand[1]){
        if(zug.Zahl[0]-zug.Zahl[2]>0){
            abstand[0] = zug.Zahl[0]-zug.Zahl[2]-1;
            abstand[1] = zug.Zahl[1]-zug.Zahl[3]-1;
        }
        else{
            abstand[0] = zug.Zahl[0]-zug.Zahl[2]+1;
            abstand[1] = zug.Zahl[1]-zug.Zahl[3]+1;
        }
        int dazwischen=0;
        for(int i=abstand[0]; i!=0; (zug.Zahl[0]-zug.Zahl[2]<0) ? i++ : i--)
        {
            if(pos.felt[zug.Zahl[0]-i][zug.Zahl[1]-i]==0)
                dazwischen+=1;
        }
        if(dazwischen==(abstand[0]<0 ? -abstand[0] : abstand[0]))
            if(farben(pos.felt[zug.Zahl[2]][zug.Zahl[3]], pos.farbe)==false)
                return true;

    }
    if(abstand[0]==(abstand[1]*-1)){
        if(zug.Zahl[0]-zug.Zahl[2]<0){
            abstand[0] = zug.Zahl[0]-zug.Zahl[2]+1;
            abstand[1] = zug.Zahl[1]-zug.Zahl[3]-1;
        }
        else{
            abstand[0] = zug.Zahl[0]-zug.Zahl[2]-1;
            abstand[1] = zug.Zahl[1]-zug.Zahl[3]+1;
        }
        int dazwischen=0;
        for(int i=abstand[0]; i!=0; (zug.Zahl[0]-zug.Zahl[2]<0) ? i++ : i--)
            if(pos.felt[zug.Zahl[0]-i][zug.Zahl[1]+i]==0)
                dazwischen+=1;
        if(dazwischen==(abstand[0]<0 ? abstand[1] : abstand[0]))
            if(farben(pos.felt[zug.Zahl[2]][zug.Zahl[3]], pos.farbe)==false)
                return true;
    }
    return false;
}

bool pferd(const position& pos, zuege& zug){
    if(farben(pos.felt[zug.Zahl[2]][zug.Zahl[3]], pos.farbe)==false)
        for(int i : {-2, 2})
            for(int j : {-1, 1}){
                if((zug.Zahl[0]==zug.Zahl[2]+i) && (zug.Zahl[1]==zug.Zahl[3]+j))
                    return true;
                else if((zug.Zahl[0]==zug.Zahl[2]+j) && (zug.Zahl[1]==zug.Zahl[3]+i))
                    return true;
                }
    return false;
}

bool echt_zug(const position& pos, zuege& zug, bool scachstehen){
        if(!((zug.Zahl[0]==zug.Zahl[2]) && (zug.Zahl[1]==zug.Zahl[3]))){
            switch(pos.felt[zug.Zahl[0]][zug.Zahl[1]]){
                case  6:
                case -6:
                    if(bauer(pos, zug)==true)
                        return true;
                    break;
                case  5:
                case -5:
                    if((Koenig(pos, zug)==true) || (scachstehen==false ? rokade(pos, zug)==true : scachstehen==false))
                        return true;
                    break;
                case  4:
                case -4:
                    if((  turm(pos, zug)==true)
                    || (leufer(pos, zug)==true))
                        return true;
                    break;
                case  3:
                case -3:
                    if(  turm(pos, zug)==true)
                        return true;
                    break;
                case  2:
                case -2:
                    if(leufer(pos, zug)==true)
                        return true;
                    break;
                case  1:
                case -1:
                    if( pferd(pos, zug)==true)
                        return true;
                    break;
            }
        }
    return false;
}
