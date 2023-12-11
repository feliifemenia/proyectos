/*
    Id.Programa: TP2V_K1092G1-Lucas Fiscella.cpp
    Autores....: Lucas Fiscella, Felipe Femenia, Tomas Pralong, Bautista Iglesias Basso
    Fecha......: Noviembre 2023
    Actividad..: Trabajo Practico 2, Turno de Medicos.
*/

#include <fstream.h>
#include<iomanip.h>

using namespace std;


//------COMIENZA ESTRCUTURAS NODOS-----
typedef char str20[21];
typedef char str15[16];
const MAX_ESPECIALIDADES = 20;
const MAX_MED = 60;

//Nodo SubLista
struct sInfoSub{
    str15 ObraSoc;
    int NroCred;
    short Horario;
};

typedef sInfoSub tInfoSub;



struct sNodoSec{
    tInfoSub tInfo;
    sNodoSec * sgte;
};

typedef struct sNodoSec * tLstSub;

//Nodo ListaPrincipal

struct sInfo{
    short Dia;
    tLstSub SubLista; //Puntero sublista
};

typedef sInfo tInfo;

struct sNodoPrin{
    tInfo Info;
    sNodoPrin * sgte;
};

typedef struct sNodoPrin * tLstPrin;


struct sDatosPun{
    str20 Esp;
    tLstPrin pEsp;
};

typedef sDatosPun vrpEsp[MAX_ESPECIALIDADES];

//--------------ESTRUCTURAS DE ARCH BIN--------

struct tsMed{
    str20 apeNom;
    int nroMat;
    str20 nomEsp;
    char turno;
};

typedef tsMed tvrMed[MAX_MED];//VECTOR DE REGISTROS

struct tsTurnDiaHora{
    str20 nomEsp;
    short dia,
          hora,
          mins;
    str15 nomOsoc;
    int nroCred;
};

struct tsSol{
    str20 apeNom;
    short edad;
    str15 nomOsoc;
    int nroCred;
    str20 nomEsp;
    short dia;
    char Turno;
};

//----------FINALIZA LAS ESTRUCTURAS-----------------

//----------COMIENZA ESPECIALIDADES.DAT--------------
void InicVEsp(vrpEsp Vector){

    for(short i=0; i <= MAX_ESPECIALIDADES-1;i++){
        strcpy(Vector[i].Esp,"*");
        Vector[i].pEsp = NULL;
    }
}

void intcmbVesp(str20 &vesp, str20 &vesp2){
    str20 aux;

    strcpy(aux,vesp);
    strcpy(vesp,vesp2);
    strcpy(vesp2,aux);
}

void ordxBurVesp(vrpEsp vEspecialidades, int cantEsp){//FUNCION PARA ORDENAR EL VECTOR DE CADENAS DE MANERA ASCENDENTE (NO POR ORDEN ALFABETICO)
    int k = 0;
    bool ordenado;
    do {

        ordenado = true;
        k = k + 1;
        for (int i = 0; i < cantEsp - k; i++) {

            if (strcmp(vEspecialidades[i].Esp, vEspecialidades[i + 1].Esp) > 0) {
                ordenado = false;
                intcmbVesp(vEspecialidades[i].Esp, vEspecialidades[i + 1].Esp);
            }
        }
    } while (ordenado == false);
}

void ProcEspecialidades(ifstream &Esp, vrpEsp Vector,int &CantEsp){
    str20 vAux;

    InicVEsp(Vector);

    Esp.read((char*)vAux, sizeof vAux);

    while(!Esp.eof()){
        strcpy(Vector[CantEsp].Esp,vAux);
        CantEsp++;
        Esp.read((char*)vAux, sizeof vAux);
    }
    ordxBurVesp(Vector,CantEsp);

}

//----------FINALIZA ESPECIALIDADES.DAT-------

//----------COMIENZA MEDICOS.DAT--------------

void InicReg(tsMed vrMedicos[]) { //INICIALIZA EL VECTOR DE REGISTROS (vrMedicos)
    for (int i = 0; i < MAX_MED; i++) {
        strcpy(vrMedicos[i].apeNom, "");
        vrMedicos[i].nroMat = 0;
        strcpy(vrMedicos[i].nomEsp, "");
        vrMedicos[i].turno = '*';
    }
}

void intCmbMed(tvrMed vrMedicos, int i){
    tsMed rAux;

    rAux = vrMedicos[i];
    vrMedicos[i] = vrMedicos[i+1];
    vrMedicos[i+1] = rAux;
}

