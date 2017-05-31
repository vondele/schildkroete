#include <iostream>

#include "rokade.h"
#include "stet_der_koenig_schach.h"
#include "types.h"

using namespace std;

void testen_ob_man_es_darf(position& pos){
    if(pos.felt[0][0]!=3)
        pos.rokaden[1] = false;
    if(pos.felt[0][4]!=5){
        pos.rokaden[1] = false;
        pos.rokaden[0] = false;
    }
    if(pos.felt[0][7]!=3)
        pos.rokaden[0] = false;

    if(pos.felt[7][0]!=-3)
        pos.rokaden[3] = false;
    if(pos.felt[7][4]!=-5){
        pos.rokaden[3] = false;
        pos.rokaden[2] = false;
    }
    if(pos.felt[7][7]!=-3)
        pos.rokaden[2] = false;
}

bool rokade(position& pos, zuege& zug){
    testen_ob_man_es_darf(pos);
    position pos2 = pos;
    pos2.farbe*=-1;
    if(pos.farbe==1){
        if(((zug.Zahl[0]==0) && (zug.Zahl[1]==4))
        && ((zug.Zahl[2]==0) && (zug.Zahl[3]==2)))
            if((pos.felt[0][1]==0) && (pos.felt[0][2]==0) && (pos.felt[0][3]==0) && (stet_der_koenig_schach(pos2, 0, 3)==false) && (stet_der_koenig_schach(pos2, 0, 4)==false))
                if(pos.rokaden[1]==true){
                    zug.rokaden=2;
                    return true;
                }

        if(((zug.Zahl[0]==0) && (zug.Zahl[1]==4))
        && ((zug.Zahl[2]==0) && (zug.Zahl[3]==6)))
            if((pos.felt[0][5]==0) && (pos.felt[0][6]==0) && (stet_der_koenig_schach(pos2, 0, 4)==false) && (stet_der_koenig_schach(pos2, 0, 5)==false))
                if(pos.rokaden[0]==true){
                    zug.rokaden=1;
                    return true;
                }
        return false;
    }
    if(((zug.Zahl[0]==7) && (zug.Zahl[1]==4))
    && ((zug.Zahl[2]==7) && (zug.Zahl[3]==2)))
        if((pos.felt[7][1]==0) && (pos.felt[7][2]==0) && (pos.felt[7][3]==0) && (stet_der_koenig_schach(pos2, 7, 3)==false) && (stet_der_koenig_schach(pos2, 7, 4)==false))
            if(pos.rokaden[3]==true){
                zug.rokaden=4;
                return true;
            }

    if(((zug.Zahl[0]==7) && (zug.Zahl[1]==4))
    && ((zug.Zahl[2]==7) && (zug.Zahl[3]==6)))
        if((pos.felt[7][5]==0) && (pos.felt[7][6]==0) && (stet_der_koenig_schach(pos2, 7, 4)==false) && (stet_der_koenig_schach(pos2, 7, 5)==false))
            if(pos.rokaden[2]==true){
                zug.rokaden=3;
                return true;
            }
    return false;
}
