/* Nombre integrantes
    - Brian Moya
    - Diego Aguirre
    - Gabriel Gonzalez
    - Gustavo Oyarce
    - Jose Donoso
    - Tomas Lillo

    INFB8081 Sistemas Operativos 2023-1
*/

#include <iostream>
#include <string.h>
#include <string>
#include <queue>

using namespace std;

struct Rafaga{
    string tipo;
    float duracion;
};

struct proceso{
    int numero_proceso;
    float tiempo_llegada;
    int numero_rafagas;
    queue<Rafaga> cola_de_rafagas;
};

void llenar_rafaga(Rafaga una_rafaga, int cant){
    int i = 0;
    queue<Rafaga> cola_de_rafagas;

    while (i < cant)
    {
        cola_de_rafagas.push(una_rafaga);
    }
};

bool validar_rafaga(queue<Rafaga> una_cola_de_rafaga){

    if (((una_cola_de_rafaga.front().tipo == "CPU") || (una_cola_de_rafaga.front().tipo == "cpu")) &&
        ((una_cola_de_rafaga.back().tipo == "CPU") || (una_cola_de_rafaga.back().tipo == "cpu")))
    {
        return true;
    }
    else
    {
        return false;
    }
};

int Pedir_int(){
    string input;
    int num;
    bool aux = true;

    while (aux == true)
    {
        input = "/0";
        getline(cin, input);

        try
        {
            num = stoi(input);
            if (num > 0)
            {
                aux = false;
            }
            else
            {
                cout << "-----------------------------------------" 
                << endl << "[!] El input ingresado no es un numero valido." << endl 
                << "-----------------------------------------";
                system("pause");
                //system("cls");
                cout << "Ingrese nuevamente" << endl;
            }
        }
        catch (invalid_argument e)
        {
            cout << "-----------------------------------------" 
                << endl << "[!] El input ingresado no es un numero valido." << endl 
                << "-----------------------------------------";
            system("pause");
            //system("cls");
            cout << "Ingrese nuevamente" << endl;
        }
    }

    return num;
}

void llenar_proceso(proceso x[], int n){
    queue<Rafaga> cola_de_rafagas;
    Rafaga una_rafaga;
    string tpo;
    int i, j;
    i = 0;
    while (i < n)
    {
        x[i].numero_proceso = i;
        cout << " Cual es el tiempo de llegada del proceso numero: " << x[i].numero_proceso + 1 << "?, "
             << "se tomara en segundos: " << endl;
        x[i].tiempo_llegada = Pedir_int();
        fflush(stdin);
        cout << " Cuantas rafagas tendra el proceso?: " << endl;
        x[i].numero_rafagas = Pedir_int();
        fflush(stdin);

        j = 0;
        do
        {
            while (j < x[i].numero_rafagas)
            {

                do
                {

                    cout << "Rafaga numero: " << j + 1 << endl;
                    cout << "Rafaga de CPU o E/S: " << endl;
                    getline(cin, una_rafaga.tipo);
                    fflush(stdin);
                    
                    if ((una_rafaga.tipo == "CPU") || (una_rafaga.tipo == "E/S") || (una_rafaga.tipo == "cpu") || (una_rafaga.tipo == "e/s"))
                    {
                        cout << "Cuanto durara la rafaga?: " << endl;
                        una_rafaga.duracion = Pedir_int();
                        fflush(stdin);
                    }

                } while ((una_rafaga.tipo != "CPU") && (una_rafaga.tipo != "E/S") && (una_rafaga.tipo != "cpu") && (una_rafaga.tipo != "e/s"));

                fflush(stdin);
                x[i].cola_de_rafagas.push(una_rafaga);
                cola_de_rafagas.push(una_rafaga);
                j++;
            }
            if (!validar_rafaga(x[i].cola_de_rafagas))
            {
                cout <<"-----------------------------------------" << endl;
                cout <<  "Rafaga no valida. "
                     << endl << "[!] La primera y la ultima rafaga deben ser CPU." << '\n'
                     << "Ingrese las rafagas nuevamente." << endl <<
                     "-----------------------------------------"<< endl;
                j = 0;
                cola_de_rafagas.pop();
                x[i].cola_de_rafagas.pop();
            }

        } while (!validar_rafaga(cola_de_rafagas));
        i++;
    }
}

