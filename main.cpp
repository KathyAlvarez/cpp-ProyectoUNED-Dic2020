/******************************************************************************

Universidad Estatal a Distancia
Vicerrectoría Académica
Escuela de Ciencias Exactas y Naturales
Carrera de Ingeniería Informática
Cátedra de Desarrollo de Sistemas
Introducción a la Programación con C++
Código: 00831
Proyecto
Valor: 4%
Tutor: Alonso Marín
Estudiante: Katherine Alvarez
Fecha de entrega: Domingo 6 de Diciembre
TERCER CUATRIMESTRE 2020

/******************************************************************************
LIBRERIAS A UTILIZAR
*******************************************************************************/
#include <iostream>
#include <wchar.h>
#include <ctime>
#include <conio.h>
#include<windows.h>
#include<stdio.h>
#include <fstream>
#include <cstring>
using namespace std;

/******************************************************************************
FUNCIONES A UTILIZAR
*******************************************************************************/

//MANEJO DE ERRORES Y CICLOS
    void progressBar(int tambar, int tiempo){
        for (int i = 0; i < tambar; i++)//barra inicial

            if (i==0){
                cout <<"\t\t\t ±";//tabular para que se vea alineada
            }else{
                cout <<"±";
            }
        cout<<"\r";// poner el cursor sobre la barra cuando se cargue

        for (int i = 0; i < tambar; i++) {//barra de progreso
            if (i==0){
                cout <<"\t\t\t »";//tabular para que se vea alineada
            }else{
                cout <<"»";
            }
            Sleep(tiempo);//tiempo de espera por cada progreso, ejemplo: 1000 = 1 segundo
        }
    }

    void borrarBitError(){
        std::cin.clear(); //borramos el bit de error para que nuestro programa no se encicle
    }

    void opcionInvalidaMensaje(){
        cout <<"\n"<<"\t\t\tError, opción inválida, intente de nuevo...\n"<<endl;
        progressBar(30,15);
    }

//MANEJO DE INTERFAZ POR COORDENADAS Y TITULOS
    void gotoxy(int x,int y){
      HANDLE hcon;
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);
      COORD dwPos;
      dwPos.X = x;
      dwPos.Y= y;
      SetConsoleCursorPosition(hcon,dwPos);
    }

    void centrarTitulo(string titulo){
        int extension;
        bool tituloPeq = false;
        extension = titulo.length();
        if (extension <=21) {
           tituloPeq = true;
       }
       extension = extension + 20;
       gotoxy(15,2);
       for (int i=0; i<=extension;i++){
        cout<<"*";
    }
    cout<<"\n\n";
    for (int i=0; i<=extension;i++){
        gotoxy(25,4);
        if (i==5){
            cout<<titulo;
        }
    }
    if (tituloPeq){
        cout<<"\n\n";
    }else{
        cout<<"\n";
    }
    gotoxy(15,6);
    for (int i=0; i<=extension;i++){

        cout<<"*";
    }
    cout<<"\n\n";
    }

long hexToDec (char *puntero, long int datoDec){
    string dato;
    char *ptrFecha, fecha[6];
    dato = puntero; //le asignamos lo que contenga el puntero a la variable
    strcpy(fecha, dato.c_str()); //convertimos el string a char
    datoDec = strtol(fecha, &ptrFecha, 16); //el char (hexadecimal) a decimal
    return datoDec;
}

/******************************************************************************
FUNCIONES SECUNDARIAS DEL MENU OPERATIVO
*******************************************************************************/

