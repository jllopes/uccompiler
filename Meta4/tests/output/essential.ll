@a = global i32 -1, align 4
define i32 @main() {
  %1 = load i32, i32* @a, align 4
  %2 = call i32 @putchar(i32 %1)
  %3 = call i32 @getchar()
  ret i32 0
}
declare i32 @putchar(i32)
declare i32 @getchar()