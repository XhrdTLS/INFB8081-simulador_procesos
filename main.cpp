#include <iostream>
#include <string.h>
#include <string>
#include <queue>

using namespace std;

struct Rafaga
{
    string tipo;
    float duracion;
    // Rafaga *siguiente;
};

struct proceso
{

    int numero_proceso;
    float tiempo_llegada;
    int numero_rafagas;
    queue<Rafaga> cola_de_rafagas;
};

void llenar_rafaga(Rafaga una_rafaga, int cant)
{

    int i = 0;
    queue<Rafaga> cola_de_rafagas;

    while (i < cant)
    {
        cola_de_rafagas.push(una_rafaga);
    }
};

bool validar_rafaga(queue<Rafaga> una_cola_de_rafaga)
{

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

void llenar_proceso(proceso x[], int n)
{
    queue<Rafaga> cola_de_rafagas;
    Rafaga una_rafaga;

    //
    string tpo;
    int i, j;
    i = 0;
    while (i < n)
    {
        x[i].numero_proceso = i;
        cout << "Cual es el tiempo de llegada del proceso numero: " << x[i].numero_proceso + 1 << "?, "
             << "se tomara en segundos: " << endl;
        cin >> x[i].tiempo_llegada;
        fflush(stdin);
        cout << "Cuantas rafagas tendra el proceso?: " << endl;
        cin >> x[i].numero_rafagas;
        fflush(stdin);
        // llenar rafagas
        j = 0;
        do
        {
            while (j < x[i].numero_rafagas)
            {

                do
                {
                    // validador_de_rafaga = 0;
                    cout << "Rafaga numero: " << j + 1 << endl;
                    cout << "Rafaga de CPU o E/S: " << endl;
                    getline(cin, una_rafaga.tipo);
                    cout << " Antes de llenar la duracion" << una_rafaga.tipo << endl;
                    fflush(stdin);
                    if ((una_rafaga.tipo == "CPU") || (una_rafaga.tipo == "E/S") || (una_rafaga.tipo == "cpu") || (una_rafaga.tipo == "e/s"))
                    {
                        cout << "Cuanto durara la rafaga?: " << endl;
                        cin >> una_rafaga.duracion;
                        fflush(stdin);
                    }
                    /*if(((j == 0)&&((una_rafaga.tipo != "CPU")&&(una_rafaga.tipo != "cpu")))||((j + 1 == x[i].numero_rafagas)&&((una_rafaga.tipo != "CPU")&&(una_rafaga.tipo != "cpu")))){cout << "Rafaga no valida. Ingrese la rafaga nuevamente." << endl;validador_de_rafaga = 1;}*/
                } while ((una_rafaga.tipo != "CPU") && (una_rafaga.tipo != "E/S") && (una_rafaga.tipo != "cpu") && (una_rafaga.tipo != "e/s"));
                /*}while(((una_rafaga.tipo != "CPU") && (una_rafaga.tipo != "E/S")&& (una_rafaga.tipo != "cpu")&& (una_rafaga.tipo != "e/s"))&& (validador_de_rafaga == 1));*/
                fflush(stdin);
                // Ver si funciona el hacer la cola de rafagas
                cout << "INSERTAR" << endl;
                x[i].cola_de_rafagas.push(una_rafaga);
                // POSIBLE ELIMINAR
                cola_de_rafagas.push(una_rafaga);
                j++;
            }
            if (!validar_rafaga(cola_de_rafagas))
            {
                cout << "Rafaga no valida. " << endl;
                cout << "La primera y la ultima rafaga deben ser CPU." << '\n'
                     << "Ingrese las rafagas nuevamente." << endl;
                j = 0;
                cola_de_rafagas.pop();
                x[i].cola_de_rafagas.pop();
            }

        } while (!validar_rafaga(cola_de_rafagas));
        i++;
    }
}

// que sea una lista de entrada, pasar el arreglo de procesos a una lista
void llenar_queue(queue<proceso> una_cola_de_procesos)
{

    queue<proceso> cola_espera_uno, cola_espera_dos;
    proceso cpu, e_s;
    float medidor = 0;
    // Para decir que estan vacios el cpu y e/s
    cpu.tiempo_llegada = 0;
    e_s.tiempo_llegada = 0;
    // no se si vaya este while, preguntar
    while ((!una_cola_de_procesos.empty()) || (!cola_espera_uno.empty()) || (!cola_espera_dos.empty()) || (cpu.tiempo_llegada != 0) || (e_s.tiempo_llegada != 0))
    {

        // 1
        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada == 0))
        {

            if ((cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada == 0))
            {

                cola_espera_uno.push(una_cola_de_procesos.front());
                una_cola_de_procesos.pop();
                cout << "El proceso numero : " << cola_espera_uno.front().numero_proceso + 1 << " ingreso a la cola de CPU" << endl;
                system("pause");
                // system("cls");
            }

            if ((!cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada == 0))
            {
                /*duda respecto a si entra o no tambien el que este en la cola de procesos en la cola espera uno
                yo creo que ya, que debe pasar el tiempo de rafaga del primero que entro a la cola
                */
                cpu = cola_espera_uno.front();
                cola_espera_uno.pop();

                cout << "El proceso numero: " << cpu.numero_proceso + 1 << " entro a la CPU" << endl;
                system("pause");
                /*cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;
                e_s = cola_espera_dos.front();
                e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
                e_s.cola_de_rafagas.pop();*/
            }

            if ((!cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada == 0))
            {

                cpu = cola_espera_uno.front();
                cola_espera_uno.pop();
                cout << "El proceso numero: " << cpu.numero_proceso + 1 << " entro a la CPU." << endl;
                system("pause");
                // cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                // cpu.cola_de_rafagas.pop();
                // cola_espera_dos.push(cpu);
                // cpu.tiempo_llegada = 0;
                //----------------e_s = cola_espera_dos.front();
                //----------------cola_espera_dos.pop();
                // e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
                // e_s.cola_de_rafagas.pop();
            }
            if ((cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada == 0))
            {
                // creo que no va, por la razon de que debe terminar la rafaga del proceso que entra e/s
                /*cola_espera_uno.push(una_cola_de_procesos.front());
                una_cola_de_procesos.pop();
                */
                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();

                cout << "El proceso numero: " << e_s.numero_proceso + 1 << " sale de cola E/S y entra a E/S." << endl;
                system("pause");
            }
        } // 2--------------ESTA ES LA CORRECTA

        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada == 0))
        {

            while ((!cpu.cola_de_rafagas.empty()) && ((cpu.cola_de_rafagas.front().tipo == "CPU") || (cpu.cola_de_rafagas.front().tipo == "cpu")))
            {
                cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
            }

            if ((cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada == 0))
            {
                /* if(cpu.tiempo_llegada == una_cola_de_procesos.front().tiempo_llegada){ medidor = una_cola_de_procesos.front().tiempo_llegada; while((cpu.tiempo_llegada >=medidor)&&(cola_espera_uno.size() < 5)&&(!una_cola_de_procesos.empty())){cola_espera_uno.push(una_cola_de_procesos.front());una_cola_de_procesos.pop();medidor = una_cola_de_procesos.front().tiempo_llegada;}cola_espera_dos.push(cpu);cpu.tiempo_llegada = 0;}*/ // cola procesos no deberia ir ahi, deberia preguntar antes que no este vacia, tal vez antes
                if (cpu.tiempo_llegada >= una_cola_de_procesos.front().tiempo_llegada)
                {

                    medidor = una_cola_de_procesos.front().tiempo_llegada;
                    while ((cpu.tiempo_llegada >= medidor) && (cola_espera_uno.size() < 5) && (!una_cola_de_procesos.empty()))
                    {
                        cout << "Como el proceso: " << una_cola_de_procesos.front().numero_proceso + 1 << " llega antes que termine el proceso: " << cpu.numero_proceso + 1;
                        cout << " ingresa el proceso " << una_cola_de_procesos.front().numero_proceso + 1 << " a la cola de CPU" << endl;
                        cola_espera_uno.push(una_cola_de_procesos.front());
                        una_cola_de_procesos.pop();

                        if (!una_cola_de_procesos.empty())
                        {
                            medidor = una_cola_de_procesos.front().tiempo_llegada;
                        }
                    }
                    if (cpu.cola_de_rafagas.empty())
                    {
                        cpu.tiempo_llegada = 0;
                        cout << "TERMINA EL PROCESO: " << cpu.numero_proceso + 1 << endl;
                        cout << "una_cola_de_procesos.empty() 2.1.4: " << una_cola_de_procesos.empty() << endl;
                        cout << "cola_espera_uno.empty() 2.1.4: " << cola_espera_uno.empty() << endl;
                        cout << "cola_espera_uno.size() 2.1.4: " << cola_espera_uno.size() << endl;
                        cout << "cpu.tiempo_llegada 2.1.4: " << cpu.tiempo_llegada << endl;
                        cout << "cola_espera_dos.empty() 2.1.4: " << cola_espera_dos.empty() << endl;
                        cout << "cola_espera_dos.size() 2.1.4: " << cola_espera_dos.size() << endl;
                        cout << "e_s.tiempo_llegada 2.1.4: " << e_s.tiempo_llegada << endl;
                        system("pause");
                    }
                    else
                    {
                        cola_espera_dos.push(cpu);
                        cpu.tiempo_llegada = 0;
                        cout << "El proceso: " << cola_espera_dos.front().numero_proceso + 1 << "sale de la cpu y entra a la cola E/S" << endl;
                    }
                }
                else
                {
                    cout << "Como el proceso: " << cpu.numero_proceso + 1 << " llega antes que termine el proceso: " << una_cola_de_procesos.front().numero_proceso + 1;
                    cout << " ingresa el proceso " << cpu.numero_proceso + 1 << endl;
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
                        cout << "Como el proceso: " << una_cola_de_procesos.front().numero_proceso + 1 << " llega antes que termine el proceso: " << cpu.numero_proceso + 1;
                        cout << " ingresa el proceso " << una_cola_de_procesos.front().numero_proceso + 1 << " a la cola de CPU" << endl;
                        cola_espera_uno.push(una_cola_de_procesos.front());
                        una_cola_de_procesos.pop();
                        if (!una_cola_de_procesos.empty())
                        {
                            medidor = una_cola_de_procesos.front().tiempo_llegada;
                        }
                    }

                    cola_espera_dos.push(cpu);
                    cpu.tiempo_llegada = 0;
                }
                else
                {

                    cola_espera_dos.push(cpu);
                    cpu.tiempo_llegada = 0;
                }
            } //////////////////////////////////////////////////////////////////////////////////
            if ((!cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada == 0))
            {

                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();
            }
            if ((cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada == 0))
            {

                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();
            }

        } // 3 cambios para revisar
        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada != 0))
        {
            cout << "3" << endl;

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
                        cola_espera_uno.push(e_s);
                        e_s.tiempo_llegada = 0;
                    }
                }
            }
            if ((!cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada != 0))
            {

                cpu = cola_espera_uno.front();
                cola_espera_uno.pop();
            }
            if ((!cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada != 0))
            {

                cpu = cola_espera_uno.front();
                cola_espera_uno.pop();
            }
            if ((cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada != 0))
            {

                if (e_s.tiempo_llegada > una_cola_de_procesos.front().tiempo_llegada)
                {
                    cola_espera_uno.push(una_cola_de_procesos.front());
                    una_cola_de_procesos.pop();
                }
                else
                {
                    if (cola_espera_uno.size() < 5)
                    {
                        cola_espera_uno.push(e_s);
                        e_s.tiempo_llegada = 0;
                    }
                }
            }
        }
        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada != 0))
        {
            cout << "4" << endl;
            while ((!cpu.cola_de_rafagas.empty()) && ((cpu.cola_de_rafagas.front().tipo == "CPU") || (cpu.cola_de_rafagas.front().tipo == "cpu")))
            {
                cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
            }
            if (cpu.cola_de_rafagas.empty())
            {
                // TERMINA EL PROCESO
            }

            while ((!e_s.cola_de_rafagas.empty()) && ((e_s.cola_de_rafagas.front().tipo == "E/S") || (e_s.cola_de_rafagas.front().tipo == "e/s")))
            {

                e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
                e_s.cola_de_rafagas.pop();
            }

            if ((cola_espera_uno.empty()) && (cola_espera_dos.empty()))
            {

                if (cpu.tiempo_llegada <= e_s.tiempo_llegada)
                {

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
                            cola_espera_uno.push(e_s);
                            e_s.tiempo_llegada = 0;
                        }
                    }
                }
            }
            if ((!cola_espera_uno.empty()) && (cola_espera_dos.empty()))
            {

                if (cpu.tiempo_llegada <= e_s.tiempo_llegada)
                {

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
                            cola_espera_uno.push(e_s);
                            e_s.tiempo_llegada = 0;
                        }
                    }
                }
            }

            if ((!cola_espera_uno.empty()) && (!cola_espera_dos.empty()))
            {

                if ((cpu.tiempo_llegada <= e_s.tiempo_llegada) && (cola_espera_dos.size() < 5))
                {

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
                            cola_espera_uno.push(e_s);
                            e_s.tiempo_llegada = 0;
                        }
                    }
                }
            }
            if ((cola_espera_uno.empty()) && (!cola_espera_dos.empty()))
            {

                if ((cpu.tiempo_llegada <= e_s.tiempo_llegada) && (cola_espera_dos.size() < 5))
                {

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
                            cola_espera_uno.push(e_s);
                            e_s.tiempo_llegada = 0;
                        }
                    }
                }
            }
        } // 2.1
        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada == 0))
        {

            cout << "2.1" << endl;
            if ((cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada == 0))
            {
                cout << "2.1.1" << endl;
                // TERMINARON TODOS LOS PROCESOS
            }
            if ((!cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada == 0))
            {
                cout << "2.1.2" << endl;
                cpu = cola_espera_uno.front();
                cola_espera_uno.pop();
            }
            if ((!cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada == 0))
            {
                cout << "2.1.3" << endl;
                cpu = cola_espera_uno.front();
                cola_espera_uno.pop();

                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();
            }
            if ((cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada == 0) && (e_s.tiempo_llegada == 0))
            {
                cout << "2.1.4" << endl;

                e_s = cola_espera_dos.front();
                cola_espera_dos.pop();

                system("pause");
            }
        } // 2.2
        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada == 0))
        {
            cout << "2.2" << endl;
            while ((!cpu.cola_de_rafagas.empty()) && ((cpu.cola_de_rafagas.front().tipo == "CPU") || (cpu.cola_de_rafagas.front().tipo == "cpu")))
            {
                cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
            }
            if (cpu.cola_de_rafagas.empty())
            {
                system("pause");

                cpu.tiempo_llegada = 0;
                cout << "TERMINA EL PROCESO: " << cpu.numero_proceso << endl;
            }
            if ((cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (!cpu.cola_de_rafagas.empty()))
            {
                cout << "2.2.1" << endl;
                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;
                system("pause");
            }
            if ((!cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (!cpu.cola_de_rafagas.empty()))
            {
                cout << "2.2.2" << endl;

                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;
            }
            if ((!cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (!cpu.cola_de_rafagas.empty()))
            {
                cout << "2.2.3" << endl;
                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;
            }
            if ((cpu.tiempo_llegada != 0) && (cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (!cpu.cola_de_rafagas.empty()))
            {
                cout << "2.2.4" << endl;
                cola_espera_dos.push(cpu);
                cpu.tiempo_llegada = 0;
            }

        } // 2.3
        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada != 0))
        {
            cout << "2.3" << endl;
            while ((!e_s.cola_de_rafagas.empty()) && ((e_s.cola_de_rafagas.front().tipo == "E/S") || (e_s.cola_de_rafagas.front().tipo == "e/s")))
            {

                e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
                e_s.cola_de_rafagas.pop();
            }
            if ((cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (e_s.tiempo_llegada != 0))
            {
                cout << "2.3.1" << endl;

                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
                system("pause");
            }
            if ((!cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (e_s.tiempo_llegada != 0))
            {
                cout << "2.3.2" << endl;
                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
            }
            if ((!cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (e_s.tiempo_llegada != 0))
            {
                cout << "2.3.3" << endl;
                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
            }
            if ((cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (e_s.tiempo_llegada != 0))
            {
                cout << "2.3.4" << endl;
                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
            }
        } // 2.4
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
            if (cpu.cola_de_rafagas.empty())
            {
                // TERMINA EL PROCESO
            }
            if ((cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada != 0))
            {

                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
            }
            if ((!cola_espera_uno.empty()) && (cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada != 0))
            {

                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
            }
            if ((!cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada != 0))
            {

                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
            }
            if ((cola_espera_uno.empty()) && (!cola_espera_dos.empty()) && (cpu.tiempo_llegada != 0) && (e_s.tiempo_llegada != 0))
            {

                cola_espera_uno.push(e_s);
                e_s.tiempo_llegada = 0;
            }
        } // 3.1
        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() == 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada == 0))
        {
            cout << "3.1" << endl;
            cpu = cola_espera_uno.front();
            cola_espera_uno.pop();

        } // 3.2
        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() == 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada == 0))
        {
            cout << "3.2" << endl;
            while ((!cpu.cola_de_rafagas.empty()) && ((cpu.cola_de_rafagas.front().tipo == "CPU") || (cpu.cola_de_rafagas.front().tipo == "cpu")))
            {
                cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
            }

            if (cpu.cola_de_rafagas.empty())
            {
                // TERMINA EL PROCESO
            }

            cola_espera_dos.push(cpu);
            cpu.tiempo_llegada = 0;

        } // 3.3
        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() == 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada != 0))
        {
            cout << "3.3" << endl;
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

            if (cpu.cola_de_rafagas.empty())
            {
                // TERMINA EL PROCESO
            }

            cola_espera_dos.push(cpu);
            cpu.tiempo_llegada = 0;
        }
        // 3.4
        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() == 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada != 0))
        {
            cout << "3.4" << endl;
            while ((!e_s.cola_de_rafagas.empty()) && ((e_s.cola_de_rafagas.front().tipo == "E/S") || (e_s.cola_de_rafagas.front().tipo == "e/s")))
            {

                e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
                e_s.cola_de_rafagas.pop();
            }

            cpu = cola_espera_uno.front();
            cola_espera_uno.pop();
        }

        // 4.1 aca quede
        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() == 5) && (e_s.tiempo_llegada == 0))
        {
            cout << "4.1" << endl;
            e_s = cola_espera_dos.front();
            cola_espera_dos.pop();
        }
        // 4.2
        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() == 5) && (e_s.tiempo_llegada == 0))
        {
            cout << "4.2" << endl;
            while ((!cpu.cola_de_rafagas.empty()) && ((cpu.cola_de_rafagas.front().tipo == "CPU") || (cpu.cola_de_rafagas.front().tipo == "cpu")))
            {
                cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
            }

            if (cpu.cola_de_rafagas.empty())
            {
                // TERMINA EL PROCESO
            }

            e_s = cola_espera_dos.front();
            cola_espera_dos.pop();
        }
        // 4.3
        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() == 5) && (e_s.tiempo_llegada != 0))
        {
            cout << "4.3" << endl;

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

            if (cpu.cola_de_rafagas.empty())
            {
                // TERMINA EL PROCESO
            }

            if (e_s.tiempo_llegada > una_cola_de_procesos.front().tiempo_llegada)
            {
                medidor = una_cola_de_procesos.front().tiempo_llegada;
                while ((e_s.tiempo_llegada >= medidor) && (cola_espera_uno.size() < 5) && (!una_cola_de_procesos.empty()))
                {
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
                    cola_espera_uno.push(e_s);
                    e_s.tiempo_llegada = 0;
                }
            }
        }
        // 4.4
        if ((!una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() == 5) && (e_s.tiempo_llegada != 0))
        {
            cout << "4.4" << endl;
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
                    cola_espera_uno.push(e_s);
                    e_s.tiempo_llegada = 0;
                }
            }
        } // 5.1
        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() == 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada == 0))
        {
            cout << "5.1" << endl;
            cpu = cola_espera_uno.front();
            cola_espera_uno.pop();
        } // 5.2
        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() == 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada == 0))
        {
            cout << "5.2" << endl;
            while ((!cpu.cola_de_rafagas.empty()) && ((cpu.cola_de_rafagas.front().tipo == "CPU") || (cpu.cola_de_rafagas.front().tipo == "cpu")))
            {
                cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
            }

            if (cpu.cola_de_rafagas.empty())
            {
                // TERMINA EL PROCESO
            }

            cola_espera_dos.push(cpu);
            cpu.tiempo_llegada = 0;

        } // 5.3
        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() == 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada != 0))
        {
            cout << "5.3" << endl;
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

            if (cpu.cola_de_rafagas.empty())
            {
                // TERMINA EL PROCESO
            }

            cola_espera_dos.push(cpu);
            cpu.tiempo_llegada = 0;
        }
        // 5.4
        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() == 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() < 5) && (e_s.tiempo_llegada != 0))
        {
            cout << "5.4" << endl;
            while ((!e_s.cola_de_rafagas.empty()) && ((e_s.cola_de_rafagas.front().tipo == "E/S") || (e_s.cola_de_rafagas.front().tipo == "e/s")))
            {
                e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
                e_s.cola_de_rafagas.pop();
            }

            cpu = cola_espera_uno.front();
            cola_espera_uno.pop();
        }
        // 6.1
        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() == 5) && (e_s.tiempo_llegada == 0))
        {
            cout << "6.1" << endl;
            e_s = cola_espera_dos.front();
            cola_espera_dos.pop();
        }
        // 6.2
        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada != 0) && (cola_espera_dos.size() == 5) && (e_s.tiempo_llegada == 0))
        {
            cout << "6.2" << endl;
            while ((!cpu.cola_de_rafagas.empty()) && ((cpu.cola_de_rafagas.front().tipo == "CPU") || (cpu.cola_de_rafagas.front().tipo == "cpu")))
            {
                cpu.tiempo_llegada = cpu.tiempo_llegada + cpu.cola_de_rafagas.front().duracion;
                cpu.cola_de_rafagas.pop();
            }

            if (cpu.cola_de_rafagas.empty())
            {
                // TERMINA EL PROCESO
            }

            e_s = cola_espera_dos.front();
            cola_espera_dos.pop();
        }
        // 6.3
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

            if (cpu.cola_de_rafagas.empty())
            {
                // TERMINA EL PROCESO
            }

            cola_espera_uno.push(e_s);
            e_s.tiempo_llegada = 0;
        }
        // 6.4
        if ((una_cola_de_procesos.empty()) && (cola_espera_uno.size() < 5) && (cpu.tiempo_llegada == 0) && (cola_espera_dos.size() == 5) && (e_s.tiempo_llegada != 0))
        {
            while ((!e_s.cola_de_rafagas.empty()) && ((e_s.cola_de_rafagas.front().tipo == "E/S") || (e_s.cola_de_rafagas.front().tipo == "e/s")))
            {

                e_s.tiempo_llegada = e_s.tiempo_llegada + e_s.cola_de_rafagas.front().duracion;
                e_s.cola_de_rafagas.pop();
            }
            cola_espera_uno.push(e_s);
            e_s.tiempo_llegada = 0;
        }
    } // FIN DEL WHILE PRINCIPAL

    if ((una_cola_de_procesos.empty()) && (cola_espera_uno.empty()) && (cola_espera_uno.empty()) && (cpu.cola_de_rafagas.empty()) && (e_s.cola_de_rafagas.empty()))
    {
        cout << "Ya no quedan procesos." << endl;
    }
}

int Cantidad_de_procesos()
{
    string input;
    int num;
    bool aux = true;

    while (aux == true)
    {
        input = "/0";
        cout << "Ingrese un numero entre 1 y 10: ";
        getline(cin, input);

        try
        {
            num = stoi(input);
            if (num >= 1 && num <= 10)
            {
                cout << "El numero ingresado es valido." << endl;
                aux = false;
            }
            else
            {
                cout << "El numero ingresado no esta entre 1 y 10." << endl;
                system("pause");
                system("cls");
            }
        }
        catch (invalid_argument e)
        {
            cout << "El input ingresado no es un numero valido." << endl;
            system("pause");
            system("cls");
        }
    }
    cout << "El numero ingresado es: " << num << endl;
    return num;
}

int main()
{
    int n, k;
    queue<proceso> cola_de_procesos;

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