//-------------------[ AGREGAR DATOS ]------------------------------------------
    bool agregarDatos(){
        bool esc = false; //para finalizar la funcion de agregar pasajero
        int tipo, sexo, dia, mes, anno, y = 15; //variables a recibir
        time_t now = time(0); //fecha/hora actual basado en el sistema
        tm * time = localtime(&now); //objeto de una estructura tm con fecha/hora local
        dia = time->tm_mday; mes = time->tm_mon+1; anno = 1900+time->tm_year;
        string tipoST,sexoST; //convertimos la entrada del usuario a string para archivo
        char continuar='Y';
        ofstream escritura;//variable de la biblioteca fstream para el manejo de archivos
        escritura.open("baseDeDatosOperativa.txt", ios::out | ios::app);//crea archivo sino existe, si existe, escribe al final del archivo
        if (escritura.is_open()){ //archivo creado/abierto con éxito
            while (continuar=='Y' || continuar=='y'){
                bool errorFound=true,errorFound2=true; //resetear cada vez que agregamos pasajero nuevo
                while (errorFound==true){
                    fflush(stdin); //borramos el buffer
                    system("CLS");
                    centrarTitulo("===> Perfil Operativo | Subsidiaria de Transporte S.A"); //titulo termina en x=25, y=6
                    gotoxy(25,9);cout <<"1. Registro de Pasajeros:"<<endl;
                    gotoxy(25,11);cout <<"[1] Adulto   [2] Niño   [3] Mayor   [4] Discapacitado [6] Salir de este Menú"<<endl;
                    gotoxy(25,13);cin>>tipo;
                    try { //manejo de errores
                        switch (tipo){
                            case 1:
                                tipoST="adl";
                                errorFound=false;
                                break;
                            case 2:
                                tipoST="nin";
                                errorFound=false;
                                break;
                            case 3:
                                tipoST="may";
                                errorFound=false;
                                break;
                            case 4:
                                tipoST="dis";
                                errorFound=false;
                                break;
                            case 6: //finaliza agregar pasajero
                                 esc = true; //para que no muestre la opción del género si presiona salir y no agregue pasajero incompleto
                                 return 1;
                            default:
                                throw 404;
                                errorFound=true;
                                break; //mandamos al catch
                    }

                } catch(...){ //maneja todos los posibles errores: 404, char, string, long, bool para que no se caiga el programa
                    opcionInvalidaMensaje();
                    borrarBitError();
                    errorFound=true;
                    }
                }
                while (errorFound2==true && !esc){
                        fflush(stdin); //borramos el buffer
                        gotoxy(25,y);cout <<"[1] Masculino   [2] Femenino [6] Salir de este Menú"<<endl;
                        gotoxy(25,y+2);cin>>sexo;
                        try { //manejo de errores
                            switch (sexo){
                                case 1:
                                    sexoST="ma";
                                    errorFound2=false;
                                    break;
                                case 2:
                                    sexoST="fe";
                                    errorFound2=false;
                                    break;
                                case 6: //finaliza agregar pasajero
                                 esc = true; //para que no agregue este registro incompleto
                                 return 1;
                                default:
                                    throw 404; //mandamos al catch
                                    errorFound2=true;
                                    break;
                            }

                        } catch(...){ //maneja todos los posibles errores: 404, char, string, long, bool para que no se caiga el programa
                            gotoxy(25,y+3);opcionInvalidaMensaje();borrarBitError();
                            y = y+8;
                        }
                    }
                    //Sino hay errores, procedemos a guardar los datos en el formato operativo, ejemplo: adl@ma@11@05@7E4
                    if (!errorFound && !errorFound2 && !esc){
                        escritura<<tipoST<<"@"<<sexoST<<"@"<<std::hex<<dia<<"@"<<std::hex<<mes<<"@"<<std::hex<<anno<<endl;
                        cout<<"\n";progressBar(20,10);
                        gotoxy(25,y+6);cout<<"Pasajero agregado satisfactoriamente!\n";
                        gotoxy(25,y+8);cout <<"Desea agregar otro pasajero? Y/N ";cin>>continuar;
                        y = 15; //reiniciamos el eje Y

                    }else {
                        gotoxy(25,y+6);cout<<"Error!, no se pudo agregar el pasajero, intente de nuevo...";
                    }

        }

        }else{
            gotoxy(25,11);cout<<"Lo sentimos, el Archivo Operativo no se pudo crear/abrir, intente de nuevo...";
        }
        escritura.close();
        return 1;
    }

