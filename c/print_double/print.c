#include <math.h>
#include <stdio.h>

typedef union {
    long l;
    unsigned char c[4];
} long_helper;

void print_long_hex(long l)
{
    long_helper h;
    h.l = l;

    printf("%d = 0x", h.l);
    for (int i = 3; i >= 0; i--)
    {
        printf("%02X", h.c[i]);
    }
    printf("\n");
}

void print_long_binary(long l)
{
    long_helper h;
    h.l = l;
    printf("%d = b'", l);
    for (int i = 3; i >= 0; i--)
    {
        for (int j = 7; j >= 0; j--)
        {
            printf(h.c[i] & (1 << j) ? "1" : "0");
        }
        if (i > 0)
            printf(" ");
    }
    printf("'\n");
}

void print_long_test()
{
    printf("============= print_long_test ================\n");

    print_long_hex(0);
    print_long_binary(0);

    print_long_hex(1);
    print_long_binary(1);

    print_long_hex(2);
    print_long_binary(2);

    print_long_hex(4);
    print_long_binary(4);

    print_long_hex(1635780);
    print_long_binary(1635780);

}

typedef union {
    double d;
    unsigned char c[8];
    long l[2];
} double_helper;

void print_double_hex(double d)
{
    double_helper h;
    h.d = d;
    printf("%f = 0x", h.d);
    for (int i = 7; i >= 0; i--)
    {
        printf("%02X", h.c[i]);
    }
    printf("\n");
}

void print_double_binary(double d)
{
    double_helper h;
    h.d = d;
    printf("%f = b'", h.d);
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 7; j >= 0; j--)
        {
            printf(h.c[i] & (1 << j) ? "1" : "0");
        }
        if (i > 0)
            printf(" ");
    }
    printf("'\n");
}

void double_to_binary(double d, char* buf)
{
    double_helper h;
    h.d = d;
    int k = 0;
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 7; j >= 0; j--)
        {
            buf[k] = h.c[i] & (1 << j) ? '1' : '0';
            k++;
        }
    }
}

void print_double_precision(double d)
{
    printf("%.20f\n", d);
    char buf[65];
    buf[64] = 0;
    double_to_binary(d, buf);
    // bool sign = '1' == buf[0]; // is nagitive ?
    double_helper h;
    h.d = d;
    short e = ((0xFF & h.c[7]) << 8) | (0xFF & h.c[6]);
    e = (e << 1) >> 5;
    char * p = buf + 12;
    double sum = 1.0;
    for (int i = 0; i < 52; i++)
    {
        if (p[i] == '1')
        {
            sum += pow(2.0, -i - 1);
        }
        printf("%d, %.20f %d %.20f\n", i, sum, 
                e - 0x3FF, sum * pow(2.0, e - 0x3FF));
    }
}

void print_double(double d, const char* format)
{
    char buf[65];
    buf[64] = 0;
    printf("%f\n", d);
    printf(format, d);
    printf("%.20f\n", d);
    print_double_hex(d);
    print_double_binary(d);
    double_to_binary(d, buf);
    printf("%s\n", buf);
    print_double_precision(d);
    printf("\n");
}

void print_double_test()
{
    printf("============= print_double_test ================\n");
    
    const char* format1 = "%.1f\n";
    print_double(1.55, format1);
    print_double(1.65, format1);
    print_double(1.75, format1);
    print_double(1.85, format1);

    const char* format2 = "%.2f\n";
    print_double(0.155, format2);
    print_double(0.165, format2);
    print_double(0.175, format2);
    print_double(0.185, format2);
}

int main(int argc, char**argv)
{
    print_long_test();
    printf("\n");
    print_double_test();
    printf("\n");
}
