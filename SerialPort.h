/**
 * @file serial_port.hpp
 * @author Abarca Robles Diego, Cruz Alvarez Fernando, Huang Rojas Armando Mao
 * Li, Oropeza Rangel Luis
 * @brief Declaraciones de la Biblioteca para configurar la comunicación serial
 * entre la tarjeta arduino y la computadora
 * @version 0.1
 * @date 2026-10-09
 *
 * @copyright Copyright (c) 2026
 *
 */

#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <string>

class SerialPort {
private:
  int serial_fd; // Descriptor del archivo del puerto serial

public:
  // Constructor: Configura y abre el puerto
  SerialPort(const char *portName);

  // Destructor: Cierra el puerto automáticamente al salir
  ~SerialPort();

  // Métodos para enviar y recibir
  bool enviarDato(char dato);
  std::string leerDato();
};

#endif
