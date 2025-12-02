(module
  (import "env" "print_i32" (func $print_i32 (param i32)))
  (func $main (export "_start")
    (local $z i32)
    (local $x i32)
    i32.const 0
    local.set $x
    i32.const 3
    local.set $z
    local.get $x
    local.get $z
    i32.eq
    if
    local.get $x
    i32.const 1
    i32.add
    local.set $x
    i32.const 0
    drop
    local.get $x
    call $print_i32
    i32.const 0
    drop
    else
    local.get $z
    local.get $x
    i32.gt_s
    if
    local.get $z
    local.get $x
    i32.sub
    local.set $x
    i32.const 0
    drop
    local.get $x
    call $print_i32
    i32.const 0
    drop
    else
    i32.const 0
    local.set $x
    i32.const 0
    drop
    local.get $x
    call $print_i32
    i32.const 0
    drop
    end
    end
    return
  )
)
