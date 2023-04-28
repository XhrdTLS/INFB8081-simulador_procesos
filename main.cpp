#include <iostream>
#include <string.h>
#include <string>
#include <queue>

using namespace std;


struct Rafaga{
    string tipo;
    float duracion;
    //Rafaga *siguiente;

};

struct proceso{

    int numero_proceso;
    float tiempo_llegada;
    int numero_rafagas;
    queue <Rafaga> cola_de_rafagas;

};

void llenar_rafaga(Rafaga una_rafaga,int cant)
{

    int i = 0;
    queue <Rafaga> cola_de_rafagas;

    while(i < cant){
        cola_de_rafagas.push(una_rafaga);
    }

}

void llenar_proceso(proceso x[], int n){

    queue <Rafaga> cola_de_rafagas;

    Rafaga una_rafaga;
    //
    string tpo;
    int i, j;
    i = 0;
    while(i<n){
        x[i].numero_proceso = i;
        cout << "Cual es el tiempo de llegada del proceso numero: "<< x[i].numero_proceso +1<<"?, " << "se tomara en segundos: " << endl;
        cin >> x[i].tiempo_llegada;
        fflush(stdin);

        cout << "Cuantas rafagas tendra el proceso?: " << endl;
        cin >> x[i].numero_rafagas;
        fflush(stdin);

        //llenar rafagas
        j = 0;
        while(j < x[i].numero_rafagas){

            do{
                cout << "Rafaga numero: " << j+1 << endl;
                cout << "Rafaga de CPU o E/S: " << endl;
                getline(cin, una_rafaga.tipo);
                cout <<" Antes de llenar la duracion" << una_rafaga.tipo << endl;
                fflush(stdin);
                if((una_rafaga.tipo == "CPU") || (una_rafaga.tipo == "E/S")){
                    cout << "Cuanto durara la rafaga?: " << endl;
                    cin >> una_rafaga.duracion;
                    fflush(stdin);
                }
            }while((una_rafaga.tipo != "CPU") && (una_rafaga.tipo != "E/S"));
            fflush(stdin);

            //Ver si funciona el hacer la cola de rafagas
            cout << "INSERTAR" << endl;
            x[i].cola_de_rafagas.push(una_rafaga);
            //POSIBLE ELIMINAR
            cola_de_rafagas.push(una_rafaga);
            j++;
        }
        i++;
    }
    //PROBAR SI ES QUE GUARDA EN LA COLA
    /*cout <<"PRIMERO TIPO: " << cola_de_rafagas.front().tipo << endl;
    cout <<"PRIMERO DURACION: " << cola_de_rafagas.front().duracion << endl;
    cola_de_rafagas.pop();
    cout <<"SEGUNDO TIPO: " << cola_de_rafagas.front().tipo << endl;
    cout <<"SEGUNDO DURACION: " << cola_de_rafagas.front().duracion << endl;
    */


}
//NO FUNCIONA, ELIMINAR
void ordenar_procesos(proceso x[], int cant_procesos)
{
    int i, j;
    proceso aux;
    cout <<"CANTIDAD PROCESOS: " << cant_procesos << endl;
    int cont;
    for(i = 0; i < cant_procesos; i++){
            cout <<"CANTIDAD PROCESOS PRIMER FOR: " << cant_procesos << endl;
        for(j = 0; j < cant_procesos; j++){
            cout <<"CANTIDAD PROCESOS SEGUNDO FOR: " << cant_procesos << endl;

            if(x[j].tiempo_llegada > x[j+1].tiempo_llegada){
                aux = x[j];
                x[j] = x[j+1];
                x[j+1] = aux;
            }
        }
    }
    for(cont = 0; cont < cant_procesos; cont ++){

        cout <<"MAIN ORDENAR: " << x[cont].tiempo_llegada << endl;
    }
}
//que sea una lista de entrada, pasar el arreglo de procesos a una lista
void llenar_queue(queue <proceso> una_cola_de_procesos){

    queue <proceso> cola_espera_uno, cola_espera_dos;
    proceso cpu, e_s;
    float medidor = 0;
    //Para decir que estan vacios el cpu y e/s
    cpu.tiempo_llegada = 0;
    e_s.tiempo_llegada = 0;
    //no se si vaya este while, preguntar
    //while((!una_cola_de_procesos.empty())||(!cola_espera_uno.empty())||(!cola_espera_uno.empty())||(!cpu.cola_de_rafagas.empty())
    //      ||(!e_s.cola_de_rafagas.empty())){}

    //Entra el primer proceso a la cola uno (CPU)
    if((!una_cola_de_procesos.empty())&&(cola_espera_uno.empty())&&(cola_espera_dos.empty())&&(cpu.tiempo_llegada == 0)
       &&(e_s.tiempo_llegada == 0)){

        cola_espera_uno.push(una_cola_de_procesos.front());
        una_cola_de_procesos.pop();
    }
    //Agregar mas adelante que si se mantiene la rafaga de tipo cpu, volver a sumar la duracion de la siguiente rafaga
    if((!cola_espera_uno.empty())&&(cpu.tiempo_llegada == 0)){

        cpu = cola_espera_uno.front();
        cola_espera_uno.pop();
        cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
        cpu.cola_de_rafagas.pop();
    }
    //Para meter el proceso que esta en la cpu en la cola 2
    if(cola_espera_dos.size()<5){

        cola_espera_dos.push(cpu);
        cpu.tiempo_llegada = 0;

    }

    /*//comprobar mas adelante si tira un error cuando este vacio y compare el front con cpu llegada
    if(!una_cola_de_procesos.empty()&&(e_s.tiempo_llegada == 0)&&(cpu.tiempo_llegada > una_cola_de_procesos.front().tiempo_llegada)&&
       (cola_espera_uno.size() < 5)){

        cola_espera_uno.push(una_cola_de_procesos.front());
        una_cola_de_procesos.pop();
       }
    if(cola_espera_uno.size() < 5){
        if((!una_cola_de_procesos.empty())&&(e_s.tiempo_llegada == 0)&&(cpu.tiempo_llegada == 0)&&(cola_espera_dos.empty()){
            cola_espera_uno.push(una_cola_de_procesos.front()));
            una_cola_de_procesos.pop();
        }
        if((!una_cola_de_procesos.empty())&&(e_s.tiempo_llegada == 0)&&(cpu.tiempo_llegada != 0)&&(cola_espera_dos.size()<5)){

           if(cola_espera_dos.front()){

           }

        }
        if((una_cola_de_procesos.empty()){

        }
    }*/
    //1
    if((!una_cola_de_procesos.empty())&&(cola_espera_uno.size() < 5)&&(cpu.tiempo_llegada == 0)&&(cola_espera_dos.size()<5)
        &&(e_s.tiempo_llegada == 0)){
        if((cola_espera_uno.empty())&&(cola_espera_dos.empty())){

            cola_espera_uno.push(una_cola_de_procesos.front());
            una_cola_de_procesos.pop();
        }
        if((!cola_espera_uno.empty())&&(cola_espera_dos.empty())){

            cpu = cola_espera_uno.front();
            cola_espera_uno.pop();
            /*cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
            cpu.cola_de_rafagas.pop();
            cola_espera_dos.push(cpu);
            cpu.tiempo_llegada = 0;
            e_s = cola_espera_dos.front();
            e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
            e_s.cola_de_rafagas.pop();*/
        }
        if((!cola_espera_uno.empty())&&(!cola_espera_dos.empty())){

            cpu = cola_espera_uno.front();
            cola_espera_uno.pop();
            //cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
            //cpu.cola_de_rafagas.pop();
            //cola_espera_dos.push(cpu);
            //cpu.tiempo_llegada = 0;
            e_s = cola_espera_dos.front();
            cola_espera_dos.pop();
            //e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
            //e_s.cola_de_rafagas.pop();
        }
        if((cola_espera_uno.empty())&&(!cola_espera_dos.empty())){

            cola_espera_uno.push(una_cola_de_procesos.front());
            una_cola_de_procesos.pop();

            e_s = cola_espera_dos.front();
            cola_espera_dos.pop();

        }
    }//2
    if((!una_cola_de_procesos.empty())&&(cola_espera_uno.size() < 5)&&(cpu.tiempo_llegada != 0)&&(cola_espera_dos.size()<5)
        &&(e_s.tiempo_llegada == 0)){

        cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
        cpu.cola_de_rafagas.pop();
        if((cola_espera_uno.empty())&&(cola_espera_dos.empty())){

            if(cpu.tiempo_llegada >= una_cola_de_procesos.front().tiempo_llegada){
                medidor = una_cola_de_procesos.front().tiempo_llegada;
                while((cpu.tiempo_llegada >=medidor)&&(cola_espera_uno.size() < 5)&&(!una_cola_de_procesos.empty())){
                    cola_espera_uno.push(una_cola_de_procesos.front());
                    una_cola_de_procesos.pop();
                    medidor = una_cola_de_procesos.front().tiempo_llegada;
                }

                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;

            }
            else{

                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;
            }
        }
        if((!cola_espera_uno.empty())&&(cola_espera_dos.empty())){


            if(cpu.tiempo_llegada >= una_cola_de_procesos.front().tiempo_llegada){
                medidor = una_cola_de_procesos.front().tiempo_llegada;
                while((cpu.tiempo_llegada >=medidor)&&(cola_espera_uno.size() < 5)&&(!una_cola_de_procesos.empty())){
                    cola_espera_uno.push(una_cola_de_procesos.front());
                    una_cola_de_procesos.pop();
                    medidor = una_cola_de_procesos.front().tiempo_llegada;
                }

                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;

                cpu = cola_espera_uno.front();
                cola_espera_uno.pop();

            }
            else{

                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;
                cpu = cola_espera_uno.front();
                cola_espera_uno.pop();
            }
        }//////////////////////////////////////////////////////////////////////////////////
        if((!cola_espera_uno.empty())&&(!cola_espera_dos.empty())){

            e_s = cola_espera_dos.front();
            cola_espera_dos.pop();
            if(cpu.tiempo_llegada >= una_cola_de_procesos.front().tiempo_llegada){
                medidor = una_cola_de_procesos.front().tiempo_llegada;
                while((cpu.tiempo_llegada >=medidor)&&(cola_espera_uno.size() < 5)&&(!una_cola_de_procesos.empty())){
                    cola_espera_uno.push(una_cola_de_procesos.front());
                    una_cola_de_procesos.pop();
                    medidor = una_cola_de_procesos.front().tiempo_llegada;

                }

                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();

            }
            else{

                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();
            }
        }
        if((cola_espera_uno.empty())&&(!cola_espera_dos.empty())){


            if(cpu.tiempo_llegada >= una_cola_de_procesos.front().tiempo_llegada){

                cola_espera_uno.push(una_cola_de_procesos.front());
                una_cola_de_procesos.pop();
                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();

            }
            else{

                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();
            }
        }

    }//3
    if((!una_cola_de_procesos.empty())&&(cola_espera_uno.size() < 5)&&(cpu.tiempo_llegada == 0)&&(cola_espera_dos.size()<5)
        &&(e_s.tiempo_llegada != 0)){

        e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
        e_s.cola_de_rafagas.pop();

        if((cola_espera_uno.empty())&&(cola_espera_dos.empty())){


            if(e_s.tiempo_llegada >= una_cola_de_procesos.front().tiempo_llegada){

                cola_espera_uno.push(una_cola_de_procesos.front());
                una_cola_de_procesos.pop();

            }
            else{

                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
            }
        }
        if((!cola_espera_uno.empty())&&(cola_espera_dos.empty())){

            if(e_s.tiempo_llegada >= una_cola_de_procesos.front().tiempo_llegada){

                cola_espera_uno.push(una_cola_de_procesos.front());
                una_cola_de_procesos.pop();
                cpu = cola_espera_uno.front();
                cola_espera_uno.pop();

            }
            else{

                cpu = cola_espera_uno.front();
                cola_espera_uno.pop();
                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
            }
        }
        if((!cola_espera_uno.empty())&&(!cola_espera_dos.empty())){

            if(e_s.tiempo_llegada >= una_cola_de_procesos.front().tiempo_llegada){

                cola_espera_uno.push(una_cola_de_procesos.front());
                una_cola_de_procesos.pop();

                cpu = cola_espera_uno.front();
                cola_espera_uno.pop();

            }
            else{

                cpu = cola_espera_uno.front();
                cola_espera_uno.pop();
                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();
            }
        }
        if((cola_espera_uno.empty())&&(!cola_espera_dos.empty())){


            if(e_s.tiempo_llegada >= una_cola_de_procesos.front().tiempo_llegada){

                cola_espera_uno.push(una_cola_de_procesos.front());
                una_cola_de_procesos.pop();
                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();

            }
            else{

                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();

            }
        }


    }//4
    if((!una_cola_de_procesos.empty())&&(cola_espera_uno.size() < 5)&&(cpu.tiempo_llegada != 0)&&(cola_espera_dos.size()<5)
        &&(e_s.tiempo_llegada != 0)){

        e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
        e_s.cola_de_rafagas.pop();
        cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
        cpu.cola_de_rafagas.pop();

        if((cola_espera_uno.empty())&&(cola_espera_dos.empty())){

            cola_espera_dos.push(cpu);
            cpu.tiempo_llegada = 0;

            if(e_s.tiempo_llegada >= una_cola_de_procesos.front().tiempo_llegada){

                cola_espera_uno.push(una_cola_de_procesos.front());
                una_cola_de_procesos.pop();
                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;

            }
            else{

                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
                cola_espera_uno.push(una_cola_de_procesos.front());
                una_cola_de_procesos.pop();
            }
        }
        if((!cola_espera_uno.empty())&&(cola_espera_dos.empty())){

            cola_espera_dos.push(cpu);
            cpu.tiempo_llegada = 0;
            cpu = cola_espera_uno.front();
            cola_espera_uno.pop();

            if(e_s.tiempo_llegada >= una_cola_de_procesos.front().tiempo_llegada){

                cola_espera_uno.push(una_cola_de_procesos.front());
                una_cola_de_procesos.pop();
                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;

            }
            else{

                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
                cola_espera_uno.push(una_cola_de_procesos.front());
                una_cola_de_procesos.pop();
            }
        }
        if((!cola_espera_uno.empty())&&(!cola_espera_dos.empty())){

            cola_espera_dos.push(cpu);
            cpu.tiempo_llegada = 0;
            cpu = cola_espera_uno.front();
            cola_espera_uno.pop();

            if(e_s.tiempo_llegada >= una_cola_de_procesos.front().tiempo_llegada){

                cola_espera_uno.push(una_cola_de_procesos.front());
                una_cola_de_procesos.pop();
                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();


            }
            else{

                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
                cola_espera_uno.push(una_cola_de_procesos.front());
                una_cola_de_procesos.pop();
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();
            }
        }
        if((cola_espera_uno.empty())&&(!cola_espera_dos.empty())){

            cola_espera_dos.push(cpu);
            cpu.tiempo_llegada = 0;

            if(e_s.tiempo_llegada >= una_cola_de_procesos.front().tiempo_llegada){

                cola_espera_uno.push(una_cola_de_procesos.front());
                una_cola_de_procesos.pop();
                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();

            }
            else{

                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
                cola_espera_uno.push(una_cola_de_procesos.front());
                una_cola_de_procesos.pop();
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();

            }
        }


    }//2.1
    if((una_cola_de_procesos.empty())&&(cola_espera_uno.size() < 5)&&(cpu.tiempo_llegada == 0)&&(cola_espera_dos.size()<5)
        &&(e_s.tiempo_llegada == 0)){
        if((cola_espera_uno.empty())&&(cola_espera_dos.empty())){

            //TERMINO
        }
        if((!cola_espera_uno.empty())&&(cola_espera_dos.empty())){

            cpu = cola_espera_uno.front();
            cola_espera_uno.pop();

        }
        if((!cola_espera_uno.empty())&&(!cola_espera_dos.empty())){

            cpu = cola_espera_uno.front();
            cola_espera_uno.pop();

            e_s = cola_espera_dos.front();
            cola_espera_dos.pop();

        }
        if((cola_espera_uno.empty())&&(!cola_espera_dos.empty())){

            e_s = cola_espera_dos.front();
            cola_espera_dos.pop();

        }
    }//2.2
    if((una_cola_de_procesos.empty())&&(cola_espera_uno.size() < 5)&&(cpu.tiempo_llegada != 0)&&(cola_espera_dos.size()<5)
        &&(e_s.tiempo_llegada == 0)){

        cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
        cpu.cola_de_rafagas.pop();
        if((cola_espera_uno.empty())&&(cola_espera_dos.empty())){

            cola_espera_dos.push(cpu);
            cpu.tiempo_llegada = 0;

        }
        if((!cola_espera_uno.empty())&&(cola_espera_dos.empty())){


            cola_espera_dos.push(cpu);
            cpu.tiempo_llegada = 0;
            cpu = cola_espera_uno.front();
            cola_espera_uno.pop();
/////////////////////////////////////////////////////////////////////////////////////////////////
        }
        if((!cola_espera_uno.empty())&&(!cola_espera_dos.empty())){


            if(cpu.tiempo_llegada >= una_cola_de_procesos.front().tiempo_llegada){

                cola_espera_uno.push(una_cola_de_procesos.front());
                una_cola_de_procesos.pop();
                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();

            }
            else{

                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();
            }
        }
        if((cola_espera_uno.empty())&&(!cola_espera_dos.empty())){


            if(cpu.tiempo_llegada >= una_cola_de_procesos.front().tiempo_llegada){

                cola_espera_uno.push(una_cola_de_procesos.front());
                una_cola_de_procesos.pop();
                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();

            }
            else{

                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();
            }
        }

    }



}


    cola_espera_uno.push(una_cola_de_procesos.front());
    una_cola_de_procesos.pop();

    cpu = cola_espera_uno.front();
    cola_espera_uno.pop();


    cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
    cpu.cola_de_rafagas.pop();

    //Este va tambien dentro del while
    if((cpu.tiempo_llegada > una_cola_de_procesos.front().tiempo_llegada)&&
       (cola_espera_uno.size() < 5) ){
        cola_espera_uno.push(una_cola_de_procesos.front());
        una_cola_de_procesos.pop();
    }

    cola_espera_dos.push(cpu);
    //Para hacer "nulo" el proceso de la cpu
    cpu.tiempo_llegada = 0;
    //Si el cpu esta vacio y la cola espera uno tiene algun proceso, lo toma la cpu y si el tiempo de cpu es mayor que lista proceso,
    //mete un proceso en la cola uno
    //Creo que va tambien en el while
    if((cpu.tiempo_llegada = 0)&&(!cola_espera_uno.empty())){
        cpu = cola_espera_uno.front();
        cola_espera_uno.pop();
        cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
        cpu.cola_de_rafagas.pop();
        cola_espera_dos.push(cpu);


        if((cpu.tiempo_llegada > una_cola_de_procesos.front().tiempo_llegada)&&
            (cola_espera_uno.size() < 5) ){
            cola_espera_uno.push(una_cola_de_procesos.front());
            una_cola_de_procesos.pop();
        }
        cpu.tiempo_llegada = 0;

    }
    e_s = cola_espera_dos.front();
    e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
    e_s.cola_de_rafagas.pop();

    //aca deberia de ir un while, que mientras e_s sea mayor a el proceso en la cola, se llena la cola 1 hasta que tenga 5
    //si no esta vacio y no se esta ocupando la cpu se le da a la cpu, se ingresa en la cola 2, si es que la cola tiene
    //menos de 5 procesos, se compara si el e/s sigue siendo mayor y se le pasa a el menor
    if((e_s.tiempo_llegada > una_cola_de_procesos.front().tiempo_llegada)&&
       (cola_espera_uno.size() < 5) ){
        cola_espera_uno.push(una_cola_de_procesos.front());
        una_cola_de_procesos.pop();
    }
    else{
        cola_espera_uno.push(e_s);
        e_s.tiempo_llegada = 0;

    }
    while((! una_cola_de_procesos.empty())||(! cola_espera_dos.empty())){
        if(cola_espera_uno.size() < 5){

        }

    }

    //Forma original para hacer lo de cpu
    /*cola_espera_uno.push(una_cola_de_procesos.front());
    una_cola_de_procesos.pop();


    //Ahora entra a la cpu, hace su rafaga y entra a la cola 2 (I/O)
    cola_espera_uno.front().tiempo_llegada = cola_espera_uno.front().tiempo_llegada + cola_espera_uno.front().cola_de_rafagas.front().duracion;
    cola_espera_uno.front().cola_de_rafagas.pop();
    cola_espera_dos.push(cola_espera_uno.front());
    cola_espera_uno.pop();

    cola_espera_dos.front().tiempo_llegada = cola_espera_dos.front().tiempo_llegada + cola_espera_dos.front().cola_de_rafagas.front().duracion;
    cola_espera_dos.front().cola_de_rafagas.pop();
    */

    //Ahora tiene que comparar que entra primero, un proceso de la cola de proceso o un proceso de la cola 2
    while((una_cola_de_procesos.size() > 0)||(cola_espera_dos.size() > 0)){

        if((cola_espera_uno.size() < 5)){

            if(una_cola_de_procesos.front().tiempo_llegada < cola_espera_dos.front().tiempo_llegada){
                cola_espera_uno.push(una_cola_de_procesos.front());
                una_cola_de_procesos.pop();
            }
            else{
                cola_espera_uno.push(cola_espera_dos.front());
                cola_espera_dos.pop();
            }
        }

        //Hacer un if que disminuya la lista que se le saca
        una_cola_de_procesos.pop();
        cola_espera_dos.pop();
    }

}

