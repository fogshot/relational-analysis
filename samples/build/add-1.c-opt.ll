; ModuleID = 'build/add-1.c-opt.bc'
source_filename = "add-1.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.14.0"

; Function Attrs: noinline nounwind ssp uwtable
define i32 @test() #0 {
entry:
  %inc = add nsw i32 1, 1
  %inc1 = add nsw i32 2, 1
  %add = add nsw i32 undef, 1
  %cmp = icmp eq i32 %add, %inc
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  %add2 = add nsw i32 %add, 1
  br label %if.end

if.end:                                           ; preds = %if.then, %entry
  %a.0 = phi i32 [ %add2, %if.then ], [ %inc, %entry ]
  %add3 = add nsw i32 %a.0, %inc1
  ret i32 %add3
}

attributes #0 = { noinline nounwind ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1}
!llvm.ident = !{!2}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 7, !"PIC Level", i32 2}
!2 = !{!"clang version 7.0.1 (https://github.com/llvm-mirror/clang.git 65f84326edb6105fb0263f0b023719b491f8cf1a) (https://github.com/llvm-mirror/llvm.git d0abf8be7d16d63c025fb9709404ee865d2acc1a)"}
