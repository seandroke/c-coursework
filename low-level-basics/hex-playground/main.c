#include <stdio.h>
#include <stdint.h>
#include<stdlib.h>

typedef uint64_t weatherlog_t;

unsigned int add(unsigned int, unsigned int);
unsigned int sub(unsigned int, unsigned int);
unsigned int mul(unsigned int, unsigned int);

void print_half_nybbles(unsigned int);
unsigned int reverse_half_nybbles(unsigned int);

int has_odd(unsigned int);
unsigned int make_odd(unsigned int);

int is_negative(int);

weatherlog_t pack_log_entry(unsigned int, unsigned int, unsigned int,
                            unsigned int,
                            int, int,
                            unsigned int, unsigned int);

unsigned int get_year(weatherlog_t entry);
unsigned int get_month(weatherlog_t entry);
unsigned int get_day(weatherlog_t entry);
unsigned int get_zip(weatherlog_t entry);
unsigned int get_high(weatherlog_t entry);
unsigned int get_low(weatherlog_t entry);
unsigned int get_precip(weatherlog_t entry);
unsigned int get_wind(weatherlog_t entry);

int main(int argc, char **argv) {
    unsigned int i, j;
    int x, y;
    unsigned int year, month, day,
    zip, high_temp, low_temp, precip, avg_wind_speed;
    weatherlog_t log_entry;
    
    printf("Enter an integer: ");
    scanf("%u", &i);
    printf("Enter another integer: ");
    scanf("%u", &j);
    printf("One more integer, please: ");
    
    scanf("%d", &x);
    
    printf("Please enter a positive integer: ");
    
    scanf("%d", &y);
    
    printf("i + j = %u\n", add(i,j));
    
    printf("i - j = %u\n", sub(i,j));
    
    printf("i * j = %u\n", mul(i,j));
    
    if (is_negative(x))
        
        printf("%d is negative\n", x);
    
    else
        
        printf("%d is non-negative\n", x);
    
    if (has_odd(y)) {
        
        printf("%x has an odd number of bits in its binary representation\n", y);
        
    }
    
    else {
        
        printf("%x has an even number of bits in its binary representation\n", y);
        
        printf("but %x has an odd number of bits in its binary representation\n", make_odd(y));
        
    }
    
    printf("The half-nybbles of %d (in hex 0x%x) are:", x, x);
    
    print_half_nybbles(x);
    
    
    
    printf("%x with reversed half-nybbles is %x\n", x, reverse_half_nybbles(x));
    
    printf("Enter a year: ");
    
    scanf("%u", &year);
    
    printf("Enter a month as an integer (1-12): ");
    
    scanf("%u", &month);
    
    printf("Enter a day as an integer (1-31): ");
    
    scanf("%u", &day);
    
    printf("Enter a zip code as an integer (0-99999): ");
    
    scanf("%u", &zip);
    
    printf("Enter a temperature as an integer: ");
    
    scanf("%u", &high_temp);
    
    printf("Enter another temperature as an integer: ");
    
    scanf("%u", &low_temp);
    
    printf("Enter rainfall amount as an integer (mm): ");
    
    scanf("%u", &precip);
    
    printf("Enter a as an integer (km/hr): ");
    
    scanf("%u", &avg_wind_speed);
    
    log_entry=pack_log_entry(year, month, day, zip, high_temp, low_temp,
                             
                             precip, avg_wind_speed);
    
    printf("You entered: %u/%u/%u for zip %5d: high %d F, low %d F, precip %d mm, wind speed %d km/hr\n",
           
           get_day(log_entry), get_month(log_entry), get_year(log_entry),
           
           get_zip(log_entry), get_high(log_entry), get_low(log_entry),
           
           get_precip(log_entry), get_wind(log_entry));
    
    system("pause");
    
    return 0;
    
}

unsigned int add(unsigned int i, unsigned int j) {
    
    unsigned int t, r;
    
    t = i ^ j;
    
    while((r = i & j) != 0) {
        
        i = t;
        
        j = r << 1;
        
        t = i ^ j;
        
    }
    
    return t;
    
}

unsigned int sub(unsigned int i, unsigned int j) {
    
    j = add(~j,1);
    
    return add(i,j);
    
}

unsigned int mul(unsigned int i, unsigned int j) {
    
    unsigned int k, product = 0;
    
    for(k = 0; k < j; k = add(k,1)) {
        
        product = add(product,i);
        
    }
    
    return product;
    
}

void print_half_nybbles(unsigned int x) {
    
    unsigned int i = 0, t = 0x3;
    
    while(t != 0) {
        
        printf("%u", (x & t) >> i);
        
        t <<= 2;
        
        i = add(i,2);
        
    }
    
    printf("\n");
    
}

unsigned int reverse_half_nybbles(unsigned int i) {
    
    unsigned r = 0, s = 0, t = 0x3, j = 0;
    
    while(j < mul(sizeof(i),8)) {
        
        r = (i >> j) & t;
        
        s<<=2;
        
        s = add(s,r);
        
        j = add(j,2);
        
    }
    
    return s;
    
}

int is_negative(int x) {
    
    return (x & 0x80000000) != 0;
    
}

int has_odd(unsigned int x) {
    
    unsigned int count = 0, i = 0, j = 1;
    
    while(i < mul(sizeof(x),8)) {
        
        if((x & j) == j)
            
            count = add(count,1);
        
        i = add(i,1);
        
        j = mul(j,2);
        
    }
    
    return (count & 1) == 1;
    
}

unsigned int make_odd(unsigned int x) {
    
    if(!has_odd(x))
        
        x ^= 0x80000000;
    
    return x;
    
}

weatherlog_t pack_log_entry(unsigned int year, unsigned int month, unsigned int day,
                            
                            unsigned int zip, int high_temp, int low_temp,
                            
                            unsigned int precip, unsigned int avg_wind_speed) {
    
    weatherlog_t log_entry = 0;
    
    
    
    log_entry ^= sub(year,2000);
    
    log_entry <<= 4;
    
    log_entry ^= month;
    
    log_entry <<= 5;
    
    log_entry ^= day;
    
    log_entry <<= 16;
    
    log_entry ^= zip;
    
    log_entry <<= 8;
    
    log_entry ^= high_temp;
    
    log_entry <<= 8;
    
    log_entry ^= low_temp;
    
    log_entry <<= 10;
    
    log_entry ^= precip;
    
    log_entry <<= 7;
    
    log_entry ^= avg_wind_speed;
    
    
    
    return log_entry;
    
}

unsigned int get_year(weatherlog_t entry) {
    
    return entry >> 58;
    
}

unsigned int get_month(weatherlog_t entry) {
    
    return 0xf & (entry >> 54);
    
}

unsigned int get_day(weatherlog_t entry) {
    
    return 0x1f & (entry >> 49);
    
}

unsigned int get_zip(weatherlog_t entry) {
    
    return 0xffff & (entry >> 33);
    
}

unsigned int get_high(weatherlog_t entry){
    
    return 0xff & (entry >> 25);
    
}

unsigned int get_low(weatherlog_t entry) {
    
    return 0xff & (entry >> 17);
    
}

unsigned int get_precip(weatherlog_t entry) {
    
    return 0x3ff & (entry >> 7);
    
}

unsigned int get_wind(weatherlog_t entry) {
    
    return 0x7f & entry;
    
}
