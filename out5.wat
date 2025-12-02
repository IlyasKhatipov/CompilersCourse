(module
  (import "env" "print_i32" (func $print_i32 (param i32)))
  (func $main (export "_start")
    (local $d i32)
    i32.const 0
    local.set $d
    i32.const 0
    call $print_i32
    i32.const 0
    drop
    i32.const 0
    call $print_i32
    i32.const 0
    drop
  )
)
