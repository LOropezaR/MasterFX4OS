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

SerialPort::SerialPort(const char *portName) {
  serial_fd = open(portName, O_RDWR | O_NOCTTY);

  if (serial_fd < 0) {
    std::cerr << "Error abriendo el puerto " << portName << std::endl;
    return;
  }

  struct termios tty;
  tcgetattr(serial_fd, &tty);

  tty.c_cflag &= ~PARENB;
  tty.c_cflag &= ~CSTOPB;
  tty.c_cflag &= ~CSIZE;
  tty.c_cflag |= CS8;
  tty.c_cflag &= ~CRTSCTS;
  tty.c_cflag |= CREAD | CLOCAL;

  tty.c_lflag &= ~ICANON;
  tty.c_lflag &= ~ECHO;

  tty.c_cc[VMIN] = 0;
  tty.c_cc[VTIME] = 5;

  cfsetispeed(&tty, B9600);
  cfsetospeed(&tty, B9600);
  tcsetattr(serial_fd, TCSANOW, &tty);

  sleep(2); // Esperar a que el Arduino se reinicie
}

SerialPort::~SerialPort() {
  if (serial_fd >= 0) {
    close(serial_fd);
  }
}

bool SerialPort::enviarDato(char dato) {
  if (serial_fd < 0)
    return false;
  return write(serial_fd, &dato, 1) > 0;
}

std::string SerialPort::leerDato() {
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
