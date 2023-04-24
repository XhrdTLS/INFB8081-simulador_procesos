#include <iostream>

using namespace std;


struct Rafaga{
    string tipo;
    int duracion;
    Rafaga *siguiente;

};

bool cola_vacia(Rafaga *frente){
    return(frente == NULL)? true : false;
}

void insertar_rafaga(Rafaga *&frente, Rafaga *&fin, string tpo, int dur){
    Rafaga *nueva_rafaga = new Rafaga();
    nueva_rafaga -> tipo = tpo;
    nueva_rafaga -> duracion = dur;
    nueva_rafaga -> siguiente = NULL;
    if (cola_vacia(frente )){
        frente = nueva_rafaga;
    }
    else{
        fin -> siguiente = nueva_rafaga;
    }
    fin = nueva_rafaga;
}
struct proceso{

    int numero_proceso;
    int tiempo_llegada;
    int numero_rafagas;
    Rafaga rafagas;

};

void llenar_proceso(proceso x[], int n){
    int i;
    i = 0;
    while(i<n){
        x[i].numero_proceso = i;
        cout << "Cual es el tiempo de llegada del proceso?, se tomara en segundos: " << endl;
        cin >> x[i].tiempo_llegada;
        fflush(stdin);

        cout << "Cuantas rafagas tendr� el proceso?: " << endl;
        cin >> x[i].numero_rafagas;
        fflush(stdin);

        //llenar rafagas
        i++;
    }

}
int main()
{
    int n;
    cout << "Ingrese la cantidad de procesos que desea (recuerde que es un maximo de 10 procesos): " << endl;
    cin >> n;
    if ((n <= 0) || ( n > 10 )){
        do{
            cout << "Ingreso un numero equivocado de procesos" << endl;
            cout << "Ingreso la cantidad de procesos que desea:" << endl;
            cin >> n;
        }while ((n <= 0) || ( n > 10 ));
    }
    proceso cantidad_procesos[n];
    llenar_proceso(cantidad_procesos, n);
    cout << "Hello world!" << endl;
    return 0;
}
