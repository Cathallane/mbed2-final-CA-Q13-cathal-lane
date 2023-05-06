/*
part of the MTU COMP71004 module
author: Krishna Panduru
the program here performs a serial passthrough operation between USB and serial (p9, p10). 
correct upto 5 errors for proper functionality. 
the 6th error is a runtime error generating the following error. correct that as well.
++ MbedOS Error Info ++ 
Error Status: 0x80010130 Code: 304 Module: 1 
Error Message: pinmap not found for peripheral 
Location: 0x4353 Error Value: 0xFFFFFFFF
*/
#include "mbed.h"


DigitalOut myled(LED1);
Serial pc(USBRX, USBTX);
Serial dev(p9, p10);

//function  to receive data from the device serial port and send it to the usb
void dev_recv(){
    while(dev.readable()){
        pc.putc(dev.getc()); //semicolon missing    
    }    
}

// Function to receive data from the usb serial port and send it to the device serisl port
void pc_recv(){
    while(pc.readable()){
        dev.putc(pc.getc());    
    }    
}

int main() {
    pc.baud(9600);
    dev.baud(115200); // incorrect vaiable name
    pc.attach(&pc_recv);
    dev.attach(&dev_recv); // // inconnect spelling of function and argument
    pc.printf("Hello!! \r\n");
    
    while(1) {
        myled = 1;
        wait(1);
        myled = 0;
        wait(1);
    }
}