int main()
{

    int n, k;
    queue <proceso> cola_de_procesos;
    //ELIMINAR cont
    int cont = 0;

    cout << "Ingrese la cantidad de procesos que desea (recuerde que es un maximo de 10 procesos): " << endl;
    cin >> n;
    if ((n <= 0) || ( n > 10 )){
        do{
            cout << "Ingreso un numero equivocado de procesos" << endl;
            cout << "Ingreso la cantidad de procesos que desea:" << endl;
            cin >> n;
        }while ((n <= 0) || ( n > 10 ));
    }



    //Se llena el arreglo con n procesos
    proceso cantidad_procesos[n];
    llenar_proceso(cantidad_procesos, n);

    /*cout <<"MAIN ORDENAR000" << endl;
    for(cont = 0; cont < n; cont ++){

        cout <<"MAIN ORDENAR: " << cantidad_procesos[cont].tiempo_llegada << endl;
    }
    */

    //PROBAR SI ES QUE GUARDA LA COLA EN EL PROCESO

    //cout <<"MAIN PRIMERO TIPO: " << cantidad_procesos[0].cola_de_rafagas.front().tipo << endl;
    //cout <<"MAIN PRIMERO DURACION: " << cantidad_procesos[0].cola_de_rafagas.front().duracion << endl;

    //PROBAR SI SE ORDENAN LOS PROCESOS DE MENOR A MAYOR


    //ordenar_procesos(cantidad_procesos, n);
    //ORDENAR menor a mayor
    cout <<"ORDENAR menor a mayor"<< endl;
    int i, j;
    proceso aux;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(cantidad_procesos[j].tiempo_llegada > cantidad_procesos[j+1].tiempo_llegada){
                aux = cantidad_procesos[j];
                cantidad_procesos[j] = cantidad_procesos[j+1];
                cantidad_procesos[j+1] = aux;
            }
        }
    }
    ////////
    //PARA PASAR EL ARREGLO DE PROCESOS A UNA LISTA DE PROCESOS
    for(k = 0; k < n; k++){

        cola_de_procesos.push(cantidad_procesos[k]);
    }
    //Para saber si se guardaron los procesos en la lista
    /*
    for(k = 0; k < n; k++){
        cout <<"Cola de procesos numero: " << cola_de_procesos.front().numero_proceso << endl;
        cout <<"Cola de procesos tiempo de llegada: " << cola_de_procesos.front().tiempo_llegada << endl;
        cola_de_procesos.pop();
    }
    */


    /*
    cout <<"MAIN ORDENAR222" << endl;
    for(cont = 0; cont < n; cont ++){
        cout <<" Tiempo de llegada: " <<cantidad_procesos[cont].tiempo_llegada << endl;
        cout <<" Tiempo de llegada RAFAGA: " <<cantidad_procesos[cont].cola_de_rafagas.front().duracion << endl;
        cantidad_procesos[cont].cola_de_rafagas.pop();
        cout <<" Tiempo de llegada RAFAGA: " <<cantidad_procesos[cont].cola_de_rafagas.front().duracion << endl;
    }
    */


    cout << "Hello world!" << endl;
    return 0;
}