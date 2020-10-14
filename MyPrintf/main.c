#include<stdarg.h>
#include<unistd.h>
#include<stdlib.h>

int my_putchar(char c) {       //to write char by char to stdout
    write(1, &c, 1);
    return 1;
}
int my_puts(char * arr){     //write the full string to stdout
    int k;
    for(k = 0;arr[k]!='\0';k++){
        my_putchar(arr[k]);
    }
    return k;
}

char* my_itoa(unsigned long num,char array[], int base){   //itoa implementation
    int i = 30;
    int remainder;
    array[i+1] = '\0';  //null character to indicate end of the string
    if(num == 0){
        array[i--]= '0';
    } else{
        do{
            remainder = num%base;
            num/=base;
            if (remainder>9){
                array[i] = 'a'+ remainder - 10; //letter from a to f using ASCII values for base 16
            }else{
                array[i]=  remainder + '0'; //   ASCII values from 0 to 9
            }
            i--;
        }while(num!=0);
    }
    return &array[i+1];         //return adress of an element of an array
}
int my_printf(char * restrict format, ...){
    va_list list;
    char* array;
    char numarray[32];  //array to store numbers
    va_start(list,format);  //initialize argument list
    int l, count= 0;
    char ch;
    void* ptr;
    for(int i = 0; format[i]!='\0'; i++) {
        if(format[i]=='%'){     //if the char is % the next one is specifier
            if(format[i+1]=='d'){
                l = va_arg(list, int);       //va_arg to get the arguments in printf
                if(l<0){
                    l = -l;
                    count+=my_putchar('-');    //put minus sign for negative decimals
                }
                array = my_itoa(l,numarray, 10);
                count+=my_puts(array);      //count to return at the end of the printf function
                i++;
            }
            if(format[i+1]=='o'){
                array = my_itoa(va_arg(list, unsigned int),numarray, 8);
                count+=my_puts(array);
                i++;
            }
            if(format[i+1]=='u'){
                array = my_itoa(va_arg(list, unsigned int),numarray, 10);
                count+=my_puts(array);
                i++;
            }
            if(format[i+1]=='x'){
                array = my_itoa(va_arg(list, unsigned int),numarray, 16);
                count+=my_puts(array);
                i++;
            }
            if(format[i+1]=='c'){
                ch = va_arg(list, int);
                count+= my_putchar(ch);
                i++;
            }
            if(format[i+1]=='s'){
                array = va_arg(list, char*);
                if(array == NULL){
                  count+=my_puts("(null)");
                }else{
                  count+= my_puts(array);
                }
                i++;
            }
            if(format[i+1]=='p'){   //prints address of a void pointer in hexadecimal
                ptr = va_arg(list,void*);
                my_putchar('0');
                my_putchar('x');
                count+=2;
                count+= my_puts(my_itoa((unsigned long)ptr, numarray, 16));
                i++;
            }
        }else{
            count+=my_putchar(format[i]);
        }
    }
    va_end(list);
    return count;
}
int main() {
    int a = -1999;
    int c = 188;
    unsigned int b = 100;
    char ch = 'a';
    char array[] = "sksksdfsdgsk";
    char *arr123 = array;
    my_printf("1 %d  %o  noitrtfg  bla bla bla  %u   %c    %s  111 %d   %p  %x", a, c, b, ch, arr123, a, arr123, c);
    return 0;
}