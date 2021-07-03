# Gestor de Tareas - RTOS

_El RTOS estaria haciendo tres tareas, de hacer que cada diodo (son tres en total) trabajen a diferentes frecuencias. El pic utilizado es el 12F675.

## Notas
Este gestor de tareas fue insipirado en el tutorial de youtube: https://www.youtube.com/watch?v=79TZ08jM7Jc
El tutorial trabajaba con un PIC que contiene  mas recursos con el que trabajamos para este pequeño desarrollo de "gestor de tareas" o RTOS, este ultimo tiene algunos defectos, es un poco inestable y se daran cuenta si lo ponen en practica.
La grabacion se llevo a cabo con un clon de la plaqueta original del pickit2, se uso el software pickit 2 tambien para realizar la programacion.
Si bien se trabajo en una plataforma MPLAB XC8, en el tutorial del video se observa que trabaja con micro C. La plataforma MPLAB XC8 genera varios archivos al compilar el codigo, el que se carga en el PIC es el que tiene extencion xxxx.HEX