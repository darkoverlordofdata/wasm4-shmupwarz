typedef struct { char *str; int strlen, offset_px; } Keyboard_Row;





#define iARR_LEN(arr) ((int)(sizeof(arr) / sizeof(arr[0])))

static Keyboard_Row keyboard[] = {
    { "qwertyuiop", 10, 5 },
    { "asdfghjkl", 9, 8 },
    { "zxcvbnm", 7, 14}
  };

