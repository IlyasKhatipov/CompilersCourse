# Team VKID Interpetator 
## How to setup project

### 1. Console run (native binary)

- Clone repository 

```bash
git clone https://github.com/IlyasKhatipov/CompilersCourse
cd CompilersCourse
```

- Build and run with `g++`:

```bash
make clean
make

# run any test
./mycompiler tests/test.o
```

---

### 2. Run in browser via Emscripten + local Python server

#### 2.1. Install Emscripten (once)

В WSL / Linux:

```bash
# зависимости
sudo apt update
sudo apt install python3 git build-essential cmake

# клонируем и ставим emsdk (можно в любую папку)
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest

# подключаем в текущей сессии
source ./emsdk_env.sh
```

Проверка:

```bash
em++ --version
```

---

#### 2.2. Сборка WASM-версии интерпретатора

```bash
cd /path/to/CompilersCourse   # папка с Makefile
make clean
make wasm
```

---

#### 2.3. Запуск локального HTTP-сервера на Python

```bash
python3 -m http.server 8000
```

---

#### 2.4. Открытие страницы в браузере

Открыть:

```
http://localhost:8000/mycompiler.html
```

---

#### 2.5. Запуск тестов

Открыть DevTools → Console:

```js
Module.callMain(["tests/test.o"]);
Module.callMain(["tests/test1.o"]);
Module.callMain(["tests/test6.o"]);
```

Вывод интерпретатора появится в black-console.