void ordBurMed(tvrMed vrMedicos, int cantMed){
    int k = 0;
    bool ordenado;
    do {
        ordenado = true;
        k = k + 1;

        for (int i = 0; i < cantMed - k; i++) {
            if (strcmp(vrMedicos[i].nomEsp, vrMedicos[i + 1].nomEsp) > 0) {
                ordenado = false;
                intCmbMed(vrMedicos, i);
            }
            else if(strcmp(vrMedicos[i].nomEsp, vrMedicos[i + 1].nomEsp) == 0 && (vrMedicos[i].turno == 'T' && vrMedicos[i + 1].turno == 'M' || vrMedicos[i].turno == 'N' && vrMedicos[i + 1].turno == 'M' || vrMedicos[i].turno == 'N' && vrMedicos[i + 1].turno == 'T')){
                ordenado = false;
                intCmbMed(vrMedicos, i);
            }
        }
    } while (ordenado == false);
}

short busBinNomMed(int cantMed, tsSol sTurnAux, tvrMed vrMedicos){
    int inicio = 0;
    int fin = cantMed - 1;

    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;

        int cmp = strcmp(vrMedicos[medio].nomEsp, sTurnAux.nomEsp);

        if (cmp == 0) {
            if (sTurnAux.Turno == vrMedicos[medio].turno) {
                return medio;
            } else if (sTurnAux.Turno == 'M' && (vrMedicos[medio].turno == 'T' || vrMedicos[medio].turno == 'N')) {
                fin = medio - 1;
            } else if (sTurnAux.Turno == 'T' && vrMedicos[medio].turno == 'N') {
                fin = medio - 1;
            } else if (vrMedicos[medio].turno == 'M' && (sTurnAux.Turno == 'T' || sTurnAux.Turno == 'N')){
                inicio = medio + 1;
            } else if (sTurnAux.Turno == 'N' && (vrMedicos[medio].turno == 'T'||vrMedicos[medio].turno == 'M')){
                inicio = medio + 1;
            }
        } else if (cmp > 0) {
            fin = medio - 1;
        } else {
            inicio = medio + 1;
        }
    }
    return -1;
}

//-------------FINALIZAN MEDICOS.DAT----------------------

//-------------COMIENZAN FUNCIONES SWITCH-----------------

short procHorario(tsTurnDiaHora rDatosAux){
    short m;
    int horaMil = rDatosAux.hora * 100;
    horaMil = horaMil + rDatosAux.mins;

    switch(horaMil){
    case 800: m = 0; break; case 830: m = 1; break; case 900: m = 2; break;
    case 930: m = 3; break; case 1000: m = 4; break; case 1030: m = 5; break;
    case 1100: m = 6; break; case 1130: m = 7; break; case 1200: m = 8; break;
    case 1230: m = 9; break; case 1300: m = 10; break; case 1330: m = 11; break;
    case 1400: m = 12; break; case 1430: m = 13; break; case 1500: m = 14; break;
    case 1530: m = 15; break; case 1600: m = 16; break; case 1630: m = 17; break;
    case 1700: m = 18; break; case 1730: m = 19; break; case 1800: m = 20; break;
    case 1830: m = 21; break; case 1900: m = 22; break; case 1930: m = 23; break;
    }
return m;
}

short obtenerHorario(tsSol sTurnAux){
    int k;
    switch (sTurnAux.Turno){
    case 'M':
        k = 0;
    break;
    case 'T':
        k = 8;
    break;
    case 'N':
        k = 16;
    break;
    }
return k;
}

