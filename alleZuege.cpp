#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

#include "echt_zug.h"
#include "stet_der_koenig_schach.h"
#include "zugmacher.h"
#include "feld.h"

using namespace std;

bool ok(const position& pos, zuege& zug, vector<zuege>& zugliste, int i, int j){
    zug.Zahl[2]=zug.Zahl[0]+i;
    zug.Zahl[3]=zug.Zahl[1]+j;
    if(zug.Zahl[2]<0 || zug.Zahl[2]>7)
        return false;
    if(zug.Zahl[3]<0 || zug.Zahl[3]>7)
        return false;
    if(pos.felt[zug.Zahl[2]][zug.Zahl[3]]*pos.farbe>0)
        return false;
    if(pos.felt[zug.Zahl[0]][zug.Zahl[1]]*pos.farbe==1){
        position pos2 = pos;
        zugmacher(pos2, zug);
        if(stet_der_koenig_schach(pos2)==true)
            return false;
        zugliste.push_back(zug);
        return true;
    }else{
        if(echt_zug(pos, zug, false)==true){
            position pos2 = pos;
            zugmacher(pos2, zug);
            if(stet_der_koenig_schach(pos2)==true)
                return false;
            zugliste.push_back(zug);
            return true;
        }
        return false;
    }
}

vector<zuege> alleZuege(const position& pos, int alphabeta_katofs){
    zuege zug = {};
    zuege zug2;
    vector<zuege> zugliste;
    for(zug.Zahl[1]=0; zug.Zahl[1]<8; zug.Zahl[1]++)
        for(zug.Zahl[0]=0; zug.Zahl[0]<8; zug.Zahl[0]++)
        {
            if (pos.felt[zug.Zahl[0]][zug.Zahl[1]]*pos.farbe<=0)
                continue;

            //pferd
            if(pos.felt[zug.Zahl[0]][zug.Zahl[1]]*pos.farbe==1){
                for(int i:{1, -1})
                    for(int j:{2, -2})
                        ok(pos, zug, zugliste, i, j);
                for(int i:{2, -2})
                    for(int j:{1, -1})
                        ok(pos, zug, zugliste, i, j);
                continue;
            }


            zug2 = zug;
            //koenig
            if(pos.felt[zug.Zahl[0]][zug.Zahl[1]]*pos.farbe==5){
                for(int i=-1; i<2; i++)
                    for(int j=-1; j<2; j++){
                        ok(pos, zug2, zugliste, i, j);
                    }
                ok(pos, zug2, zugliste,  0,  2);
                ok(pos, zug2, zugliste,  0, -2);
                continue;
            }

            //bauer
            if(pos.felt[zug.Zahl[0]][zug.Zahl[1]]*pos.farbe==6){
                for(int j=-1; j<2; j++){
                    if(ok(pos, zug2, zugliste, 1*pos.farbe, j)==true){
                       if(zugliste[zugliste.size()-1].promotion==1){
                           zugliste[zugliste.size()-1].promotion=1*pos.farbe;
                           for(int k=2; k<=4; k++){
                               zug2.promotion=k*pos.farbe;
                               zugliste.push_back(zug2);
                           }
                        }
                    }
                }
                ok(pos, zug2, zugliste,  2*pos.farbe,  0);
                continue;
            }

            //turm
            if(pos.felt[zug2.Zahl[0]][zug2.Zahl[1]]*pos.farbe==3){
                for(int i=-zug2.Zahl[0]; i<8-zug2.Zahl[0]; i++)
                    ok(pos, zug, zugliste, i, 0);
                for(int i=-zug2.Zahl[1]; i<8-zug2.Zahl[1]; i++)
                    ok(pos, zug, zugliste, 0, i);
                continue;
            }

            //leufer
            if(pos.felt[zug2.Zahl[0]][zug2.Zahl[1]]*pos.farbe==2){
                for(int i=-7; i<8; i++)
                    ok(pos, zug, zugliste, i, i);
                for(int i=-7; i<8; i++)
                    ok(pos, zug, zugliste, -i, i);
                continue;
            }

            //dame
            if(pos.felt[zug2.Zahl[0]][zug2.Zahl[1]]*pos.farbe==4){
                for(int i=-7; i<8; i++)
                    ok(pos, zug, zugliste, i, i);
                for(int i=-7; i<8; i++)
                    ok(pos, zug, zugliste, -i, i);
                for(int i=-zug2.Zahl[0]; i<8-zug2.Zahl[0]; i++)
                    ok(pos, zug, zugliste, i, 0);
                for(int i=-zug2.Zahl[1]; i<8-zug2.Zahl[1]; i++)
                    ok(pos, zug, zugliste, 0, i);
                continue;
            }
        }

    int linie[8]={5, 10, 25, 50, 50, 25, 10, 5};
    for(unsigned int i=0; i<zugliste.size(); i++){
       if (pos.felt[zugliste[i].Zahl[2]][zugliste[i].Zahl[3]]!=0)
           zugliste[i].wert+=200;
       if (pos.felt[zugliste[i].Zahl[0]][zugliste[i].Zahl[1]]==6)
           zugliste[i].wert+=100;
       zugliste[i].wert+=linie[zugliste[i].Zahl[3]];
    }

    for(unsigned int i=0; i<zugliste.size(); i++)
       zugliste[i].wert*=alphabeta_katofs;


    std::sort(zugliste.begin(),zugliste.end(),[](zuege& a, zuege& b) {
        return b.wert < a.wert;   
    });
    return zugliste;
}
