(module
  (import "env" "print_i32" (func $print_i32 (param i32)))
  (func $main (export "_start")
    (local $limit i32)
    (local $i i32)
    i32.const 0
    local.set $i
    i32.const 5
    local.set $limit
    block $while0
      loop $loop0
    local.get $i
    local.get $limit
    i32.lt_s
        i32.eqz
        br_if $while0
    local.get $i
    i32.const 1
    i32.add
    local.set $i
    i32.const 0
    drop
    local.get $i
    call $print_i32
    i32.const 0
    drop
        br $loop0
      end
    end
    return
  )
)
