## Overview

**Fast. Safe. Zero-runtime.** <br>
A systems programming language designed for **predictable memory**, **automatic cleanup** and **compile-time guarantees**.

## Why Ferret?

Ferret is a **modern compiled language** for developers who what:

- **Performance** like C – Ferret compiles directly to optimized machine code.

- **Safety without runtime** – no garbage collector, no reference counting, no hidden overhead.

- **Predictable memory management** – variables are automatically freed at **compile time**, never at runtime.

- **Real-time feedback** – the compiler and language server **share the same analysis engine**.

Unlike other languages, Ferret doesn't bolt on a borrow checker or hide cleanup behind a runtime. Instead, **memory safety is baked into the compilation process itself**.

## Philosophy

> "You own what you create, and you always know when it's gone."

Ferret enforces **scrict scoping rules**, **deterministic cleanup**, and **safe returns** – all at **compile time**.

---

### 1.Scopes manage memory

Variables are automatically freed when they **go out of scope**. No manual `free()`. No background GC.

```ferret
int main() {
  String str = "Hello, World!";

  # 'str' is automatically freed here.
  return 0;
}
```

### 2. Returning values is always safe.

When you **return a value** from a function, Ferret ensures it remains **valid** for the caller.

#### Option A: Clone before returning

```ferret
String clone_example() {
  String data = "Hello!";

  # Caller get's an independant copy.
  return data.clone();
}
```

#### Option B: Moves by default

```ferret
String move_example() {
  String data = "Ferret!";

  # Ownership is transferred to caller,
  # 'data' in local scope is freed.
  return data;
}
```

> Node: After a move, using the old variable will fail to compile.

### 3. Real-time memory safety.

Ferret's **LSP** and **compiler** share the **same analysis engine**. If you try to use freed variables, you'll know **instantly**.

```ferret
int main() {
  String msg = "Hello!";
  println(msg);

  # LSP flags error: use-after-free, dangling pointer.
  msg;

  return 0;
}
```

- The **editor flags** it while you type.
- The **compiler refuses to build** if you ignore it.
- Result: **no runtime crashes**.

### 4. No top-level code

Everything must live **inside functions** or scopes:

```ferret
# LSP flags error: top-level side-effects are forbidden.
int PI = 3.14;
```

Correct way to do the same.

```ferret
int get_pi() {
  return 3.14;
}
```

## Memory Management

Ferret manages memory using scopes and owners, and there are **no garbage collectors** and **no runtime allocator overhead**. This means **zero runtime tracking** – binaries stay **small**, **fast**, and **predictable**.

Ferret enforces **safety at compile time**. Unlike C, Ferret **won't let you write unsafe code by accident**.

## Comparison Table

| Feature                 | Ferret | C       | Rust    | Go          |
| ----------------------- | ------ | ------- | ------- | ----------- |
| Zero-cost memory safety | ✅ Yes | ❌ No   | ✅ Yes  | ❌ No       |
| No garbage collector    | ✅ Yes | ✅ Yes  | ✅ Yes  | ❌ No       |
| Real-time diagnostics   | ✅ Yes | ❌ No   | ✅ Yes  | ❌ No       |
| Compile-time cleanup    | ✅ Yes | ❌ No   | ✅ Yes  | ❌ No       |
| Runtime overhead        | None   | Minimal | Minimal | Significant |
| Learning curve          | Easy   | Medium  | High    | Easy        |

## License

MIT © 2025 — Built for developers who care about **performance** and **safety**.