void procContraHorario(int HorarioReal, char HoMi[]){
    char Hora[2], Minuto[2];

    switch(HorarioReal){
    case 0: Hora[0]='0'; Hora[1] = '8'; Minuto[0]='0'; Minuto[1]='0'; break; case 1: Hora[0]='0'; Hora[1] = '8'; Minuto[0]='3'; Minuto[1]='0'; break;
    case 2: Hora[0]='0'; Hora[1] = '9'; Minuto[0]= '0'; Minuto[1]= '0'; break; case 3:Hora[0]='0'; Hora[1] = '9'; Minuto[0]='3'; Minuto[1]='0'; break;
    case 4: Hora[0] = '1'; Hora[1] = '0'; Minuto[0]='0'; Minuto[1]='0'; break; case 5:Hora[0] = '1'; Hora[1] = '0'; Minuto[0]='3'; Minuto[1]='0'; break;
    case 6: Hora[0] = '1'; Hora[1] = '1'; Minuto[0]='0'; Minuto[1]='0'; break; case 7:Hora[0] = '1'; Hora[1] = '1'; Minuto[0]='3'; Minuto[1]='0'; break;
    case 8: Hora[0] = '1'; Hora[1] = '2'; Minuto[0]='0'; Minuto[1]='0'; break; case 9:Hora[0] = '1'; Hora[1] = '2'; Minuto[0]='3'; Minuto[1]='0'; break;
    case 10: Hora[0] = '1'; Hora[1] = '3'; Minuto[0]='0'; Minuto[1]='0'; break; case 11:Hora[0] = '1'; Hora[1] = '3'; Minuto[0]='3'; Minuto[1]='0'; break;
    case 12: Hora[0] = '1'; Hora[1] = '4'; Minuto[0]='0'; Minuto[1]='0'; break; case 13:Hora[0] = '1'; Hora[1] = '4'; Minuto[0]='3'; Minuto[1]='0'; break;
    case 14: Hora[0] = '1'; Hora[1] = '5'; Minuto[0]='0'; Minuto[1]='0'; break; case 15:Hora[0] = '1'; Hora[1] = '5'; Minuto[0]='3'; Minuto[1]='0'; break;
    case 16: Hora[0] = '1'; Hora[1] = '6'; Minuto[0]='0'; Minuto[1]='0'; break; case 17:Hora[0] = '1'; Hora[1] = '6'; Minuto[0]='3'; Minuto[1]='0'; break;
    case 18: Hora[0] = '1'; Hora[1] = '7'; Minuto[0]='0'; Minuto[1]='0'; break; case 19:Hora[0] = '1'; Hora[1] = '7'; Minuto[0]='3'; Minuto[1]='0'; break;
    case 20: Hora[0] = '1'; Hora[1] = '8'; Minuto[0]='0'; Minuto[1]='0'; break; case 21:Hora[0] = '1'; Hora[1] = '8'; Minuto[0]='3'; Minuto[1]='0'; break;
    case 22: Hora[0] = '1'; Hora[1] = '9'; Minuto[0]='0'; Minuto[1]='0'; break; case 23:Hora[0] = '1'; Hora[1] = '9'; Minuto[0]='3'; Minuto[1]='0'; break;
    }
    HoMi[0] = Hora[0];
    HoMi[1] = Hora[1];
    HoMi[2] = ':';
    HoMi[3] = Minuto[0];
    HoMi[4] = Minuto[1];
}
//-------------FINALIZAN FUNCIONES SWITCH-----------------

//-------------COMIENZAN FUNCIONES DE NODOS---------------
tLstPrin existeNodo(tLstPrin &lista, tLstPrin &pAnt,short vClv){

tLstPrin pAct = lista;
pAnt = NULL;

    while(pAct!=NULL && vClv > pAct -> Info.Dia){
        pAnt = pAct;
        pAct = pAct->sgte;
    }
    if(pAct!=NULL && vClv == pAct ->Info.Dia){
        return pAct;
    }
    else{
        return NULL;
    }
}

tLstSub ExisteNodoTurno(tLstSub &lista,tLstSub &pAnt,int vClv){

tLstSub pAct = lista;
pAnt = NULL;

    while(pAct!=NULL && vClv > pAct -> tInfo.Horario){
        pAnt = pAct;
        pAct = pAct->sgte;
    }
    if(pAct!=NULL && vClv == pAct -> tInfo.Horario){
        return pAct;
    }
    else{
        return NULL;
    }
}

void InsertaInicio(tLstPrin &lista,tInfo Valor){

   tLstPrin pNvo = new sNodoPrin;
   pNvo -> Info = Valor;
   pNvo -> sgte = lista;
   lista = pNvo;

}

void InsertaInicioTurno(tLstSub &lista,tInfoSub Paquete){

    tLstSub pNvo = new sNodoSec;
    pNvo -> tInfo = Paquete;
    pNvo -> sgte = lista;
    lista = pNvo;
}

void InsertaEnLugar(tLstPrin &pAnt,tInfo Valor){
   tLstPrin pNvo = new sNodoPrin;
   pNvo -> Info = Valor;
   pNvo -> sgte = pAnt -> sgte;
   pAnt -> sgte = pNvo;
}

