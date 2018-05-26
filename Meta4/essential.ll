; ModuleID = 'tests/input/essential.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@b = common global i8 0, align 1
@d = common global i16 0, align 2
@a = common global i32 0, align 4
@c = common global double 0.000000e+00, align 8

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
  ret i32 0
}

; Function Attrs: nounwind uwtable
define i32 @teste(i32 %e, i8 signext %f, i16 signext %g) #0 {
  %1 = alloca i32, align 4
  %2 = alloca i8, align 1
  %3 = alloca i16, align 2
  %h = alloca i32, align 4
  %x = alloca double, align 8
  %as = alloca i16, align 2
  %z = alloca i8, align 1
  %y = alloca i32, align 4
  store i32 %e, i32* %1, align 4
  store i8 %f, i8* %2, align 1
  store i16 %g, i16* %3, align 2
  store i32 62, i32* %h, align 4
  store double 5.500000e+00, double* %x, align 8
  store i16 1, i16* %as, align 2
  store i8 97, i8* %z, align 1
  %4 = load i32, i32* %h, align 4
  %5 = call i32 (i32, ...) bitcast (i32 (...)* @putchar to i32 (i32, ...)*)(i32 %4)
  store i32 6, i32* %y, align 4
  ret i32 5
}

declare i32 @putchar(...) #1

; Function Attrs: nounwind uwtable
define void @teste3(i32 %a) #0 {
  %1 = alloca i32, align 4
  store i32 %a, i32* %1, align 4
  %2 = load i32, i32* %1, align 4
  %3 = load i8, i8* @b, align 1
  %4 = load i16, i16* @d, align 2
  %5 = call i32 @teste(i32 %2, i8 signext %3, i16 signext %4)
  ret void
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.0-2ubuntu4 (tags/RELEASE_380/final)"}
