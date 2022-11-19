const char static Days[] PROGMEM = {
  "Senin\0\0"
  "Selasa\0"
  "Rabu\0\0\0"
  "Kamis\0\0"
  "Jum'at\0"
  "Sabtu\0\0"
  "Ahad\0\0\0"
};

char* Ndays(int num) {
  static char str[7];
  int strLen = (num - 1) * 7;

  memccpy_P(str, Days + strLen, 0, 7);
  return str;
}

