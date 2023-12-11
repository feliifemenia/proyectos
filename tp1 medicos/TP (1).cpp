/*
    Id.Programa: G1Ej01a2.cpp
    Autores....: Lucas Fiscella, Felipe Femenia, Tomas Pralong, Bautista Iglesias Basso, Juan Ignacio Vivas
    Fecha......: Agosto 2023
    Actividad..: Trabajo Practico, Turno de Medicos.
*/

#include<iostream>
#include<fstream>
#include<string.h>
#include<cstring>
#include<iomanip.h>

using namespace std;

typedef char str20[21];
typedef char str15[16];

const int max_especialidades = 20,
          max_medicos = 100,
          max_dias = 31,
          max_horario = 24;

struct tsMed{
    str20 apeNom;
    int nroMat;
    str20 nomEsp;
    char turno;
};

struct tsTurn {
    str15 nomOsoc;
    int nroCred;
};

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
    int edad;
    str15 nomOsoc;
    int nroCred;
    str20 nomEsp;
    int dia;
    char Turno;
};

typedef tsTurn tTurnos[max_especialidades][max_dias][max_horario];

typedef tsMed tvrMed[max_medicos];//VECTOR DE REGISTROS

//PROCESAR ARCHIVO DE ESPECIALIDADES

bool leeUnaEsp(ifstream &especialidades, str20 &vAux){//LEE LAS LINEAS DEL ARCHIVO ESPECIALIDADES.TXT
    especialidades >> vAux;
    especialidades.ignore();

    return especialidades.good();
}

void iniVesp(str20 vEspecialidades[]){//INICIALIZAR EL VECTOR DE CADENAS vEspecialidades con "*"
    for(int i = 0; i< max_especialidades; i++){
     strcpy(vEspecialidades[i], "*");
  };
}

void acum(str20 vEspecialidades[], str20 &vAux, int &cantEsp){
    strcpy(vEspecialidades[cantEsp],vAux);
    cantEsp++;
}

void intcmbVesp(str20 &vesp, str20 &vesp2){
    str20 aux;

    strcpy(aux,vesp);
    strcpy(vesp,vesp2);
    strcpy(vesp2,aux);
}

void ordxBurVesp(str20 vEspecialidades[], int cantEsp){//FUNCION PARA ORDENAR EL VECTOR DE CADENAS DE MANERA ASCENDENTE (NO POR ORDEN ALFABETICO)
    int k = 0;
    bool ordenado;
    do {
        ordenado = true;
        k = k + 1;

        for (int i = 0; i < cantEsp - k; i++) {
            if (strcmp(vEspecialidades[i], vEspecialidades[i + 1]) > 0) {
                ordenado = false;
                intcmbVesp(vEspecialidades[i], vEspecialidades[i + 1]);
            }
        }
    } while (ordenado == false);
}


    void ProcEspecialidad(ifstream &especialidades, str20 vEspecialidades[], str20 &vAux, int &cantEsp){//FUNCION DONDE SE ENCUENTRAN TODAS LAS SUBFUNCIONES DE PORCESAR ARCHIVOS
    iniVesp(vEspecialidades);
    while(leeUnaEsp(especialidades,vAux)){
        acum(vEspecialidades, vAux, cantEsp);
        ordxBurVesp(vEspecialidades,cantEsp);
    }

}

//PROCESAR ARCHIVO DE MEDICOS.TXT

void InicReg(tsMed vrMedicos[]) { //INICIALIZA EL VECTOR DE REGISTROS (vrMedicos)
    for (int i = 0; i < max_medicos; i++) {
        strcpy(vrMedicos[i].apeNom, "");
        vrMedicos[i].nroMat = 0;
        strcpy(vrMedicos[i].nomEsp, "");
        vrMedicos[i].turno = '*';
    }
}

bool leeUnReg(ifstream &medicos, tsMed &rAux){//LEE LOS REGISTROS DEL ARCHIVO MEDICOS.TXT
    medicos.get(rAux.apeNom,20);
    medicos >> rAux.nroMat;
    medicos.ignore();
    medicos >> rAux.nomEsp;
    medicos.ignore();
    medicos >> rAux.turno;
    medicos.ignore();
return medicos.good();
}

short BusLinVec(tvrMed vrMedicos, tsMed rAux, int &cantMed){//BUSCA LA POSICION LIBRE EN vrMedicos
short i=0;

while (i<cantMed && vrMedicos[i].nroMat!=rAux.nroMat){
    i++;
}
return i;
}

