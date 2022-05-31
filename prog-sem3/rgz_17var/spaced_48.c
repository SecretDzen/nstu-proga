int spaced_48(int count, char* buf) {
    int x = 0;

    for (int n = 0; buf[n] != '\0'; n++) {
        if (buf[n] > 48) {
            buf[n] = ' ';
            x++;
        }

        if (x == count) {
            break;
        }
    }

    return x;
}