//-------------------[ MOSTRAR DATOS ]------------------------------------------
    bool mostrarDatos(){
        int dia, mes, anno, y=11, tamanoArchivo=0;
        string tipoST,sexoST;
        bool continuar=false;
        fflush(stdin); //borramos el buffer
        system("CLS");
        centrarTitulo("===> Perfil Operativo | Subsidiaria de Transporte S.A"); //titulo termina en x=25, y=6
        gotoxy(25,8.5);cout <<"2. Listado Dispositivo Móvil:"<<endl;
        ///variable de la biblioteca fstream para el manejo de archivos
        ifstream consulta;
        consulta.open("baseDeDatosOperativa.txt", ios::in);//solamente consulta o lee usando la variable sobre el archivo existente
        if (consulta.is_open()){
            //leyendo cada linea del archivo de manera secuencial
            consulta>>tipoST;
            if (tipoST == ""){ //verificamos si el archivo está vacío
                gotoxy(25,y);cout<<"No hay datos, proceda a agregar pasajeros al Archivo Operativo..."<<endl;
            }else{
                while (!consulta.eof()){ //para mostrar todos los valores
                //imprimimos cada linea de registro con la variable llave
                gotoxy(25,y);cout<<tipoST<<endl;
                consulta>>tipoST; //leer siguiente registro
                y=y+2; //coordenada de filas
                }
            }
        }else{
            gotoxy(25,11);cout<<"Lo sentimos, el archivo operativo no existe, proceda a agregar pasajeros...";
        }
        gotoxy(25,y+2);cout <<"Presione [enter] para regresar";getchar();
        consulta.close();
        return 1;
    }
/******************************************************************************
FUNCIONES SECUNDARIAS DEL MENU ADMINISTRATIVO
*******************************************************************************/
//-------------------[ GENERAR REPORTE ]------------------------------------------
    bool generarReporte(){
        fflush(stdin); //borramos el buffer
        string tipo, sexo;
        char *puntero, lineaOperativa[20];
        int variable = 1;
        long int annoDec, diaDec, mesDec; //nos guarda el valor que retorne nuestra funcion hexToDec
        system("CLS");
        centrarTitulo("===> Perfil Administrativo | Subsidiaria de Transporte S.A"); //titulo termina en x=25, y=6
        gotoxy(25,9);cout <<"1. Generar Reporte Administrativo:"<<endl;
        ifstream consulta; //variable de la biblioteca fstream para el manejo de archivos
        consulta.open("baseDeDatosOperativa.txt", ios::in);//solamente consulta o lee usando la variable sobre el archivo existente
        if (consulta.is_open()){
            //creamos archivo de reporte admin
            ofstream escritura;//variable de la biblioteca fstream para el manejo de archivos
            escritura.open("reporteAdministrativo.txt", ios::out | ios::app);//crea archivo sino existe, si existe, escribe al final del archivo
            if (escritura.is_open()){
           //LEYENDO Y MOSTRANDO CADA CAMPO DEL ARCHIVO DE FORMA SECUENCIAL
             consulta>>lineaOperativa;
           while (!consulta.eof()){ //para recorrer todos los valores
                puntero = strtok(lineaOperativa,"@"); //hacemos split cada vez que encuentre @
                while(puntero!=NULL){
                  if (variable==1){ //leemos el tipo
                      tipo= puntero; //le asignamos lo que contenga el puntero a la variable
                      if (tipo == "nin"){
                        tipo = "Niño";
                        }else if (tipo == "adl"){
                            tipo = "Adulto";
                        }else if (tipo == "may"){
                            tipo = "Mayor";
                        }else if (tipo == "dis"){
                            tipo = "Discapacitado";
                        }
                   }else if(variable==2){ // leemos el sexo
                        sexo = puntero; //le asignamos lo que contenga el puntero a la variable
                        if (sexo == "fe"){
                            sexo = "Femenino";
                        }else if (sexo == "ma"){
                            sexo = "Masculino";
                        }

                   }else if(variable==3){//leemos el dia
                        diaDec = hexToDec(puntero,diaDec); //mandamos a convertir el dia a decimal

                   }else if(variable==4){ //leemos el mes
                        mesDec = hexToDec(puntero,mesDec); //mandamos a convertir el mes a decimal

                   }else if(variable==5){ //leemos el año
                        annoDec = hexToDec(puntero,annoDec); //mandamos a convertir el año a decimal
                }
                variable++;
                puntero = strtok(NULL,"@"); //lee siguiente variable

               }
                variable = 1; //reseteamos la variable

                escritura<<tipo<<" "<<sexo<<" "<<diaDec<<"/"<<mesDec<<"/"<<annoDec<<endl;
                consulta>>lineaOperativa; //leer siguiente registro
            }
            progressBar(40,30);
            gotoxy(25,13);cout<<"El Reporte Administrativo se ha generado y/o actualizado satisfactoriamente...";
            escritura.close(); //cerramos el reporte administrativo
            consulta.clear(); //borramos los datos que ya enviamos al reporte administrativo
            consulta.close(); //cerramos el archivo operativo
            //abrir y limpiar el archivo operativo con trunc
            ofstream limpiarArchivo; //Variable de la biblioteca fstream para el manejo de archivos
            limpiarArchivo.open("baseDeDatosOperativa.txt", ios::out | ios::trunc);//si abrimos el archivo en modo trunc borra el contenido
            limpiarArchivo.close(); //cerramos el archivo operativo en blanco

        }else {
            gotoxy(25,15);cout<<"Lo sentimos, el Reporte Administrativo no se pudo generar/actualizar...";
        }

    }else{
        gotoxy(25,13);cout<<"Error, no se pudo generar el reporte, proceda a agregar pasajeros...";
    }
    gotoxy(25,17);cout <<"Presione [enter] para regresar";getchar();
    return 1;
    }

