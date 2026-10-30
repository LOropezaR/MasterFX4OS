/**
 * @file serial.cpp
 * @author Diego Abarca Robles (dabarcar2200@alumno.ipn.mx)
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
#include <termios.h>
#include <unistd.h>
/**
 * ADVERTENCIA PINGÜINITOS: este programa sólo funciona en sistemas linux.
 * Para windows se utilizan otras librerías pero los principios son los mismos
 *
 **/
int main() {
  int serialPort =
      open("/dev/ttyACM0",
           O_RDWR); // cambiar esta cosa por el puerto q estemos trabajando

  if (serialPort < 0) {
    std::cerr << "Error al abrir el puerto serial" << std::endl;
    return 1;
  }

  struct termios tty; // Configuración de parámetros.
  tcgetattr(serialPort, &tty);
  cfsetospeed(&tty, B9600);
  cfsetispeed(&tty, B9600);

  tty.c_cflag &= ~PARENB; // sin bit de paridad
  tty.c_cflag &= ~CSTOPB; // 1 bit de parada
  tty.c_cflag |= CS8;     // 8 bits de lectura de datos

  tcsetattr(serialPort, TCSANOW, &tty);

  char buffer[256];
  while (true) {
    /**
     * Aquí iría todo lo del programa para cambiar los bancos
     **/
  }

  close(serialPort);
  return 0;
}
