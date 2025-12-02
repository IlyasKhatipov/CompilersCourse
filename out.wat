(module
  (import "env" "print_i32" (func $print_i32 (param i32)))
  (func $main (export "_start")
    (local $limit i32)
    i32.const 0
    local.set $limit
    block $while0
      loop $loop0
    i32.const 1
        i32.eqz
        br_if $while0
    i32.const 0
    i32.const 0
    i32.add
    drop
    i32.const 0
    drop
        br $loop0
      end
    end
    return
  )
)