//-------------------[ MOSTRAR REPORTE ]------------------------------------------

    bool mostrarReporte(){
        bool continuar=false;
        char *puntero, lineaOperativa[20]; //para el puntero
        int y = 14, contador = 1, regNum=1;
        fflush(stdin); //borramos el buffer
        system("CLS");
        centrarTitulo("===> Perfil Administrativo | Subsidiaria de Transporte S.A"); //titulo termina en x=25, y=6
        gotoxy(25,8);cout <<"2. Reporte Administrativo:"<<endl;

        ///variable de la biblioteca fstream para el manejo de archivos
        ifstream consulta;
        consulta.open("reporteAdministrativo.txt", ios::in);//solamente consulta o lee usando la variable sobre el archivo existente
        if (consulta.is_open()){
            gotoxy(28,9.5);cout <<"_______________________________________________________";
            gotoxy(30,11.5);cout <<"#";gotoxy(37,11.5);cout <<"Tipo de Usuario";gotoxy(57,11);cout <<"Género";gotoxy(72,11);cout <<"Fecha       ";
            gotoxy(28,12);cout  <<"_______________________________________________________";
            //LEYENDO Y MOSTRANDO CADA CAMPO DEL ARCHIVO DE FORMA SECUENCIAL
            consulta>>lineaOperativa;
            while (!consulta.eof()){ //para recorrer todos los valores
                puntero = strtok(lineaOperativa," "); //hacemos split cada vez que encuentre espacio en blanco
                while(puntero!=NULL){
                    if (contador == 1){
                        gotoxy(30,y);cout<<regNum;gotoxy(37,y);cout<<puntero;
                        regNum++;
                    } else if (contador == 2){
                        gotoxy(57,y);cout<<puntero;
                    } else if (contador == 3){ //hacer salto de linea y reiniciar gotoxy para columnas
                        gotoxy(72,y);cout<<puntero;
                        y = y+2;
                        contador = 0;
                    }
                puntero = strtok(NULL," "); //lee siguiente variable
                contador = contador + 1 ;
                }
                consulta>>lineaOperativa; //leer siguiente registro

            }

        }else{
            gotoxy(25,11);cout<<"Lo sentimos, el archivo del Reporte Administrativo no existe, proceda a generar reporte...";
        }
        gotoxy(25,y+2);cout <<"Presione [enter] para regresar";getchar();
        consulta.close();
        return 1;
    }

/******************************************************************************
FUNCIONES PRINCIPALES
*******************************************************************************/

//-------------------------MENU OPERATIVO---------------------------------------
    bool perfilOpera(int op){
        bool sel = true, errorFound=false, mostrarMenuOperativo=true;
        while (mostrarMenuOperativo==true){
                fflush(stdin); //borramos el buffer
                system("CLS");
                system("color E0");
                centrarTitulo("===> Perfil Operativo | Subsidiaria de Transporte S.A"); //titulo termina en x=25, y=6
                gotoxy(25,9);cout  <<"[1] Registro de Pasajeros"<<endl;
                gotoxy(25,11);cout <<"[2] Reporte Parcial de Dispositivo"<<endl;
                gotoxy(25,13);cout <<"[3] Regresar al Menú Principal"<<endl;
                gotoxy(25,15);cout <<"Seleccione una opción: ";cin >>op;
                try {
                    switch (op){
                        case 1:
                            mostrarMenuOperativo = agregarDatos();
                            break;
                        case 2:
                            mostrarMenuOperativo = mostrarDatos();
                            break;
                        case 3:
                            gotoxy(25,17);cout <<"Regresando al Menú Principal, por favor espere...\n"<<endl;
                            progressBar(40,30);
                            return 0;
                        default:
                            throw 404; //enviamos al catch
                            break;
                                }

                        } catch(...){ //maneja los errores para que no se caiga el programa
                            opcionInvalidaMensaje();
                            borrarBitError();
                            errorFound = true;
                        }

                    }
            return sel; //retornamos true (1), para que nos vuelva a mostrar el Menu Operativo
    }