void InsertaEnLugarTurno(tLstSub &pAnt,tInfoSub Valor){
   tLstSub pNvo = new sNodoSec;
   pNvo -> tInfo = Valor;
   pNvo -> sgte = pAnt -> sgte;
   pAnt -> sgte = pNvo;
}

void InsertaEnFin(tLstSub &pAct,tInfoSub Valor){
   tLstSub pNvo = new sNodoSec;

   pNvo -> tInfo = Valor;
   pAct -> sgte = pNvo;
   pNvo -> sgte = NULL;
   pAct = pNvo;
}

void CrearNodoDia(tLstPrin &lista,tLstPrin &pAnt,tInfo valor){

    if( pAnt == NULL ){
        InsertaInicio(lista,valor);
    }
    else{
        InsertaEnLugar(pAnt,valor);
    }
}

void CrearNodoTurno(tLstSub &lista,tLstSub &pAnt,tInfoSub valor){

    if(pAnt == NULL){
        InsertaInicioTurno(lista,valor);
    }
    else{
        InsertaEnLugarTurno(pAnt,valor);
    }
}

void SacarNodoDia(tLstPrin &pAct,sInfo &Valor){

    Valor = pAct -> Info;
    pAct = pAct -> sgte;

}

void SacarNodoTurno(tLstSub &pAct,tInfoSub &Valor){

    Valor = pAct -> tInfo;
    pAct = pAct -> sgte;

}

void ElimNodoTurno(tLstSub &pAnt,tLstSub &pAct){
    pAnt = pAct;
    pAct = pAct -> sgte;
    delete pAnt;
}

void ElimNodoDia(tLstPrin &pAntPrin,tLstPrin &pActPrin){
    pAntPrin = pActPrin;
    pActPrin = pActPrin -> sgte;
    delete pAntPrin;
}

//---------------FINALIZAN FUNCIONES DE NODOS------------

int busBinEsp(vrpEsp vEsp, int fin, str20 elemento) {//Funcion para buscar la posicion de la especialidad en el vector de punteros de especialidad.
   int inicio = 0;
    while (inicio <= fin) {
    int medio = (inicio + fin) / 2;

        if (strcmp(vEsp[medio].Esp, elemento) == 0) {
            return medio;
        }

        else if (strcmp(vEsp[medio].Esp, elemento) < 0) {
            inicio = medio + 1;

        }
        else
            fin = medio - 1;
    }
    return -1;
}

void FuncionRepetido(tLstSub &pAct,tLstSub &pAnt,tInfoSub Paquete,short vClv){

    while(pAct -> sgte != NULL && pAct -> sgte -> tInfo.Horario == vClv + 1){
    pAnt = pAct;
    pAct = pAct -> sgte;
    vClv++;
    Paquete.Horario = vClv;
    }

        if(pAct -> sgte == NULL){

            vClv++;
            Paquete.Horario = vClv;
            InsertaEnFin(pAct,Paquete);
        }
        else{
            pAnt = pAct;
            pAct = pAct -> sgte;
            vClv++;
            Paquete.Horario = vClv;
            InsertaEnLugarTurno(pAnt,Paquete);
        }
}

void ProcTurnos(ifstream &TurnosDiaHora,vrpEsp pVec, int cantEsp){

    tInfoSub PaqueteTurno;
    tInfo PaqueteDia;
    tsTurnDiaHora turnDiaAux;
    short Hora;
    tLstPrin pEspAct,
             pEspAnt= NULL;
    tLstSub pAct = NULL,
            pSubAnt = NULL;

    TurnosDiaHora.read( (char*) &turnDiaAux,sizeof turnDiaAux);

    while(!TurnosDiaHora.eof()){


              Hora = procHorario(turnDiaAux);
        int posEsp = busBinEsp(pVec,cantEsp-1,turnDiaAux.nomEsp);

        pEspAct = existeNodo(pVec[posEsp].pEsp,pEspAnt,turnDiaAux.dia);

        if(pEspAct == NULL){//preguntamos existe nodo Dia

            PaqueteDia.Dia = turnDiaAux.dia; //Armamos PaqueteDia
            PaqueteDia.SubLista = NULL;

            PaqueteTurno.Horario = Hora; //Armamos PaqueteTurno
            PaqueteTurno.NroCred = turnDiaAux.nroCred;
            strcpy(PaqueteTurno.ObraSoc,turnDiaAux.nomOsoc);


            CrearNodoDia(pVec[posEsp].pEsp,pEspAnt,PaqueteDia);

            if(pEspAnt){
                InsertaInicioTurno(pEspAnt -> sgte -> Info.SubLista,PaqueteTurno);
            }
            else{
                InsertaInicioTurno(pVec[posEsp].pEsp -> Info.SubLista,PaqueteTurno);
            }
       }
        else{
            pAct = ExisteNodoTurno(pEspAct -> Info.SubLista,pSubAnt,Hora);


                if(pAct == NULL){

                    PaqueteTurno.Horario = Hora; //Armamos PaqueteTurno
                    PaqueteTurno.NroCred = turnDiaAux.nroCred;
                    strcpy(PaqueteTurno.ObraSoc,turnDiaAux.nomOsoc);

                    CrearNodoTurno(pVec[posEsp].pEsp -> Info.SubLista,pSubAnt,PaqueteTurno);

                }
                else{

                    PaqueteTurno.Horario = Hora; //Armamos PaqueteTurno
                    PaqueteTurno.NroCred = turnDiaAux.nroCred;
                    strcpy(PaqueteTurno.ObraSoc,turnDiaAux.nomOsoc);

                    FuncionRepetido(pAct,pSubAnt,PaqueteTurno,Hora);

                }

        }

        TurnosDiaHora.read( (char*) &turnDiaAux,sizeof turnDiaAux);
    }
}