void llenar_queue(queue<proceso> una_cola_de_procesos){

    queue<proceso> cola_espera_uno, cola_espera_dos;
    proceso cpu, e_s;
    float medidor = 0;

    cpu.tiempo_llegada = 0;
    e_s.tiempo_llegada = 0;

    while ((!una_cola_de_procesos.empty()) || (!cola_espera_uno.empty()) || (!cola_espera_dos.empty()) || (cpu.tiempo_llegada != 0) || (e_s.tiempo_llegada != 0))
    {

        // 1
        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada == 0))
        {

            if ((cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada == 0))
            {

                cola_espera_uno.push(una_cola_de_procesos.front());
                una_cola_de_procesos.pop();
                cout << " - El proceso numero : " << cola_espera_uno.front().numero_proceso + 1 << " ingreso a la cola de CPU" << endl;
                system("pause");
            }

            if ((!cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada == 0))
            {

                cpu = cola_espera_uno.front();
                cola_espera_uno.pop();

                cout << " - El proceso numero: " << cpu.numero_proceso + 1 << " entro a la CPU" << endl;
                system("pause");
            }

            if ((!cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada == 0))
            {
                cpu = cola_espera_uno.front();
                cola_espera_uno.pop();

                cout << " - El proceso numero: " << cpu.numero_proceso + 1 << " entro a la CPU." << endl;
                system("pause");
            }
            if ((cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada == 0))
            {
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();

                cout << " - El proceso numero: " << e_s.numero_proceso + 1 << " sale de cola E/S y entra a E/S." << endl;
                system("pause");
            }
        }

        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada == 0))
        {
            while ((!cpu.cola_de_rafagas.empty()) && ((cpu.cola_de_rafagas.front().tipo == "CPU") || (cpu.cola_de_rafagas.front().tipo == "cpu")))
            {
                cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
            }

            if ((cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada == 0))
            {
                if (cpu.tiempo_llegada >= una_cola_de_procesos.front().tiempo_llegada)
                {
                    medidor = una_cola_de_procesos.front().tiempo_llegada;
                    while ((cpu.tiempo_llegada >= medidor) && (cola_espera_uno.size() < 5) && (!una_cola_de_procesos.empty()))
                    {
                        cout << " - Como el proceso: " << una_cola_de_procesos.front().numero_proceso + 1 << " llega antes que termine el proceso: " << cpu.numero_proceso + 1;
                        cout << " ingresa el proceso " << una_cola_de_procesos.front().numero_proceso + 1 << " a la cola de CPU" << endl;
                        cola_espera_uno.push(una_cola_de_procesos.front());
                        una_cola_de_procesos.pop();
                        system("pause");

                        if (!una_cola_de_procesos.empty())
                        {
                            medidor = una_cola_de_procesos.front().tiempo_llegada;
                        }
                    }
                    if (cpu.cola_de_rafagas.empty())
                    {
                        cpu.tiempo_llegada = 0;
                        cout << " TERMINA EL PROCESO: " << cpu.numero_proceso + 1 << endl;
                        system("pause");
                    }
                    else
                    {
                        cola_espera_dos.push(cpu);
                        cpu.tiempo_llegada = 0;
                        cout << " - El proceso: " << cola_espera_dos.front().numero_proceso + 1 << " sale de la cpu y entra a la cola E/S" << endl;
                        system("pause");
                    }
                }
                if (cpu.cola_de_rafagas.empty() && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada == 0))
                {
                    cpu.tiempo_llegada = 0;
                    cout << " TERMINA EL PROCESO: " << cpu.numero_proceso + 1 << endl;
                    system("pause");
                }
                if ((!una_cola_de_procesos.empty()))
                {
                    /*system("pause");
                    cout << "una_cola_de_procesos.empty() 2.1.4: " << una_cola_de_procesos.empty() << endl;
                    cout << "cola_espera_uno.empty() 2.1.4: " << cola_espera_uno.empty() << endl;
                    cout << "cola_espera_uno.size() 2.1.4: " << cola_espera_uno.size() << endl;
                    cout << "cpu.tiempo_llegada 2.1.4: " << cpu.tiempo_llegada << endl;
                    cout << "cola_espera_dos.empty() 2.1.4: " << cola_espera_dos.empty() << endl;
                    cout << "cola_espera_dos.size() 2.1.4: " << cola_espera_dos.size() << endl;
                    cout << "e_s.tiempo_llegada 2.1.4: " << e_s.tiempo_llegada << endl;
                    cout << "Como el proceso: " << cpu.numero_proceso + 1 << " llega antes que termine el proceso: " << una_cola_de_procesos.front().numero_proceso + 1;
                    cout << " ingresa el proceso " << cpu.numero_proceso + 1 << endl;*/
                    system("pause");
                    cola_espera_dos.push(cpu);
                    cpu.tiempo_llegada = 0;
                }
            }
            if ((!cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada == 0))
            {
                if (cpu.tiempo_llegada >= una_cola_de_procesos.front().tiempo_llegada)
                {
                    medidor = una_cola_de_procesos.front().tiempo_llegada;
                    while ((cpu.tiempo_llegada >= medidor) && (cola_espera_uno.size() < 5) && (!una_cola_de_procesos.empty()))
                    {
                        cout << " - Como el proceso: " << una_cola_de_procesos.front().numero_proceso + 1 << " llega antes que termine el proceso: " << cpu.numero_proceso + 1;
                        cout << " ingresa el proceso " << una_cola_de_procesos.front().numero_proceso + 1 << " a la cola de CPU" << endl;
                        system("pause");
                        cola_espera_uno.push(una_cola_de_procesos.front());
                        una_cola_de_procesos.pop();
                        if (!una_cola_de_procesos.empty())
                        {
                            medidor = una_cola_de_procesos.front().tiempo_llegada;
                        }
                    }

                    if (cpu.cola_de_rafagas.empty() && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada == 0))
                    {
                        cpu.tiempo_llegada = 0;
                        cout << " TERMINA EL PROCESO 2: " << cpu.numero_proceso + 1 << endl;
                        system("pause");
                    }
                    else
                    {
                        cola_espera_dos.push(cpu);
                        cpu.tiempo_llegada = 0;
                        cout << " - El proceso: " << cola_espera_dos.front().numero_proceso + 1 << " sale de la cpu y entra a la cola E/S" << endl;
                        system("pause");
                    }
                }
                else
                {
                    cout << " - Como el proceso: " << cpu.numero_proceso + 1 << " llega antes que termine el proceso: " << una_cola_de_procesos.front().numero_proceso + 1;
                    cout << " ingresa el proceso " << cpu.numero_proceso + 1 << endl;
                    system("pause");
                    cola_espera_dos.push(cpu);
                    cpu.tiempo_llegada = 0;
                }
            }
            if ((!cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada == 0))
            {
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();
                cout << " - El proceso numero: " << e_s.numero_proceso + 1 << " sale de cola E/S y entra a E/S." << endl;
                system("pause");
            }
            if ((cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada == 0))
            {

                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();
                cout << " - El proceso numero: " << e_s.numero_proceso + 1 << " sale de cola E/S y entra a E/S." << endl;
                system("pause");
            }
        }
        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada != 0))
        {
            while ((!e_s.cola_de_rafagas.empty()) && ((e_s.cola_de_rafagas.front().tipo == "E/S") || (e_s.cola_de_rafagas.front().tipo == "e/s")))
            {
                e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
                e_s.cola_de_rafagas.pop();
            }
            if ((cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada != 0))
            {
                if (e_s.tiempo_llegada > una_cola_de_procesos.front().tiempo_llegada)
                {
                    medidor = una_cola_de_procesos.front().tiempo_llegada;
                    while ((e_s.tiempo_llegada >= medidor) && (cola_espera_uno.size() < 5) && (!una_cola_de_procesos.empty()))
                    {
                        cout << " - Como el proceso: " << una_cola_de_procesos.front().numero_proceso + 1 << " llega antes que termine el proceso: " << e_s.numero_proceso + 1;
                        cout << " ingresa el proceso " << una_cola_de_procesos.front().numero_proceso + 1 << " a la cola de CPU" << endl;
                        system("pause");
                        cola_espera_uno.push(una_cola_de_procesos.front());
                        una_cola_de_procesos.pop();
                        if (!una_cola_de_procesos.empty())
                        {
                            medidor = una_cola_de_procesos.front().tiempo_llegada;
                        }
                    }
                }
                else
                {
                    if (cola_espera_uno.size() < 5)
                    {
                        cout << " - El proceso " << e_s.numero_proceso + 1 << " Sale del E/S y entra en la cola cpu " << endl;
                        system("pause");
                        cola_espera_uno.push(e_s);
                        e_s.tiempo_llegada = 0;
                    }
                }
            }
            if ((!cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada != 0))
            {
                cout << " - El proceso " << cola_espera_uno.front().numero_proceso + 1 << " Sale de la cola cpu y entra a la CPU " << endl;
                system("pause");
                cpu = cola_espera_uno.front();
                cola_espera_uno.pop();
            }
            if ((!cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada != 0))
            {
                cout << " - El proceso " << cola_espera_uno.front().numero_proceso + 1 << " Sale de la cola cpu y entra a la CPU " << endl;
                system("pause");
                cpu = cola_espera_uno.front();
                cola_espera_uno.pop();
            }
            if ((cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada != 0))
            {

                if (e_s.tiempo_llegada > una_cola_de_procesos.front().tiempo_llegada)
                {
                    cout << " - Como el proceso: " << una_cola_de_procesos.front().numero_proceso + 1 << " llega antes que termine el proceso: " << e_s.numero_proceso + 1;
                    cout << " ingresa el proceso " << una_cola_de_procesos.front().numero_proceso + 1 << " a la cola de CPU" << endl;
                    system("pause");
                    cola_espera_uno.push(una_cola_de_procesos.front());
                    una_cola_de_procesos.pop();
                }
                else
                {
                    if (cola_espera_uno.size() < 5)
                    {
                        cout << " - El proceso " << e_s.numero_proceso + 1 << " Sale del E/S y entra en la cola cpu " << endl;
                        system("pause");
                        cola_espera_uno.push(e_s);
                        e_s.tiempo_llegada = 0;
                    }
                }
            }
        }
        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada != 0))
        {

            while ((!cpu.cola_de_rafagas.empty()) && ((cpu.cola_de_rafagas.front().tipo == "CPU") || (cpu.cola_de_rafagas.front().tipo == "cpu")))
            {
                cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
            }
            if (cpu.cola_de_rafagas.empty() && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada != 0))
            {
                cpu.tiempo_llegada = 0;
                cout << " TERMINA EL PROCESO: " << cpu.numero_proceso + 1 << endl;
                system("pause");
                // TERMINA EL PROCESO
            }

            while ((!e_s.cola_de_rafagas.empty()) && ((e_s.cola_de_rafagas.front().tipo == "E/S") || (e_s.cola_de_rafagas.front().tipo == "e/s")))
            {

                e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
                e_s.cola_de_rafagas.pop();
            }

            if ((cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada != 0))
            {

                if (cpu.tiempo_llegada <= e_s.tiempo_llegada)
                {

                    cout << " - El proceso " << cpu.numero_proceso + 1 << " Sale del CPU y entra en la cola E/S " << endl;
                    system("pause");
                    cola_espera_dos.push(cpu);
                    cpu.tiempo_llegada = 0;
                }
                else
                {

                    if (e_s.tiempo_llegada > una_cola_de_procesos.front().tiempo_llegada)
                    {
                        medidor = una_cola_de_procesos.front().tiempo_llegada;
                        while ((e_s.tiempo_llegada >= medidor) && (cola_espera_uno.size() < 5) && (!una_cola_de_procesos.empty()))
                        {
                            cout << " - Como el proceso: " << una_cola_de_procesos.front().numero_proceso + 1 << " llega antes que termine el proceso: " << e_s.numero_proceso + 1;
                            cout << " ingresa el proceso " << una_cola_de_procesos.front().numero_proceso + 1 << " a la cola de CPU" << endl;
                            system("pause");
                            cola_espera_uno.push(una_cola_de_procesos.front());
                            una_cola_de_procesos.pop();
                            if (!una_cola_de_procesos.empty())
                            {
                                medidor = una_cola_de_procesos.front().tiempo_llegada;
                            }
                        }
                    }
                    else
                    {
                        if (cola_espera_uno.size() < 5)
                        {
                            cout << " - El proceso " << e_s.numero_proceso + 1 << " Sale del E/S y entra en la cola cpu " << endl;
                            system("pause");
                            cola_espera_uno.push(e_s);
                            e_s.tiempo_llegada = 0;
                        }
                    }
                }
            }
            if ((!cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada != 0))
            {

                if (cpu.tiempo_llegada <= e_s.tiempo_llegada)
                {
                    cout << " - El proceso " << cpu.numero_proceso + 1 << " Sale del CPU y entra en la cola E/S " << endl;
                    system("pause");
                    cola_espera_dos.push(cpu);
                    cpu.tiempo_llegada = 0;
                }
                else
                {

                    if (e_s.tiempo_llegada > una_cola_de_procesos.front().tiempo_llegada)
                    {
                        medidor = una_cola_de_procesos.front().tiempo_llegada;
                        while ((e_s.tiempo_llegada >= medidor) && (cola_espera_uno.size() < 5) && (!una_cola_de_procesos.empty()))
                        {
                            cout << " - Como el proceso: " << una_cola_de_procesos.front().numero_proceso + 1 << " llega antes que termine el proceso: " << e_s.numero_proceso + 1;
                            cout << " ingresa el proceso " << una_cola_de_procesos.front().numero_proceso + 1 << " a la cola de CPU" << endl;
                            system("pause");
                            cola_espera_uno.push(una_cola_de_procesos.front());
                            una_cola_de_procesos.pop();
                            if (!una_cola_de_procesos.empty())
                            {
                                medidor = una_cola_de_procesos.front().tiempo_llegada;
                            }
                        }
                    }
                    else
                    {
                        if (cola_espera_uno.size() < 5)
                        {
                            cout << " - El proceso " << e_s.numero_proceso + 1 << " Sale del E/S y entra en la cola cpu " << endl;
                            system("pause");
                            cola_espera_uno.push(e_s);
                            e_s.tiempo_llegada = 0;
                        }
                    }
                }
            }

            if ((!cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada != 0))
            {
                if ((cpu.tiempo_llegada <= e_s.tiempo_llegada) && (cola_espera_dos.size() < 5))
                {
                    cout << " - El proceso " << cpu.numero_proceso + 1 << " Sale del CPU y entra en la cola E/S " << endl;
                    system("pause");
                    cola_espera_dos.push(cpu);
                    cpu.tiempo_llegada = 0;
                }
                else
                {

                    if (e_s.tiempo_llegada > una_cola_de_procesos.front().tiempo_llegada)
                    {
                        medidor = una_cola_de_procesos.front().tiempo_llegada;
                        while ((e_s.tiempo_llegada >= medidor) && (cola_espera_uno.size() < 5) && (!una_cola_de_procesos.empty()))
                        {
                            cout << " - Como el proceso: " << una_cola_de_procesos.front().numero_proceso + 1 << " llega antes que termine el proceso: " << e_s.numero_proceso + 1;
                            cout << " ingresa el proceso " << una_cola_de_procesos.front().numero_proceso + 1 << " a la cola de CPU" << endl;
                            system("pause");
                            cola_espera_uno.push(una_cola_de_procesos.front());
                            una_cola_de_procesos.pop();
                            if (!una_cola_de_procesos.empty())
                            {
                                medidor = una_cola_de_procesos.front().tiempo_llegada;
                            }
                        }
                    }
                    else
                    {
                        if (cola_espera_uno.size() < 5)
                        {
                            cout << " - El proceso " << e_s.numero_proceso + 1 << " Sale del E/S y entra en la cola cpu " << endl;
                            system("pause");
                            cola_espera_uno.push(e_s);
                            e_s.tiempo_llegada = 0;
                        }
                    }
                }
            }
            if ((cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada != 0))
            {
                if ((cpu.tiempo_llegada <= e_s.tiempo_llegada) && (cola_espera_dos.size() < 5))
                {
                    cout << " - El proceso " << cpu.numero_proceso + 1 << " Sale del CPU y entra en la cola E/S " << endl;
                    system("pause");
                    cola_espera_dos.push(cpu);
                    cpu.tiempo_llegada = 0;
                }
                else
                {

                    if (e_s.tiempo_llegada > una_cola_de_procesos.front().tiempo_llegada)
                    {
                        medidor = una_cola_de_procesos.front().tiempo_llegada;
                        while ((e_s.tiempo_llegada >= medidor) && (cola_espera_uno.size() < 5) && (!una_cola_de_procesos.empty()))
                        {
                            cout << " - Como el proceso: " << una_cola_de_procesos.front().numero_proceso + 1 << " llega antes que termine el proceso: " << e_s.numero_proceso + 1;
                            cout << " ingresa el proceso " << una_cola_de_procesos.front().numero_proceso + 1 << " a la cola de CPU" << endl;
                            system("pause");
                            cola_espera_uno.push(una_cola_de_procesos.front());
                            una_cola_de_procesos.pop();
                            if (!una_cola_de_procesos.empty())
                            {
                                medidor = una_cola_de_procesos.front().tiempo_llegada;
                            }
                        }
                    }
                    else
                    {
                        if (cola_espera_uno.size() < 5)
                        {
                            cout << " - El proceso " << e_s.numero_proceso + 1 << " Sale del E/S y entra en la cola cpu " << endl;
                            system("pause");
                            cola_espera_uno.push(e_s);
                            e_s.tiempo_llegada = 0;
                        }
                    }
                }
            }
        }
        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada == 0))
        {

            if ((cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada == 0))
            {

                cout << " Se terminaron todos los procesos " << endl;
                system("pause");
            }
            if ((!cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada == 0))
            {

                cout << " - El proceso " << cola_espera_uno.front().numero_proceso + 1 << " Sale de la cola cpu y entra a la CPU " << endl;
                system("pause");
                cpu = cola_espera_uno.front();
                cola_espera_uno.pop();
            }
            if ((!cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada == 0))
            {

                cout << " - El proceso " << cola_espera_uno.front().numero_proceso + 1 << " Sale de la cola cpu y entra a la CPU " << endl;
                system("pause");
                cpu = cola_espera_uno.front();
                cola_espera_uno.pop();
                cout << " - El proceso numero: " << cola_espera_dos.front().numero_proceso + 1 << " sale de cola E/S y entra a E/S." << endl;
                system("pause");
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();
            }
            if ((cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada == 0))
            {

                cout << " - El proceso numero: " << cola_espera_dos.front().numero_proceso + 1 << " sale de cola E/S y entra a E/S." << endl;
                system("pause");
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();
            }
        }
        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada == 0))
        {

            while ((!cpu.cola_de_rafagas.empty()) && ((cpu.cola_de_rafagas.front().tipo == "CPU") || (cpu.cola_de_rafagas.front().tipo == "cpu")))
            {
                cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
            }
            if (cpu.cola_de_rafagas.empty() && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada == 0))
            {
                system("pause");

                cpu.tiempo_llegada = 0;
                cout << " TERMINA EL PROCESO: " << cpu.numero_proceso + 1 << endl;
            }
            if ((cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (!cpu.cola_de_rafagas.empty()))
            {

                cout << " - El proceso numero: " << cpu.numero_proceso + 1 << " sale del cpu y entra a la cola de espera E/S." << endl;
                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;
                system("pause");
            }
            if ((!cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (!cpu.cola_de_rafagas.empty()))
            {

                cout << " - El proceso numero: " << cpu.numero_proceso + 1 << " sale del cpu y entra a la cola de espera E/S." << endl;
                system("pause");
                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;
            }
            if ((!cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (!cpu.cola_de_rafagas.empty()))
            {

                cout << " - El proceso numero: " << cpu.numero_proceso + 1 << " sale del cpu y entra a la cola de espera E/S." << endl;
                system("pause");
                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;
            }
            if ((cpu.tiempo_llegada != 0) && (cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (!cpu.cola_de_rafagas.empty()))
            {

                cout << " - El proceso numero: " << cpu.numero_proceso + 1 << " sale del cpu y entra a la cola de espera E/S." << endl;
                system("pause");
                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;
            }
        }
        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada != 0))
        {

            while ((!e_s.cola_de_rafagas.empty()) && ((e_s.cola_de_rafagas.front().tipo == "E/S") || (e_s.cola_de_rafagas.front().tipo == "e/s")))
            {

                e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
                e_s.cola_de_rafagas.pop();
            }
            if ((cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (e_s.tiempo_llegada != 0))
            {

                cout << " - El proceso " << e_s.numero_proceso + 1 << " Sale del E/S y entra en la cola cpu " << endl;
                system("pause");
                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
            }
            if ((!cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (e_s.tiempo_llegada != 0))
            {

                cout << " - El proceso " << e_s.numero_proceso + 1 << " Sale del E/S y entra en la cola cpu " << endl;
                system("pause");
                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
            }
            if ((!cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (e_s.tiempo_llegada != 0))
            {

                cout << " - El proceso " << e_s.numero_proceso + 1 << " Sale del E/S y entra en la cola cpu " << endl;
                system("pause");
                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
            }
            if ((cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (e_s.tiempo_llegada != 0))
            {

                cout << " - El proceso " << e_s.numero_proceso + 1 << " Sale del E/S y entra en la cola cpu " << endl;
                system("pause");
                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
            }
        }
        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada != 0))
        {

            while ((!e_s.cola_de_rafagas.empty()) && ((e_s.cola_de_rafagas.front().tipo == "E/S") || (e_s.cola_de_rafagas.front().tipo == "e/s")))
            {

                e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
                e_s.cola_de_rafagas.pop();
            }

            while ((!cpu.cola_de_rafagas.empty()) && ((cpu.cola_de_rafagas.front().tipo == "CPU") || (cpu.cola_de_rafagas.front().tipo == "cpu")))
            {
                cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
            }

            if (cpu.cola_de_rafagas.empty() && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada != 0))
            {

                cout << " TERMINA EL PROCESO: " << cpu.numero_proceso + 1 << endl;
                cpu.tiempo_llegada = 0;
                system("pause");
            }
            if ((cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada != 0))
            {

                cout << " - El proceso " << e_s.numero_proceso + 1 << " Sale del E/S y entra en la cola cpu " << endl;
                system("pause");
                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
            }
            if ((!cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada != 0))
            {

                cout << " - El proceso " << e_s.numero_proceso + 1 << " Sale del E/S y entra en la cola cpu " << endl;
                system("pause");
                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
            }
            if ((!cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada != 0))
            {

                cout << " - El proceso " << e_s.numero_proceso + 1 << " Sale del E/S y entra en la cola cpu " << endl;
                system("pause");
                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
            }
            if ((cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada != 0))
            {

                cout << " - El proceso " << e_s.numero_proceso + 1 << " Sale del E/S y entra en la cola cpu " << endl;
                system("pause");
                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
            }
        }
        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() == 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada == 0))
        {

            cout << " - El proceso " << cola_espera_uno.front().numero_proceso + 1 << " Sale de la cola cpu y entra a la CPU " << endl;
            system("pause");
            cpu = cola_espera_uno.front();
            cola_espera_uno.pop();
        }
        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() == 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada == 0))
        {

            while ((!cpu.cola_de_rafagas.empty()) && ((cpu.cola_de_rafagas.front().tipo == "CPU") || (cpu.cola_de_rafagas.front().tipo == "cpu")))
            {
                cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
            }

            if (cpu.cola_de_rafagas.empty() && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada == 0))
            {
                cpu.tiempo_llegada = 0;
                cout << " TERMINA EL PROCESO: " << cpu.numero_proceso + 1 << endl;
                system("pause");
            }

            cout << " - El proceso numero: " << cpu.numero_proceso + 1 << " sale del cpu y entra a la cola de espera E/S." << endl;
            system("pause");
            cola_espera_dos.push(cpu);
            cpu.tiempo_llegada = 0;
        }
        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() == 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada != 0))
        {

            while ((!e_s.cola_de_rafagas.empty()) && ((e_s.cola_de_rafagas.front().tipo == "E/S") || (e_s.cola_de_rafagas.front().tipo == "e/s")))
            {

                e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
                e_s.cola_de_rafagas.pop();
            }

            while ((!cpu.cola_de_rafagas.empty()) && ((cpu.cola_de_rafagas.front().tipo == "CPU") || (cpu.cola_de_rafagas.front().tipo == "cpu")))
            {
                cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
            }

            if (cpu.cola_de_rafagas.empty() && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada != 0))
            {
                cpu.tiempo_llegada = 0;
                cout << " TERMINA EL PROCESO: " << cpu.numero_proceso + 1 << endl;
                system("pause");
            }
            cout << " - El proceso numero: " << cpu.numero_proceso + 1 << " sale del cpu y entra a la cola de espera E/S." << endl;
            system("pause");
            cola_espera_dos.push(cpu);
            cpu.tiempo_llegada = 0;
        }
        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() == 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada != 0))
        {

            while ((!e_s.cola_de_rafagas.empty()) && ((e_s.cola_de_rafagas.front().tipo == "E/S") || (e_s.cola_de_rafagas.front().tipo == "e/s")))
            {

                e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
                e_s.cola_de_rafagas.pop();
            }
            cout << " - El proceso " << cola_espera_uno.front().numero_proceso + 1 << " Sale de la cola cpu y entra a la CPU " << endl;
            system("pause");
            cpu = cola_espera_uno.front();
            cola_espera_uno.pop();
        }

        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() == 5) && (e_s.tiempo_llegada == 0))
        {

            cout << " - El proceso numero: " << cola_espera_dos.front().numero_proceso + 1 << " sale de cola E/S y entra a E/S." << endl;
            system("pause");
            e_s = cola_espera_dos.front();
            cola_espera_dos.pop();
        }

        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() == 5) && (e_s.tiempo_llegada == 0))
        {

            while ((!cpu.cola_de_rafagas.empty()) && ((cpu.cola_de_rafagas.front().tipo == "CPU") || (cpu.cola_de_rafagas.front().tipo == "cpu")))
            {
                cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
            }

            if (cpu.cola_de_rafagas.empty() && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada == 0))
            {
                cpu.tiempo_llegada = 0;
                cout << " TERMINA EL PROCESO: " << cpu.numero_proceso + 1 << endl;
                system("pause");
            }

            cout << " - El proceso numero: " << cola_espera_dos.front().numero_proceso + 1 << " sale de cola E/S y entra a E/S." << endl;
            system("pause");
            e_s = cola_espera_dos.front();
            cola_espera_dos.pop();
        }

        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() == 5) && (e_s.tiempo_llegada != 0))
        {

            while ((!e_s.cola_de_rafagas.empty()) && ((e_s.cola_de_rafagas.front().tipo == "E/S") || (e_s.cola_de_rafagas.front().tipo == "e/s")))
            {

                e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
                e_s.cola_de_rafagas.pop();
            }
            while ((!cpu.cola_de_rafagas.empty()) && ((cpu.cola_de_rafagas.front().tipo == "CPU") || (cpu.cola_de_rafagas.front().tipo == "cpu")))
            {
                cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
            }

            if (cpu.cola_de_rafagas.empty() && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada != 0))
            {
                cpu.tiempo_llegada = 0;
                cout << " TERMINA EL PROCESO: " << cpu.numero_proceso + 1 << endl;
                system("pause");
            }

            if (e_s.tiempo_llegada > una_cola_de_procesos.front().tiempo_llegada)
            {
                medidor = una_cola_de_procesos.front().tiempo_llegada;
                while ((e_s.tiempo_llegada >= medidor) && (cola_espera_uno.size() < 5) && (!una_cola_de_procesos.empty()))
                {
                    cout << " - Como el proceso: " << una_cola_de_procesos.front().numero_proceso + 1 << " llega antes que termine el proceso: " << e_s.numero_proceso + 1;
                    cout << " ingresa el proceso " << una_cola_de_procesos.front().numero_proceso + 1 << " a la cola de CPU" << endl;
                    system("pause");
                    cola_espera_uno.push(una_cola_de_procesos.front());
                    una_cola_de_procesos.pop();
                    if (!una_cola_de_procesos.empty())
                    {
                        medidor = una_cola_de_procesos.front().tiempo_llegada;
                    }
                }
            }
            else
            {
                if (cola_espera_uno.size() < 5)
                {
                    cout << " - El proceso " << e_s.numero_proceso + 1 << " Sale del E/S y entra en la cola cpu " << endl;
                    system("pause");
                    cola_espera_uno.push(e_s);
                    e_s.tiempo_llegada = 0;
                }
            }
        }

        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() == 5) && (e_s.tiempo_llegada != 0))
        {

            while ((!e_s.cola_de_rafagas.empty()) && ((e_s.cola_de_rafagas.front().tipo == "E/S") || (e_s.cola_de_rafagas.front().tipo == "e/s")))
            {

                e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
                e_s.cola_de_rafagas.pop();
            }
            if (e_s.tiempo_llegada > una_cola_de_procesos.front().tiempo_llegada)
            {
                medidor = una_cola_de_procesos.front().tiempo_llegada;
                while ((e_s.tiempo_llegada >= medidor) && (cola_espera_uno.size() < 5) && (!una_cola_de_procesos.empty()))
                {
                    cout << " - Como el proceso: " << una_cola_de_procesos.front().numero_proceso + 1 << " llega antes que termine el proceso: " << e_s.numero_proceso + 1;
                    cout << " ingresa el proceso " << una_cola_de_procesos.front().numero_proceso + 1 << " a la cola de CPU" << endl;
                    system("pause");
                    cola_espera_uno.push(una_cola_de_procesos.front());
                    una_cola_de_procesos.pop();
                    if (!una_cola_de_procesos.empty())
                    {
                        medidor = una_cola_de_procesos.front().tiempo_llegada;
                    }
                }
            }
            else
            {
                if (cola_espera_uno.size() < 5)
                {
                    cout << " - El proceso " << e_s.numero_proceso + 1 << " Sale del E/S y entra en la cola cpu " << endl;
                    system("pause");
                    cola_espera_uno.push(e_s);
                    e_s.tiempo_llegada = 0;
                }
            }
        }
        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() == 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada == 0))
        {

            cout << " - El proceso " << cola_espera_uno.front().numero_proceso + 1 << " Sale de la cola cpu y entra a la CPU " << endl;
            system("pause");
            cpu = cola_espera_uno.front();
            cola_espera_uno.pop();
        }
        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() == 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada == 0))
        {

            while ((!cpu.cola_de_rafagas.empty()) && ((cpu.cola_de_rafagas.front().tipo == "CPU") || (cpu.cola_de_rafagas.front().tipo == "cpu")))
            {
                cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
            }

            if (cpu.cola_de_rafagas.empty() && (cpu.tiempo_llegada != 0))
            {
                cpu.tiempo_llegada = 0;
                cout << " TERMINA EL PROCESO: " << cpu.numero_proceso + 1 << endl;
                system("pause");
            }

            cout << " - El proceso numero: " << cpu.numero_proceso + 1 << " sale del cpu y entra a la cola de espera E/S." << endl;
            system("pause");
            cola_espera_dos.push(cpu);
            cpu.tiempo_llegada = 0;
        }
        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() == 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada != 0))
        {

            while ((!e_s.cola_de_rafagas.empty()) && ((e_s.cola_de_rafagas.front().tipo == "E/S") || (e_s.cola_de_rafagas.front().tipo == "e/s")))
            {

                e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
                e_s.cola_de_rafagas.pop();
            }

            while ((!cpu.cola_de_rafagas.empty()) && ((cpu.cola_de_rafagas.front().tipo == "CPU") || (cpu.cola_de_rafagas.front().tipo == "cpu")))
            {
                cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
            }

            if (cpu.cola_de_rafagas.empty() && (cpu.tiempo_llegada != 0))
            {
                cpu.tiempo_llegada = 0;
                cout << " TERMINA EL PROCESO: " << cpu.numero_proceso + 1 << endl;
                system("pause");
            }
            cout << " - El proceso numero: " << cpu.numero_proceso + 1 << " sale del cpu y entra a la cola de espera E/S." << endl;
            system("pause");
            cola_espera_dos.push(cpu);
            cpu.tiempo_llegada = 0;
        }

        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() == 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada != 0))
        {

            while ((!e_s.cola_de_rafagas.empty()) && ((e_s.cola_de_rafagas.front().tipo == "E/S") || (e_s.cola_de_rafagas.front().tipo == "e/s")))
            {

                e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
                e_s.cola_de_rafagas.pop();
            }
            cout << " - El proceso " << cola_espera_uno.front().numero_proceso + 1 << " Sale de la cola cpu y entra a la CPU " << endl;
            system("pause");
            cpu = cola_espera_uno.front();
            cola_espera_uno.pop();
        }

        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() == 5) && (e_s.tiempo_llegada == 0))
        {

            cout << " - El proceso numero: " << cola_espera_dos.front().numero_proceso + 1 << " sale de cola E/S y entra a E/S." << endl;
            system("pause");
            e_s = cola_espera_dos.front();
            cola_espera_dos.pop();
        }

        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() == 5) && (e_s.tiempo_llegada == 0))
        {

            while ((!cpu.cola_de_rafagas.empty()) && ((cpu.cola_de_rafagas.front().tipo == "CPU") || (cpu.cola_de_rafagas.front().tipo == "cpu")))
            {
                cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
            }

            if (cpu.cola_de_rafagas.empty() && (cpu.tiempo_llegada != 0))
            {

                cpu.tiempo_llegada = 0;
                cout << " TERMINA EL PROCESO: " << cpu.numero_proceso + 1 << endl;
                system("pause");
            }
            cout << " - El proceso numero: " << cola_espera_dos.front().numero_proceso + 1 << " sale de cola E/S y entra a E/S." << endl;
            system("pause");
            e_s = cola_espera_dos.front();
            cola_espera_dos.pop();
        }

        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() == 5) && (e_s.tiempo_llegada != 0))
        {

            while ((!e_s.cola_de_rafagas.empty()) && ((e_s.cola_de_rafagas.front().tipo == "E/S") || (e_s.cola_de_rafagas.front().tipo == "e/s")))
            {

                e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
                e_s.cola_de_rafagas.pop();
            }
            while ((!cpu.cola_de_rafagas.empty()) && ((cpu.cola_de_rafagas.front().tipo == "CPU") || (cpu.cola_de_rafagas.front().tipo == "cpu")))
            {
                cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
            }

            if (cpu.cola_de_rafagas.empty() && (cpu.tiempo_llegada != 0))
            {
                cpu.tiempo_llegada = 0;
                cout << " TERMINA EL PROCESO: " << cpu.numero_proceso + 1 << endl;
                system("pause");
            }
            cout << " - El proceso " << e_s.numero_proceso + 1 << " Sale del E/S y entra en la cola cpu " << endl;
            system("pause");
            cola_espera_uno.push(e_s);
            e_s.tiempo_llegada = 0;
        }

        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() == 5) && (e_s.tiempo_llegada != 0))
        {

            while ((!e_s.cola_de_rafagas.empty()) && ((e_s.cola_de_rafagas.front().tipo == "E/S") || (e_s.cola_de_rafagas.front().tipo == "e/s")))
            {

                e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
                e_s.cola_de_rafagas.pop();
            }
            cout << " - El proceso " << e_s.numero_proceso + 1 << " Sale del E/S y entra en la cola cpu " << endl;
            system("pause");
            cola_espera_uno.push(e_s);
            e_s.tiempo_llegada = 0;
        }
    } // FIN DEL WHILE PRINCIPAL

    if ((una_cola_de_procesos.empty()) && (cola_espera_uno.empty()) && (cola_espera_uno.empty()) && (cpu.cola_de_rafagas.empty()) && (e_s.cola_de_rafagas.empty()))
    {
        cout << "=====================\nYa no quedan procesos.\n=====================" << endl;
        system("pause");
    }
}