void intCmbMed(tvrMed vrMedicos, int i){
    char turnAux;
    str20 nEspAux,
          apeNomAux;
    int nromataux;

    turnAux = vrMedicos[i].turno;
    vrMedicos[i].turno = vrMedicos[i+1].turno;
    vrMedicos[i+1].turno = turnAux;

    strcpy(nEspAux, vrMedicos[i].nomEsp);
    strcpy(vrMedicos[i].nomEsp, vrMedicos[i+1].nomEsp);
    strcpy(vrMedicos[i+1].nomEsp, nEspAux);

    strcpy(apeNomAux, vrMedicos[i].apeNom);
    strcpy(vrMedicos[i].apeNom, vrMedicos[i+1].apeNom);
    strcpy(vrMedicos[i+1].apeNom, apeNomAux);

    nromataux = vrMedicos[i].nroMat;
    vrMedicos[i].nroMat = vrMedicos[i+1].nroMat;
    vrMedicos[i+1].nroMat = nromataux;
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


void AcumMedicos(tvrMed vrMedicos, tsMed rAux, int &cantMed) {//SE COPIAN LOS REGISTROS MEDICOS EN vrMedicos Y SE LLEVA EL CONTADOR DE MEDICOS
    short posMed;
          posMed= BusLinVec(vrMedicos, rAux, cantMed);
    if (posMed <= cantMed && cantMed < max_medicos) {
        strcpy(vrMedicos[posMed].apeNom, rAux.apeNom);
        vrMedicos[posMed].nroMat = rAux.nroMat;
        strcpy(vrMedicos[posMed].nomEsp, rAux.nomEsp);
        vrMedicos[posMed].turno = rAux.turno;
        cantMed++;
    }
}



void ProcMedicos(ifstream &medicos, tvrMed vrMedicos, tsMed rAux, int &cantMed){//FUNCION DONDE SE ENCUENTRAN LAS SUBFUNCIONES
     InicReg(vrMedicos);
     while(leeUnReg(medicos,rAux)){
        AcumMedicos(vrMedicos,rAux,cantMed);
        ordBurMed(vrMedicos, cantMed);
     }
     medicos.close();

}

//PROCESAR ARCHIVO TURNOSDIAHORA

void inicTernario(tTurnos ternTurnos){//INICIALIZAR TERNARIO
    for(int i = 0; i < max_especialidades; i++){
        for(int j = 0; j < max_dias; j++){
            for(int k = 0; k < max_horario; k++){
                strcpy(ternTurnos[i][j][k].nomOsoc, "*");
                ternTurnos[i][j][k].nroCred = 0;

            }
        }
    }
}

bool leeUnTernario(ifstream &TurnosDiaHora, tsTurnDiaHora &rDatosAux){//FUNCION QUE LEE UN TERNARIO
    TurnosDiaHora >> rDatosAux.nomEsp;
    TurnosDiaHora >> rDatosAux.dia;
    TurnosDiaHora >> rDatosAux.hora;
    TurnosDiaHora >> rDatosAux.mins;
    TurnosDiaHora.ignore();
    TurnosDiaHora.get(rDatosAux.nomOsoc,15);
    TurnosDiaHora >> rDatosAux.nroCred;
    TurnosDiaHora.ignore();

return TurnosDiaHora.good();
}

int busBinEsp(str20 vEspecialidades[], int fin, str20 elemento) {
   int inicio = 0;
    while (inicio <= fin) {
    int medio = (inicio + fin) / 2;

        if (strcmp(vEspecialidades[medio], elemento) == 0) {
            return medio;
        }

        else if (strcmp(vEspecialidades[medio], elemento) < 0) {
            inicio = medio + 1;

        }
        else
            fin = medio - 1;
    }
    return -1;
}



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

void acumturprevios(tTurnos TernTurnos, tsTurnDiaHora rDatosAux, str20 vEspecialidades[], int cantEsp){
    int posEsp,posHora;
    posEsp = busBinEsp(vEspecialidades, cantEsp -1 ,rDatosAux.nomEsp);
    posHora = procHorario(rDatosAux);
    strcpy(TernTurnos[posEsp][rDatosAux.dia-1][posHora].nomOsoc,rDatosAux.nomOsoc);
    TernTurnos[posEsp][rDatosAux.dia-1][posHora].nroCred = rDatosAux.nroCred;
}

void ProcTernario (ifstream &TurnosDiaHora, tTurnos ternTurnos, tsTurnDiaHora rDatosAux, str20 vEspecialidades[], int cantEsp){
    inicTernario(ternTurnos);
    while(leeUnTernario(TurnosDiaHora, rDatosAux)){
    acumturprevios(ternTurnos, rDatosAux,vEspecialidades,cantEsp);
    }
    TurnosDiaHora.close();
}

//PROCESAR SOLICITUDTURNOS.TXT

bool leeUnaSol(ifstream &solTurn, tsSol &sTurnAux){
    solTurn.get(sTurnAux.apeNom, 20);
    solTurn.ignore();
    solTurn >> sTurnAux.edad;
    solTurn.get(sTurnAux.nomOsoc, 15);
    solTurn.ignore();
    solTurn >> sTurnAux.nroCred;
    solTurn >> sTurnAux.nomEsp;
    solTurn.ignore();
    solTurn >> sTurnAux.dia;
    solTurn >> sTurnAux.Turno;
    solTurn.ignore();
    return solTurn.good();
}

int busquedaEspecialidad(str20 vEspecialidades[], int fin, str20 elemento) {
   int inicio = 0;
    while (inicio <= fin) {
    int medio = (inicio + fin) / 2;

        if (strcmp(vEspecialidades[medio], elemento) == 0) {
            return medio;
        }

        else if (strcmp(vEspecialidades[medio], elemento) < 0) {
            inicio = medio + 1;

        }
        else
            fin = medio - 1;
    }
return -1;
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

//GRABAR ARCHIVO LISTADOX2

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

int TurnTernIgual(tTurnos ternario,int nroCred){
    for(int i = 0; i < max_especialidades; i++){
        for(int j=0 ; j < max_dias ; j++){
            for(int k = 0; k < max_horario; k++){
                if(ternario[i][j][k].nroCred != 0){
                    if(ternario[i][j][k].nroCred == nroCred){
                        return k;
                    }
                }
            }
        }
    }
    return -1;
}

void ListadoX2(ofstream &listado, tsSol sTurnAux, tvrMed vrMedicos,int  cantMed,tTurnos ternTurnos){
    char Hora[5];
    procContraHorario(TurnTernIgual(ternTurnos,sTurnAux.nroCred),Hora);

    listado << std::left << setw(20)<< sTurnAux.apeNom << setw(17) << sTurnAux.nomOsoc << setw(7) << sTurnAux.nroCred << setw(21) << sTurnAux.nomEsp;
    if(sTurnAux.dia<10){
        listado << std::left << '0' << sTurnAux.dia << ' ';
    }
    else{
        listado << std::left << sTurnAux.dia << ' ';
    }
    listado << Hora[0] << Hora[1] << Hora[2] << Hora[3]<< Hora[4] << ' ' << setw(20)<< vrMedicos[busBinNomMed(cantMed,sTurnAux,vrMedicos)].apeNom << endl;
}

void acumTurnNuevos(tTurnos ternTurnos, str20 vEspecialidades[], int cantEsp, tsSol sTurnAux){
    int posEspNueva;
    int horario;

    posEspNueva = busquedaEspecialidad(vEspecialidades, cantEsp - 1,  sTurnAux.nomEsp);
    horario = obtenerHorario(sTurnAux);


    while (horario < max_horario && strcmp(ternTurnos[posEspNueva][sTurnAux.dia - 1][horario].nomOsoc, "*") != 0) {
        horario++;
    }

    if (horario < max_horario) {
        strcpy(ternTurnos[posEspNueva][sTurnAux.dia - 1][horario].nomOsoc, sTurnAux.nomOsoc);
        ternTurnos[posEspNueva][sTurnAux.dia - 1][horario].nroCred = sTurnAux.nroCred;
    }
}

 void ProcSolicitudTurnos(ifstream &solTurn, tTurnos ternTurnos, str20 vEspecialidades[], int cantEsp, tsSol sTurnAux, int cantMed,tvrMed vrMedicos){
    ofstream listado("JOAKO.txt", ios::app); // Abre un nuevo archivo de salida
    listado << "\nApeNom: " << setw(20) << "O.Soc: " << setw(15) << "NroCred: " << setw(15) << "Especialidad: " << setw(8) << "Dia:"<< setw(7) << "Turno:" << setw(8) << "Medico:" << endl;
    while(leeUnaSol(solTurn, sTurnAux)){
        acumTurnNuevos(ternTurnos, vEspecialidades, cantEsp, sTurnAux);
        ListadoX2(listado,sTurnAux,vrMedicos,cantMed,ternTurnos);
    }
    listado.close();
     solTurn.close();
 }

// GRABAR AL ARCHIVO LISTADOX1
void lstTurnos(tTurnos ternTurnos, str20 vEspecialidades[], int cantEsp) {
    char HoraReal[5];
    ofstream listado("JOAKO.txt"); // Abre un nuevo archivo de salida
    listado << std::left << setw(18) << "Especialidad: " << "Dia: " << setw(6) << "Hora: " << setw(11) << "O.Soc: " << setw(8) << "Nro.Cred:" << endl;
    for (int i = 0; i < cantEsp; i++) {
        for (int j = 0; j < max_dias; j++) {
            for (int k = 0; k < max_horario; k++) {
                    if(strcmp(ternTurnos[i][j][k].nomOsoc, "*") != 0){
                            procContraHorario(k,HoraReal);
                        listado << std::left << setw(20) << vEspecialidades[i];
                        if(j+1<10){
                            listado << '0' << setw(2)<<j + 1;
                        }
                        else{
                            listado << setw(3) <<j + 1;
                        }
                        listado << std::left << HoraReal[0] << HoraReal[1] << HoraReal[2] << HoraReal[3] << setw (2) << HoraReal[4];
                        listado << setw(16) << ternTurnos[i][j][k].nomOsoc;
                        listado << setw(9) << ternTurnos[i][j][k].nroCred << endl;

                    }
            }
        }
    }

    listado.close(); // Cierra el archivo de salida
}

// GRABAR AL ARCHIVO LISTADOX3
void lstTurnosAct(tTurnos ternTurnos, str20 vEspecialidades[], int cantEsp) {
    char HoraReal[5];
    ofstream listado("JOAKO.txt", ios::app); // Abre el archivo de salida nuevamente
    listado << "\nEspecialidades: " << setw(6) << "Dia: " << setw(7) << "Hora: " << "O.Soc: " << setw(12) << "NroCred:"<< endl;
    for (int i = 0; i < cantEsp; i++) {
        for (int j = 0; j < max_dias; j++) {
            for (int k = 0; k < max_horario; k++) {
                    if(strcmp(ternTurnos[i][j][k].nomOsoc, "*") != 0){
                            procContraHorario(k,HoraReal);
                        listado << std::left << setw(20) << vEspecialidades[i];
                        if(j+1<10){
                            listado << '0' << setw(2)<< j + 1;
                        }
                        else{
                            listado << setw(3) << j + 1;
                        }
                        listado << std::left << setw(1) << HoraReal[0] << HoraReal[1] << HoraReal[2] << HoraReal[3] << HoraReal[4] <<' ';
                        listado << setw(15) << ternTurnos[i][j][k].nomOsoc;
                        listado << setw(9) << ternTurnos[i][j][k].nroCred << endl;
                    }
            }
        }
    }
    listado.close(); // Cierra el archivo de salida
}

main(){

    int cantEsp = 0,//CONTADOR DE ESPECIALIDADES
      cantMed = 0;//CONTADOR DE MEDICOS

    tvrMed vrMedicos;//VECTOR DE REGISTROS MEDICOS
    tsMed rAux;//REGISTRO DE MEDICOS AUXILIAR

    str20 vEspecialidades[max_especialidades]; //DEFINIR VECTOR DE CADENAS (vector de especialidades)
    str20 vAux;//VARIABLE AUXILIAR

    tTurnos ternTurnos;
    tsTurnDiaHora rDatosAux;

    tsSol sTurnAux;

    ifstream especialidades("Especialidades.txt");
    ifstream medicos("Medicos.txt");
    ifstream TurnosDiaHora("TurnosDiaHora.txt");
    ifstream solTurn("SolicitudTurnos.txt");

    ProcEspecialidad(especialidades, vEspecialidades, vAux, cantEsp);//PROCESAR ARCHIVO ESPECIALIDADES Y ORDENARLO
    ProcMedicos(medicos,vrMedicos,rAux,cantMed);//PROCESAR ARCHIVO DE MEDICOS

    ProcTernario(TurnosDiaHora, ternTurnos, rDatosAux, vEspecialidades, cantEsp);//PROCESAR TERNARIO
    lstTurnos(ternTurnos,vEspecialidades,cantEsp);//GRABAR EL ARCHIVO PREVIO

    ProcSolicitudTurnos(solTurn,ternTurnos, vEspecialidades, cantEsp, sTurnAux,cantMed,vrMedicos);//AGREGAR LOS NUEVOS TURNOS
    lstTurnosAct(ternTurnos,vEspecialidades,cantEsp);//GRABAR EL ARCHIVO CON LOS TURNOS ACTUALIZADOS

    especialidades.close();
    medicos.close();
    TurnosDiaHora.close();
    solTurn.close();

    cout << 5 + '3';

return 0;
}