void EmitirListado(ofstream &Listado, vrpEsp vpEsp) {
    char Hora[5];
    tLstPrin pActPrin = NULL;
    short Dia;
    sInfo PaqueteDia;
    tInfoSub PaqueteTurno;

    Listado << std::left << setw(18) << "Especialidades: " << "Dia: " << "Hora: " << "ObraSoc: " << "     NroCred:" << endl;

    for(short i = 0 ; i <= MAX_ESPECIALIDADES-1 ; i++){

        pActPrin = vpEsp[i].pEsp;

        while(pActPrin){

            SacarNodoDia(pActPrin,PaqueteDia);

            while(PaqueteDia.SubLista != NULL){

                SacarNodoTurno(PaqueteDia.SubLista,PaqueteTurno);
                procContraHorario(PaqueteTurno.Horario,Hora);

                if(PaqueteDia.Dia < 10){
                    Listado << vpEsp[i].Esp << ' ' << '0' << PaqueteDia.Dia << ' ' << Hora[0] << Hora[1] << Hora[2] << Hora[3] << Hora[4] << ' ' << PaqueteTurno.ObraSoc << ' ' <<PaqueteTurno.NroCred << endl;
                }
                else{
                    Listado << vpEsp[i].Esp << ' ' << PaqueteDia.Dia << ' ' << Hora[0] << Hora[1] << Hora[2] << Hora[3] << Hora[4] << ' ' << PaqueteTurno.ObraSoc << ' ' <<PaqueteTurno.NroCred << endl;
                }

            }
        }
    }
}//EMITIR LISTADO 1 Y 3

void ProcMedicos(ifstream &Medicos,tvrMed Med, int &CantMed){
    tsMed rMedAux;

    InicReg(Med);//Inicializo vrMED

    Medicos.read((char*)&rMedAux, sizeof rMedAux);

    while(!Medicos.eof()){

        strcpy(Med[CantMed].apeNom,rMedAux.apeNom);
        Med[CantMed].nroMat = rMedAux.nroMat;
        strcpy(Med[CantMed].nomEsp,rMedAux.nomEsp);
        Med[CantMed].turno = rMedAux.turno;
        CantMed++;
        Medicos.read((char*)&rMedAux,sizeof rMedAux);
    }
    ordBurMed(Med,CantMed);
}//PROCMEDICOS

void EmiteListado2(ofstream &Listado,tsSol rSolAux,short PosMed,tInfoSub PaqueteTurno,tvrMed Medicos){

char Hora[5];
    procContraHorario(PaqueteTurno.Horario,Hora);

    Listado << rSolAux.apeNom << ' ' << rSolAux.nomOsoc << ' ' << rSolAux.nroCred << ' ' << rSolAux.nomEsp << ' ';
        if(rSolAux.dia < 10){
            Listado << '0' << rSolAux.dia << ' ';
        }
        else{
            Listado << rSolAux.dia << ' ';
        }
            Listado << Hora[0] << Hora[1] << Hora[2]<< Hora [3] << Hora[4] << ' ' << Medicos[PosMed].apeNom << endl;
}//EMITE LISTADO 2

