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
 *
 */
#include <fcntl.h>
#include <iostream>
#include <ostream>
#include <termios.h>
#include <unistd.h>
/**
 * ADVERTENCIA PINGÜINITOS: este programa sólo funciona en sistemas linux.
 * Para windows se utilizan otras librerías pero los principios son los mismos
 *
 **/
int main() {
  const char *port = "/dev/ttyUSB0";
  int serial_fd = open(port, O_RDWR | O_NOCTTY);

  if (serial_fd < 0) {
    std::cerr << "Error al abrir el puerto" << std::endl;
    return 1;
  }

  struct termios tty;
  tcgetattr(serial_fd, &tty);

  // Configuracion del puerto para enviar y recibir datos
  tty.c_cflag &= ~PARENB;
  tty.c_cflag &= ~CSTOP;
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;
  tty.c_cflag &= ~CRTSCTS;
  tty.c_cflag |= CREAD | CLOCAL;

  tty.c_cflag &= ~ICANON;
  tty.c_cflag &= ~ECHO;

  tty.c_cc[VMIN] = 0;
  tty.c_cc[VTIME] = 5;

  cfsetispeed(&tty, B9600);
  cfsetospeed(&tty, B9600);
  tcsetattr(serial_fd, TCSANOW, &tty);

  sleep(2);

  char opc;
  char buffer[256];

  std::cout << "Master FX4OS" << std::endl;

  while (true) {
    std::cout << "a) Configurar Bancos" << std::endl;
    std::cout << "q) Salir" << std::endl;
    std::cout << "> ";
    std::cin >> opc;

    if (opc == 'q' || opc == 'Q') {
      std::cout << "Saliendo ..." << std::endl;
      break;
    }

    switch (opc) {
    case 'a':
      std::cout << "Seleccionar banco:";

      break;
    }
  }
}
