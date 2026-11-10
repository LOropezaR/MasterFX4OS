/**
 * @file serial_port.cpp
 * @author Abarca Robles Diego, Cruz Alvarez Fernando, Huang Rojas Armando Mao
 * Li, Oropeza Rangel Luis
 * @brief Definciones de la biblioteca para establecer la comunicacion serial
 * entre el arduino y la computadora
 * @version 0.1
 * @date 2026-10-09
 *
 * @copyright Copyright (c) 2026
 *
 */

#include "SerialPort.h"
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>

SerialPort::SerialPort(
    const char *portName) { // Definición del método de contrucción
  serial_fd = open(portName, O_RDWR | O_NOCTTY);

  if (serial_fd < 0) { // verifica que el puerto se haya abierto correctamente
    std::cerr << "Error abriendo el puerto " << portName << std::endl;
    return;
  }

  struct termios tty; // Struct que nos permite configurar la comunicación
                      // serial
  tcgetattr(serial_fd, &tty);

  tty.c_cflag &= ~PARENB;        // Sin bit de paridad
  tty.c_cflag &= ~CSTOPB;        // 1 bit de parada
  tty.c_cflag &= ~CSIZE;         // Limpiar la máscara de tamaño
  tty.c_cflag |= CS8;            // 8 bits de datos
  tty.c_cflag &= ~CRTSCTS;       // Sin control de flujo por hardware
  tty.c_cflag |= CREAD | CLOCAL; // Activar lectura y modo local

  // Desactivar el procesamiento de terminal para recibir datos "crudos"
  tty.c_lflag &= ~ICANON;
  tty.c_lflag &= ~ECHO;

  tty.c_cc[VMIN] = 0;  // cantidad mínima de carácteres a leer
  tty.c_cc[VTIME] = 5; // tiempo de espera máximo de 0.5 s

  cfsetispeed(&tty, B9600);
  cfsetospeed(&tty, B9600);
  tcsetattr(serial_fd, TCSANOW, &tty); // Se guarda la configuracion
                                       // del puerto

  sleep(2); // Esperar a que el Arduino se reinicie
}

SerialPort::~SerialPort() { // Definición del destructor del puerto
  if (serial_fd >= 0) {
    close(serial_fd);
  }
}

bool SerialPort::enviarDato(
    char dato) { // Definición del método para enviar datos a través del puerto
  if (serial_fd < 0)
    return false;
  return write(serial_fd, &dato, 1) > 0;
}

std::string SerialPort::leerDato() { // Definición del método para recibir datos
  if (serial_fd < 0)
    return "";

  char buffer[256];
  memset(buffer, 0, sizeof(buffer));

  int bytes_leidos = read(serial_fd, buffer, sizeof(buffer) - 1);

  if (bytes_leidos > 0) {
    return std::string(buffer);
  }
  return "";
}