void ProcTurNuevos(ifstream &SolTur,ofstream &Listado,tvrMed Med,int &CantMed,vrpEsp pVec, short cantEsp){
    tsSol rSolAux;
    tInfoSub PaqueteTurno;
    tInfo PaqueteDia;
    tLstPrin pEspAct,
             pEspAnt= NULL;
    tLstSub pAct = NULL,
            pSubAnt = NULL;

    SolTur.read( (char*) &rSolAux,sizeof rSolAux);


    Listado <<"\nApeNom:              " << "O.Soc:        " << "NroCred: " << setw(15) << "Especialidad:      " << "Dia: " << "Hora: " << "Medico:" << endl;
    while(!SolTur.eof()){
        short Hora = obtenerHorario(rSolAux);
        short posMed = busBinNomMed(CantMed,rSolAux,Med);
          int posEsp = busBinEsp(pVec,cantEsp-1,rSolAux.nomEsp);

    tLstPrin pEspAct = existeNodo(pVec[posEsp].pEsp,pEspAnt,rSolAux.dia);

            PaqueteDia.Dia = rSolAux.dia; //Armamos PaqueteDia
            PaqueteDia.SubLista = NULL;
            PaqueteTurno.Horario = Hora; //Armamos PaqueteTurno
            PaqueteTurno.NroCred = rSolAux.nroCred;
            strcpy(PaqueteTurno.ObraSoc,rSolAux.nomOsoc);
        if(pEspAct == NULL){//preguntamos si ya esa posicion de especialidad esta enlazada a una lista

            CrearNodoDia(pVec[posEsp].pEsp,pEspAnt,PaqueteDia);
            if(pEspAnt){
                InsertaInicioTurno(pEspAnt -> sgte -> Info.SubLista,PaqueteTurno);
            }
            else{
                InsertaInicioTurno(pVec[posEsp].pEsp -> Info.SubLista,PaqueteTurno);
            }
       }
        else{
            pAct = ExisteNodoTurno(pEspAct -> Info.SubLista,pSubAnt,Hora);
                if(pAct == NULL){
                    CrearNodoTurno(pVec[posEsp].pEsp -> Info.SubLista,pSubAnt,PaqueteTurno);
                }
                else{
                    FuncionRepetido(pAct,pSubAnt,PaqueteTurno,Hora);
                }
        }
        EmiteListado2(Listado,rSolAux,posMed,PaqueteTurno,Med);
        SolTur.read( (char*) &rSolAux,sizeof rSolAux);
    }
     Listado << endl;
}//PROC TURNOS NUEVOS

void ElimNodos(vrpEsp vpEsp){

tLstPrin pActPrin,
        pAntPrin;
tLstSub pActSec,
        pAntSec;
    for(register int i = 0; i<= MAX_ESPECIALIDADES - 1 ; i++){

        pActPrin = vpEsp[i].pEsp;
        while(pActPrin){
            pActSec = pActPrin -> Info.SubLista;
            while(pActSec){
                ElimNodoTurno(pAntSec,pActSec);
            }
            ElimNodoDia(pAntPrin,pActPrin);
        }
    }
}//ELIMINA NODOS

void CerrarArch(ifstream &Esp,ifstream &Medicos,ifstream &TurnosDiaHora,ifstream &SolTur,ofstream &Listado){

Esp.close();
Medicos.close();
TurnosDiaHora.close();
SolTur.close();
Listado.close();
}

main(){
    ifstream Esp("Especialidades.dat",ios::binary);
    ifstream Medicos("Medicos.dat",ios::binary);
    ifstream TurnosDiaHora("TurnosDiaHora.dat",ios::binary);
    ifstream SolTur("SolicitudTurnos.Dat",ios::binary);
    ofstream Listado("Listado.txt");

    tvrMed Med;

    int cantEsp = 0,
        CantMed = 0;
    vrpEsp vpEsp;
    tLstPrin pNvo;
    tLstSub pNvoSec;


    ProcEspecialidades(Esp,vpEsp,cantEsp);
    ProcMedicos(Medicos,Med,CantMed);
    ProcTurnos(TurnosDiaHora,vpEsp,cantEsp);
    EmitirListado(Listado,vpEsp);
    ProcTurNuevos(SolTur,Listado,Med,CantMed,vpEsp,cantEsp);
    EmitirListado(Listado,vpEsp);
    ElimNodos(vpEsp);
    CerrarArch(Esp,Medicos,TurnosDiaHora,SolTur,Listado);

return 0;
}
