(module
  (import "env" "print_i32" (func $print_i32 (param i32)))
  (func $main (export "_start")
    (local $z i32)
    i32.const 0
    local.set $z
    i32.const 0
    local.get $z
    i32.eq
    if
    i32.const 0
    i32.const 0
    i32.add
    drop
    i32.const 0
    drop
    else
    local.get $z
    i32.const 0
    i32.gt_s
    if
    local.get $z
    i32.const 0
    i32.sub
    drop
    i32.const 0
    drop
    else
    i32.const 0
    drop
    i32.const 0
    drop
    end
    end
    return
  )
)
