/**
 * @file serial.cpp
 * @author Abarca Robles Diego, Cruz Alvarez Fernando, Huang Rojas Armando Mao
 * Li, Oropeza Rangel Luis
 * @brief Programa de prueba del primer prototipo de Master FX4OS donde se
 * prueba la comunicacion serial entre el arduino y la computadora para cambiar
 * los bancos.
 * @version 0.1
 * @date 2026-10-09
 *
 * @copyright Copyright (c) 2026
 */
#include "SerialPort.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>

char obtenerTeclaSinEnter() { // Función para leer teclas similar a getch()
  char buf = 0;
  struct termios old;

  tcgetattr(STDIN_FILENO, &old);

  struct termios current = old;

  current.c_lflag &= ~ICANON;
  current.c_lflag &= ~ECHO;

  tcsetattr(STDIN_FILENO, TCSANOW, &current);

  read(STDIN_FILENO, &buf, 1);

  tcsetattr(STDIN_FILENO, TCSANOW, &old);

  return buf;
}

int main() {
  std::cout << "Master FX4OS" << std::endl;
  SerialPort arduino(
      "/dev/ttyUSB0"); // Creamos un puerto para empezar a trabajar

  char opc;
  std::cout
      << "\nPresiona n (Siguiente Banco), p (Banco Anterior) o q (Salir): \n";

  while (true) {
    opc = obtenerTeclaSinEnter();

    if (opc == 'q' || opc == 'Q') {
      std::cout << "\nSaliendo..." << std::endl;
      break;
    }

    if (opc == 'n' || opc == 'N' || opc == 'p' || opc == 'P') {
      std::cout << "Enviando: " << opc << std::endl;
      arduino.enviarDato(opc);

      usleep(100000);

      std::string respuesta = arduino.leerDato();
      if (!respuesta.empty()) {
        std::cout << respuesta;
      }
    } else {
      std::cout << "opcion no valida" << std::endl;
    }
  }

  return 0;
}
