declare i32 @putchar(i32)
declare i32 @getchar()

@a = common global i32 0

@b = common global i8 0

@c = common global double 0.000000e+00

@d = common global i16 0

define i32 @main() {
%main.h = alloca i32
store i32 42, i32* %main.h
%main.x = alloca double
store double 5.5, double* %main.x
%main.as = alloca i16
store i16 1, i16* %main.as
%main.z = alloca i8
store i8 97, i8* %main.z
%1 = load i32, i32* %main.h
%2 = call i32 @putchar(i32 %1)
%3 = load i8, i8* %main.z
%4 = call i32 @putchar(i8 %3)
%main.y = alloca i32
store i32 6, i32* %main.y
%5 = load i32, i32* %main.h
ret i32 %5
}

