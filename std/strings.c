int cpy(int start, char *dst, char *msg) {
  unsigned int i = 0;
  unsigned int loc = start;

  while(msg[i] != '\0') {
    dst[loc] = msg[i];

    loc++;
    i++;
  }

  return loc;
}
