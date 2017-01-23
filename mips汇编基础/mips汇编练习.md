# mips汇编练习

通过反汇编自己写的C语言程序，通过C语言代码和汇编的对照来快速学习一门新的汇编。下面主要通过以下几个方面的案例来进行分析。

* 参数传递
* 函数的进入和返回
* 堆栈的使用
* 函数的调用
* 条件分支

## 参数传递

这段代码定义了一个函数，接收2个int类型的参数，然后计算这两个数的和。

    #include <stdio.h>

    // Function that calls another function with some arguments.
    // This will be below the max amount of a(x) registers.
    // by b1ack0wl

    void main(){

    int a = 0;
    int b = 0x41;
    pass_args_to_me(a,b);
    }
    int pass_args_to_me(int a, int b){
    return (a+b);
    }

使用交叉编译工具，编译代码。然后使用IDA载入进行反汇编。

    /root/buildroot-2016.08.1/output/host/usr/bin/mips-buildroot-linux-gnu-gcc arguments.c -o arguments

使用IDA反汇编如下：

    # int __cdecl main(int argc, const char **argv, const char **envp)
    .globl main
    main:

    var_10= -0x10
    var_C= -0xC
    var_8= -8
    var_4= -4

    addiu   $sp, -0x28                      //分配栈空间，0x28=40个字节
    sw      $ra, 0x28+var_4($sp)        //把返回地址存入栈空间
    sw      $fp, 0x28+var_8($sp)        //把帧指针存入栈空间
    move    $fp, $sp                        //把栈指针存入帧指针
    sw      $zero, 0x28+var_10($fp)   //把栈空间的一段初始为零
    li      $v0, 0x41                          //把0x41写入$v0
    sw      $v0, 0x28+var_C($fp)       //把$v0的数据0x41存入栈空间
    lw      $a0, 0x28+var_10($fp)       //把栈空间数据(0)写入寄存器$a0
    lw      $a1, 0x28+var_C($fp)        //把栈空间数据(0x41)写入寄存器$a1
    jal     pass_args_to_me             //跳转到pass_args_to_me函数
    nop                                         //空指令，跳转之前执行
    move    $sp, $fp                       //把帧指针存入栈指针
    lw      $ra, 0x28+var_4($sp)        //从栈上恢复保存的返回地址
    lw      $fp, 0x28+var_8($sp)        //从栈上恢复保存的帧指针
    addiu   $sp, 0x28                       //恢复栈指针
    jr      $ra                                   //跳转到返回地址处继续执行
    nop                                          // 跳转之前不执行指令
    # End of function main


pass_args_to_me 函数代码如下：

    .globl pass_args_to_me
    pass_args_to_me:

    var_4= -4
    arg_0=  0
    arg_4=  4

    addiu   $sp, -8                     //分配栈空间
    sw      $fp, 8+var_4($sp)       //保存帧指针,叶子函数，所有没有保存$ra的指令
    move    $fp, $sp                    //把栈指针地址写入帧指针寄存器
    sw      $a0, 8+arg_0($fp)       //把$a0存入栈空间
    sw      $a1, 8+arg_4($fp)       //把$a1存入栈空间
    lw      $v1, 8+arg_0($fp)       //把栈空间上$a0的值存入$v1
    lw      $v0, 8+arg_4($fp)       //把栈空间上$a1的值存入$v0
    addu    $v0, $v1, $v0           // $v0加$v1的和存入$v0
    move    $sp, $fp                // 
    lw      $fp, 8+var_4($sp)       //
    addiu   $sp, 8                      //
    jr      $ra                            //
    nop
    # End of function pass_args_to_me

在mips中，前4个传入的参数通过$a0-$a3传递，当函数参数超过4个的时候，多于的参数会放入调用参数空间。x86架构下的所有参数都是通过堆栈传递的。

测试如下打码，传递10个参数时的实现。

    #include <stdio.h>

    // Function that calls another function with some arguments.
    // Passing more than 4 arguments to see what happens
    // by b1ack0wl

    void main(){

    int a = 0;
    int b = 1;
    int c = 2;
    int d = 3;
    int e = 4;
    int f = 5;
    int g = 6;
    int h = 7;
    int i = 8;
    int j = 9;

    pass_args_to_me(a,b,c,d,e,f,g,h,i,j);
    }


    int pass_args_to_me(int a, int b, int c ,int d, int e, int f, int g ,int h, int i, int j){

    return (a+b+c+d+e+f+g+h+i+j);
    }

