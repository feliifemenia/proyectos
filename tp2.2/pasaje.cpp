
#include<fstream.h>

using namespace std;

typedef char str20[21];
typedef char str15[16];

struct tsMed{
    str20 apeNom;
    int nroMat;
    str20 nomEsp;
    char turno;
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

void CopiarEsp(ifstream &Arch,ofstream &ArchBin){
    str20 vAux;
        while(Arch.good()){

        Arch.get(vAux,21);
        Arch.ignore();

        ArchBin.write((char*)&vAux,sizeof vAux);
        }
}

void CopiarMed(ifstream &Arch,ofstream &ArchBin){
    tsMed rAux;
        while(Arch.good()){

            Arch.get(rAux.apeNom,21);
            Arch >> rAux.nroMat;
            Arch.ignore();
            Arch.get(rAux.nomEsp,21);
            Arch >> rAux.turno;
            Arch.ignore();

        ArchBin.write((char*)&rAux,sizeof rAux);
        }
}


void CopiarTur(ifstream &Arch,ofstream &ArchBin){
    tsTurnDiaHora rDatosAux;
        while(Arch.good()){

            Arch.get(rDatosAux.nomEsp,21);
            Arch >> rDatosAux.dia;
            Arch >> rDatosAux.hora;
            Arch >> rDatosAux.mins;
            Arch.ignore();
            Arch.get(rDatosAux.nomOsoc,16);
            Arch >> rDatosAux.nroCred;
            Arch.ignore();
        ArchBin.write((char*)&rDatosAux,sizeof rDatosAux);
        }
}

void CopiarSolTur(ifstream &Arch,ofstream &ArchBin){
    tsSol rDatosAux;
        while(Arch.good()){

                Arch.get(rDatosAux.apeNom, 21);
                Arch >> rDatosAux.edad;
                Arch.ignore();
                Arch.get(rDatosAux.nomOsoc, 16);
                Arch >> rDatosAux.nroCred;
                Arch.ignore();
                Arch.get(rDatosAux.nomEsp,21);
                Arch >> rDatosAux.dia;
                Arch.ignore();
                Arch >> rDatosAux.Turno;
                Arch.ignore();

        ArchBin.write((char*)&rDatosAux,sizeof rDatosAux);
        }
}


main(){
    ifstream Arch("Especialidades.txt");
    ofstream ArchBin("Especialidades.dat",ios::binary);
    ifstream Medicostxt("medicos.txt");
    ofstream MedicosDat("medicos.dat",ios::binary);
    ifstream TurnosDiaHoratxt("TurnosDiaHora.txt");
    ofstream TurnosDiaHoraDat("TurnosDiaHora.dat",ios::binary);
    ifstream SolTurtxt("SolicitudTurnos.txt");
    ofstream SolTurDat("SolicitudTurnos.Dat",ios::binary);



CopiarEsp(Arch,ArchBin);
CopiarMed(Medicostxt,MedicosDat);
CopiarTur(TurnosDiaHoratxt,TurnosDiaHoraDat);
CopiarSolTur(SolTurtxt,SolTurDat);





return 0;
}
