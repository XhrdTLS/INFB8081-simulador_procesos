# Simulador de Procesos
Simulador de procesos de un Sistema Operativo, basado en C++

## Detalles de funcionamiento
El programa requiere que se sigan los siguientes pasos (si se está usando la versión ejecutable de ***main.cpp***):
- Se debe ingresar la *cantidad* de procesos, los que van del **1 al 10**.

- Para continuar se debe indicar el tiempo en que llega el proceso x (esto en segundos), condiderando que los procesos tienen un tiempo de llegada predefinido, por lo que no importa el orden en que se indiquen, puesto que el programa es quién los ordena postteriormente.

- Luego, indicar la cantidad de *ráfagas* del proceso.

- Dependiendo de las ráfagas, tendrá que indicar si es de tipo *CPU* o *E/S* (entrada/salida), y cuánto durará la ráfaga respectivamente.