反汇编代码如下：

    # int __cdecl main(int argc, const char **argv, const char **envp)
    .globl main
    main:

    var_50= -0x50
    var_4C= -0x4C
    var_48= -0x48
    var_44= -0x44
    var_40= -0x40
    var_3C= -0x3C
    var_30= -0x30
    var_2C= -0x2C
    var_28= -0x28
    var_24= -0x24
    var_20= -0x20
    var_1C= -0x1C
    var_18= -0x18
    var_14= -0x14
    var_10= -0x10
    var_C= -0xC
    var_8= -8
    var_4= -4

    addiu   $sp, -0x60
    sw      $ra, 0x60+var_4($sp)
    sw      $fp, 0x60+var_8($sp)
    move    $fp, $sp
    sw      $zero, 0x60+var_30($fp)
    li      $v0, 1
    sw      $v0, 0x60+var_2C($fp)
    li      $v0, 2
    sw      $v0, 0x60+var_28($fp)
    li      $v0, 3
    sw      $v0, 0x60+var_24($fp)
    li      $v0, 4
    sw      $v0, 0x60+var_20($fp)
    li      $v0, 5
    sw      $v0, 0x60+var_1C($fp)
    li      $v0, 6
    sw      $v0, 0x60+var_18($fp)
    li      $v0, 7
    sw      $v0, 0x60+var_14($fp)
    li      $v0, 8
    sw      $v0, 0x60+var_10($fp)
    li      $v0, 9
    sw      $v0, 0x60+var_C($fp)
    lw      $v0, 0x60+var_20($fp)
    sw      $v0, 0x60+var_50($sp)
    lw      $v0, 0x60+var_1C($fp)
    sw      $v0, 0x60+var_4C($sp)
    lw      $v0, 0x60+var_18($fp)
    sw      $v0, 0x60+var_48($sp)
    lw      $v0, 0x60+var_14($fp)
    sw      $v0, 0x60+var_44($sp)
    lw      $v0, 0x60+var_10($fp)
    sw      $v0, 0x60+var_40($sp)
    lw      $v0, 0x60+var_C($fp)
    sw      $v0, 0x60+var_3C($sp)
    lw      $a0, 0x60+var_30($fp)       //参数写入寄存器$a0
    lw      $a1, 0x60+var_2C($fp)       //参数写入寄存器$a1
    lw      $a2, 0x60+var_28($fp)       //参数写入寄存器$a2
    lw      $a3, 0x60+var_24($fp)       //参数写入寄存器$a3
    jal     pass_args_to_me
    nop
    move    $sp, $fp
    lw      $ra, 0x60+var_4($sp)
    lw      $fp, 0x60+var_8($sp)
    addiu   $sp, 0x60
    jr      $ra
    nop
    # End of function main


这里就不对每一句代码进行注释说明了。可以看到前4个参数分别放入$a0-$a3传递，超过4个的参数写入了栈空间。通过栈来传递参数。

## 函数的进入 调用和返回

一个需要注意的点是在mips和arm处理器中的返回地址寄存器($ra)。当一个跳转
指令(jal)在mips中执行的时候，$ra的地址是当前指令地址加8bytes。之所以这样是因为
mips处理器流水线的设计。PC+4bytes的指令会在跳转之前执行。

如下示例为在返回main函数前调用了两个函数的程序。


    #include <stdio.h>

    // Function callception!
    // This is to analyze what happens when a function calls a function.
    // by b1ack0wl

    int call_one(); // declaration
    int call_two(); // declaration

    void main(){
    int a = 0;
    int b = 1;
    call_one(a,b);
    }

    int call_one(int a, int b){
    call_two();
    return (a+b);
    }

    int call_two(){
    return 1;
    }


得到汇编代码如下：

    # int __cdecl main(int argc, const char **argv, const char **envp)
    .globl main
    main:

    var_10= -0x10
    var_C= -0xC
    var_8= -8
    var_4= -4

    addiu   $sp, -0x28
    sw      $ra, 0x28+var_4($sp)
    sw      $fp, 0x28+var_8($sp)
    move    $fp, $sp
    sw      $zero, 0x28+var_10($fp)
    li      $v0, 1
    sw      $v0, 0x28+var_C($fp)
    lw      $a0, 0x28+var_10($fp)
    lw      $a1, 0x28+var_C($fp)
    jal     call_one
    nop
    move    $sp, $fp
    lw      $ra, 0x28+var_4($sp)
    lw      $fp, 0x28+var_8($sp)
    addiu   $sp, 0x28
    jr      $ra
    nop
    # End of function main


    .globl call_one
    call_one:

    var_8= -8
    var_4= -4
    arg_0=  0
    arg_4=  4

    addiu   $sp, -0x20
    sw      $ra, 0x20+var_4($sp)
    sw      $fp, 0x20+var_8($sp)
    move    $fp, $sp
    sw      $a0, 0x20+arg_0($fp)
    sw      $a1, 0x20+arg_4($fp)
    jal     call_two
    nop
    lw      $v1, 0x20+arg_0($fp)
    lw      $v0, 0x20+arg_4($fp)
    addu    $v0, $v1, $v0
    move    $sp, $fp
    lw      $ra, 0x20+var_4($sp)
    lw      $fp, 0x20+var_8($sp)
    addiu   $sp, 0x20
    jr      $ra
    nop
    # End of function call_one

    .globl call_two
    call_two:

    var_4= -4

    addiu   $sp, -8
    sw      $fp, 8+var_4($sp)
    move    $fp, $sp
    li      $v0, 1
    move    $sp, $fp
    lw      $fp, 8+var_4($sp)
    addiu   $sp, 8
    jr      $ra
    nop
    # End of function call_two

记住 发生函数调用（JAL）会把 $PC+8 保存到$ra寄存器中，但是如果被调用函数还会调用其他函数时，$ra寄存器会被覆盖，调用者的地址会丢失。为了防止这种情况，返回地址首先被保存到函数入口的栈上.所以我们可以看到所有的函数会将返回地址保存到栈上，除了 函数call_two，因为call_two()没有调用其他函数。
因为call_two不再调用其他函数，所以称为叶子函数，否则像call_one一样，称为非叶子函数。

## 条件分支

分析一个新架构的时候，最重要的事情之一是处理器怎么处理条件分支。
下面的程序会传入一个命令行参数，类型为int， 并判断是否小于5

    #include <stdio.h>

    // What if....
    // This is to analyze how basic branching works on MIPS
    // by b1ack0wl

    int main(int argc, char **argv[]){
    if (argc < 2 ){
        printf("Usage: %s number", argv[0]);
        return 1;
    }

    int a = atoi(argv[1]); // cast argv[1] as an integer
    if (a < 5) {
        printf("%i is less than 5", a);
    }
    else{
        printf("%i is greater than 5", a);
    }
    return 0;
    }