int Cantidad_de_procesos(){
    string input;
    int num;
    bool aux = true;

    while (aux == true)
    {
        input = "/0";
        cout << "\nIngrese la cantidad de procesos a trabajar (su numero  debe estar entre 1 y 10): ";
        getline(cin, input);

        try
        {
            num = stoi(input);
            if (num >= 1 && num <= 10)
            {
                //cout << "El numero ingresado es valido." << endl;
                aux = false;
            }
            else
            {
                cout << "-----------------------------------------" 
                << endl << "[!] El numero ingresado no esta entre 1 y 10." << endl 
                << "-----------------------------------------";
                system("pause");
                //system("cls");
            }
        }
        catch (invalid_argument e)
        {
            cout << "-----------------------------------------" 
                << endl << "[!] El input ingresado no es un numero valido." << endl 
                << "-----------------------------------------";
                system("pause");
            //system("cls");
        }
    }
    return num;
}

int main(){
    int n, k;
    queue<proceso> cola_de_procesos;
    int cont = 0;
    n = Cantidad_de_procesos();
    proceso cantidad_procesos[n];
    llenar_proceso(cantidad_procesos, n);

    int i, j;
    proceso aux;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (cantidad_procesos[j].tiempo_llegada > cantidad_procesos[j + 1].tiempo_llegada)
            {
                aux = cantidad_procesos[j];
                cantidad_procesos[j] = cantidad_procesos[j + 1];
                cantidad_procesos[j + 1] = aux;
            }
        }
    }

    for (k = 0; k < n; k++)
    {
        cola_de_procesos.push(cantidad_procesos[k]);
    }

    llenar_queue(cola_de_procesos);

    return 0;
}