//----------------------------------MENU ADMINISTRATIVO-------------------------------------------------------
    bool perfilAdmin(int op){
        bool sel = true, errorFound=false, mostrarMenuAdministrativo=true;
        while (mostrarMenuAdministrativo==true){
            fflush(stdin); //borramos el buffer
            system("CLS");
            system("color B0");
            centrarTitulo("===> Perfil Administrativo | Subsidiaria de Transporte S.A"); //titulo termina en x=25, y=6
            gotoxy(25,9);cout  <<"[1] Generar Reporte"<<endl;
            gotoxy(25,11);cout <<"[2] Reporte Administrativo"<<endl;
            gotoxy(25,13);cout <<"[3] Regresar al Menú Principal"<<endl;
            gotoxy(25,15);cout <<"Seleccione una opción: ";cin >>op;
            try {
                switch (op){
                    case 1:
                        mostrarMenuAdministrativo = generarReporte();
                        break;
                    case 2:
                        mostrarMenuAdministrativo = mostrarReporte();
                        break;
                    case 3:
                        gotoxy(25,17);cout <<"Regresando al Menú Principal, por favor espere...\n"<<endl;
                        progressBar(40,30);
                        return 0;
                    default:
                        throw 404; //enviamos al catch
                        break;
                            }

                    } catch(...){ //maneja los errores para que no se caiga el programa
                        opcionInvalidaMensaje();
                        borrarBitError();
                        errorFound = true;
                    }
                }
        return sel; //retornamos true (1), para que nos vuelva a mostrar el Menu Administrativo
    }

//--------------------------------------------PANTALLA PRINCIPAL------------------------------------------------------
    bool iniciarMenu(){
        bool sel = true, mostrarMenuPrincipal=true;
        int op = 0;
        while (sel==true){
                fflush(stdin); //borramos el buffer
                system("CLS");
                system("color 4F");
                op = 0; //reinicializamos la opcion
                //tabulado con gotoxy x = 25 para texto, y = 6 termina titulo
                //contamos eje Y de 2 en 2 para que quede espaciado
                centrarTitulo("Bienvenido a Subsidiaria de Transporte S.A | Katherine Alvarez | UNED CR");
                gotoxy(25,9);cout  <<"[1] Perfil Operativo";
                gotoxy(70,9);cout <<"[2] Perfil Administrativo";
                gotoxy(52,11);cout <<"[3] Salir";
                gotoxy(25,13);cout <<"Seleccione una opción: ";cin >>op;
                try {
                    switch (op){
                        case 1:
                            mostrarMenuPrincipal = perfilOpera(op); //le mandamos op para reutilizar la variable
                            break;
                            case 2:
                            mostrarMenuPrincipal = perfilAdmin(op); //le mandamos op para reutilizar la variable
                            break;
                            case 3:
                            gotoxy(25,17);cout <<"Programa finalizado con éxito!, le esperamos pronto!\n"<<endl;
                            progressBar(30,15);
                            return 1; //retorna true para terminar programa
                            default:
                            throw 404; //enviamos al catch
                            break;
                        }

                } catch(...){ //maneja los errores para que no se caiga el programa
                    opcionInvalidaMensaje();
                    borrarBitError();
                }
            }
            return 0;
        }

/******************************************************************************
MENU PRINCIPAL MAIN
*******************************************************************************/
    int main()
        {
        setlocale(LC_ALL, "");//imprime acentos y caracteres especiales
        bool salir=false;
        do {
            salir=iniciarMenu();
            if (salir == true) {
               return 0; //finaliza programa si usuario presiona salir
           }else {
                //seguir mostrando menu principal
           }
       }while (salir==true);
       return 0;
    }
