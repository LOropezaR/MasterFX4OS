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

char obtenerTeclaSinEnter() {
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
  std::cout << "Iniciando comunicación con Arduino..." << std::endl;
  SerialPort arduino("/dev/ttyUSB0");

  char opcion;
  std::cout << "\nPresiona 1 (Encender), 0 (Apagar) o q (Salir): \n";

  while (true) {
    opcion = obtenerTeclaSinEnter();

    if (opcion == 'q' || opcion == 'Q') {
      std::cout << "\nSaliendo..." << std::endl;
      break;
    }

    if (opcion == '1' || opcion == '0') {
      std::cout << "Enviando: " << opcion << std::endl;
      arduino.enviarDato(opcion);

      usleep(100000);

      std::string respuesta = arduino.leerDato();
      if (!respuesta.empty()) {
        std::cout << "Arduino respondió: " << respuesta;
      }
    }
  }

  return 0;
}
